#pragma once

#include "MemoryBarrier.h"
#include "Internal/Graphics/vk/PipelineBarrier.h"

namespace GLEEC::Internal::Graphics::vk
{
    inline void transitionColorImageUndefinedToGeneral(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierUndefinedToGeneral(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionColorImageUndefinedToColorAttachment(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierUndefinedToColorAttachment(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionColorImageUndefinedToTransferDst(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierUndefinedToTransferDst(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionColorImageGeneralToTransferSrc(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierGeneralToTransferSrc(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionColorImageGeneralToPresentSrc(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierGeneralToPresentSrc(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionColorImageColorAttachmentToTransferSrc(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierColorAttachmentToTransferSrc(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionColorImageTransferDstToPresentSrc(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierTransferDstToPresentSrc(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionColorImageTransferDstToShaderReadOnly(
        VkCommandBuffer commandBuffer, VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierTransferDstToShaderReadOnly(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionDepthImageUndefinedToGeneral(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierUndefinedToGeneral(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionDepthImageUndefinedToTransferDst(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierUndefinedToTransferDst(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionDepthImageGeneralToTransferSrc(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierGeneralToTransferSrc(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionDepthImageGeneralToPresentSrc(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierGeneralToPresentSrc(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionDepthImageTransferDstToPresentSrc(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierTransferDstToPresentSrc(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionStencilImageUndefinedToGeneral(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierUndefinedToGeneral(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionStencilImageUndefinedToTransferDst(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierUndefinedToTransferDst(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionStencilImageGeneralToTransferSrc(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierGeneralToTransferSrc(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionStencilImageGeneralToPresentSrc(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierGeneralToPresentSrc(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }

    inline void transitionStencilImageTransferDstToPresentSrc(VkCommandBuffer commandBuffer,
        VkImage image)
    {
        VkImageMemoryBarrier2 barrier =
            colorImageMemoryBarrierTransferDstToPresentSrc(image);

        VkDependencyInfo info = dependencyInfo(barrier);

        cmdPipelineBarrier2(commandBuffer, info);
    }
}
