#pragma once

#include "Config/Export.h"
#include "helpers/ProcAddress.h"

namespace GLEEC::Internal::Graphics::vk
{
    template <typename T>
    inline void ensureExtensionFunctionExists(std::string_view name, T ptr)
    {
        if (ptr == nullptr)
        {
            LOG_WARNING("Vulkan: failed to load extension function: {}",
                name);
        }
    }

#define EXISTS_FUN(fun) ensureExtensionFunctionExists(#fun, GET_FUN(fun))
#define FUN_WORK(fun) fun = reinterpret_cast<PFN_##fun>(GET_FUN(fun)); EXISTS_FUN(fun)

#define DEF_FUN(fun) GLEEC_API_EXTERN PFN_##fun fun

    DEF_FUN(vkGetDescriptorEXT);
    DEF_FUN(vkCmdBindDescriptorBuffersEXT);
    DEF_FUN(vkCmdSetDescriptorBufferOffsetsEXT);
    DEF_FUN(vkGetDescriptorSetLayoutSizeEXT);
    DEF_FUN(vkGetDescriptorSetLayoutBindingOffsetEXT);

    inline void loadInstanceExtensions(VkInstance instance)
    {
#define GET_FUN(fun) vkGetInstanceProcAddr(instance, #fun)

        FUN_WORK(vkGetDescriptorEXT);
        FUN_WORK(vkCmdBindDescriptorBuffersEXT);
        FUN_WORK(vkCmdSetDescriptorBufferOffsetsEXT);
        FUN_WORK(vkGetDescriptorSetLayoutSizeEXT);
        FUN_WORK(vkGetDescriptorSetLayoutBindingOffsetEXT);

#undef GET_FUN
    }

    DEF_FUN(vkCreateShadersEXT);
    DEF_FUN(vkDestroyShaderEXT);
    DEF_FUN(vkGetShaderBinaryDataEXT);
    DEF_FUN(vkCmdBindShadersEXT);

    DEF_FUN(vkCmdSetPolygonModeEXT);
    DEF_FUN(vkCmdSetRasterizationSamplesEXT);
    DEF_FUN(vkCmdSetSampleMaskEXT);
    DEF_FUN(vkCmdSetColorWriteMaskEXT);
    DEF_FUN(vkCmdSetColorBlendEnableEXT);
    DEF_FUN(vkCmdSetColorBlendEquationEXT);
    DEF_FUN(vkCmdSetSampleMaskEXT);
    DEF_FUN(vkCmdSetColorWriteMaskEXT);
    DEF_FUN(vkCmdSetAlphaToCoverageEnableEXT);
    DEF_FUN(vkCmdSetAlphaToOneEnableEXT);
    DEF_FUN(vkCmdSetDepthClampEnableEXT);
    DEF_FUN(vkCmdSetVertexInputEXT);
    DEF_FUN(vkCmdSetLogicOpEnableEXT);

#undef DEF_FUN
    inline void loadDeviceExtensions(VkDevice device)
    {
#define GET_FUN(fun) vkGetDeviceProcAddr(device, #fun)

        FUN_WORK(vkCreateShadersEXT);
        FUN_WORK(vkDestroyShaderEXT);
        FUN_WORK(vkGetShaderBinaryDataEXT);
        FUN_WORK(vkCmdBindShadersEXT);

        FUN_WORK(vkCmdSetPolygonModeEXT);
        FUN_WORK(vkCmdSetRasterizationSamplesEXT);
        FUN_WORK(vkCmdSetColorBlendEnableEXT);
        FUN_WORK(vkCmdSetSampleMaskEXT);
        FUN_WORK(vkCmdSetColorWriteMaskEXT);
        FUN_WORK(vkCmdSetColorBlendEquationEXT);
        FUN_WORK(vkCmdSetSampleMaskEXT);
        FUN_WORK(vkCmdSetColorWriteMaskEXT);
        FUN_WORK(vkCmdSetAlphaToCoverageEnableEXT);
        FUN_WORK(vkCmdSetAlphaToOneEnableEXT);
        FUN_WORK(vkCmdSetDepthClampEnableEXT);
        FUN_WORK(vkCmdSetVertexInputEXT);
        FUN_WORK(vkCmdSetLogicOpEnableEXT);

#undef GET_FUN
    }

#undef EXISTS_FUN
#undef FUN_WORK
}
