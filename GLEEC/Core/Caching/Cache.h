#pragma once

#include "Config/Version.h"
#include "Core/Config/Configuration.h"

#include "ResourceType.h"

#include <fstream>
#include <filesystem>

namespace GLEEC::Caching
{
    struct CachedHeader
    {
        size_t magic = STATIC_MAGIC;
        size_t version = GLEEC_VERSION;
        size_t size = 0;

        size_t ABI = sizeof(void*);

        static constexpr size_t STATIC_MAGIC = 3175928559; // 0xDEAD_BEEF
    };

    inline std::string cacheFilepath()
    {
        return Config::Configuration::gets("cwd") + "gcache/";
    }

    // all of the complexity allows for identical names of shader files,
    // but in different directories. if only using name its impossible
#if GLEEC_WINDOWS
    inline std::string getCachedName(std::string filepath)
#else
    inline std::string getCachedName(const std::string& filepath)
#endif
    {
// why does windows have to be so difficult :(
#if GLEEC_WINDOWS
        for (char& c : filepath)
        {
            if (c == '\\') c = '/';
        }
#endif

        std::string path = filepath.substr(0, filepath.find_last_of('/'));

        // name provided, happens with descriptor set layouts
        // because they are not loaded from a file, but still
        // get saved to a file and have a name
        // is it a dirty hack? yes
        // does it work? also yes.
        if (path == filepath)
        {
            return filepath;
        }

        std::string newstr = path.substr(0, path.find_last_of('/'));

        std::string end = filepath.substr(newstr.size() + 1,
            filepath.find_last_of('.') - newstr.size() - 1);

        end[end.find('/')] = '-';

        return end;
    }

    inline std::string getCachedFilepathFromName(ResourceType resource,
        const std::string& name)
    {
        return cacheFilepath() + detail::filepathPrefix(resource)
            + std::string(name) + ".bin";
    }

    inline std::string getCachedFilepath(ResourceType resource,
        std::string_view cachedName)
    {
        return cacheFilepath() + detail::filepathPrefix(resource)
            + std::string(cachedName) + ".bin";
    }

    inline std::string getCachedFilepathFromFilepath(ResourceType resource,
        const std::string& filepath)
    {
        std::string cachedName = getCachedName(filepath);

        if (cachedName == "")
        {
            // name already instead of filepath
            return getCachedFilepath(resource, filepath);
        }

        return getCachedFilepath(resource, cachedName);
    }

    inline bool getCachedResourceExists(ResourceType resource,
        std::string_view name)
    {
        return std::filesystem::exists(getCachedFilepath(resource, name));
    }

    inline bool getCachedResourceFromFilepathExists(ResourceType resource,
        const std::string& filepath)
    {
        return getCachedResourceExists(resource, getCachedName(filepath));
    }

    template <typename T>
    using CacheCallback = T(*)(std::ifstream&, const CachedHeader&);

    template <typename T>
    using LoadCallback = T(*)(std::ifstream&, std::string_view);

    template <typename T>
    using NonFileLoadCallback = T(*)();

    template <typename T>
    using WriteCallback = void(*)(std::ofstream&, const T&);

    template <typename T>
    using DestroyCallback = void(*)(const T&);

#if GLEEC_DEBUG
    inline bool verifyHeader(const CachedHeader& header, std::string_view filepath)
#else
    inline bool verifyHeader(const CachedHeader& header)
#endif
    {
        if (header.magic != CachedHeader::STATIC_MAGIC)
        {
#if GLEEC_DEBUG
            LOG_WARNING("Size of the cached header loading: {} was 0!",
                filepath);
#endif

            return false;
        }

        if (header.ABI != sizeof(void*))
        {
#if GLEEC_DEBUG
            LOG_WARNING("The sizeof(void*) of the cache of: {}, is {}, which differs from current: {}, ignoring cache!",
                header.ABI, filepath, sizeof(void*));
#endif

            return false;
        }

        if (header.version != GLEEC_VERSION)
        {
#if GLEEC_DEBUG
            LOG_WARNING("Version of GLEEC: {} differs from cache version: {}, ignoring cache: {}",
                GLEEC_VERSION, header.version, filepath);
#endif

            return false;
        }

        if (header.size == 0)
        {
#if GLEEC_DEBUG
            LOG_WARNING("Header size was 0 for cache: {}, ignoring cache!",
                filepath);
#endif

            return false;
        }

        LOG_MESSAGE("Header was verified to be correct for cache: {}",
            filepath);

        return true;
    }

    template <typename T>
    T createCachedResource(std::string_view filepath,
        CacheCallback<T> createCached, NonFileLoadCallback<T> createLoad)
    {
        std::ifstream file(filepath.data(),
            std::ios::in | std::ios::binary);

        CachedHeader header = {};

        file.read(reinterpret_cast<char*>(&header), sizeof(header));

        if (!verifyHeader(header,
#if GLEEC_DEBUG
            filepath
#endif
        ))
        {
#if GLEEC_DEBUG
            T temp = createLoad();

            LOG_MESSAGE("Loaded resource file: {}!", filepath);

            return temp;
#else
            return createLoad();
#endif
        }

        // if cache differs from resource file, load resource file
#if GLEEC_DEBUG
        T temp = createCached(file, filepath, header);
        T loaded = createLoad();

        if (temp != loaded)
        {
            LOG_MESSAGE("Cached version of: {} differs from file, ignoring cache!",
                filepath);

            return loaded;
        }

        LOG_MESSAGE("Loaded cached version of: {}!",
            filepath);

        return temp;
#else
        return createCached(file, filepath, header);
#endif
    }

    template <typename T>
    T createCachedResource(std::string_view filepath, std::string_view cacheFilepath,
        CacheCallback<T> createCached, LoadCallback<T> createLoad)
    {
        std::ifstream file(cacheFilepath.data(),
            std::ios::in | std::ios::binary);

        CachedHeader header = {};

        file.read(reinterpret_cast<char*>(&header), sizeof(header));

        if (!verifyHeader(header,
#if GLEEC_DEBUG
            cacheFilepath
#endif
        ))
        {
#if GLEEC_DEBUG
            T temp = createLoad(file, filepath);

            LOG_MESSAGE("Loaded resource file: {}!", filepath);

            return temp;
#else
            return createLoad(file, cacheFilepath);
#endif
        }

        // if cache differs from resource file, load resource file
/* #if GLEEC_DEBUG
        T temp = createCached(file, cacheFilepath, header);
        T loaded = createLoad(file2, filepath);

        if (temp != loaded)
        {
            LOG_WARNING("Cached version of: {} differs from file, ignoring cache!",
                filepath);

            return loaded;
        }

        LOG_MESSAGE("Loaded cached version of: {}!",
            cacheFilepath);

        return temp;
#else */
        return createCached(file, header);
/* #endif */
    }

    template <typename T>
    T createPossiblyCachedResource(ResourceType resource,
        std::string_view filepath, CacheCallback<T> createCached,
        LoadCallback<T> createLoad)
    {
        std::string name = getCachedName(std::string(filepath));

        if (getCachedResourceExists(resource, name))
        {
            return createCachedResource<T>(filepath,
                getCachedFilepath(resource, name), createCached, createLoad);
        }

        std::ifstream file(filepath.data(),
            std::ios::in | std::ios::binary);

        return createLoad(file, filepath);
    }

    template <typename T>
    void writeToCache(ResourceType resource, std::string_view filepath,
        const T& object, size_t objectSize, WriteCallback<T> writeResource)
    {
        std::ofstream file(getCachedFilepathFromFilepath(resource,
            std::string(filepath)), std::ios::out | std::ios::binary);

        CachedHeader header = {};
        header.size = objectSize;

        file.write(reinterpret_cast<const char*>(&header), sizeof(header));

        writeResource(file, object);

        LOG_MESSAGE("Wrote cache file for resource: {}!", filepath);
    }

    template <typename T>
    void cacheResource(ResourceType resource,
        std::string_view filepath, const T& object, size_t objectSize,
        WriteCallback<T> writeResource, DestroyCallback<T> destroyResource)
    {
        if (objectSize != 0)
            writeToCache<T>(resource, filepath, object, objectSize, writeResource);

        destroyResource(object);
    }
}
