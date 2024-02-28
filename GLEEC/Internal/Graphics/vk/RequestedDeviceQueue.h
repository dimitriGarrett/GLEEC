#pragma once

#include "PhysicalDevice.h"

#include <set>

namespace GLEEC::Internal::Graphics::vk
{
    // a glorified VkDeviceQueueCreateInfo wrapper
    struct RequestedDeviceQueue
    {
        VkDeviceQueueCreateInfo info = {};

        std::vector<float> queuePriorities = {};

        static std::vector<VkDeviceQueueCreateInfo> preprocess(const std::set<RequestedDeviceQueue>& requested)
        {
            std::vector<VkDeviceQueueCreateInfo> processed = {};

            for (const RequestedDeviceQueue& deviceQueue : requested)
            {
                processed.emplace_back(deviceQueue.info);
                processed.back().pQueuePriorities = deviceQueue.queuePriorities.data();
            }

            return processed;
        }
    };

    inline bool operator< (const RequestedDeviceQueue& lhs, const RequestedDeviceQueue& rhs)
    {
        return lhs.info.queueFamilyIndex < rhs.info.queueFamilyIndex;
    }

    inline RequestedDeviceQueue prepareRequestedQueueForDevice(
        uint32_t queueFamilyIndex, uint32_t queueCount, const std::vector<float>& queuePriorities = {})
    {
        VkDeviceQueueCreateInfo info = {
            VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO
        };

        info.flags = 0;

        info.queueFamilyIndex = queueFamilyIndex;
        info.queueCount = queueCount;

        if (queuePriorities.empty())
        {
            std::vector<float> queuePriorities2 = std::vector<float>(queueCount, 1.0f);

            info.pQueuePriorities = queuePriorities2.data();

            return { info, queuePriorities2 };
        }

        else
        {
            info.pQueuePriorities = queuePriorities.data();

            return { info, queuePriorities };
        }
    }

    inline RequestedDeviceQueue prepareRequestedQueueForDevice(
        uint32_t queueFamilyIndex, float queuePriority)
    {
        return prepareRequestedQueueForDevice(queueFamilyIndex, 1, { queuePriority });
    }

    inline RequestedDeviceQueue prepareGraphicsQueueForDevice(VkPhysicalDevice physicalDevice,
        uint32_t queueCount, const std::vector<float>& queuePriorities = {})
    {
        return prepareRequestedQueueForDevice(getPhysicalDeviceGraphicsQueueFamilyIndex(physicalDevice),
            queueCount, queuePriorities);
    }

    inline RequestedDeviceQueue prepareGraphicsQueueForDevice(VkPhysicalDevice physicalDevice, float queuePriority)
    {
        return prepareRequestedQueueForDevice(getPhysicalDeviceGraphicsQueueFamilyIndex(physicalDevice),
            1, { queuePriority });
    }

    inline RequestedDeviceQueue prepareGraphicsQueueForDevice(VkPhysicalDevice physicalDevice)
    {
        return prepareRequestedQueueForDevice(getPhysicalDeviceGraphicsQueueFamilyIndex(physicalDevice),
            1, { 1.0f });
    }

    inline RequestedDeviceQueue prepareComputeQueueForDevice(VkPhysicalDevice physicalDevice,
        uint32_t queueCount, const std::vector<float>& queuePriorities = {})
    {
        return prepareRequestedQueueForDevice(getPhysicalDeviceComputeQueueFamilyIndex(physicalDevice),
            queueCount, queuePriorities);
    }

    inline RequestedDeviceQueue prepareComputeQueueForDevice(VkPhysicalDevice physicalDevice, float queuePriority)
    {
        return prepareRequestedQueueForDevice(getPhysicalDeviceComputeQueueFamilyIndex(physicalDevice),
            1, { queuePriority });
    }

    inline RequestedDeviceQueue prepareComputeQueueForDevice(VkPhysicalDevice physicalDevice)
    {
        return prepareRequestedQueueForDevice(getPhysicalDeviceComputeQueueFamilyIndex(physicalDevice),
            1, { 1.0f });
    }

    inline RequestedDeviceQueue prepareTransferQueueForDevice(VkPhysicalDevice physicalDevice,
        uint32_t queueCount, const std::vector<float>& queuePriorities = {})
    {
        return prepareRequestedQueueForDevice(getPhysicalDeviceTransferQueueFamilyIndex(physicalDevice),
            queueCount, queuePriorities);
    }

    inline RequestedDeviceQueue prepareTransferQueueForDevice(VkPhysicalDevice physicalDevice, float queuePriority)
    {
        return prepareRequestedQueueForDevice(getPhysicalDeviceTransferQueueFamilyIndex(physicalDevice),
            1, { queuePriority });
    }

    inline RequestedDeviceQueue prepareTransferQueueForDevice(VkPhysicalDevice physicalDevice)
    {
        return prepareRequestedQueueForDevice(getPhysicalDeviceComputeQueueFamilyIndex(physicalDevice),
            1, { 1.0f });
    }

    inline RequestedDeviceQueue preparePresentQueueForDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, float queuePriority)
    {
        return prepareRequestedQueueForDevice(getPhysicalDevicePresentQueueFamilyIndex(physicalDevice, surface),
            1, { queuePriority });
    }

    inline RequestedDeviceQueue preparePresentQueueForDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        return prepareRequestedQueueForDevice(getPhysicalDevicePresentQueueFamilyIndex(physicalDevice, surface),
            1, { 1.0f });
    }

    inline std::set<RequestedDeviceQueue> defaultPreparedQueuesForDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        return
        {
            prepareGraphicsQueueForDevice(physicalDevice),
            preparePresentQueueForDevice(physicalDevice, surface)
        };
    }
}
