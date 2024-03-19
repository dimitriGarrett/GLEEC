#pragma once

#include "PhysicalDevice.h"

namespace GLEEC::Internal::Graphics::vk
{
    using PipelineLayout = VkPipelineLayout;

    inline PipelineLayout createPipelineLayout(VkDevice device,
        const std::vector<VkDescriptorSetLayout>& descriptorSetLayouts,
        const std::vector<VkPushConstantRange>& pushConstants)
    {
        VkPipelineLayoutCreateInfo info = {
            VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO
        };

        info.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
        info.pSetLayouts = descriptorSetLayouts.data();

        info.pushConstantRangeCount = static_cast<uint32_t>(pushConstants.size());
        info.pPushConstantRanges = pushConstants.data();

        PipelineLayout layout = {};
        CHECK_VK(vkCreatePipelineLayout(device, &info, nullptr, &layout));

        return layout;
    }

    inline void destroyPipelineLayout(VkDevice device, const PipelineLayout& layout)
    {
        vkDestroyPipelineLayout(device, layout, nullptr);
    }
}
