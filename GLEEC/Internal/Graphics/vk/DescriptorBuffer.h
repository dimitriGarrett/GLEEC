#pragma once

#include "Descriptor.h"
#include "Internal/Graphics/vk/Buffer.h"
#include "Internal/Graphics/vk/helpers/CHECK_VK.h"

#define GLEEC_DEFAULT_DESCRIPTOR_BUFFER_SIZE 32

namespace GLEEC::Internal::Graphics::vk
{
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

        // layout stores how big the descriptor set layout is
        DescriptorBufferDescriptorSetLayout layout = {};

        operator VkBuffer() const
        {
            return buffer;
        }
    };

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
            all | VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT;
        default: return all;
        };
    }

    inline DescriptorBuffer createDescriptorBuffer(
        VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device,
        Allocator& allocator, VkDescriptorType descriptorType,
        uint32_t binding, VkDescriptorSetLayout layout,
        VkDeviceSize startingDescriptors = GLEEC_DEFAULT_DESCRIPTOR_BUFFER_SIZE)
    {
        DescriptorBuffer descriptorBuffer = {};

        descriptorBuffer.descriptorType = descriptorType;
        descriptorBuffer.descriptorSize =
            getDescriptorSize(physicalDevice, descriptorType);

        descriptorBuffer.descriptors = startingDescriptors;
        descriptorBuffer.capacity = startingDescriptors * 2;

        descriptorBuffer.layout = getDescriptorBufferDescriptorSetLayout(
            instance, physicalDevice, device, binding, layout);

        descriptorBuffer.buffer = createBuffer(allocator, createBuffer(
            descriptorBuffer.descriptors * descriptorBuffer.layout.size,
            getDescriptorBufferFlags(descriptorType)), VMA_MEMORY_USAGE_CPU_TO_GPU);

        mapMemory(allocator, descriptorBuffer.buffer);

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

    inline VkDescriptorGetInfoEXT getCombinedImageSamplerDescriptorGetInfo(
        VkSampler sampler, VkImageView imageView,
        VkImageLayout imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
    {
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

        return getInfo;
    }

    inline VkDescriptorGetInfoEXT getUniformBufferDescriptorGetInfo(
        VkDevice device, VkBuffer buffer, VkDeviceSize range)
    {
        VkDescriptorAddressInfoEXT addrInfo = {
            VK_STRUCTURE_TYPE_DESCRIPTOR_ADDRESS_INFO_EXT
        };

        addrInfo.address = getBufferDeviceAddress(device, buffer);
        addrInfo.range = range;
        addrInfo.format = VK_FORMAT_UNDEFINED;

        VkDescriptorGetInfoEXT getInfo = {
            VK_STRUCTURE_TYPE_DESCRIPTOR_GET_INFO_EXT
        };
        
        getInfo.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        getInfo.data.pUniformBuffer = &addrInfo;

        return getInfo;
    }

    inline VkDescriptorGetInfoEXT getUniformBufferDescriptorGetInfo(
        VkDevice device, const DescriptorBuffer& descriptorBuffer)
    {
        return getUniformBufferDescriptorGetInfo(device, descriptorBuffer,
            descriptorBuffer.capacity * descriptorBuffer.descriptorSize);
    }

    // returns the index of the descriptor
    inline uint32_t getDescriptor(VkInstance instance,
        VkPhysicalDevice physicalDevice, VkDevice device,
        Allocator& allocator, VkDescriptorGetInfoEXT getInfo,
        DescriptorBuffer& descriptorBuffer)
    {
        // reallocate and resize
        if (descriptorBuffer.descriptors >= descriptorBuffer.capacity)
        {
            descriptorBuffer.capacity <<= 1; // *= 2

            DescriptorBuffer buffer = createDescriptorBuffer(
                instance, physicalDevice, device, allocator,
                descriptorBuffer.descriptorType, descriptorBuffer.binding,
                descriptorBuffer.layout.layout, descriptorBuffer.capacity);

            memcpy_s(buffer.buffer.map, descriptorBuffer.descriptors *
                descriptorBuffer.descriptorSize, descriptorBuffer.buffer.map,
                descriptorBuffer.descriptors * descriptorBuffer.descriptorSize);

            destroyDescriptorBuffer(allocator, descriptorBuffer);
            descriptorBuffer = buffer;
        }

        getDescriptor(physicalDevice, device, getInfo,
            descriptorBuffer.descriptorType,
            descriptorBuffer.buffer.map + descriptorBuffer.descriptors *
            descriptorBuffer.descriptorSize + descriptorBuffer.layout.offset);

        return ++descriptorBuffer.descriptors;
    }

    inline uint32_t getUniformBufferDescriptor(VkInstance instance,
        VkPhysicalDevice physicalDevice, VkDevice device,
        Allocator& allocator, DescriptorBuffer& descriptorBuffer)
    {
        return getDescriptor(instance, physicalDevice, device, allocator,
            getUniformBufferDescriptorGetInfo(device, descriptorBuffer),
            descriptorBuffer);
    }

    inline uint32_t getCombinedImageSamplerDescriptor(VkInstance instance,
        VkPhysicalDevice physicalDevice, VkDevice device,
        Allocator& allocator, DescriptorBuffer& descriptorBuffer,
        VkSampler sampler, VkImageView imageView,
        VkImageLayout imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
    {
        return getDescriptor(instance, physicalDevice, device, allocator,
            getCombinedImageSamplerDescriptorGetInfo(sampler, imageView, imageLayout),
            descriptorBuffer);
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

    inline void cmdBindDescriptorBuffers(VkInstance instance, VkDevice device,
        VkCommandBuffer commandBuffer,
        const std::vector<DescriptorBuffer>& descriptorBuffers)
    {
        size_t size = descriptorBuffers.size();
        std::vector<VkDescriptorBufferBindingInfoEXT> bindings(size);

        for (size_t i = 0; i < size; ++i)
        {
            bindings[i].sType = VK_STRUCTURE_TYPE_DESCRIPTOR_BUFFER_BINDING_INFO_EXT;
            bindings[i].address = getBufferDeviceAddress(device,
                descriptorBuffers[i]);
            bindings[i].usage = descriptorBuffers[i].buffer.usage;
        }

        cmdBindDescriptorBuffers(instance, commandBuffer, bindings);
    }

    inline void cmdBindDescriptorBuffers(VkInstance instance, VkDevice device,
        VkCommandBuffer commandBuffer, const DescriptorBuffer& descriptorBuffer)
    {
        cmdBindDescriptorBuffers(instance, device, commandBuffer, std::vector<
            DescriptorBuffer>{ descriptorBuffer });
    }

    inline void cmdSetDescriptorBufferOffsets(
        VkInstance instance, VkCommandBuffer commandBuffer,
        VkPipelineBindPoint bindPoint, VkPipelineLayout pipelineLayout,
        uint32_t firstSet, uint32_t setCount, const uint32_t* bufferIndices,
        const VkDeviceSize* offsets)
    {
        vkCmdSetDescriptorBufferOffsetsEXT(commandBuffer, bindPoint,
            pipelineLayout, firstSet, setCount, bufferIndices, offsets);
    }

    inline void cmdSetDescriptorBufferOffsets(
        VkInstance instance, VkCommandBuffer commandBuffer,
        VkPipelineBindPoint bindPoint, VkPipelineLayout pipelineLayout,
        uint32_t firstSet, uint32_t setCount, const uint32_t& bufferIndex,
        const VkDeviceSize* offsets)
    {
        cmdSetDescriptorBufferOffsets(instance, commandBuffer,
            bindPoint, pipelineLayout, firstSet,
            setCount, &bufferIndex, offsets);
    }

    inline void cmdSetDescriptorBufferOffsets(
        VkInstance instance, VkCommandBuffer commandBuffer,
        VkPipelineBindPoint bindPoint, VkPipelineLayout pipelineLayout,
        uint32_t firstSet, uint32_t setCount, const uint32_t& bufferIndex,
        VkDeviceSize& offsets)
    {
        cmdSetDescriptorBufferOffsets(instance, commandBuffer,
            bindPoint, pipelineLayout, firstSet,
            setCount, &bufferIndex, &offsets);
    }

    inline void cmdSetGraphicsPipelineDescriptorBufferOffsets(
        VkInstance instance, VkCommandBuffer commandBuffer,
        VkPipelineLayout pipelineLayout, uint32_t firstSet,
        uint32_t setCount, const uint32_t* bufferIndices, const VkDeviceSize* offsets)
    {
        cmdSetDescriptorBufferOffsets(instance, commandBuffer,
            VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, firstSet, setCount,
            bufferIndices, offsets);
    }

    inline void cmdSetGraphicsPipelineDescriptorBufferOffsets(
        VkInstance instance, VkCommandBuffer commandBuffer,
        VkPipelineLayout pipelineLayout, uint32_t firstSet,
        uint32_t setCount, const uint32_t& bufferIndex, const VkDeviceSize* offsets)
    {
        cmdSetGraphicsPipelineDescriptorBufferOffsets(instance, commandBuffer,
            pipelineLayout, firstSet, setCount, &bufferIndex, offsets);
    }

    inline void cmdSetGraphicsPipelineDescriptorBufferOffsets(
        VkInstance instance, VkCommandBuffer commandBuffer,
        VkPipelineLayout pipelineLayout, uint32_t firstSet,
        uint32_t setCount, const uint32_t& bufferIndex, const VkDeviceSize& offsets)
    {
        cmdSetGraphicsPipelineDescriptorBufferOffsets(instance, commandBuffer,
            pipelineLayout, firstSet, setCount, &bufferIndex, &offsets);
    }

    inline void cmdSetComputePipelineDescriptorBufferOffsets(
        VkInstance instance, VkCommandBuffer commandBuffer,
        VkPipelineLayout pipelineLayout, uint32_t firstSet,
        uint32_t setCount, const uint32_t* bufferIndices, const VkDeviceSize* offsets)
    {
        cmdSetDescriptorBufferOffsets(instance, commandBuffer,
            VK_PIPELINE_BIND_POINT_COMPUTE, pipelineLayout, firstSet, setCount,
            bufferIndices, offsets);
    }

    inline void cmdSetComputePipelineDescriptorBufferOffsets(
        VkInstance instance, VkCommandBuffer commandBuffer,
        VkPipelineLayout pipelineLayout, uint32_t firstSet,
        uint32_t setCount, const uint32_t& bufferIndex, const VkDeviceSize* offsets)
    {
        cmdSetComputePipelineDescriptorBufferOffsets(instance, commandBuffer,
            pipelineLayout, firstSet, setCount, &bufferIndex, offsets);
    }

    inline void cmdSetComputePipelineDescriptorBufferOffsets(
        VkInstance instance, VkCommandBuffer commandBuffer,
        VkPipelineLayout pipelineLayout, uint32_t firstSet,
        uint32_t setCount, const uint32_t& bufferIndex, const VkDeviceSize& offsets)
    {
        cmdSetComputePipelineDescriptorBufferOffsets(instance, commandBuffer,
            pipelineLayout, firstSet, setCount, &bufferIndex, &offsets);
    }
}
