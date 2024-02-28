#pragma once

#include "Internal/Graphics/Backend.h"
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Queue.h"
#include "Internal/Graphics/vk/Device.h"
#include "Internal/Graphics/vk/helpers/Allocator.h"
#endif

namespace GLEEC::Graphics
{
    struct GPU
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        // it would be a physical device and device,
        // but device holds a reference to physical device already
        Internal::Graphics::vk::Device device = {};

        Internal::Graphics::vk::Queue graphicsQueue = {};
        Internal::Graphics::vk::Queue presentQueue = {};

        Internal::Graphics::vk::Allocator allocator = {};
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        void wait()
        {
            Internal::Graphics::vk::deviceWaitIdle(device);
        }
#endif

        bool connected()
        {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            return device.device != VK_NULL_HANDLE;
#else
            return false;
#endif
        }
    };
}
