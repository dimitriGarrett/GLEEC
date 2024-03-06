#include "PhysicalDeviceFeatures.h"

namespace GLEEC::Internal::Graphics::vk
{
    std::vector<PhysicalDeviceFeature> PhysicalDeviceFeatures::requestedFeatures()
    {
        static VkPhysicalDeviceBufferDeviceAddressFeatures deviceAddressFeatures = {
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES
        };
        deviceAddressFeatures.bufferDeviceAddress = VK_TRUE;

        static VkPhysicalDeviceDescriptorBufferFeaturesEXT descriptorBufferFeatures = {
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_FEATURES_EXT
        };
        descriptorBufferFeatures.descriptorBuffer = VK_TRUE;

        static VkPhysicalDeviceVulkan13Features features13 = {
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES
        };
        features13.synchronization2 = VK_TRUE;
        features13.dynamicRendering = VK_TRUE;

        static VkPhysicalDeviceShaderObjectFeaturesEXT shaderObjectFeatures = {
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT
        };
        shaderObjectFeatures.shaderObject = VK_TRUE;

        return
        {
            PhysicalDeviceFeature
            {
                &deviceAddressFeatures,
                {
                    &deviceAddressFeatures.bufferDeviceAddress
                },
#if GLEEC_DEBUG
                "VkPhysicalDeviceBufferDeviceAddressFeatures"
#endif
            },

            PhysicalDeviceFeature
            {
                &descriptorBufferFeatures,
                {
                    &descriptorBufferFeatures.descriptorBuffer
                },
#if GLEEC_DEBUG
                "VkPhysicalDeviceDescriptorBufferFeaturesEXT"
#endif
            },

            PhysicalDeviceFeature
            {
                &features13,
                {
                    &features13.synchronization2,
                    &features13.dynamicRendering,
                },

#if GLEEC_DEBUG
                "VkPhysicalDeviceVulkan13Features",
#endif
            },

            PhysicalDeviceFeature
            {
                &shaderObjectFeatures,
                {
                    &shaderObjectFeatures.shaderObject
                },

#if GLEEC_DEBUG
                "VkPhysicalDeviceShaderObjectFeatures",
#endif
            },
        };
    }
}
