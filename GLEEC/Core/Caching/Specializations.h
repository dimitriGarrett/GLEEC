#pragma once

#include "Cache.h"
#include "Funcs.h"

namespace GLEEC::Caching
{
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    template <typename T>
    T createPossiblyCachedResource(
        std::string_view filepath)
    {
        return {};
    }

    template <>
    inline Internal::Graphics::vk::ShaderBinary createPossiblyCachedResource<
        Internal::Graphics::vk::ShaderBinary>(std::string_view filepath)
    {
        return createPossiblyCachedResource(SHADER, filepath,
            &loadCachedShader, &loadLoadedShader);
    }

    template <>
    inline Graphics::DescriptorSets createPossiblyCachedResource
        <Graphics::DescriptorSets>(std::string_view filepath)
    {
        return createPossiblyCachedResource(DESCRIPTOR_SET_LAYOUT, filepath,
            &loadCachedDescriptorSetBindings, &loadLoadedDescriptorSetBindings);
    }

    inline void cacheResource(std::string_view filepath,
        const Internal::Graphics::vk::ShaderBinary& cache)
    {
        Caching::cacheResource(SHADER, filepath, cache, cache.code.size(),
            &writeShader, &destroyShader);
    }

    inline void cacheResource(std::string_view filepath,
        const Graphics::DescriptorSets& bindings)
    {
        size_t size = 0;

        for (const auto& binding : bindings)
        {
            size += binding.size();
        }

        // now size is the total size in bytes of all the descriptor set layouts
        size *= sizeof(Internal::Graphics::vk::DescriptorSetBinding);

        // now add the size of the headers interleaved
        size += bindings.size() * sizeof(CachedHeader);
        
        Caching::cacheResource(DESCRIPTOR_SET_LAYOUT, filepath, bindings, size,
            &writeDescriptorSetBindings, &destroyDescriptorSetBindings);
    }
#endif
}
