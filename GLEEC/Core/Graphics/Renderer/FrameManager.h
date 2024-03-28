#pragma once

#include "Core/Window/WindowManager.h"
#include "Frame.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Fence.h"
#endif

namespace GLEEC::Graphics
{
    struct FrameManager
    {
        GLEEC_API static void init();
        GLEEC_API static void destroy();

        GLEEC_API static void begin();
        GLEEC_API static void end();

        GLEEC_API static FrameData& frame(size_t i);

        GLEEC_API static std::array<Frame, GLEEC_WINDOW_MAX_WINDOWS> frames;

#if GLEEC_USE_FRAMES_IN_FLIGHT
        GLEEC_API static uint32_t activeFrame;
#endif

    private:
        GLEEC_API static void beginFrame();
        GLEEC_API static void endFrame();

        GLEEC_API static void destroyFrame(size_t i);
        GLEEC_API static void initFrame(size_t i);

#if GLEEC_USE_FRAMES_IN_FLIGHT
        GLEEC_API static uint32_t lastFrame;
#endif

        GLEEC_API static bool justRendered;

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static bool batchSubmits();
        GLEEC_API static void batchPresents();

#if GLEEC_USE_FRAMES_IN_FLIGHT
        GLEEC_API static std::array<
            Internal::Graphics::vk::Fence, Frame::FRAMES_IN_FLIGHT> fences;
#else
        GLEEC_API static Internal::Graphics::vk::Fence fence;
#endif
#endif

        friend struct Window::WindowManager;
    };
}
