#pragma once

#include "Internal/Graphics/Backends/vk.h"
#include "helpers/CHECK_VK.h"

namespace GLEEC::Internal::Graphics::vk
{
    using ImageView = VkImageView;

    inline ImageView createImageView(VkDevice device, VkImage image, VkFormat format,
        VkImageViewType viewType, VkComponentMapping components,
        VkImageSubresourceRange subresourceRange)
    {
        VkImageViewCreateInfo info = {
            VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO
        };

        info.flags = 0;

        info.image = image;
        info.viewType = viewType;

        info.format = format;

        info.components = components;
        info.subresourceRange = subresourceRange;

        ImageView imageView = {};
        CHECK_VK(vkCreateImageView(device, &info, nullptr, &imageView));

        return imageView;
    }

    inline ImageView createImageView1D(VkDevice device, VkImage image, VkFormat format,
        VkComponentMapping components, VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_1D,
            components, subresourceRange);
    }

    inline ImageView createImageView2D(VkDevice device, VkImage image, VkFormat format,
        VkComponentMapping components, VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_2D,
            components, subresourceRange);
    }

    inline ImageView createImageView3D(VkDevice device, VkImage image, VkFormat format,
        VkComponentMapping components, VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_3D,
            components, subresourceRange);
    }

    inline ImageView createImageViewCube(VkDevice device, VkImage image, VkFormat format,
        VkComponentMapping components, VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_CUBE,
            components, subresourceRange);
    }

    inline ImageView createImageView1DArray(VkDevice device, VkImage image, VkFormat format,
        VkComponentMapping components, VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_1D_ARRAY,
            components, subresourceRange);
    }

    inline ImageView createImageView2DArray(VkDevice device, VkImage image, VkFormat format,
        VkComponentMapping components, VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_2D_ARRAY,
            components, subresourceRange);
    }

    inline ImageView createImageViewCubeArray(VkDevice device, VkImage image, VkFormat format,
        VkComponentMapping components, VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_CUBE_ARRAY,
            components, subresourceRange);
    }

    inline ImageView createImageView1D(VkDevice device, VkImage image, VkFormat format,
        VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_1D,
            {}, subresourceRange);
    }

    inline ImageView createImageView2D(VkDevice device, VkImage image, VkFormat format,
        VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_2D,
            {}, subresourceRange);
    }

    inline ImageView createImageView3D(VkDevice device, VkImage image, VkFormat format,
        VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_3D,
            {}, subresourceRange);
    }

    inline ImageView createImageViewCube(VkDevice device, VkImage image, VkFormat format,
        VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_CUBE,
            {}, subresourceRange);
    }

    inline ImageView createImageView1DArray(VkDevice device, VkImage image, VkFormat format,
        VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_1D_ARRAY,
            {}, subresourceRange);
    }

    inline ImageView createImageView2DArray(VkDevice device, VkImage image, VkFormat format,
        VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_2D_ARRAY,
            {}, subresourceRange);
    }

    inline ImageView createImageViewCubeArray(VkDevice device, VkImage image, VkFormat format,
        VkImageSubresourceRange subresourceRange)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_CUBE_ARRAY,
            {}, subresourceRange);
    }

    inline ImageView createImageView1D(VkDevice device, VkImage image, VkFormat format,
        VkImageAspectFlags imageAspect)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_1D,
            {}, { imageAspect, 0, 1, 0, 1 });
    }

    inline ImageView createImageView2D(VkDevice device, VkImage image, VkFormat format,
        VkImageAspectFlags imageAspect)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_2D,
            {}, { imageAspect, 0, 1, 0, 1 });
    }

    inline ImageView createImageView3D(VkDevice device, VkImage image, VkFormat format,
        VkImageAspectFlags imageAspect)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_3D,
            {}, { imageAspect, 0, 1, 0, 1 });
    }

    inline ImageView createImageViewCube(VkDevice device, VkImage image, VkFormat format,
        VkImageAspectFlags imageAspect)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_CUBE,
            {}, { imageAspect, 0, 1, 0, 1 });
    }

    inline ImageView createImageView1DArray(VkDevice device, VkImage image, VkFormat format,
        VkImageAspectFlags imageAspect)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_1D_ARRAY,
            {}, { imageAspect, 0, 1, 0, 1 });
    }

    inline ImageView createImageView2DArray(VkDevice device, VkImage image, VkFormat format,
        VkImageAspectFlags imageAspect)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_2D_ARRAY,
            {}, { imageAspect, 0, 1, 0, 1 });
    }

    inline ImageView createImageViewCubeArray(VkDevice device, VkImage image, VkFormat format,
        VkImageAspectFlags imageAspect)
    {
        return createImageView(device, image, format, VK_IMAGE_VIEW_TYPE_CUBE_ARRAY,
            {}, { imageAspect, 0, 1, 0, 1 });
    }

    inline ImageView createColorImageView1D(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView1D(device, image, format,
            VK_IMAGE_ASPECT_COLOR_BIT);
    }

    inline ImageView createColorImageView2D(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView2D(device, image, format,
            VK_IMAGE_ASPECT_COLOR_BIT);
    }

    inline ImageView createColorImageView3D(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView3D(device, image, format,
            VK_IMAGE_ASPECT_COLOR_BIT);
    }

    inline ImageView createColorImageViewCube(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageViewCube(device, image, format,
            VK_IMAGE_ASPECT_COLOR_BIT);
    }

    inline ImageView createColorImageView1DArray(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView1DArray(device, image, format,
            VK_IMAGE_ASPECT_COLOR_BIT);
    }

    inline ImageView createColorImageView2DArray(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView2DArray(device, image, format,
            VK_IMAGE_ASPECT_COLOR_BIT);
    }

    inline ImageView createColorImageViewCubeArray(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageViewCubeArray(device, image, format,
            VK_IMAGE_ASPECT_COLOR_BIT);
    }

    inline ImageView createDepthImageView1D(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView1D(device, image, format,
            VK_IMAGE_ASPECT_DEPTH_BIT);
    }

    inline ImageView createDepthImageView2D(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView2D(device, image, format,
            VK_IMAGE_ASPECT_DEPTH_BIT);
    }

    inline ImageView createDepthImageView3D(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView3D(device, image, format,
            VK_IMAGE_ASPECT_DEPTH_BIT);
    }

    inline ImageView createDepthImageViewCube(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageViewCube(device, image, format,
            VK_IMAGE_ASPECT_DEPTH_BIT);
    }

    inline ImageView createDepthImageView1DArray(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView1DArray(device, image, format,
            VK_IMAGE_ASPECT_DEPTH_BIT);
    }

    inline ImageView createDepthImageView2DArray(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView2DArray(device, image, format,
            VK_IMAGE_ASPECT_DEPTH_BIT);
    }

    inline ImageView createDepthImageViewCubeArray(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageViewCubeArray(device, image, format,
            VK_IMAGE_ASPECT_DEPTH_BIT);
    }

    inline ImageView createStencilImageView1D(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView1D(device, image, format,
            VK_IMAGE_ASPECT_STENCIL_BIT);
    }

    inline ImageView createStencilImageView2D(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView2D(device, image, format,
            VK_IMAGE_ASPECT_STENCIL_BIT);
    }

    inline ImageView createStencilImageView3D(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView3D(device, image, format,
            VK_IMAGE_ASPECT_STENCIL_BIT);
    }

    inline ImageView createStencilImageViewCube(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageViewCube(device, image, format,
            VK_IMAGE_ASPECT_STENCIL_BIT);
    }

    inline ImageView createStencilImageView1DArray(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView1DArray(device, image, format,
            VK_IMAGE_ASPECT_STENCIL_BIT);
    }

    inline ImageView createStencilImageView2DArray(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageView2DArray(device, image, format,
            VK_IMAGE_ASPECT_STENCIL_BIT);
    }

    inline ImageView createStencilImageViewCubeArray(VkDevice device, VkImage image, VkFormat format)
    {
        return createImageViewCubeArray(device, image, format,
            VK_IMAGE_ASPECT_STENCIL_BIT);
    }

    inline void destroyImageView(VkDevice device, const VkImageView& imageView)
    {
        vkDestroyImageView(device, imageView, nullptr);
    }
}
