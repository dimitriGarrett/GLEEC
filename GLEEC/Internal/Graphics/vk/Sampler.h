#pragma once

#include "PhysicalDevice.h"
#include "Device.h"

namespace GLEEC::Internal::Graphics::vk
{
    using Sampler = VkSampler;

    inline Sampler createSampler(VkPhysicalDevice physicalDevice,
        VkDevice device)
    {
        VkSamplerCreateInfo info = {
            VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO
        };

        info.magFilter = info.minFilter = VK_FILTER_LINEAR;

        info.addressModeU = info.addressModeV = info.addressModeW =
            VK_SAMPLER_ADDRESS_MODE_REPEAT;

        info.anisotropyEnable = getPhysicalDeviceSupportsAnisotropy(
            physicalDevice);

        info.maxAnisotropy = getPhysicalDeviceProperties(physicalDevice)
            .limits.maxSamplerAnisotropy / 2.0f;

        info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        info.unnormalizedCoordinates = VK_FALSE;

        info.compareEnable = VK_FALSE;
        info.compareOp = VK_COMPARE_OP_ALWAYS;

        info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        info.mipLodBias = 0.0f;
        info.minLod = 0.0f;
        info.maxLod = 0.0;

        Sampler sampler = {};
        CHECK_VK(vkCreateSampler(device, &info, nullptr, &sampler));

        return sampler;
    }

    inline Sampler createSampler(const Device& device)
    {
        return createSampler(device.physicalDevice, device);
    }

    inline void destroySampler(VkDevice device, VkSampler sampler)
    {
        vkDestroySampler(device, sampler, nullptr);
    }
}
