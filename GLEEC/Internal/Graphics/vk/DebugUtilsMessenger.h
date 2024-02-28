#pragma once

#include "helpers/InstanceProcAddress.h"
#include "DebugMessenger.h"

namespace GLEEC::Internal::Graphics::vk
{
    using DebugUtilsMessenger = VkDebugUtilsMessengerEXT;

    inline DebugUtilsMessenger createDebugUtilsMessenger(VkInstance instance)
    {
        VkDebugUtilsMessengerCreateInfoEXT info = DebugMessenger::instanceCreateInfo();

        DebugUtilsMessenger messenger = {};
        CHECK_CALL_INSTANCE_PROC(instance, vkCreateDebugUtilsMessengerEXT, instance, &info, nullptr, &messenger);

        return messenger;
    }

    inline void destroyDebugUtilsMessenger(VkInstance instance, DebugUtilsMessenger messenger)
    {
        CALL_INSTANCE_PROC(instance, vkDestroyDebugUtilsMessengerEXT, instance, messenger, nullptr);
    }
}
