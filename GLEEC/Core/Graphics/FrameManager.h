#pragma once

#include "Frame.h"

#include "Core/Window/WindowManager.h"

#include <bitset>

namespace GLEEC::Graphics
{
    struct FrameManager
    {
        /*
           The idea was to have this defined in cpp file
           but it was just getting too convoluted so it goes here now :)
        */

        static void init()
        {
            for (int i = 0; i < Window::WindowManager::openWindows; ++i)
            {
                initFrame(i);
            }

#if GLEEC_USE_FRAMES_IN_FLIGHT
            fences[0] = Internal::Graphics::vk::createSignaledFence(
                GPUManager::activeGPU.device);

            for (size_t i = 1; i < fences.size(); ++i)
            {
                fences[i] = Internal::Graphics::vk::createFence(
                    GPUManager::activeGPU.device);
            }
#else
            fence = Internal::Graphics::vk::createSignaledFence(
                GPUManager::activeGPU.device);
#endif
        }

        static void destroy()
        {
            for (int i = 0; i < Window::WindowManager::openWindows; ++i)
            {
                destroyFrame(i);
            }

#if GLEEC_USE_FRAMES_IN_FLIGHT
            for (auto& fence : fences)
            {
#endif
                Internal::Graphics::vk::destroyFence(
                    GPUManager::activeGPU.device, fence);

#if GLEEC_USE_FRAMES_IN_FLIGHT
            }
#endif
        }

        GLEEC_API static void begin();
        GLEEC_API static void end();

        GLEEC_API static std::array<Frame, GLEEC_WINDOW_MAX_WINDOWS> frames;

        // needs to be accessible by window manager
        GLEEC_API static void destroyFrame(size_t i);
        GLEEC_API static void initFrame(size_t i);

        GLEEC_API static void swap(size_t a, size_t b);
        /* {
            Frame&& fa = std::move(frames[a]);
            frames[a] = std::move(frames[b]);
            frames[b] = std::move(fa);

            bool bb = recreateFlags[b];
            recreateFlags[b] = recreateFlags[a];
            recreateFlags[a] = bb;
        } */

        static void recreateFrame(size_t i)
        {
            recreateFlags[i] = true;
        }

        GLEEC_API static uint32_t activeFrame;
    private:
        GLEEC_API static void beginFrame(size_t i);
        GLEEC_API static void endFrame(size_t i);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static void beginRendering(size_t i);

        GLEEC_API static bool batchSubmits();
        GLEEC_API static void batchPresents();

        GLEEC_API static bool justRendered;

        GLEEC_API static std::bitset<GLEEC_WINDOW_MAX_WINDOWS> recreateFlags;

        GLEEC_API static void recreateFrameInternal(size_t i);

    #if GLEEC_USE_FRAMES_IN_FLIGHT
        GLEEC_API static uint32_t lastFrame;

        GLEEC_API static std::array<Internal::Graphics::vk::Fence,
            Frame::FRAMES_IN_FLIGHT> fences;
    #else
        GLEEC_API static Internal::Graphics::vk::Fence fence;
    #endif
#endif
    };
}
