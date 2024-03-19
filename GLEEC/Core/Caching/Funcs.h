#pragma once

#include "Cache.h"

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Shader.h"
#endif

#include "Core/Graphics/Shaders.h"

namespace GLEEC::Caching
{
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    GLEEC_API Internal::Graphics::vk::ShaderBinary loadCachedShader(
        std::ifstream& file, const CachedHeader& header);

    GLEEC_API Internal::Graphics::vk::ShaderBinary loadLoadedShader(
        std::ifstream& file, std::string_view filepath);

    GLEEC_API void writeShader(std::ofstream& file,
        const Internal::Graphics::vk::ShaderBinary& cache);

    GLEEC_API void destroyShader(
        const Internal::Graphics::vk::ShaderBinary& cache);
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    GLEEC_API Graphics::DescriptorSets loadCachedDescriptorSetBindings(
        std::ifstream& file, const Caching::CachedHeader& header);

    GLEEC_API Graphics::DescriptorSets loadLoadedDescriptorSetBindings(
        std::ifstream& file, std::string_view filepath);

    GLEEC_API void writeDescriptorSetBindings(std::ofstream& file,
        const Graphics::DescriptorSets& layout);

    GLEEC_API void destroyDescriptorSetBindings(const Graphics::DescriptorSets&);
#endif
}
