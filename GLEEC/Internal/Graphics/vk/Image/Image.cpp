#include "Image.h"

namespace GLEEC::Internal::Graphics::vk
{
    // too lazy to create a library for vma to export all functions,
    // so can only call vma from source files in GLEEC lib

    Image createImage(Allocator& allocator, const VkImageCreateInfo& info)
    {
        VmaAllocationCreateInfo allocationInfo = {};
        allocationInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
        allocationInfo.requiredFlags =
            VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        Image image = {};
        CHECK_VK(vmaCreateImage(allocator, &info, &allocationInfo, &image.image, &image.allocation, nullptr));

        image.extent = info.extent;
        image.format = info.format;

        return image;
    }

    void destroyImage(Allocator& allocator, const Image& image)
    {
        vmaDestroyImage(allocator, image.image, image.allocation);
    }
}
