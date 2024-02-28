#pragma once

#include "PhysicalDevice.h"

namespace GLEEC::Internal::Graphics::vk
{
    struct PhysicalDeviceFeature
    {
        void* feature;

        std::vector<VkBool32*> references = {};

#if GLEEC_DEBUG
        const char* name = "unknown feature";
#endif
    };

    struct PhysicalDeviceFeaturesChain
    {
        VkPhysicalDeviceFeatures2 features = {};

        pNextChain chain = {};
    };

    struct PhysicalDeviceFeatures
    {
        static PhysicalDeviceFeaturesChain availableRequestedFeatures(
            VkPhysicalDevice physicalDevice,
            const std::vector<PhysicalDeviceFeature>& requested = requestedFeatures())
        {
            PhysicalDeviceFeaturesChain chain = {};
            for (const PhysicalDeviceFeature& feature : requested)
            {
                chain.chain.add(feature.feature);
            }

            chain.features = getPhysicalDeviceFeatures2(physicalDevice, chain.chain.base);

            chain.chain.add_front(chain.features);

#if GLEEC_DEBUG
            bool allSupported = true;
#endif
            for (const PhysicalDeviceFeature& feature : requested)
            {
                for (VkBool32* ensured : feature.references)
                {
                    if (!(*ensured))
                    {
// log isnt defined during debug, but feature doesnt have name in release
#if GLEEC_DEBUG
                        LOG_WARNING("Vulkan: device feature: {} was not supported on physical device: {}!",
                            feature.name, static_cast<void*>(physicalDevice));

                        allSupported = false;
#endif
                    }
                }
            }

#if GLEEC_DEBUG
            if (allSupported)
            {
                LOG_INFO("Vulkan: all device features were supported on physical device: {}!",
                    static_cast<void*>(physicalDevice));
            }

            else
            {
                LOG_INFO("Vulkan: not all device features were supported on physical device: {}!",
                    static_cast<void*>(physicalDevice));
            }
#endif

            return chain;
        }

        GLEEC_API static std::vector<PhysicalDeviceFeature> requestedFeatures();
    };

    //inline pNextChain physicalDeviceFeatures
/*
    struct PhysicalDeviceFeature
    {
        char* features = {};
        size_t offset = 0;

        bool compare() const
        {
            return *reinterpret_cast<VkBool32*>(features + offset);
        }
    };

    struct PhysicalDeviceFeatures
    {
        static std::vector<PhysicalDeviceFeatures> availableRequestedFeatures(
            VkPhysicalDevice physicalDevice,
            const std::vector<PhysicalDeviceFeature>& requested = requestedFeatures())
        {
            pNextChain chain = {};
            for (const PhysicalDeviceFeature& feature : requested)
            {
                chain.add(feature);
            }

            VkPhysicalDeviceFeatures2 physicalDeviceFeatures =
                getPhysicalDeviceFeatures2(physicalDevice, chain.base);

            std::vector<PhysicalDeviceFeature

            for (const PhysicalDeviceFeature& feature : requested)
            {
                if (!feature.compare())
                {
                    LOG_WARNING("Vulkan: a requested device feature was not found!");
                }
            }
        }

        GLEEC_API static std::vector<PhysicalDeviceFeature> requestedFeatures();
    }; */
}
