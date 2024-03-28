#pragma once

#include "Core/Graphics/Buffer.h"
#include "Core/Graphics/Texture.h"
#include "math/utility/defines.h"

#include <string>

namespace GLEEC::Graphics
{
    enum MaterialType
    {
        COLOR_MATERIAL = 0,
        TEXTURE_MATERIAL,
    };

    struct Material
    {
        ~Material() = default;

        math::vec3 ambient  = {};
        math::vec3 diffuse  = {};
        math::vec3 specular = {};

        float d = 1.0f;
        float shininess = 0.0f;

        MaterialType type = {};

        uint32_t offset = {};

        size_t shaderClass = static_cast<size_t>(-1);

        std::string name = "Unknown Material";
    };

    struct ColorMaterial final : Material
    {
        Buffer colorBuffer = {};
    };

    struct TextureMaterial final : Material
    {
        Texture texture = {};
    };
}
