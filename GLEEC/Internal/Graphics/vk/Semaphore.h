#pragma once

#include "PhysicalDevice.h"

namespace GLEEC::Internal::Graphics::vk
{
    using Semaphore = VkSemaphore;

    inline Semaphore createSemaphore(VkDevice device)
    {
        // the info never changes, no flags are present in vulkan 1.3
        static const VkSemaphoreCreateInfo info = {
            VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
        };

        Semaphore semaphore = {};
        CHECK_VK(vkCreateSemaphore(device, &info, nullptr, &semaphore));

        return semaphore;
    }

    inline void destroySemaphore(VkDevice device, VkSemaphore semaphore)
    {
        vkDestroySemaphore(device, semaphore, nullptr);
    }

    inline VkSemaphoreSubmitInfo semaphoreSubmitInfo(
        VkSemaphore semaphore, VkPipelineStageFlags2 stageMask)
    {
        VkSemaphoreSubmitInfo info = {
            VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO
        };

        info.semaphore = semaphore;
        info.stageMask = stageMask;

        info.deviceIndex = 0; // no device groups
        info.value = 1; // no timeline semaphores either

        return info;
    }
}
