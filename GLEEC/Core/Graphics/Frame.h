#pragma once

#include "GPUManager.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/CommandPool.h"
#include "Internal/Graphics/vk/Fence.h"
#include "Internal/Graphics/vk/Semaphore.h"
#include "Internal/Graphics/vk/Image.h"
#include "Internal/Graphics/vk/Submit.h"
#else
#error "Unknown Graphics backend for GLEEC!"
#endif

#define GLEEC_USE_FRAMES_IN_FLIGHT 1

namespace GLEEC::Graphics
{
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    // just for caching frequently used information
    struct SubmitInfo
    {
        VkCommandBufferSubmitInfo commandBuffer = {};

        VkSemaphoreSubmitInfo waitSemaphore = {};
        VkSemaphoreSubmitInfo signalSemaphore = {};

        VkSubmitInfo2 submit = {};
    };
#endif

    // all data needed on a per-frame basis
    // (mainly for multiple frames in flight,
    // but also helps a lot with organization)
    struct FrameData
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::CommandPool commandPool = {};

        // TODO: add another command buffer just for image transitions
        Internal::Graphics::vk::CommandBuffer commandBuffer = {};

        Internal::Graphics::vk::Semaphore swapchainSemaphore = {};
        Internal::Graphics::vk::Semaphore renderSemaphore = {};

        SubmitInfo submitInfo = {};
#endif
    };

    struct Frame
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        uint32_t swapchainImageIndex = static_cast<uint32_t>(-1);

        VkClearColorValue clearColor = { { 1.0f, 0.0f, 0.0f, 1.0f } };
#endif

#if GLEEC_USE_FRAMES_IN_FLIGHT
        // anything more than 2 might lead to too much input lag
        static constexpr uint32_t FRAMES_IN_FLIGHT = 2;

        std::array<FrameData, FRAMES_IN_FLIGHT> frames = {};
#else
        FrameData frame = {};
#endif
    };
}
