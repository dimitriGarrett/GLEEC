#pragma once

#include "DescriptorSetLayout.h"
#include "Device.h"

#include "helpers/align.h"

#include "Extensions.h"

namespace GLEEC::Internal::Graphics::vk
{
    // all the information for a descriptor buffer
    // to handle a descriptorSetLayout
    struct DescriptorBufferDescriptorSetLayout
    {
        VkDescriptorSetLayout layout = {};

        VkDeviceSize size = {};

        VkDeviceSize alignment = {};
        VkDeviceSize offset = {};
    };

    inline VkPhysicalDeviceDescriptorBufferPropertiesEXT getPhysicalDeviceDescriptorBufferProperties(
        VkPhysicalDevice physicalDevice)
    {
        VkPhysicalDeviceDescriptorBufferPropertiesEXT properties = {
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_PROPERTIES_EXT
        };

        getPhysicalDeviceProperties2(physicalDevice, &properties);

        return properties;
    }

    inline VkDeviceSize getDescriptorSetLayoutSize(VkDevice device,
        VkDescriptorSetLayout layout)
    {
        VkDeviceSize size = 0;

        vkGetDescriptorSetLayoutSizeEXT(device, layout, &size);

        return size;
    }

    inline VkDeviceSize getDescriptorSetLayoutAlignedSize(VkDevice device,
        VkDescriptorSetLayout layout, VkDeviceSize alignment)
    {
        return alignedSize(getDescriptorSetLayoutSize(device, layout),
            alignment);
    }

    inline VkDeviceSize getDescriptorSetLayoutAlignedSize(
        VkPhysicalDevice physicalDevice, VkDevice device,
        VkDescriptorSetLayout layout)
    {
        return alignedSize(getDescriptorSetLayoutSize(device, layout),
            getPhysicalDeviceDescriptorBufferProperties(physicalDevice).
                descriptorBufferOffsetAlignment);
    }

    inline VkDeviceSize getDescriptorSetLayoutAlignedSize(const Device& device,
        VkDescriptorSetLayout layout)
    {
        return getDescriptorSetLayoutAlignedSize(
            device.physicalDevice, device.device, layout);
    }

    inline VkDeviceSize getDescriptorSetLayoutBindingOffset(
        VkDevice device,
        uint32_t binding, VkDescriptorSetLayout layout)
    {
        VkDeviceSize offset = 0;

        vkGetDescriptorSetLayoutBindingOffsetEXT(device, layout,
            binding, &offset);

        return offset;
    }

    inline DescriptorBufferDescriptorSetLayout getDescriptorBufferDescriptorSetLayout(
        VkPhysicalDevice physicalDevice, VkDevice device,
        uint32_t binding, VkDescriptorSetLayout setLayout)
    {
        DescriptorBufferDescriptorSetLayout layout = {};

        layout.offset = getDescriptorSetLayoutBindingOffset(device,
            binding, setLayout);

        layout.alignment = 
            getPhysicalDeviceDescriptorBufferProperties(physicalDevice).
                descriptorBufferOffsetAlignment;

        layout.size = getDescriptorSetLayoutAlignedSize(device,
            setLayout, layout.alignment);

        layout.layout = setLayout;

        return layout;
    }

    inline VkDeviceSize getDescriptorSize(VkPhysicalDevice physicalDevice,
        VkDescriptorType descriptorType)
    {
        VkPhysicalDeviceDescriptorBufferPropertiesEXT properties =
            getPhysicalDeviceDescriptorBufferProperties(physicalDevice);

        switch (descriptorType)
        {
        case VK_DESCRIPTOR_TYPE_SAMPLER: return 
            properties.samplerDescriptorSize;
        case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER: return 
            properties.combinedImageSamplerDescriptorSize;
        case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE: return 
            properties.sampledImageDescriptorSize;
        case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE: return 
            properties.storageImageDescriptorSize;
        case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER: return 
            properties.uniformTexelBufferDescriptorSize;
        /* case VK_DESCRIPTOR_TYPE_ROBUST_UNIFORM_TEXEL_BUFFER: return 
            properties.uniformTexelBufferDescriptorSize; */
        case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER: return 
            properties.storageTexelBufferDescriptorSize;
        /* case VK_DESCRIPTOR_TYPE_ROBUST_STORAGE_TEXEL_BUFFER: return 
            properties.storageTexelBufferDescriptorSize; */
        case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER: return 
            properties.uniformBufferDescriptorSize;
        /* case VK_DESCRIPTOR_TYPE_ROBUST_UNIFORM_BUFFER: return 
            properties.uniformBufferDescriptorSize; */
        case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER: return 
            properties.storageBufferDescriptorSize;
        /* case VK_DESCRIPTOR_TYPE_ROBUST_STORAGE_BUFFER: return 
            properties.storageBufferDescriptorSize; */
        case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT: return 
            properties.inputAttachmentDescriptorSize;
        case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR: return 
            properties.accelerationStructureDescriptorSize;
        default: abort(); return 0;
        };
    }
}
