#pragma once

#include "Image.h"

namespace GLEEC::Internal::Graphics::vk
{
    inline VkImageMemoryBarrier2 imageMemoryBarrier(
        VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout,
        VkPipelineStageFlags2 srcStageMask, VkAccessFlags2 srcAccessMask,
        VkPipelineStageFlags2 dstStageMask, VkAccessFlags2 dstAccessMask, VkImageSubresourceRange subresourceRange)
    {
        return {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
            .pNext = nullptr,

            .srcStageMask = srcStageMask,
            .srcAccessMask = srcAccessMask,

            .dstStageMask = dstStageMask,
            .dstAccessMask = dstAccessMask,

            .oldLayout = oldLayout,
            .newLayout = newLayout,

            .srcQueueFamilyIndex = static_cast<uint32_t>(-1),
            .dstQueueFamilyIndex = static_cast<uint32_t>(-1),

            .image = image,
            .subresourceRange = subresourceRange,
        };
    }

    inline VkImageMemoryBarrier2 colorImageMemoryBarrier(
        VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout,
        VkPipelineStageFlags2 srcStageMask, VkAccessFlags2 srcAccessMask,
        VkPipelineStageFlags2 dstStageMask, VkAccessFlags2 dstAccessMask)
    {
        return imageMemoryBarrier(image, oldLayout, newLayout,
            srcStageMask, srcAccessMask, dstStageMask, dstAccessMask,
            { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });
    }

    inline VkImageMemoryBarrier2 depthImageMemoryBarrier(
        VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout,
        VkPipelineStageFlags2 srcStageMask, VkAccessFlags2 srcAccessMask,
        VkPipelineStageFlags2 dstStageMask, VkAccessFlags2 dstAccessMask)
    {
        return imageMemoryBarrier(image, oldLayout, newLayout,
            srcStageMask, srcAccessMask, dstStageMask, dstAccessMask,
            { VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1 });
    }

    inline VkImageMemoryBarrier2 stencilImageMemoryBarrier(
        VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout,
        VkPipelineStageFlags2 srcStageMask, VkAccessFlags2 srcAccessMask,
        VkPipelineStageFlags2 dstStageMask, VkAccessFlags2 dstAccessMask)
    {
        return imageMemoryBarrier(image, oldLayout, newLayout,
            srcStageMask, srcAccessMask, dstStageMask, dstAccessMask,
            { VK_IMAGE_ASPECT_STENCIL_BIT, 0, 1, 0, 1 });
    }

    inline VkImageMemoryBarrier2 colorImageMemoryBarrierUndefinedToGeneral(VkImage image)
    {
        return colorImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL,
            VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT, 0,
            VK_PIPELINE_STAGE_2_TRANSFER_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT);
    }

    inline VkImageMemoryBarrier2 depthImageMemoryBarrierUndefinedToGeneral(VkImage image)
    {
        return depthImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL,
            VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT, 0,
            VK_PIPELINE_STAGE_2_TRANSFER_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT);
    }

    inline VkImageMemoryBarrier2 stencilImageMemoryBarrierUndefinedToGeneral(VkImage image)
    {
        return stencilImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL,
            VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT, 0,
            VK_PIPELINE_STAGE_2_TRANSFER_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT);
    }

    inline VkImageMemoryBarrier2 colorImageMemoryBarrierUndefinedToColorAttachment(VkImage image)
    {
        return colorImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
            VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT, 0,
            VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT, VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT);
    }
/*
    inline VkImageMemoryBarrier2 depthImageMemoryBarrierUndefinedToColorAttachment(VkImage image)
    {
        return depthImageMemoryBarrier(image,
                VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT, 0,
                VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT, VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT);
    }

    inline VkImageMemoryBarrier2 stencilImageMemoryBarrierUndefinedToColorAttachment(VkImage image)
    {
        return stencilImageMemoryBarrier(image,
                VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT, 0,
                VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT, VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT);
    } */

    inline VkImageMemoryBarrier2 colorImageMemoryBarrierUndefinedToTransferDst(VkImage image)
    {
        return colorImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_PIPELINE_STAGE_2_CLEAR_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BLIT_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT);
    }

    inline VkImageMemoryBarrier2 depthImageMemoryBarrierUndefinedToTransferDst(VkImage image)
    {
        return depthImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_PIPELINE_STAGE_2_CLEAR_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BLIT_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT);
    }

    inline VkImageMemoryBarrier2 stencilImageMemoryBarrierUndefinedToTransferDst(VkImage image)
    {
        return stencilImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_PIPELINE_STAGE_2_CLEAR_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BLIT_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT);
    }

    inline VkImageMemoryBarrier2 colorImageMemoryBarrierGeneralToTransferSrc(VkImage image)
    {
        return colorImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            VK_PIPELINE_STAGE_2_CLEAR_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BLIT_BIT, VK_ACCESS_2_TRANSFER_READ_BIT);
    }

    inline VkImageMemoryBarrier2 depthImageMemoryBarrierGeneralToTransferSrc(VkImage image)
    {
        return depthImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            VK_PIPELINE_STAGE_2_CLEAR_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BLIT_BIT, VK_ACCESS_2_TRANSFER_READ_BIT);
    }

    inline VkImageMemoryBarrier2 stencilImageMemoryBarrierGeneralToTransferSrc(VkImage image)
    {
        return stencilImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            VK_PIPELINE_STAGE_2_CLEAR_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BLIT_BIT, VK_ACCESS_2_TRANSFER_READ_BIT);
    }

    inline VkImageMemoryBarrier2 colorImageMemoryBarrierColorAttachmentToTransferSrc(VkImage image)
    {
        return colorImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT, VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT, 0);
    }
/*
    inline VkImageMemoryBarrier2 depthImageMemoryBarrierColorAttachmentToTransferSrc(VkImage image)
    {
        return depthImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT, VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT, 0);
    }

    inline VkImageMemoryBarrier2 stencilImageMemoryBarrierColorAttachmentToTransferSrc(VkImage image)
    {
        return stencilImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT, VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT, 0);
    } */

    inline VkImageMemoryBarrier2 colorImageMemoryBarrierGeneralToPresentSrc(VkImage image)
    {
        return colorImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_PIPELINE_STAGE_2_TRANSFER_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT, 0);
    }

    inline VkImageMemoryBarrier2 depthImageMemoryBarrierGeneralToPresentSrc(VkImage image)
    {
        return depthImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_PIPELINE_STAGE_2_TRANSFER_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT, 0);
    }

    inline VkImageMemoryBarrier2 stencilImageMemoryBarrierGeneralToPresentSrc(VkImage image)
    {
        return stencilImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_PIPELINE_STAGE_2_TRANSFER_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT, 0);
    }

    inline VkImageMemoryBarrier2 colorImageMemoryBarrierTransferDstToPresentSrc(VkImage image)
    {
        return colorImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_PIPELINE_STAGE_2_BLIT_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT, 0);
    }

    inline VkImageMemoryBarrier2 depthImageMemoryBarrierTransferDstToPresentSrc(VkImage image)
    {
        return depthImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_PIPELINE_STAGE_2_BLIT_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT, 0);
    }

    inline VkImageMemoryBarrier2 stencilImageMemoryBarrierTransferDstToPresentSrc(VkImage image)
    {
        return stencilImageMemoryBarrier(image,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_PIPELINE_STAGE_2_BLIT_BIT, VK_ACCESS_2_TRANSFER_WRITE_BIT,
            VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT, 0);
    }

    inline VkDependencyInfo dependencyInfo(const VkImageMemoryBarrier2& barrier)
    {
        VkDependencyInfo info = {
            VK_STRUCTURE_TYPE_DEPENDENCY_INFO
        };

        info.imageMemoryBarrierCount = 1;
        info.pImageMemoryBarriers = &barrier;

        return info;
    }
}
