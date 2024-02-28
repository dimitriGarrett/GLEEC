#pragma once

#include "Internal/Graphics/Backends/vk.h"
#include "Internal/Log/Log.h"

namespace GLEEC::Internal::Graphics::vk
{
    struct DebugMessenger
    {
        static VKAPI_ATTR VkBool32 VKAPI_CALL defaultDebugMessengerCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT severity,
            VkDebugUtilsMessageTypeFlagsEXT type,
            const VkDebugUtilsMessengerCallbackDataEXT* data,
            void* user_data)
        {
            if (severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
            {
                // warning is here instead of error because stuff can still
                // work with some vulkan errors, so just notify but dont crash
                LOG_WARNING("Vulkan Error: {}", data->pMessage);
            }

            else if (severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
            {
                LOG_WARNING("Vulkan Warning: {}", data->pMessage);
            }

            // verbose or init
            else
            {
                LOG_MESSAGE("Vulkan Info: {}", data->pMessage);
            }

            return VK_FALSE;
        }

        static VkDebugUtilsMessengerCreateInfoEXT instanceCreateInfo()
        {
            VkDebugUtilsMessengerCreateInfoEXT info = {
                VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT
            };

            info.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

            info.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;

            info.pfnUserCallback = &defaultDebugMessengerCallback;

            return info;
        }
    };
}
