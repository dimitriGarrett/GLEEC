#pragma once

#include "CommandBuffer.h"

namespace GLEEC::Internal::Graphics::vk
{
    inline VkSubmitInfo2 submitInfo2(
        const std::vector<VkCommandBufferSubmitInfo>& commandBuffers,
        const std::vector<VkSemaphoreSubmitInfo> signalSemaphores,
        const std::vector<VkSemaphoreSubmitInfo> waitSemaphores)
    {
        VkSubmitInfo2 info = {
            VK_STRUCTURE_TYPE_SUBMIT_INFO_2
        };

        info.commandBufferInfoCount = static_cast<uint32_t>(commandBuffers.size());
        info.pCommandBufferInfos = commandBuffers.data();

        info.waitSemaphoreInfoCount = static_cast<uint32_t>(waitSemaphores.size());
        info.pWaitSemaphoreInfos = waitSemaphores.data();

        info.signalSemaphoreInfoCount = static_cast<uint32_t>(signalSemaphores.size());
        info.pWaitSemaphoreInfos = signalSemaphores.data();

        return info;
    }

    inline VkSubmitInfo2 submitInfo2(const VkCommandBufferSubmitInfo& commandBuffer,
        const std::vector<VkSemaphoreSubmitInfo>& signalSemaphores,
        const std::vector<VkSemaphoreSubmitInfo>& waitSemaphores)
    {
        return submitInfo2(std::vector<VkCommandBufferSubmitInfo>{ commandBuffer },
            signalSemaphores, waitSemaphores);
    }

    inline VkSubmitInfo2 submitInfo2(const VkCommandBufferSubmitInfo& commandBuffer,
        const VkSemaphoreSubmitInfo& signalSemaphore,
        const VkSemaphoreSubmitInfo& waitSemaphore)
    {
        VkSubmitInfo2 info = {
            VK_STRUCTURE_TYPE_SUBMIT_INFO_2
        };

        info.commandBufferInfoCount = 1;
        info.pCommandBufferInfos = &commandBuffer;

        info.waitSemaphoreInfoCount = 1;
        info.pWaitSemaphoreInfos = &waitSemaphore;

        info.signalSemaphoreInfoCount = 1;
        info.pSignalSemaphoreInfos = &signalSemaphore;

        return info;
    }

    inline void queueSubmit2(VkQueue queue, const std::vector<VkSubmitInfo2>& submitInfos,
        VkFence fence)
    {
        CHECK_VK(vkQueueSubmit2(queue, static_cast<uint32_t>(submitInfos.size()),
            submitInfos.data(), fence));
    }

    inline void queueSubmit2(VkQueue queue, const VkSubmitInfo2* submitInfo, VkFence fence)
    {
        CHECK_VK(vkQueueSubmit2(queue, 1, submitInfo, fence));
    }

    inline void queueSubmit2(VkQueue queue, const VkSubmitInfo2& submitInfo, VkFence fence)
    {
        CHECK_VK(vkQueueSubmit2(queue, 1, &submitInfo, fence));
    }
}
