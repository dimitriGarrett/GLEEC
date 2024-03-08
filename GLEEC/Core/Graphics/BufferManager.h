#pragma once

#include "Buffer.h"

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

        GLEEC_API static void cmdCopyBuffer(const Buffer& src, const Buffer& dst);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static void cmdCopyBuffer(
            VkCommandBuffer commandBuffer, const Buffer& src, const Buffer& dst);
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static void bindVertexBuffer(VkCommandBuffer commandBuffer,
            const Buffer& buffer, VkDeviceSize offset = 0);
#endif

    private:
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static Internal::Graphics::vk::CommandPool commandPool;

        // one time submit for command buffer copy and stuff
        GLEEC_API static Internal::Graphics::vk::CommandBuffer quickCommandBuffer();
        GLEEC_API static void stopCommandBuffer(const Internal::Graphics::vk::CommandBuffer& commandBuffer);
#endif

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
    };
}
