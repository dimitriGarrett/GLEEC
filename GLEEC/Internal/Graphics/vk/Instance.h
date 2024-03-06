#pragma once

#include "AppInfo.h"

#include "helpers/pNextChain.h"
#include "helpers/CHECK_VK.h"

#include "InstanceLayers.h"
#include "InstanceExtensions.h"

#if GLEEC_DEBUG
#include "DebugUtilsMessenger.h"
#endif

namespace GLEEC::Internal::Graphics::vk
{
    struct Instance
    {
        VkInstance instance = {};

#if GLEEC_DEBUG
        DebugUtilsMessenger messenger = {};
#endif

        operator VkInstance() const
        {
            return instance;
        }
    };

    // default appInfo fills all data anyways
    inline Instance createInstance(const AppInfo& appInfo = {})
    {
        VkInstanceCreateInfo info = {
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO
        };

        info.flags = 0;
        info.pApplicationInfo = &appInfo.appInfo;

        std::vector<const char*> layers = InstanceLayerProperties::availableRequestedLayers();
        std::vector<const char*> extensions = InstanceExtensionProperties::availableRequestedExtensions();

        info.enabledLayerCount = static_cast<uint32_t>(layers.size());
        info.ppEnabledLayerNames = layers.data();

        info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        info.ppEnabledExtensionNames = extensions.data();

        pNextChain chain = {};

        // its really annoying, even in debug lol
#define ALLOW_ANNOYING_VULKAN_LOGGING 1
#if ALLOW_ANNOYING_VULKAN_LOGGING
        VkDebugUtilsMessengerCreateInfoEXT messenger = DebugMessenger::instanceCreateInfo();
        chain.add(messenger);
#endif

#if GLEEC_DEBUG
        VkValidationFeatureEnableEXT enable[] = {
            VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT,
            // incompatible with shader objects
            //VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
        };
#else
        VkValidationFeatureDisableEXT disable[] = {
            VK_VALIDATION_FEATURE_DISABLE_ALL_EXT
        };
#endif

        VkValidationFeaturesEXT validationFeatures = {
            VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT
        };

#if GLEEC_DEBUG
        validationFeatures.enabledValidationFeatureCount = sizeof(enable) / sizeof(enable[0]);
        validationFeatures.pEnabledValidationFeatures = enable;
#else
        validationFeatures.disabledValidationFeatureCount = sizeof(disable) / sizeof(disable[0]);
        validationFeatures.pDisabledValidationFeatures = disable;
#endif

        chain.add(validationFeatures);
        chain.apply(info);

        Instance instance = {};
        CHECK_VK(vkCreateInstance(&info, nullptr, &instance.instance));

#if GLEEC_DEBUG
        instance.messenger = createDebugUtilsMessenger(instance.instance);
#endif

        return instance;
    }

    inline void destroyInstance(const Instance& instance)
    {
#if GLEEC_DEBUG
        destroyDebugUtilsMessenger(instance, instance.messenger);
#endif

        vkDestroyInstance(instance.instance, nullptr);
    }

    inline uint32_t instanceSupportedApiVersion()
    {
        uint32_t temp = 0;
        CHECK_VK(vkEnumerateInstanceVersion(&temp));
        return temp;
    }

    inline uint32_t instanceSupportedApiVersionMajor()
    {
        return VK_API_VERSION_MAJOR(instanceSupportedApiVersion());
    }

    inline uint32_t instanceSupportedApiVersionMinor()
    {
        return VK_API_VERSION_MINOR(instanceSupportedApiVersion());
    }

    inline uint32_t instanceSupportedApiVersionVariant()
    {
        return VK_API_VERSION_VARIANT(instanceSupportedApiVersion());
    }
}
