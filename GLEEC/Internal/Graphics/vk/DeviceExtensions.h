#pragma once

#include "InstanceExtensions.h"

namespace GLEEC::Internal::Graphics::vk
{
    struct DeviceExtensionProperties
    {
        static std::vector<VkExtensionProperties> enumerateExtensionProperties(VkPhysicalDevice physicalDevice)
        {
            uint32_t count = 0;
            CHECK_VK(vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, nullptr));
            
            std::vector<VkExtensionProperties> properties(count);
            CHECK_VK(vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, properties.data()));

            return properties;
        }

        static std::vector<const char*> availableRequestedExtensions(VkPhysicalDevice physicalDevice,
            const std::vector<const char*>& requested = requestedExtensions())
        {
            std::vector<const char*> available = {};

            const std::vector<VkExtensionProperties> extensions = enumerateExtensionProperties(physicalDevice);
            for (const char* rExtension : requested)
            {
                for (const VkExtensionProperties& extension : extensions)
                {
                    if (std::string_view(rExtension) == extension.extensionName)
                    {
                        available.push_back(rExtension);

                        LOG_INFO("Vulkan: requested (device) extension: \"{}\" found!", rExtension);

                        goto found;
                    }
                }

                LOG_WARNING("Vulkan: requested (device) extension: \"{}\" not found!", rExtension);

            found:
                continue;
            }

            return available;
        }

        GLEEC_API static std::vector<const char*> requestedExtensions();
    };
}
