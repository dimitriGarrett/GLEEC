#pragma once

#include "Internal/Graphics/vk/Device.h"
#include "helpers/SwapchainCreation.h"

#include "ImageView.h"

namespace GLEEC::Internal::Graphics::vk
{
    struct Swapchain
    {
        VkSwapchainKHR swapchain = {};

        VkExtent3D extent = {};

        VkSurfaceFormatKHR surfaceFormat = {};

        std::vector<VkImage> images = {};
        std::vector<ImageView> imageViews = {};

        VkSwapchainCreateInfoKHR createInfo = {};

        VkPresentScalingFlagsEXT scalingMethod = {};

        operator VkSwapchainKHR() const
        {
            return swapchain;
        }
    };

    inline std::vector<VkImage> getSwapchainImages(VkDevice device, VkSwapchainKHR swapchain)
    {
        uint32_t count = 0;
        CHECK_VK(vkGetSwapchainImagesKHR(device, swapchain, &count, nullptr));

        std::vector<VkImage> images(count);
        CHECK_VK(vkGetSwapchainImagesKHR(device, swapchain, &count, images.data()));

        return images;
    }

    inline std::vector<ImageView> getSwapchainImageViews(VkDevice device, const Swapchain& swapchain)
    {
        std::vector<ImageView> imageViews;

        for (const VkImage& image : swapchain.images)
        {
            imageViews.push_back(createColorImageView2D(device,
                image, swapchain.surfaceFormat.format));
        }

        return imageViews;
    }

    inline std::vector<ImageView> getSwapchainImageViews(VkDevice device, VkSwapchainKHR swapchain, VkFormat format)
    {
        const std::vector<VkImage> images = getSwapchainImages(device, swapchain);
        std::vector<ImageView> imageViews;

        for (const VkImage& image : images)
        {
            imageViews.push_back(createColorImageView2D(device,
                image, format));
        }

        return imageViews;
    }

    // must include physicalDevice and surface to test for scaling
    // capabilities reliably :(
    inline Swapchain createSwapchain(VkPhysicalDevice physicalDevice,
        VkDevice device, VkSurfaceKHR surface, const VkSwapchainCreateInfoKHR& createInfo)
    {
        VkSwapchainCreateInfoKHR info = createInfo;

        Swapchain swapchain = {};

        swapchain.extent = {
            info.imageExtent.width,
            info.imageExtent.height,
            1 };

        swapchain.surfaceFormat.format = info.imageFormat;
        swapchain.surfaceFormat.colorSpace = info.imageColorSpace;

#if GLEEC_VK_USE_PRESENT_SCALING
        VkSurfacePresentScalingCapabilitiesEXT scalingCaps = {
            VK_STRUCTURE_TYPE_SURFACE_PRESENT_SCALING_CAPABILITIES_EXT
        };

        VkSurfaceCapabilities2KHR surfaceCapabilities =
            getPhysicalDeviceSurfaceCapabilities2(physicalDevice, surface,
                info.presentMode, &scalingCaps);

        VkSwapchainPresentScalingCreateInfoEXT preferredScalingCaps =
            swapchainCreation::preferredScalingCapabilities(scalingCaps);

        swapchain.scalingMethod = preferredScalingCaps.scalingBehavior;

        info.pNext = &preferredScalingCaps;
#endif

        swapchain.createInfo = info;

        CHECK_VK(vkCreateSwapchainKHR(device, &info, nullptr, &swapchain.swapchain));

        if (swapchain.swapchain)
        {
            swapchain.images = getSwapchainImages(device, swapchain);
            swapchain.imageViews = getSwapchainImageViews(device, swapchain);
        }

        return swapchain;
    }

    inline Swapchain createSwapchain(const Device& device, VkSurfaceKHR surface, const VkSwapchainCreateInfoKHR& info)
    {
        return createSwapchain(device.physicalDevice, device.device, surface, info);
    }
            
    inline Swapchain createSwapchain(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, VkPresentModeKHR presentMode = swapchainCreation::NO_VSYNC, VkSwapchainKHR oldSwapchain = VK_NULL_HANDLE)
    {
        VkSwapchainCreateInfoKHR info = {
            VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR
        };

        // needs to be before surfaceCapabilities if using present scaling
        info.presentMode = swapchainCreation::presentMode(
            getPhysicalDeviceSurfacePresentModes(physicalDevice, surface), presentMode);

#if GLEEC_VK_USE_PRESENT_SCALING
        VkSurfacePresentScalingCapabilitiesEXT scalingCaps = {
            VK_STRUCTURE_TYPE_SURFACE_PRESENT_SCALING_CAPABILITIES_EXT
        };

        VkSurfaceCapabilities2KHR surfaceCapabilities =
            getPhysicalDeviceSurfaceCapabilities2(physicalDevice, surface,
                info.presentMode, &scalingCaps);

        VkSwapchainPresentScalingCreateInfoEXT preferredScalingCaps =
            swapchainCreation::preferredScalingCapabilities(scalingCaps);
#define ACCESS_SURFACE_CAPS surfaceCapabilities.surfaceCapabilities
#else
        VkSurfaceCapabilitiesKHR surfaceCapabilities =
            getPhysicalDeviceSurfaceCapabilities(physicalDevice, surface);
#define ACCESS_SURFACE_CAPS surfaceCapabilities
#endif

        info.surface = surface;
        info.minImageCount = swapchainCreation::imageCount(
            ACCESS_SURFACE_CAPS);

        VkSurfaceFormatKHR surfaceFormat = swapchainCreation::surfaceFormat(
            getPhysicalDeviceSurfaceFormats(physicalDevice, surface));

        info.imageFormat = surfaceFormat.format;
        info.imageColorSpace = surfaceFormat.colorSpace;

        info.imageExtent = ACCESS_SURFACE_CAPS.currentExtent;
        info.preTransform = ACCESS_SURFACE_CAPS.currentTransform;

        info.imageArrayLayers = 1;
        info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;

        info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        info.queueFamilyIndexCount = 0;
        info.pQueueFamilyIndices = nullptr;

        info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        info.clipped = VK_TRUE;

        info.oldSwapchain = nullptr; // probably will use soon

        Swapchain swapchain = {};

        swapchain.extent = {
            info.imageExtent.width,
            info.imageExtent.height,
            1 };

        swapchain.surfaceFormat = surfaceFormat;

        swapchain.createInfo = info;

#if GLEEC_VK_USE_PRESENT_SCALING
        swapchain.scalingMethod = preferredScalingCaps.scalingBehavior;

        info.pNext = &preferredScalingCaps;
#endif

        CHECK_VK(vkCreateSwapchainKHR(device, &info, nullptr, &swapchain.swapchain));

        if (swapchain.swapchain)
        {
            swapchain.images = getSwapchainImages(device, swapchain);
            swapchain.imageViews = getSwapchainImageViews(device, swapchain);
        }

        return swapchain;
    }

    inline Swapchain createSwapchain(const Device& device, VkSurfaceKHR surface, VkPresentModeKHR presentMode = swapchainCreation::VSYNC)
    {
        return createSwapchain(device.physicalDevice, device.device, surface, presentMode);
    }

    inline void destroySwapchain(VkDevice device, VkSwapchainKHR swapchain)
    {
        vkDestroySwapchainKHR(device, swapchain, nullptr);
    }

    // useful for reusing old swapchain for resizing window
    inline void destroySwapchainResources(VkDevice device, const Swapchain& swapchain)
    {
        for (const auto& imageView : swapchain.imageViews)
        {
            vkDestroyImageView(device, imageView, nullptr);
        }
    }

    inline void destroySwapchain(VkDevice device, const Swapchain& swapchain)
    {
        destroySwapchain(device, swapchain.swapchain);
        destroySwapchainResources(device, swapchain);
    }

    inline VkResult getStatus(VkDevice device, VkSwapchainKHR swapchain)
    {
        return vkGetSwapchainStatusKHR(device, swapchain);
    }

    inline bool isSwapchainStatusCompatible(VkDevice device, VkSwapchainKHR swapchain)
    {
        return getStatus(device, swapchain) > 0;
    }

    inline VkPresentInfoKHR presentInfo(VkSwapchainKHR swapchain,
        uint32_t swapchainImageIndex,
        const std::vector<VkSemaphore>& waitSemaphores)
    {
        VkPresentInfoKHR info = {
            VK_STRUCTURE_TYPE_PRESENT_INFO_KHR
        };

        info.waitSemaphoreCount =
            static_cast<uint32_t>(waitSemaphores.size());
        info.pWaitSemaphores = waitSemaphores.data();

        info.swapchainCount = 1;
        info.pSwapchains = &swapchain;

        info.pImageIndices = &swapchainImageIndex;

        return info;
    }

    inline VkPresentInfoKHR presentInfo(VkSwapchainKHR swapchain,
        uint32_t swapchainImageIndex, VkSemaphore waitSemaphore)
    {
        VkPresentInfoKHR info = {
            VK_STRUCTURE_TYPE_PRESENT_INFO_KHR
        };

        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = &waitSemaphore;

        info.swapchainCount = 1;
        info.pSwapchains = &swapchain;

        info.pImageIndices = &swapchainImageIndex;

        return info;
    }

    inline VkAcquireNextImageInfoKHR acquireNextImageInfo(VkSwapchainKHR swapchain,
        uint64_t timeout, VkSemaphore semaphore, VkFence fence = nullptr)
    {
        VkAcquireNextImageInfoKHR info = {
            VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR
        };

        info.swapchain = swapchain;
        info.timeout = timeout;
        info.semaphore = semaphore;
        info.fence = fence;
        info.deviceMask = 1;

        return info;
    }

    inline VkResult acquireNextImage2(VkDevice device,
        const VkAcquireNextImageInfoKHR* acquireInfo, uint32_t* imageIndex)
    {
        return vkAcquireNextImage2KHR(device, acquireInfo, imageIndex);
    }
}
