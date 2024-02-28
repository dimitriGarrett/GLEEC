#pragma once

#include "CommandBuffer.h"

namespace GLEEC::Internal::Graphics::vk
{
    using CommandPool = VkCommandPool;

    inline CommandPool createCommandPool(VkDevice device, uint32_t queueFamilyIndex,
        VkCommandPoolCreateFlags flags = 0)
    {
        VkCommandPoolCreateInfo info = {
            VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO
        };

        info.queueFamilyIndex = queueFamilyIndex;
        info.flags = flags;

        CommandPool commandPool = {};
        CHECK_VK(vkCreateCommandPool(device, &info, nullptr, &commandPool));

        return commandPool;
    }

    inline CommandPool createTransientCommandPool(VkDevice device, uint32_t queueFamilyIndex)
    {
        return createCommandPool(device, queueFamilyIndex,
            VK_COMMAND_POOL_CREATE_TRANSIENT_BIT);
    }

    inline void destroyCommandPool(VkDevice device, VkCommandPool commandPool)
    {
        vkDestroyCommandPool(device, commandPool, nullptr);
    }

    inline void resetCommandPool(VkDevice device, VkCommandPool commandPool,
        VkCommandPoolResetFlags flags)
    {
        CHECK_VK(vkResetCommandPool(device, commandPool, flags));
    }

    inline void resetCommandPool(VkDevice device, VkCommandPool commandPool)
    {
        resetCommandPool(device, commandPool, 0);
    }

    inline void resetCommandPoolReleaseResources(VkDevice device, VkCommandPool commandPool)
    {
        resetCommandPool(device, commandPool,
            VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
    }

    inline VkCommandBufferAllocateInfo commandBufferAllocateInfo(
        VkCommandPool commandPool, uint32_t count,
        VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY)
    {
        return {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .pNext = nullptr,

            .commandPool = commandPool,
            .level = level,
            .commandBufferCount = count,
        };
    }

    inline VkCommandBufferAllocateInfo commandBufferAllocateInfo(
        VkCommandPool commandPool,
        VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY)
    {
        return commandBufferAllocateInfo(commandPool, 1, level);
    }

    inline VkCommandBufferAllocateInfo secondaryCommandBufferAllocateInfo(
        VkCommandPool commandPool, uint32_t count)
    {
        return commandBufferAllocateInfo(commandPool, count,
            VK_COMMAND_BUFFER_LEVEL_SECONDARY);
    }

    inline VkCommandBufferAllocateInfo secondaryCommandBufferAllocateInfo(
        VkCommandPool commandPool)
    {
        return commandBufferAllocateInfo(commandPool, 1,
            VK_COMMAND_BUFFER_LEVEL_SECONDARY);
    }

    inline CommandBuffer allocateCommandBuffer(VkDevice device,
        const VkCommandBufferAllocateInfo& allocateInfo)
    {
        CommandBuffer commandBuffer = {};
        CHECK_VK(vkAllocateCommandBuffers(device, &allocateInfo, &commandBuffer));

        return commandBuffer;
    }

    inline std::vector<CommandBuffer> allocateCommandBuffers(VkDevice device,
        const VkCommandBufferAllocateInfo& allocateInfo)
    {
        std::vector<CommandBuffer> commandBuffers(allocateInfo.commandBufferCount);
        CHECK_VK(vkAllocateCommandBuffers(device, &allocateInfo, commandBuffers.data()));

        return commandBuffers;
    }
}
