#include "Surface.h"

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_WINDOW_BACKEND == GRAPHICS_WINDOW_BACKEND_GLFW
#include "Internal/Graphics/Backends/glfw.h"
#endif

namespace GLEEC::Internal::Graphics::vk
{
#if GLEEC_GRAPHICS_WINDOW_BACKEND == GRAPHICS_WINDOW_BACKEND_GLFW
    inline Surface createSurface(VkInstance instance, GLFWwindow* window)
    {
        Surface surface = {};

        CHECK_VK(glfwCreateWindowSurface(instance, window, nullptr, &surface));

        return surface;
    }
#endif
}
