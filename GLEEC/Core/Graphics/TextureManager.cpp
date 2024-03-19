#include "TextureManager.h"

#include "Core/Graphics/BufferManager.h"
#include "Core/Graphics/GPUManager.h"

#include "STB/stb_image.h"

namespace GLEEC::Graphics
{
    std::unordered_map<size_t, Texture> TextureManager::textures = {};

    Texture TextureManager::loadTexture(std::string_view filepath, unsigned char** data)
    {
        Texture temp = {};

        int width, height, channels;

        // always includes alpha, makes later calculations easier
        (*data) = stbi_load(filepath.data(), &width, &height, &channels,
            4);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        temp.image.extent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height),
            1
        };
#endif

        return temp;
    }

    Texture& TextureManager::createTexture(std::string_view filepath)
    {
        unsigned char* data = nullptr;

        Texture& texture = (textures[key(filepath)] =
            loadTexture(filepath, &data));

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        texture.image = Internal::Graphics::vk::createImage(
            GPUManager::activeGPU.allocator,
            Internal::Graphics::vk::createImage(
                VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_USAGE_TRANSFER_DST_BIT |
                    VK_IMAGE_USAGE_SAMPLED_BIT,
                VK_IMAGE_TYPE_2D, texture.image.format, texture.image.extent));

        Buffer stagingBuffer = BufferManager::createStagingBuffer(
            texture.image.extent.width * texture.image.extent.height,
            data);

        BufferManager::cmdCopyBufferToColorImage(stagingBuffer, texture);

        BufferManager::destroyStagingBuffer(stagingBuffer);
#endif

        stbi_image_free(data);

        return texture;
    }

    void TextureManager::destroyTexture(Texture& texture)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::destroyImage(
            GPUManager::activeGPU.device, texture.image);
#endif
    }
}
