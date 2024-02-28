#pragma once

#include "CHECK_VK.h"

#include "vk_mem_alloc.h"

namespace GLEEC::Internal::Graphics::vk
{
    using Allocator = VmaAllocator;
    using Allocation = VmaAllocation;

    inline Allocator createAllocator(VkInstance instance,
        VkPhysicalDevice physicalDevice, VkDevice device)
    {
        VmaAllocatorCreateInfo info = {};

        info.instance = instance;
        info.physicalDevice = physicalDevice;
        info.device = device;

        info.flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;

        Allocator allocator = {};
        CHECK_VK(vmaCreateAllocator(&info, &allocator));

        return allocator;
    }

    inline void destroyAllocator(const Allocator& allocator)
    {
        vmaDestroyAllocator(allocator);
    }
}
