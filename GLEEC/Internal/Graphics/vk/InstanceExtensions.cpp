#include "InstanceExtensions.h"

#include "Internal/Input/Backend.h"

// only use glfw if it is actually used
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/Backends/GLFW.h"
#define GLFW_USED 1
#else
#include "Internal/Window/Backend.h"
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
#include "Internal/Window/Backends/GLFW.h"
#define GLFW_USED 1
#endif
#endif

namespace GLEEC::Internal::Graphics::vk
{
    std::vector<const char*> InstanceExtensionProperties::requestedExtensions()
    {
        std::vector<const char*> extensions = {};
#if GLFW_USED
        uint32_t count = 0;
        const char** temp = glfwGetRequiredInstanceExtensions(&count);

        if (count == 0)
        {
            LOG_INFO("No glfw instance extensions needed? (is that bad?)");
        }
        
        else
        {
            extensions = std::vector<const char*>(temp, temp + count);

            for (const char* extension : extensions)
            {
                LOG_INFO("glfw required extension: {}", extension);
            }
        }
#endif

// only want debug utils if debugging because they are annoying and slow
#if GLEEC_DEBUG
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        //extensions.push_back(VK_EXT_DEVICE_ADDRESS_BINDING_REPORT_EXTENSION_NAME);
#endif
        
#if GLEEC_VK_USE_PRESENT_SCALING
        // stuff for swapchain scaling
        extensions.push_back(VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME);
        extensions.push_back(VK_EXT_SURFACE_MAINTENANCE_1_EXTENSION_NAME);
#endif

        return extensions;
    }
}
