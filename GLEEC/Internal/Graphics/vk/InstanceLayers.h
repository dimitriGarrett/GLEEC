#pragma once

#include "Config/Export.h"
#include "Internal/Graphics/Backends/vk.h"

#include "Internal/Log/Log.h"
#include "helpers/CHECK_VK.h"

#include <vector>
#include <string_view>

namespace GLEEC::Internal::Graphics::vk
{
    struct InstanceLayerProperties
    {
        static std::vector<VkLayerProperties> enumerateLayerProperties()
        {
            uint32_t count = 0;
            CHECK_VK(vkEnumerateInstanceLayerProperties(&count, nullptr));

            std::vector<VkLayerProperties> layers(count);
            CHECK_VK(vkEnumerateInstanceLayerProperties(&count, layers.data()));
            
            return layers;
        }

        static std::vector<const char*> availableRequestedLayers(
            const std::vector<const char*>& requested = requestedLayers(),
            const std::vector<VkLayerProperties>& layers = enumerateLayerProperties())
        {
            std::vector<const char*> available = {};

            for (const char* rLayer : requested)
            {
                for (const VkLayerProperties& layer : layers)
                {
                    if (std::string_view(rLayer) == layer.layerName)
                    {
                        available.push_back(rLayer);

                        LOG_INFO("Vulkan: requested layer: \"{}\" found!", rLayer);

                        goto found;
                    }
                }

                LOG_WARNING("Vulkan: requested layer: \"{}\" not found!", rLayer);

            found:
                continue;
            }

            return available;
        }

        GLEEC_API static std::vector<const char*> requestedLayers();
    };
}
