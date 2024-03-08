#include "Buffer.h"

namespace GLEEC::Internal::Graphics::vk
{
    Buffer createBuffer(Allocator& allocator,
        const VkBufferCreateInfo& createInfo, VmaMemoryUsage memoryUsage)
    {
        VmaAllocationCreateInfo info = {};
        info.usage = memoryUsage;

        Buffer buffer = {};
        CHECK_VK(vmaCreateBuffer(allocator, &createInfo, &info, &buffer.buffer, &buffer.allocation, nullptr));

        buffer.usage = createInfo.usage;
        buffer.size = createInfo.size;

        return buffer;
    }

    void destroyBuffer(Allocator& allocator, Buffer& buffer)
    {
        if (buffer.map != nullptr) unmapMemory(allocator, buffer);
        vmaDestroyBuffer(allocator, buffer.buffer, buffer.allocation);
    }

    void mapMemory(Allocator& allocator, Allocation& allocation,
        void** memoryPtr)
    {
        CHECK_VK(vmaMapMemory(allocator, allocation, memoryPtr));
    }

    void unmapMemory(Allocator& allocator, Allocation& allocation)
    {
        vmaUnmapMemory(allocator, allocation);
    }
}
