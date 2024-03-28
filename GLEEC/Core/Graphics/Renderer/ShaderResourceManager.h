#pragma once

#include "Core/Graphics/Texture.h"
#include "ShaderResource.h"

#include "Core/Graphics/Buffer.h"
#include "Core/Graphics/Renderer/Shaders.h"
#include "Core/Graphics/Renderer/Frame.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Sampler.h"
#endif

#define CAMERA_SET 0
#define MODEL_SET 1
#define FRAGMENT_SET 2

namespace GLEEC::Graphics
{
    struct ShaderResourceManager
    {
        GLEEC_API static void init();
        GLEEC_API static void destroy();

        GLEEC_API static ShaderResource createUniformBufferShaderResource(
            const Shaders& shaders, uint32_t set);

        GLEEC_API static uint32_t addUniformBuffer(ShaderResource& resources,
            const Buffer& buffer);

        GLEEC_API static ShaderResource createCombinedImageShaderResource(
            const Shaders& shaders, uint32_t set);

        GLEEC_API static uint32_t addCombinedImage(ShaderResource& resources,
            const Texture& texture);

        GLEEC_API static void use(const FrameData& frame,
            const ShaderResource& resource, const Buffer& buffer);
        GLEEC_API static void use(const FrameData& frame,
            const ShaderResource& resource, const Texture& texture);

        GLEEC_API static void use(const FrameData& frame,
            const ShaderResource& resource, const void* resourceptr);

        GLEEC_API static void use(const FrameData& frame,
            const ShaderResource& resource, uint32_t offset);

        GLEEC_API static void bind(const FrameData& frame);

    private:
        GLEEC_API static std::vector<ShaderResource> resources;

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static ShaderResource addBinding(const ShaderResource&);

        GLEEC_API static std::vector<VkDescriptorBufferBindingInfoEXT>
            internalBindings;

        GLEEC_API static Internal::Graphics::vk::Sampler sampler;
#endif
    };
}
