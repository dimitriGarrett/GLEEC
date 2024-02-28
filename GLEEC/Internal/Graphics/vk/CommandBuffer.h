#pragma once

#include "Internal/Graphics/vk/helpers/CHECK_VK.h"
#include "PhysicalDevice.h"

namespace GLEEC::Internal::Graphics::vk
{
    using CommandBuffer = VkCommandBuffer;

    inline void resetCommandBuffer(CommandBuffer commandBuffer, VkCommandBufferResetFlags flags = 0)
    {
        CHECK_VK(vkResetCommandBuffer(commandBuffer, flags));
    }

    inline void resetCommandBufferAndResources(CommandBuffer commandBuffer)
    {
        resetCommandBuffer(commandBuffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
    }

    inline VkCommandBufferBeginInfo commandBufferBeginInfo(
        const VkCommandBufferInheritanceInfo* inheritanceInfo,
        VkCommandBufferUsageFlags flags)
    {
        return {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .pNext = nullptr,

            .flags = flags,
            .pInheritanceInfo = inheritanceInfo,
        };
    }

    inline VkCommandBufferBeginInfo commandBufferBeginInfo(
        const VkCommandBufferInheritanceInfo* inheritanceInfo)
    {
        return commandBufferBeginInfo(inheritanceInfo, 0);
    }

    inline VkCommandBufferBeginInfo commandBufferBeginInfo(
        VkCommandBufferUsageFlags flags)
    {
        return commandBufferBeginInfo(nullptr, flags);
    }

    inline VkCommandBufferBeginInfo commandBufferBeginInfo()
    {
        static const VkCommandBufferBeginInfo info = {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO
        };

        return info;
    }

    inline VkCommandBufferBeginInfo commandBufferBeginInfoOneTimeSubmit()
    {
        return commandBufferBeginInfo(nullptr,
            VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    }

    inline void beginCommandBuffer(VkCommandBuffer commandBuffer,
        const VkCommandBufferBeginInfo& beginInfo)
    {
        CHECK_VK(vkBeginCommandBuffer(commandBuffer, &beginInfo));
    }

    inline void beginCommandBufferOneTimeSubmit(VkCommandBuffer commandBuffer)
    {
        static const VkCommandBufferBeginInfo beginInfo =
            commandBufferBeginInfoOneTimeSubmit();

        beginCommandBuffer(commandBuffer, beginInfo);
    }

    inline void endCommandBuffer(VkCommandBuffer commandBuffer)
    {
        CHECK_VK(vkEndCommandBuffer(commandBuffer));
    }

    inline VkCommandBufferSubmitInfo commandBufferSubmitInfo(VkCommandBuffer commandBuffer)
    {
        VkCommandBufferSubmitInfo info = {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO
        };

        info.commandBuffer = commandBuffer;
        info.deviceMask = 0;

        return info;
    }
}
