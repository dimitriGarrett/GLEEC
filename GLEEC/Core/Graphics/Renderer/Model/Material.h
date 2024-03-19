#pragma once

#include "Core/Graphics/Buffer.h"
#include "Core/Graphics/Texture.h"
#include "math/utility/defines.h"

#include "Core/Graphics/Shader.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Sampler.h"
#include "Internal/Graphics/vk/DescriptorBuffer.h"
#endif

#include <string>

namespace GLEEC::Graphics
{
    struct Material
    {
        ~Material() = default;

        math::vec3 ambient  = {};
        math::vec3 diffuse  = {};
        math::vec3 specular = {};

        float d = 1.0f;
        float shininess = 0.0f;

        virtual void bind() = 0;

        // choose the descriptor buffer for this material
        virtual uint32_t buffer(uint32_t color, uint32_t texture) = 0;

        // for indexing into descriptor buffers
        size_t offset = 0;

        size_t shaderClass = static_cast<size_t>(-1);

        std::string name = "Unknown Material";
    };

    struct ColorMaterial final : Material
    {
        GLEEC_API void bind() override;
        GLEEC_API uint32_t buffer(uint32_t color, uint32_t texture) override;

        Buffer colorBuffer = {};
    };

    struct TextureMaterial final : Material
    {
        GLEEC_API void bind() override;
        GLEEC_API uint32_t buffer(uint32_t color, uint32_t texture) override;

        Texture texture = {};

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::ImageView imageView = {};
        Internal::Graphics::vk::Sampler sampler = {};
#endif
    };
}
