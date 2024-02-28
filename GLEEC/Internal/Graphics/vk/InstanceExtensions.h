#pragma once

#include "InstanceLayers.h"

// it is helpful for coding, but not sure about the results
#define GLEEC_VK_USE_PRESENT_SCALING 1

namespace GLEEC::Internal::Graphics::vk
{
    struct InstanceExtensionProperties
    {
        static std::vector<VkExtensionProperties> enumerateLayerExtensionProperties(std::string_view layerName)
        {
            uint32_t count = 0;
            CHECK_VK(vkEnumerateInstanceExtensionProperties(layerName.data(), &count, nullptr));

            std::vector<VkExtensionProperties> extensions(count);
            CHECK_VK(vkEnumerateInstanceExtensionProperties(layerName.data(), &count, extensions.data()));

            return extensions;
        }

        static std::vector<VkExtensionProperties> enumerateGlobalExtensionProperties()
        {
            uint32_t count = 0;
            CHECK_VK(vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr));

            std::vector<VkExtensionProperties> extensions(count);
            CHECK_VK(vkEnumerateInstanceExtensionProperties(nullptr, &count, extensions.data()));
            
            return extensions;
        }

        static std::vector<VkExtensionProperties> enumerateAllExtensionProperties(
            const std::vector<VkLayerProperties>& layerProperties = InstanceLayerProperties::enumerateLayerProperties())
        {
            std::vector<VkExtensionProperties> extensions = enumerateGlobalExtensionProperties();

            for (const VkLayerProperties& layer : layerProperties)
            {
                for (const VkExtensionProperties& extension : enumerateLayerExtensionProperties(layer.layerName))
                {
                    extensions.push_back(extension);
                }
            }

            return extensions;
        }

        static std::vector<const char*> availableRequestedExtensions(
            const std::vector<const char*>& requested = requestedExtensions(),
            const std::vector<VkExtensionProperties>& extensions = enumerateAllExtensionProperties(InstanceLayerProperties::enumerateLayerProperties()))
        {
            std::vector<const char*> available = {};

            for (const char* rExtension : requested)
            {
                for (const VkExtensionProperties& extension : extensions)
                {
                    if (std::string_view(rExtension) == extension.extensionName)
                    {
                        available.push_back(rExtension);

                        LOG_INFO("Vulkan: requested (instance) extension: \"{}\" found!", rExtension);
                        goto found;
                    }
                }

                LOG_WARNING("Vulkan: requested (instance) extension: \"{}\" not found!", rExtension);

            found:
                continue;
            }

            return available;
        }

        GLEEC_API static std::vector<const char*> requestedExtensions();
    };
}
