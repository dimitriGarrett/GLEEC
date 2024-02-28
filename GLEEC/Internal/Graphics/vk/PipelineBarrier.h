#pragma once

#include "Image.h"

namespace GLEEC::Internal::Graphics::vk
{
    inline void cmdPipelineBarrier2(VkCommandBuffer commandBuffer,
        const VkDependencyInfo& dependencyInfo)
    {
        vkCmdPipelineBarrier2(commandBuffer, &dependencyInfo);
    }
}
