#pragma once

#include "math/utility/defines.h"

#include <string>

namespace GLEEC::Graphics
{
    struct Material
    {
        math::vec3 ambient  = {};
        math::vec3 diffuse  = {};
        math::vec3 specular = {};

        float d = 1.0f;

        std::string name = "Unknown Material";
        //float shininess = 0.0f;
    };
}
