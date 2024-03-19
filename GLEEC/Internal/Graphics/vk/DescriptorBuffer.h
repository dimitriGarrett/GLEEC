#pragma once

#include "Descriptor.h"
#include "Internal/Graphics/vk/Buffer.h"
#include "Internal/Graphics/vk/helpers/CHECK_VK.h"

#include "Internal/Graphics/vk/Extensions.h"

#define GLEEC_DEFAULT_DESCRIPTOR_BUFFER_SIZE 32

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

    struct DescriptorBuffer
    {
        Buffer buffer = {};

        VkDescriptorType descriptorType = {};
        // the size of the descriptors inside
        VkDeviceSize descriptorSize = {};

        // how many vs capacity
        VkDeviceSize descriptors = {};
        VkDeviceSize capacity = {};

        // binding in the descriptor set
        uint32_t binding = 0;

        VkDeviceSize address = {};

        // layout stores how big the descriptor set layout is
        DescriptorBufferDescriptorSetLayout layout = {};
    };

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

    inline VkBufferUsageFlags getDescriptorBufferFlags(
        VkDescriptorType descriptorType)
    {
        constexpr VkBufferUsageFlags all =
            VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT |
            VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;

        switch (descriptorType)
        {
        case VK_DESCRIPTOR_TYPE_SAMPLER:
        case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
        
        // unsure if sampled image should be included. oh well!
        case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE: return
            all | VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT;
        default: return all;
        };
    }

    inline DescriptorBuffer createDescriptorBuffer(
        VkPhysicalDevice physicalDevice, VkDevice device,
        Allocator& allocator, VkDescriptorType descriptorType,
        uint32_t binding, VkDescriptorSetLayout layout,
        VkDeviceSize startingDescriptors = GLEEC_DEFAULT_DESCRIPTOR_BUFFER_SIZE)
    {
        DescriptorBuffer descriptorBuffer = {};

        descriptorBuffer.descriptorType = descriptorType;
        descriptorBuffer.descriptorSize =
            getDescriptorSize(physicalDevice, descriptorType);

        //descriptorBuffer.descriptors = startingDescriptors;
        descriptorBuffer.capacity = startingDescriptors * 2;

        descriptorBuffer.layout = getDescriptorBufferDescriptorSetLayout(
            physicalDevice, device, binding, layout);

        descriptorBuffer.buffer = createBuffer(allocator, createBuffer(
            descriptorBuffer.capacity * descriptorBuffer.layout.size,
            getDescriptorBufferFlags(descriptorType)), VMA_MEMORY_USAGE_CPU_TO_GPU);

        mapMemory(allocator, descriptorBuffer.buffer);

        descriptorBuffer.address = getBufferDeviceAddress(device,
            descriptorBuffer.buffer);

        return descriptorBuffer;
    }

    inline void destroyDescriptorBuffer(Allocator& allocator,
        DescriptorBuffer& descriptorBuffer)
    {
        destroyBuffer(allocator, descriptorBuffer.buffer);
    }

    inline void getDescriptor(VkDevice device,
        const VkDescriptorGetInfoEXT& getInfo,
        VkDeviceSize descriptorSize, void* where)
    {
        vkGetDescriptorEXT(device, &getInfo, descriptorSize, where);
    }

    inline void getDescriptor(VkPhysicalDevice physicalDevice,
        VkDevice device, const VkDescriptorGetInfoEXT& getInfo,
        VkDescriptorType descriptorType, void* where)
    {
        getDescriptor(device, getInfo,
            getDescriptorSize(physicalDevice, descriptorType), where);
    }

    // returns the index of the descriptor
    inline void checkCapacity(
        VkPhysicalDevice physicalDevice, VkDevice device,
        Allocator& allocator, DescriptorBuffer& descriptorBuffer)
    {
        // reallocate and resize
        if (descriptorBuffer.descriptors >= descriptorBuffer.capacity)
        {
            descriptorBuffer.capacity <<= 1; // *= 2

            DescriptorBuffer buffer = createDescriptorBuffer(
                physicalDevice, device, allocator,
                descriptorBuffer.descriptorType, descriptorBuffer.binding,
                descriptorBuffer.layout.layout, descriptorBuffer.capacity);
            buffer.descriptors = descriptorBuffer.descriptors;

            memcpy_s(buffer.buffer.map, descriptorBuffer.descriptors *
                descriptorBuffer.descriptorSize, descriptorBuffer.buffer.map,
                descriptorBuffer.descriptors * descriptorBuffer.descriptorSize);

            destroyDescriptorBuffer(allocator, descriptorBuffer);
            descriptorBuffer = buffer;
        }
    }

    inline uint32_t getUniformBufferDescriptor(VkPhysicalDevice physicalDevice,
        VkDevice device, Allocator& allocator, DescriptorBuffer& descriptorBuffer,
        const Buffer& buffer)
    {
        checkCapacity(physicalDevice, device, allocator, descriptorBuffer);

        VkDescriptorAddressInfoEXT addrInfo = {
            VK_STRUCTURE_TYPE_DESCRIPTOR_ADDRESS_INFO_EXT
        };

        addrInfo.address = getBufferDeviceAddress(device, buffer);
        addrInfo.range = buffer.size;
        addrInfo.format = VK_FORMAT_UNDEFINED;

        VkDescriptorGetInfoEXT getInfo = {
            VK_STRUCTURE_TYPE_DESCRIPTOR_GET_INFO_EXT
        };
        
        getInfo.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        getInfo.data.pUniformBuffer = &addrInfo;

        getDescriptor(device, getInfo, descriptorBuffer.descriptorSize,
            descriptorBuffer.buffer.map + descriptorBuffer.descriptors *
            descriptorBuffer.layout.size + descriptorBuffer.layout.offset);

        return descriptorBuffer.descriptors++ * descriptorBuffer.descriptorSize;
    }

    inline uint32_t getCombinedImageSamplerDescriptor(
        VkPhysicalDevice physicalDevice, VkDevice device,
        Allocator& allocator, DescriptorBuffer& descriptorBuffer,
        VkSampler sampler, VkImageView imageView,
        VkImageLayout imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
    {
        checkCapacity(physicalDevice, device, allocator, descriptorBuffer);

        VkDescriptorImageInfo imageInfo = {
            sampler,
            imageView,
            imageLayout
        };

        VkDescriptorGetInfoEXT getInfo = {
            VK_STRUCTURE_TYPE_DESCRIPTOR_GET_INFO_EXT
        };

        getInfo.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        getInfo.data.pCombinedImageSampler = &imageInfo;

        getDescriptor(physicalDevice, device, getInfo,
            descriptorBuffer.descriptorType,
            descriptorBuffer.buffer.map + descriptorBuffer.descriptors *
            descriptorBuffer.descriptorSize + descriptorBuffer.layout.offset);

        return descriptorBuffer.descriptors++ * descriptorBuffer.descriptorSize;
    }

    inline void cmdBindDescriptorBuffers(VkCommandBuffer commandBuffer,
        const std::vector<VkDescriptorBufferBindingInfoEXT>& bindings)
    {
        vkCmdBindDescriptorBuffersEXT(commandBuffer,
            static_cast<uint32_t>(bindings.size()), bindings.data());
    }

    inline void cmdBindDescriptorBuffers(VkCommandBuffer commandBuffer,
        const VkDescriptorBufferBindingInfoEXT& binding)
    {
        cmdBindDescriptorBuffers(commandBuffer, std::vector<
            VkDescriptorBufferBindingInfoEXT>{ binding });
    }

    inline void cmdBindDescriptorBuffers(VkDevice device,
        VkCommandBuffer commandBuffer,
        const std::vector<DescriptorBuffer>& descriptorBuffers)
    {
        std::vector<VkDescriptorBufferBindingInfoEXT> bindings = {};

        for (const DescriptorBuffer& buffer : descriptorBuffers)
        {
            if (buffer.buffer == nullptr) continue;

            auto& binding = bindings.emplace_back();

            binding.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_BUFFER_BINDING_INFO_EXT;
            binding.address = buffer.address;

            constexpr VkBufferUsageFlags exclude =
                ~VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;

            binding.usage = buffer.buffer.usage & exclude;
        }

        vkCmdBindDescriptorBuffersEXT(commandBuffer,
            static_cast<uint32_t>(bindings.size()), bindings.data());
/*         cmdBindDescriptorBuffers(commandBuffer, bindings); */
    }

    inline void cmdBindDescriptorBuffer(VkDevice device,
        VkCommandBuffer commandBuffer, const DescriptorBuffer& descriptorBuffer)
    {
        cmdBindDescriptorBuffers(device, commandBuffer, std::vector<
            DescriptorBuffer>{ descriptorBuffer });
    }

    inline void cmdSetDescriptorBufferOffsets(
        VkCommandBuffer commandBuffer, VkPipelineBindPoint bindPoint,
        VkPipelineLayout pipelineLayout, uint32_t firstSet, uint32_t setCount,
        const uint32_t* bufferIndices, const VkDeviceSize* offsets)
    {
        vkCmdSetDescriptorBufferOffsetsEXT(commandBuffer, bindPoint,
            pipelineLayout, firstSet, setCount, bufferIndices, offsets);
    }

    inline void cmdSetDescriptorBufferOffsets(
        VkCommandBuffer commandBuffer, VkPipelineBindPoint bindPoint,
        VkPipelineLayout pipelineLayout, uint32_t firstSet, uint32_t setCount,
        const uint32_t& bufferIndex, const VkDeviceSize* offsets)
    {
        cmdSetDescriptorBufferOffsets(commandBuffer,
            bindPoint, pipelineLayout, firstSet,
            setCount, &bufferIndex, offsets);
    }

    inline void cmdSetDescriptorBufferOffsets(
        VkCommandBuffer commandBuffer, VkPipelineBindPoint bindPoint,
        VkPipelineLayout pipelineLayout, uint32_t firstSet, uint32_t setCount,
        const uint32_t& bufferIndex, const VkDeviceSize& offsets)
    {
        cmdSetDescriptorBufferOffsets(commandBuffer,
            bindPoint, pipelineLayout, firstSet,
            setCount, &bufferIndex, &offsets);
    }

    inline void cmdSetGraphicsPipelineDescriptorBufferOffsets(
        VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout,
        uint32_t firstSet, uint32_t setCount,
        const uint32_t* bufferIndices, const VkDeviceSize* offsets)
    {
        cmdSetDescriptorBufferOffsets(commandBuffer,
            VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, firstSet, setCount,
            bufferIndices, offsets);
    }

    inline void cmdSetGraphicsPipelineDescriptorBufferOffsets(
        VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout,
        uint32_t firstSet, uint32_t setCount,
        const uint32_t& bufferIndex, const VkDeviceSize* offsets)
    {
        cmdSetGraphicsPipelineDescriptorBufferOffsets(commandBuffer,
            pipelineLayout, firstSet, setCount, &bufferIndex, offsets);
    }

    inline void cmdSetGraphicsPipelineDescriptorBufferOffsets(
        VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout,
        uint32_t firstSet, uint32_t setCount,
        const uint32_t& bufferIndex, const VkDeviceSize& offsets)
    {
        cmdSetGraphicsPipelineDescriptorBufferOffsets(commandBuffer,
            pipelineLayout, firstSet, setCount, &bufferIndex, &offsets);
    }

    inline void cmdSetComputePipelineDescriptorBufferOffsets(
        VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout,
        uint32_t firstSet, uint32_t setCount,
        const uint32_t* bufferIndices, const VkDeviceSize* offsets)
    {
        cmdSetDescriptorBufferOffsets(commandBuffer,
            VK_PIPELINE_BIND_POINT_COMPUTE, pipelineLayout, firstSet, setCount,
            bufferIndices, offsets);
    }

    inline void cmdSetComputePipelineDescriptorBufferOffsets(
        VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout,
        uint32_t firstSet, uint32_t setCount,
        const uint32_t& bufferIndex, const VkDeviceSize* offsets)
    {
        cmdSetComputePipelineDescriptorBufferOffsets(commandBuffer,
            pipelineLayout, firstSet, setCount, &bufferIndex, offsets);
    }

    inline void cmdSetComputePipelineDescriptorBufferOffsets(
        VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout,
        uint32_t firstSet, uint32_t setCount,
        const uint32_t& bufferIndex, const VkDeviceSize& offsets)
    {
        cmdSetComputePipelineDescriptorBufferOffsets(commandBuffer,
            pipelineLayout, firstSet, setCount, &bufferIndex, &offsets);
    }
}
