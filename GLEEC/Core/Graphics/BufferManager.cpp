#include "BufferManager.h"
#include "Core/Graphics/GPUManager.h"
#include "Internal/Graphics/vk/Submit.h"

namespace GLEEC::Graphics
{
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    Internal::Graphics::vk::CommandPool BufferManager::commandPool = {};
#endif

    void BufferManager::init()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        commandPool = Internal::Graphics::vk::createCommandPool(
            GPUManager::activeGPU.device,
            GPUManager::activeGPU.graphicsQueue.index,
            VK_COMMAND_POOL_CREATE_TRANSIENT_BIT);
#endif
    }

    void BufferManager::destroy()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::destroyCommandPool(
            GPUManager::activeGPU.device, commandPool);
#endif
    }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    Internal::Graphics::vk::CommandBuffer BufferManager::quickCommandBuffer()
    {
        static const VkCommandBufferAllocateInfo allocateInfo =
            Internal::Graphics::vk::commandBufferAllocateInfo(
                commandPool);

        auto commandBuffer = Internal::Graphics::vk::allocateCommandBuffer(
            GPUManager::activeGPU.device, allocateInfo);

        Internal::Graphics::vk::beginCommandBufferOneTimeSubmit(commandBuffer);

        return commandBuffer;
    }

    void BufferManager::stopCommandBuffer(
        const Internal::Graphics::vk::CommandBuffer& commandBuffer)
    {
        Internal::Graphics::vk::endCommandBuffer(commandBuffer);

        VkSubmitInfo2 submitInfo = {
            VK_STRUCTURE_TYPE_SUBMIT_INFO_2
        };

        VkCommandBufferSubmitInfo commandBufferSubmission = {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO
        };

        commandBufferSubmission.commandBuffer = commandBuffer;
        commandBufferSubmission.deviceMask = 0;

        submitInfo.commandBufferInfoCount = 1;
        submitInfo.pCommandBufferInfos = &commandBufferSubmission;

        Internal::Graphics::vk::queueSubmit2(
            GPUManager::activeGPU.graphicsQueue,
            &submitInfo, VK_NULL_HANDLE);
        Internal::Graphics::vk::queueWaitIdle(
            GPUManager::activeGPU.graphicsQueue);

        Internal::Graphics::vk::freeCommandBuffer(
            GPUManager::activeGPU.device,
            commandPool, &commandBuffer);
    }
#endif

    void BufferManager::destroyBuffer(Buffer& buffer)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::destroyBuffer(
            GPUManager::activeGPU.allocator, buffer.buffer);
#endif
    }

    Buffer BufferManager::createStagingBuffer(size_t size)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        return { Internal::Graphics::vk::createBuffer(
            GPUManager::activeGPU.allocator,
            Internal::Graphics::vk::createBuffer(size,
                VK_BUFFER_USAGE_TRANSFER_SRC_BIT),
            VMA_MEMORY_USAGE_CPU_TO_GPU)
        };
#endif
    }

    Buffer BufferManager::createStagingBuffer(size_t size, const void* data)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Buffer buffer = createStagingBuffer(size);
        Internal::Graphics::vk::mapMemory(
            GPUManager::activeGPU.allocator,
            buffer.buffer);

        memcpy_s(buffer.buffer.map, size, data, size);

        return buffer;
#endif
    }

    Buffer BufferManager::createVertexBuffer(size_t size)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        return { Internal::Graphics::vk::createBuffer(
            GPUManager::activeGPU.allocator,
            Internal::Graphics::vk::createBuffer(size,
                VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
                VK_BUFFER_USAGE_TRANSFER_DST_BIT),
            VMA_MEMORY_USAGE_GPU_ONLY)
        };
#endif
    }

    Buffer BufferManager::createVertexBuffer(size_t size, const void* data)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Buffer buffer = createVertexBuffer(size);

        Buffer stagingBuffer = createStagingBuffer(size, data);
        cmdCopyBuffer(stagingBuffer, buffer);
        destroyStagingBuffer(stagingBuffer);

        return buffer;
#endif
    }

    Buffer BufferManager::createIndexBuffer(size_t size, uint32_t indexType)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        return { Internal::Graphics::vk::createBuffer(
            GPUManager::activeGPU.allocator,
            Internal::Graphics::vk::createBuffer(size,
                VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
                VK_BUFFER_USAGE_TRANSFER_DST_BIT),
            VMA_MEMORY_USAGE_GPU_ONLY),
            indexType
        };
#endif
    }

    Buffer BufferManager::createIndexBuffer(size_t size, const void* data,
        uint32_t indexType)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Buffer buffer = createIndexBuffer(size, indexType);

        Buffer stagingBuffer = createStagingBuffer(size, data);
        cmdCopyBuffer(stagingBuffer, buffer);
        destroyStagingBuffer(stagingBuffer);

        return buffer;
#endif
    }

    Buffer BufferManager::createUniformBuffer(size_t size)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Buffer buffer = { Internal::Graphics::vk::createBuffer(
            GPUManager::activeGPU.allocator,
            Internal::Graphics::vk::createBuffer(size,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
                VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
            VMA_MEMORY_USAGE_CPU_TO_GPU) };
        Internal::Graphics::vk::mapMemory(
            GPUManager::activeGPU.allocator,
            buffer.buffer);

        return buffer;
#endif
    }

    Buffer BufferManager::createUniformBuffer(size_t size, const void* data)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Buffer buffer = createUniformBuffer(size);

        memcpy_s(buffer.buffer.map, size, data, size);

        return buffer;
#endif
    }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    void BufferManager::cmdCopyBuffer(VkCommandBuffer commandBuffer,
        const Buffer& src, const Buffer& dst)
    {
        VkBufferCopy copy = {};
        copy.size = dst.buffer.size;

        vkCmdCopyBuffer(commandBuffer, src.buffer, dst.buffer, 1, &copy);
    }
#endif

    void BufferManager::cmdCopyBuffer(const Buffer& src, const Buffer& dst)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        VkCommandBuffer commandBuffer = quickCommandBuffer();

        cmdCopyBuffer(commandBuffer, src, dst);

        stopCommandBuffer(commandBuffer);
#endif
    }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    void BufferManager::cmdCopyBufferToColorImage(VkCommandBuffer commandBuffer,
        const Buffer& src, const Texture& dst)
    {
        // this will clear the contents of the texture
        Internal::Graphics::vk::transitionColorImageUndefinedToTransferDst(commandBuffer, dst.image);

        VkBufferImageCopy copy = {};
        copy.imageExtent = dst.image.extent;

        copy.imageSubresource.mipLevel = 0;
        copy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        copy.imageSubresource.baseArrayLayer = 0;
        copy.imageSubresource.layerCount = 1;

        vkCmdCopyBufferToImage(commandBuffer, src.buffer, dst.image,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy);

        Internal::Graphics::vk::transitionColorImageTransferDstToShaderReadOnly(commandBuffer, dst.image);
    }

    void BufferManager::cmdCopyBufferToDepthImage(VkCommandBuffer commandBuffer,
        const Buffer& src, const Texture& dst)
    {
        // this will clear the contents of the texture
        Internal::Graphics::vk::transitionDepthImageUndefinedToTransferDst(commandBuffer, dst.image);

        VkBufferImageCopy copy = {};
        copy.imageExtent = dst.image.extent;

        copy.imageSubresource.mipLevel = 0;
        copy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        copy.imageSubresource.baseArrayLayer = 0;
        copy.imageSubresource.layerCount = 1;

        vkCmdCopyBufferToImage(commandBuffer, src.buffer, dst.image,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy);
    }

    void BufferManager::cmdCopyBufferToStencilImage(VkCommandBuffer commandBuffer,
        const Buffer& src, const Texture& dst)
    {
        // this will clear the contents of the texture
        Internal::Graphics::vk::transitionStencilImageUndefinedToTransferDst(commandBuffer, dst.image);

        VkBufferImageCopy copy = {};
        copy.imageExtent = dst.image.extent;

        copy.imageSubresource.mipLevel = 0;
        copy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_STENCIL_BIT;
        copy.imageSubresource.baseArrayLayer = 0;
        copy.imageSubresource.layerCount = 1;

        vkCmdCopyBufferToImage(commandBuffer, src.buffer, dst.image,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy);
    }
#endif

    void BufferManager::cmdCopyBufferToColorImage(const Buffer& src,
        const Texture& dst)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        VkCommandBuffer commandBuffer = quickCommandBuffer();

        cmdCopyBufferToColorImage(commandBuffer, src, dst);

        stopCommandBuffer(commandBuffer);
#endif
    }

    void BufferManager::cmdCopyBufferToDepthImage(const Buffer& src,
        const Texture& dst)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        VkCommandBuffer commandBuffer = quickCommandBuffer();

        cmdCopyBufferToDepthImage(commandBuffer, src, dst);

        stopCommandBuffer(commandBuffer);
#endif
    }

    void BufferManager::cmdCopyBufferToStencilImage(const Buffer& src,
        const Texture& dst)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        VkCommandBuffer commandBuffer = quickCommandBuffer();

        cmdCopyBufferToStencilImage(commandBuffer, src, dst);

        stopCommandBuffer(commandBuffer);
#endif
    }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    void BufferManager::bindVertexBuffer(VkCommandBuffer commandBuffer,
        const Buffer& buffer, VkDeviceSize offset)
    {
        vkCmdBindVertexBuffers(commandBuffer, 0, 1,
            &buffer.buffer.buffer, &offset);
    }
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    void BufferManager::bindIndexBuffer(VkCommandBuffer commandBuffer,
        const Buffer& buffer, VkDeviceSize offset)
    {
        vkCmdBindIndexBuffer(commandBuffer, buffer.buffer, offset,
            static_cast<VkIndexType>(buffer.indexType));
    }
#endif
}
