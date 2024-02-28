#pragma once

#include "Internal/Graphics/vk/DeviceExtensions.h"

#include "PhysicalDeviceFeatures.h"
#include "RequestedDeviceQueue.h"

namespace GLEEC::Internal::Graphics::vk
{
    struct Device
    {
        PhysicalDevice physicalDevice = {};
        VkDevice device = {};

        operator VkDevice() const
        {
            return device;
        }
    };

    inline Device createDevice(VkPhysicalDevice physicalDevice,
        const std::vector<VkDeviceQueueCreateInfo>& queueCreateInfos)
    {
        VkDeviceCreateInfo info = {
            VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO
        };

        info.flags = 0;

        // deprecated, here just to be verbose
        info.enabledLayerCount = 0;
        info.ppEnabledLayerNames = nullptr;

        std::vector<const char*> extensions = DeviceExtensionProperties::availableRequestedExtensions(physicalDevice);

        info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        info.ppEnabledExtensionNames = extensions.data();

        info.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());

        info.pQueueCreateInfos = queueCreateInfos.data();

        PhysicalDeviceFeaturesChain physicalDeviceFeatures =
            PhysicalDeviceFeatures::availableRequestedFeatures(physicalDevice);

        pNextChain chain = physicalDeviceFeatures.chain;

#if GLEEC_DEBUG && VK_NV_device_diagnostics_config
        VkDeviceDiagnosticsConfigCreateInfoNV diagnosticsConfigCreateInfo = {
            VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV
        };

        diagnosticsConfigCreateInfo.flags =
            VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_SHADER_DEBUG_INFO_BIT_NV |
            VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_RESOURCE_TRACKING_BIT_NV |
            VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_AUTOMATIC_CHECKPOINTS_BIT_NV |
            VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_SHADER_ERROR_REPORTING_BIT_NV;

        chain.add(diagnosticsConfigCreateInfo);
#endif

        // instead of setting info::pEnabledFeatures, because i am using the 2 version
        chain.apply(info);

        Device device = {};
        device.physicalDevice = physicalDevice;

        CHECK_VK(vkCreateDevice(physicalDevice, &info, nullptr, &device.device));
        
        return device;
    }

    inline Device createDevice(VkPhysicalDevice physicalDevice,
        const std::set<RequestedDeviceQueue>& requestedQueues)
    {
        return createDevice(physicalDevice,
            RequestedDeviceQueue::preprocess(requestedQueues));
    }

    inline Device createDevice(VkPhysicalDevice physicalDevice,
        const RequestedDeviceQueue& requestedQueue)
    {
        return createDevice(physicalDevice, std::set<RequestedDeviceQueue>{ requestedQueue });
    }

    inline void destroyDevice(VkDevice device)
    {
        vkDestroyDevice(device, nullptr);
    }

    inline void deviceWaitIdle(VkDevice device)
    {
        CHECK_VK(vkDeviceWaitIdle(device));
    }
}
