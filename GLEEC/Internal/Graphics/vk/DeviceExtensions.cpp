#include "DeviceExtensions.h"

namespace GLEEC::Internal::Graphics::vk
{
    inline std::vector<const char*> DeviceExtensionProperties::requestedExtensions()
    {
        // dont know when the preprocessor guards wont be defined but its here just in case
        return
        {
#if VK_KHR_swapchain
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
#endif

#if VK_EXT_descriptor_buffer
            VK_EXT_DESCRIPTOR_BUFFER_EXTENSION_NAME,
#endif

#if GLEEC_DEBUG && VK_NV_device_diagnostics_config
            VK_NV_DEVICE_DIAGNOSTICS_CONFIG_EXTENSION_NAME,
#endif

/*             VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME, */
        };
    }
}
