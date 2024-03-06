#pragma once

#include "PhysicalDevice.h"

namespace GLEEC::Internal::Graphics::vk
{
    inline constexpr uint32_t formatSize(VkFormat format)
    {
        switch (format)
		{
        case VK_FORMAT_R32_SFLOAT:          return sizeof(float) * 1;
        case VK_FORMAT_R32G32_SFLOAT:       return sizeof(float) * 2;
        case VK_FORMAT_R32G32B32_SFLOAT:    return sizeof(float) * 3;
        case VK_FORMAT_R32G32B32A32_SFLOAT: return sizeof(float) * 4;

        case VK_FORMAT_R64_SFLOAT:          return sizeof(double) * 1;
        case VK_FORMAT_R64G64_SFLOAT:       return sizeof(double) * 2;
        case VK_FORMAT_R64G64B64_SFLOAT:    return sizeof(double) * 3;
        case VK_FORMAT_R64G64B64A64_SFLOAT: return sizeof(double) * 4;

        case VK_FORMAT_R64_SINT:          return sizeof(int) * 1;
        case VK_FORMAT_R64G64_SINT:       return sizeof(int) * 2;
        case VK_FORMAT_R64G64B64_SINT:    return sizeof(int) * 3;
        case VK_FORMAT_R64G64B64A64_SINT: return sizeof(int) * 4;

        case VK_FORMAT_R64_UINT:          return sizeof(unsigned int) * 1;
        case VK_FORMAT_R64G64_UINT:       return sizeof(unsigned int) * 2;
        case VK_FORMAT_R64G64B64_UINT:    return sizeof(unsigned int) * 3;
        case VK_FORMAT_R64G64B64A64_UINT: return sizeof(unsigned int) * 4;

		default: return -1;
		}
    }
}
