#pragma once

#include "Semaphore.h"

namespace GLEEC::Internal::Graphics::vk
{
    using Fence = VkFence;

    inline Fence createFence(VkDevice device, VkFenceCreateFlags flags = 0)
    {
        VkFenceCreateInfo info = {
            VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        };

        info.flags = flags;

        Fence fence = {};
        CHECK_VK(vkCreateFence(device, &info, nullptr, &fence));

        return fence;
    }

    inline Fence createSignaledFence(VkDevice device)
    {
        static const VkFenceCreateInfo info = {
            VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            nullptr,

            VK_FENCE_CREATE_SIGNALED_BIT
        };

        Fence fence = {};
        CHECK_VK(vkCreateFence(device, &info, nullptr, &fence));

        return fence;
    }

    inline void destroyFence(VkDevice device, VkFence fence)
    {
        vkDestroyFence(device, fence, nullptr);
    }

    inline void resetFences(VkDevice device,
        const std::vector<Fence>& fences)
    {
        CHECK_VK(vkResetFences(device, static_cast<uint32_t>(fences.size()),
            fences.data()));
    }

    inline void resetFence(VkDevice device, VkFence fence)
    {
        CHECK_VK(vkResetFences(device, 1, &fence));
    }

    inline void waitForFence(VkDevice device, VkFence fence, uint64_t timeout = UINT64_MAX)
    {
        CHECK_VK(vkWaitForFences(device, 1, &fence, VK_TRUE, timeout));
    }

    inline void waitForFences(VkDevice device, const std::vector<Fence> fences,
        VkBool32 waitAll = VK_TRUE, uint64_t timeout = UINT64_MAX)
    {
        CHECK_VK(vkWaitForFences(device, static_cast<uint32_t>(fences.size()),
            fences.data(), waitAll, timeout));
    }

    inline VkResult getFenceStatus(VkDevice device, VkFence fence)
    {
        return vkGetFenceStatus(device, fence);
    }
}
