#pragma once

#include "Config/Export.h"

#include "../Swapchain.h"

#include "../helpers/Allocator.h"

namespace GLEEC::Internal::Graphics::vk
{
    struct Image
    {
        VkImage image = {};

        Allocation allocation = {};

        VkExtent3D extent = {};
        VkFormat format = {};

        operator VkImage() const
        {
            return image;
        }
    };

    inline VkImageCreateInfo createImage(VkImageLayout initialLayout,
        VkImageUsageFlags usage,
        VkImageType imageType, VkFormat format, VkExtent3D extent,
        uint32_t mipLevels = 1, uint32_t arrayLayers = 1)
    {
        VkImageCreateInfo info = {
            VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO
        };

        info.flags = 0;
        info.imageType = imageType;

        info.format = format;
        info.extent = extent;

        info.mipLevels = mipLevels;
        info.arrayLayers = arrayLayers;

        info.samples = VK_SAMPLE_COUNT_1_BIT;
        info.tiling = VK_IMAGE_TILING_OPTIMAL;

        info.usage = usage;

        info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        info.queueFamilyIndexCount = 0;
        info.pQueueFamilyIndices = nullptr;

        info.initialLayout = initialLayout;

        return info;
    }

    inline VkImageCreateInfo image1D(VkImageLayout initialLayout,
        VkImageUsageFlags usage,
        VkFormat format, VkExtent3D extent,
        uint32_t mipLevels = 1, uint32_t arrayLayers = 1)
    {
        return createImage(initialLayout, usage,
            VK_IMAGE_TYPE_1D, format, extent, mipLevels, arrayLayers = 1);
    }

    inline VkImageCreateInfo image2D(VkImageLayout initialLayout,
        VkImageUsageFlags usage,
        VkFormat format, VkExtent3D extent,
        uint32_t mipLevels = 1, uint32_t arrayLayers = 1)
    {
        return createImage(initialLayout, usage,
            VK_IMAGE_TYPE_2D, format, extent, mipLevels, arrayLayers = 1);
    }

    inline VkImageCreateInfo image3D(VkImageLayout initialLayout,
        VkImageUsageFlags usage,
        VkFormat format, VkExtent3D extent,
        uint32_t mipLevels = 1, uint32_t arrayLayers = 1)
    {
        return createImage(initialLayout, usage,
            VK_IMAGE_TYPE_3D, format, extent, mipLevels, arrayLayers = 1);
    }

    inline VkImageCreateInfo image1D(VkImageUsageFlags usage,
        VkFormat format, VkExtent3D extent,
        uint32_t mipLevels = 1, uint32_t arrayLayers = 1)
    {
        return createImage(VK_IMAGE_LAYOUT_UNDEFINED, usage,
            VK_IMAGE_TYPE_1D, format, extent, mipLevels, arrayLayers = 1);
    }

    inline VkImageCreateInfo image2D(VkImageUsageFlags usage,
        VkFormat format, VkExtent3D extent,
        uint32_t mipLevels = 1, uint32_t arrayLayers = 1)
    {
        return createImage(VK_IMAGE_LAYOUT_UNDEFINED, usage,
            VK_IMAGE_TYPE_2D, format, extent, mipLevels, arrayLayers = 1);
    }

    inline VkImageCreateInfo image3D(VkImageUsageFlags usage,
        VkFormat format, VkExtent3D extent,
        uint32_t mipLevels = 1, uint32_t arrayLayers = 1)
    {
        return createImage(VK_IMAGE_LAYOUT_UNDEFINED, usage,
            VK_IMAGE_TYPE_3D, format, extent, mipLevels, arrayLayers);
    }

    GLEEC_API_EXTERN Image createImage(Allocator allocator, const VkImageCreateInfo& info);

    GLEEC_API_EXTERN void destroyImage(Allocator allocator, const Image& image);

    inline void destroyImage(VkDevice device, VkImage image)
    {
        vkDestroyImage(device, image, nullptr);
    }
}
