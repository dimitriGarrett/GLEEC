#pragma once

#include "Config/Export.h"
#include "Internal/Graphics/vk/helpers/Allocator.h"

namespace GLEEC::Internal::Graphics::vk
{
    struct Buffer
    {
        VkBuffer buffer = {};
        VkBufferUsageFlags usage = {};

        VkDeviceSize size = {};

        char* map = nullptr;
        Allocation allocation = {};

        operator VkBuffer() const
        {
            return buffer;
        }
    };

    inline VkBufferCreateInfo createBuffer(
        VkDeviceSize size, VkBufferUsageFlags usage, VkBufferCreateFlags flags,
        VkSharingMode sharingMode, uint32_t queueFamilyIndexCount,
        const uint32_t* queueFamilyIndices)
    {
        return {
            .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .pNext = nullptr,

            .flags = flags,

            .size = size,
            .usage = usage,

            .sharingMode = sharingMode,

            .queueFamilyIndexCount = queueFamilyIndexCount,
            .pQueueFamilyIndices = queueFamilyIndices,
        };
    }

    inline VkBufferCreateInfo createBuffer(
        VkDeviceSize size, VkBufferUsageFlags usage,
        VkSharingMode sharingMode, uint32_t queueFamilyIndexCount,
        const uint32_t* queueFamilyIndices)
    {
        return createBuffer(size, usage, 0, sharingMode,
            queueFamilyIndexCount, queueFamilyIndices);
    }

    inline VkBufferCreateInfo createBuffer(
        VkDeviceSize size, VkBufferUsageFlags usage, VkBufferCreateFlags flags)
    {
        return createBuffer(size, usage, flags,
            VK_SHARING_MODE_EXCLUSIVE, 0, nullptr);
    }

    inline VkBufferCreateInfo createBuffer(
        VkDeviceSize size, VkBufferUsageFlags usage)
    {
        return createBuffer(size, usage, 0,
            VK_SHARING_MODE_EXCLUSIVE, 0, nullptr);
    }

    GLEEC_API_EXTERN Buffer createBuffer(Allocator& allocator,
        const VkBufferCreateInfo& createInfo, VmaMemoryUsage memoryUsage);

    GLEEC_API_EXTERN void destroyBuffer(Allocator& allocator,
        Buffer& buffer);

    GLEEC_API_EXTERN void mapMemory(Allocator& allocator, Allocation& allocation,
        void** memoryPtr);

    inline void mapMemory(Allocator& allocator, Buffer& buffer)
    {
        mapMemory(allocator, buffer.allocation, reinterpret_cast<void**>(&buffer.map));
    }

    GLEEC_API_EXTERN void unmapMemory(Allocator& allocator, Allocation& allocation);

    inline void unmapMemory(Allocator& allocator, Buffer& buffer)
    {
        unmapMemory(allocator, buffer.allocation);
        buffer.map = nullptr;
    }

    inline VkDeviceAddress getBufferDeviceAddress(
        VkDevice device, VkBuffer buffer)
    {
        VkBufferDeviceAddressInfo info = {
            VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO
        };

        info.buffer = buffer;

        return vkGetBufferDeviceAddress(device, &info);
    }
}
