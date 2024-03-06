#include "Extensions.h"

namespace GLEEC::Internal::Graphics::vk
{
#define DEF_FUN(fun) PFN_##fun fun = nullptr;

    DEF_FUN(vkGetDescriptorEXT);
    DEF_FUN(vkCmdBindDescriptorBuffersEXT);
    DEF_FUN(vkCmdSetDescriptorBufferOffsetsEXT);
    DEF_FUN(vkGetDescriptorSetLayoutSizeEXT);
    DEF_FUN(vkGetDescriptorSetLayoutBindingOffsetEXT);

    DEF_FUN(vkCreateShadersEXT);
    DEF_FUN(vkDestroyShaderEXT);
    DEF_FUN(vkGetShaderBinaryDataEXT);
    DEF_FUN(vkCmdBindShadersEXT);

    DEF_FUN(vkCmdSetPolygonModeEXT);
    DEF_FUN(vkCmdSetRasterizationSamplesEXT);
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
}
