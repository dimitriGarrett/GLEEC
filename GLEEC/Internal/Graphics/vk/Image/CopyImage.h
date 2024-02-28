#pragma once

#include "Image.h"

namespace GLEEC::Internal::Graphics::vk
{
    inline VkImageBlit2 imageBlit(VkExtent3D srcExtent, VkExtent3D dstExtent,
        VkImageSubresource srcSubresource, VkImageSubresource dstSubresource)
    {
        VkImageBlit2 blit = {
            VK_STRUCTURE_TYPE_IMAGE_BLIT_2
        };

        blit.srcSubresource.aspectMask = srcSubresource.aspectMask;
        blit.srcSubresource.baseArrayLayer = srcSubresource.arrayLayer;
        blit.srcSubresource.mipLevel = srcSubresource.mipLevel;
        blit.srcSubresource.layerCount = 1;

        blit.dstSubresource.aspectMask = dstSubresource.aspectMask;
        blit.dstSubresource.baseArrayLayer = dstSubresource.arrayLayer;
        blit.dstSubresource.mipLevel = dstSubresource.mipLevel;
        blit.dstSubresource.layerCount = 1;

        blit.srcOffsets[1].x = srcExtent.width;
        blit.srcOffsets[1].y = srcExtent.height;
        blit.srcOffsets[1].z = srcExtent.depth;

        blit.dstOffsets[1].x = dstExtent.width;
        blit.dstOffsets[1].y = dstExtent.height;
        blit.dstOffsets[1].z = dstExtent.depth;

        return blit;
    }

    inline VkImageBlit2 imageBlit(VkExtent3D srcExtent, VkExtent3D dstExtent,
        VkImageAspectFlags srcAspect, VkImageAspectFlags dstAspect)
    {
        return imageBlit(srcExtent, dstExtent,
            VkImageSubresource{ srcAspect, 0, 0 },
            VkImageSubresource{ dstAspect, 0, 0 });
    }

    inline VkImageBlit2 colorImageBlit(VkExtent3D srcExtent, VkExtent3D dstExtent)
    {
        return imageBlit(srcExtent, dstExtent,
            VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_ASPECT_COLOR_BIT);
    }

    inline VkImageBlit2 depthImageBlit(VkExtent3D srcExtent, VkExtent3D dstExtent)
    {
        return imageBlit(srcExtent, dstExtent,
            VK_IMAGE_ASPECT_DEPTH_BIT, VK_IMAGE_ASPECT_DEPTH_BIT);
    }

    inline VkImageBlit2 stencilImageBlit(VkExtent3D srcExtent, VkExtent3D dstExtent)
    {
        return imageBlit(srcExtent, dstExtent,
            VK_IMAGE_ASPECT_STENCIL_BIT, VK_IMAGE_ASPECT_STENCIL_BIT);
    }

    inline VkBlitImageInfo2 imageBlitInfo(const VkImageBlit2& blit,
        VkImage src, VkImage dst)
    {
        VkBlitImageInfo2 info = {
            VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2
        };

        info.srcImage = src;
        info.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;

        info.dstImage = dst;
        info.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

        info.regionCount = 1;
        info.pRegions = &blit;

        info.filter = VK_FILTER_LINEAR;

        return info;
    }

    inline void blitImage(VkCommandBuffer commandBuffer, const VkBlitImageInfo2& info)
    {
        vkCmdBlitImage2(commandBuffer, &info);
    }
}
