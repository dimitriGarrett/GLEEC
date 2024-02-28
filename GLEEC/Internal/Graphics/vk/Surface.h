#pragma once

#include "Config/Export.h"
#include "Instance.h"

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_WINDOW_BACKEND == GRAPHICS_WINDOW_BACKEND_GLFW
struct GLFWwindow;
#endif

namespace GLEEC::Internal::Graphics::vk
{
    using Surface = VkSurfaceKHR;

#if GLEEC_GRAPHICS_WINDOW_BACKEND == GRAPHICS_WINDOW_BACKEND_GLFW
    GLEEC_API Surface createSurface(VkInstance instance, GLFWwindow* window);
#endif

    inline void destroySurface(VkInstance instance, const Surface& surface)
    {
        vkDestroySurfaceKHR(instance, surface, nullptr);
    }
}
