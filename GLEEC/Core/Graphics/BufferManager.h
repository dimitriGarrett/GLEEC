#pragma once

#include "Buffer.h"
#include "Texture.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/CommandPool.h"
#endif

namespace GLEEC::Graphics
{
    struct BufferManager
    {
        GLEEC_API static void init();
        GLEEC_API static void destroy();

        GLEEC_API static void destroyBuffer(Buffer& buffer);

        GLEEC_API static Buffer createVertexBuffer(size_t size);
        GLEEC_API static Buffer createVertexBuffer(size_t size, const void* data);

        template <typename T>
        static Buffer createVertexBuffer(const std::vector<T>& data)
        {
            return createVertexBuffer(data.size() * sizeof(T), data.data());
        }

        static void destroyVertexBuffer(Buffer& buffer)
        {
            destroyBuffer(buffer);
        }

        GLEEC_API static Buffer createIndexBuffer(size_t size,
            uint32_t indexType);
        GLEEC_API static Buffer createIndexBuffer(size_t size, const void* data,
            uint32_t indexType);

        template <typename T>
        static Buffer createIndexBuffer(const std::vector<T>& data)
        {
            uint32_t indexType = -1;
            
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            if constexpr (sizeof(T) == sizeof(uint16_t))
                indexType = VK_INDEX_TYPE_UINT16;
            else if constexpr (sizeof(T) == sizeof(uint32_t))
                indexType = VK_INDEX_TYPE_UINT32;
            else
            {
                LOG_WARNING("Unknown index type with size: {}, using UINT16!",
                    sizeof(T));

                indexType = VK_INDEX_TYPE_UINT16;
            }
#endif

            return createIndexBuffer(data.size() * sizeof(T), data.data(),
                indexType);
        }

        static void destroyIndexBuffer(Buffer& buffer)
        {
            destroyBuffer(buffer);
        }

        GLEEC_API static Buffer createStagingBuffer(size_t size);
        GLEEC_API static Buffer createStagingBuffer(size_t size, const void* data);

        template <typename T>
        static Buffer createStagingBuffer(const std::vector<T>& data)
        {
            return createStagingBuffer(data.size() * sizeof(T), data.data());
        }

        static void destroyStagingBuffer(Buffer& buffer)
        {
            destroyBuffer(buffer);
        }

        GLEEC_API static Buffer createUniformBuffer(size_t size);
        GLEEC_API static Buffer createUniformBuffer(size_t size, const void* data);

        template <typename T>
        static Buffer createUniformBuffer(const std::vector<T>& data)
        {
            return createUniformBuffer(data.size() * sizeof(T), data.data());
        }

        static void destroyUniformBuffer(Buffer& buffer)
        {
            destroyBuffer(buffer);
        }

        GLEEC_API static void cmdCopyBuffer(const Buffer& src,
            const Buffer& dst);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static void cmdCopyBuffer(
            VkCommandBuffer commandBuffer, const Buffer& src,
            const Buffer& dst);
#endif

        GLEEC_API static void cmdCopyBufferToColorImage(const Buffer& src,
            const Texture& dst);

        GLEEC_API static void cmdCopyBufferToDepthImage(const Buffer& src,
            const Texture& dst);

        GLEEC_API static void cmdCopyBufferToStencilImage(const Buffer& src,
            const Texture& dst);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static void cmdCopyBufferToColorImage(
            VkCommandBuffer commandBuffer, const Buffer& src,
            const Texture& dst);

        GLEEC_API static void cmdCopyBufferToDepthImage(
            VkCommandBuffer commandBuffer, const Buffer& src,
            const Texture& dst);

        GLEEC_API static void cmdCopyBufferToStencilImage(
            VkCommandBuffer commandBuffer, const Buffer& src,
            const Texture& dst);
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static void bindVertexBuffer(VkCommandBuffer commandBuffer,
            const Buffer& buffer, VkDeviceSize offset = 0);
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static void bindIndexBuffer(VkCommandBuffer commandBuffer,
            const Buffer& buffer, VkDeviceSize offset = 0);
#endif

    private:
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static Internal::Graphics::vk::CommandPool commandPool;

        // one time submit for command buffer copy and stuff
        GLEEC_API static Internal::Graphics::vk::CommandBuffer quickCommandBuffer();
        GLEEC_API static void stopCommandBuffer(const Internal::Graphics::vk::CommandBuffer& commandBuffer);
#endif
    };
}
