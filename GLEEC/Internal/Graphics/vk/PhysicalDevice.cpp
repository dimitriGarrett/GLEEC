#include "PhysicalDevice.h"

namespace GLEEC::Internal::Graphics::vk
{
    inline bool physicalDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        return getPhysicalDeviceGraphicsQueueSurfaceSupport(physicalDevice, surface);
    }

#if GLEEC_GRAPHICS_WINDOW_BACKEND == GRAPHICS_WINDOW_BACKEND_GLFW
    PhysicalDevice bestPhysicalDevice(VkInstance instance, GLFWwindow* window)
    {
        VkSurfaceKHR surface = {};
        CHECK_VK(glfwCreateWindowSurface(instance, window, nullptr, &surface));

        PhysicalDevice best = bestPhysicalDevice(instance, surface);

        vkDestroySurfaceKHR(instance, surface, nullptr);

        return best;
    }
#endif
}
