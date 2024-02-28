#pragma once

#include "../PhysicalDevice.h"

#if !GLEEC_DEBUG
#include <algorithm>
#endif

namespace GLEEC::Internal::Graphics::vk::swapchainCreation
{
    inline constexpr uint32_t DOUBLE_BUFFERED = 2;
    inline constexpr uint32_t TRIPLE_BUFFERED = 3;

    // if allowed by physical device, TRIPLE_BUFFERED is usually preferred because it circumvents having to wait for a v sync signal to proceed
    // here is an explanation with example code: (also my source)
    // https://docs.vulkan.org/samples/latest/samples/performance/swapchain_images/README.html 
    inline uint32_t imageCount(VkSurfaceCapabilitiesKHR caps, uint32_t preferredImageCount = TRIPLE_BUFFERED)
    {
        if (caps.maxImageCount == 0)
        {
            LOG_INFO("Vulkan: no maximum on swapchain image count: so the inputted {} was unaffected.", preferredImageCount);

            return preferredImageCount;
        }

#if GLEEC_DEBUG
        if (preferredImageCount < caps.minImageCount)
        {
            LOG_INFO("Vulkan: requested swapchain image count: {} was below allowed minimum: {}",
                preferredImageCount, caps.minImageCount);
        }

        if (preferredImageCount > caps.maxImageCount)
        {
            LOG_INFO("Vulkan: requested swapchain image count: {} was above allowed maximum: {}",
                preferredImageCount, caps.maxImageCount);
        }

        LOG_INFO("Vulkan: requested swapchain image count: {} is acceptable!", preferredImageCount);

        return preferredImageCount;
#else
        return std::clamp(preferredImageCount, caps.minImageCount, caps.maxImageCount);
#endif
    }

    inline constexpr VkPresentModeKHR VSYNC = VK_PRESENT_MODE_FIFO_KHR;
    inline constexpr VkPresentModeKHR NO_VSYNC = VK_PRESENT_MODE_MAILBOX_KHR;

    inline VkPresentModeKHR presentMode(const std::vector<VkPresentModeKHR>& presentModes, VkPresentModeKHR preferredPresentMode = VSYNC)
    {
        // FIFO is always supported
        if (preferredPresentMode == VK_PRESENT_MODE_FIFO_KHR)
        {
            LOG_INFO("Vulkan: preferred present mode found!");

            return VK_PRESENT_MODE_FIFO_KHR;
        }

        for (const VkPresentModeKHR& presentMode : presentModes)
        {
            if (presentMode == preferredPresentMode)
            {
                LOG_INFO("Vulkan: preferred present mode found!");

                return preferredPresentMode;
            }
        }

        LOG_INFO("Vulkan: preferred present mode not found, FIFO returned!");

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    inline VkSurfaceFormatKHR surfaceFormat(const std::vector<VkSurfaceFormatKHR>& surfaceFormats, VkFormat preferredFormat = VK_FORMAT_B8G8R8A8_SRGB, VkColorSpaceKHR preferredColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
    {
        for (const VkSurfaceFormatKHR& surfaceFormat : surfaceFormats)
        {
            if (surfaceFormat.format == preferredFormat && 
                surfaceFormat.colorSpace == preferredColorSpace)
            {
                LOG_INFO("Vulkan: preferred surface format found!");

                return surfaceFormat;
            }
        }

        LOG_INFO("Vulkan: preferred surface mode not found, returning first in vector!");

        return surfaceFormats[0];
    }

    inline VkSurfaceFormatKHR surfaceFormat(const std::vector<VkSurfaceFormatKHR>& surfaceFormats, const VkSurfaceFormatKHR& preferredSurfaceFormat)
    {
        return surfaceFormat(surfaceFormats,
            preferredSurfaceFormat.format, preferredSurfaceFormat.colorSpace);
    }

    inline VkSwapchainPresentScalingCreateInfoEXT preferredScalingCapabilities(const VkSurfacePresentScalingCapabilitiesEXT& supported)
    {
        VkSwapchainPresentScalingCreateInfoEXT info = {
            VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_SCALING_CREATE_INFO_EXT
        };

        if (supported.supportedPresentScaling == 0)
        {
            LOG_INFO("No supported swapchain present scaling!");
        }

        else if (supported.supportedPresentScaling &
            VK_PRESENT_SCALING_STRETCH_BIT_EXT)
        {
            info.scalingBehavior = VK_PRESENT_SCALING_STRETCH_BIT_EXT;

            LOG_INFO("Swapchain supported stretch bit!");
        }

        else if (supported.supportedPresentScaling &
            VK_PRESENT_SCALING_ASPECT_RATIO_STRETCH_BIT_EXT)
        {
            info.scalingBehavior = VK_PRESENT_SCALING_ASPECT_RATIO_STRETCH_BIT_EXT;

            LOG_INFO("Swapchain supported ratio stretch bit!");
        }

        else
        {
            info.scalingBehavior = VK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXT;

            LOG_INFO("Swapchain supports one to one scaling!");
        }

        return info;
    }
}
