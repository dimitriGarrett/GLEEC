#pragma once

#include "PhysicalDevice.h"
#include "Device.h"

namespace GLEEC::Internal::Graphics::vk
{
    struct Queue
    {
        VkQueue queue = {};

        uint32_t index = 0;

        operator VkQueue() const
        {
            return queue;
        }
    };

    inline Queue getDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex)
    {
        Queue queue = {};
        queue.index = queueFamilyIndex;

        vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, &queue.queue);
        return queue;
    }

    inline Queue getDeviceQueue(VkDevice device, uint32_t queueFamilyIndex)
    {
        return getDeviceQueue(device, queueFamilyIndex, 0);
    }

    inline Queue getDeviceFirstQueue(VkDevice device, uint32_t queueFamilyIndex)
    {
        return getDeviceQueue(device, queueFamilyIndex, 0);
    }

    inline Queue getDeviceGraphicsQueue(VkPhysicalDevice physicalDevice, VkDevice device, uint32_t queueIndex)
    {
        return getDeviceQueue(device, getPhysicalDeviceGraphicsQueueFamilyIndex(physicalDevice), queueIndex);
    }

    inline Queue getDeviceGraphicsQueue(VkPhysicalDevice physicalDevice, VkDevice device)
    {
        return getDeviceGraphicsQueue(physicalDevice, device, 0);
    }

    inline Queue getDeviceFirstGraphicsQueue(VkPhysicalDevice physicalDevice, VkDevice device)
    {
        return getDeviceGraphicsQueue(physicalDevice, device, 0);
    }

    inline Queue getDeviceGraphicsQueue(const Device& device, uint32_t queueIndex)
    {
        return getDeviceGraphicsQueue(device.physicalDevice, device.device, queueIndex);
    }

    inline Queue getDeviceGraphicsQueue(const Device& device)
    {
        return getDeviceGraphicsQueue(device, 0);
    }

    inline Queue getDeviceFirstGraphicsQueue(const Device& device)
    {
        return getDeviceGraphicsQueue(device, 0);
    }

    inline Queue getDeviceComputeQueue(VkPhysicalDevice physicalDevice, VkDevice device, uint32_t queueIndex)
    {
        return getDeviceQueue(device, getPhysicalDeviceComputeQueueFamilyIndex(physicalDevice), queueIndex);
    }

    inline Queue getDeviceComputeQueue(VkPhysicalDevice physicalDevice, VkDevice device)
    {
        return getDeviceComputeQueue(physicalDevice, device, 0);
    }

    inline Queue getDeviceFirstComputeQueue(VkPhysicalDevice physicalDevice, VkDevice device)
    {
        return getDeviceComputeQueue(physicalDevice, device, 0);
    }

    inline Queue getDeviceComputeQueue(const Device& device, uint32_t queueIndex)
    {
        return getDeviceComputeQueue(device.physicalDevice, device.device, queueIndex);
    }

    inline Queue getDeviceComputeQueue(const Device& device)
    {
        return getDeviceComputeQueue(device, 0);
    }

    inline Queue getDeviceFirstComputeQueue(const Device& device)
    {
        return getDeviceComputeQueue(device, 0);
    }

    inline Queue getDeviceTransferQueue(VkPhysicalDevice physicalDevice, VkDevice device, uint32_t queueIndex)
    {
        return getDeviceQueue(device, getPhysicalDeviceTransferQueueFamilyIndex(physicalDevice), queueIndex);
    }

    inline Queue getDeviceTransferQueue(VkPhysicalDevice physicalDevice, VkDevice device)
    {
        return getDeviceTransferQueue(physicalDevice, device, 0);
    }

    inline Queue getDeviceFirstTransferQueue(VkPhysicalDevice physicalDevice, VkDevice device)
    {
        return getDeviceTransferQueue(physicalDevice, device, 0);
    }

    inline Queue getDeviceTransferQueue(const Device& device, uint32_t queueIndex)
    {
        return getDeviceTransferQueue(device.physicalDevice, device.device, queueIndex);
    }

    inline Queue getDeviceTransferQueue(const Device& device)
    {
        return getDeviceTransferQueue(device, 0);
    }

    inline Queue getDeviceFirstTransferQueue(const Device& device)
    {
        return getDeviceTransferQueue(device, 0);
    }

    inline Queue getDevicePresentQueue(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, uint32_t queueIndex)
    {
        return getDeviceQueue(device, getPhysicalDevicePresentQueueFamilyIndex(physicalDevice, surface), queueIndex);
    }

    inline Queue getDevicePresentQueue(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface)
    {
        return getDevicePresentQueue(physicalDevice, device, surface, 0);
    }

    inline Queue getDeviceFirstPresentQueue(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface)
    {
        return getDevicePresentQueue(physicalDevice, device, surface, 0);
    }

    inline Queue getDevicePresentQueue(const Device& device, VkSurfaceKHR surface, uint32_t queueIndex)
    {
        return getDevicePresentQueue(device.physicalDevice, device.device, surface, queueIndex);
    }

    inline Queue getDevicePresentQueue(const Device& device, VkSurfaceKHR surface)
    {
        return getDevicePresentQueue(device, surface, 0);
    }

    inline Queue getDeviceFirstPresentQueue(const Device& device, VkSurfaceKHR surface)
    {
        return getDevicePresentQueue(device, surface, 0);
    }

    inline void queuePresent(VkQueue queue, const VkPresentInfoKHR& presentInfo)
    {
        CHECK_VK(vkQueuePresentKHR(queue, &presentInfo));
    }
}
