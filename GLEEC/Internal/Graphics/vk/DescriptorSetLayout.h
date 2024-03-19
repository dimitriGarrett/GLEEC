#pragma once

#include "PhysicalDevice.h"

namespace GLEEC::Internal::Graphics::vk
{
    using DescriptorSetBinding = VkDescriptorSetLayoutBinding;
    using DescriptorSetLayout = VkDescriptorSetLayout;

    using DescriptorSetLayouts = std::vector<DescriptorSetLayout>;
    using DescriptorSetBindings = std::vector<DescriptorSetBinding>;

    inline DescriptorSetLayout createDescriptorSetLayout(VkDevice device,
        const std::vector<DescriptorSetBinding>& bindings)
    {
        VkDescriptorSetLayoutCreateInfo info = {
            VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO
        };

        info.bindingCount = static_cast<uint32_t>(bindings.size());
        info.pBindings = bindings.data();
        info.flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT;

        DescriptorSetLayout layout = {};
        CHECK_VK(vkCreateDescriptorSetLayout(device, &info, nullptr, &layout));

        return layout;
    }

    inline void destroyDescriptorSetLayout(VkDevice device,
        VkDescriptorSetLayout descriptorSetLayout)
    {
        vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
    }
}
