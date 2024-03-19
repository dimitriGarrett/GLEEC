#pragma once

#include "Texture.h"
#include <unordered_map>

namespace GLEEC::Graphics
{
    struct TextureManager
    {
        static Texture& findTexture(std::string_view filepath)
        {
            if (textures.contains(key(filepath)))
            {
                return textures.at(key(filepath));
            }

            return createTexture(filepath);
        }

        static void destroyTextures()
        {
            for (auto& [_, texture] : textures)
            {
                destroyTexture(texture);
            }
        }

        GLEEC_API static std::unordered_map<size_t, Texture> textures;

    private:
        // load from file
        GLEEC_API static Texture loadTexture(std::string_view filepath, unsigned char** data);

        // create along with vk stuffs
        GLEEC_API static Texture& createTexture(std::string_view filepath);
        GLEEC_API static void destroyTexture(Texture& texture);

        static size_t key(std::string_view filepath)
        {
            return std::hash<std::string_view>{}(filepath);
        }
    };
}
