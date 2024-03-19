#pragma once

#include "Material.h"

namespace GLEEC::Graphics
{
    struct MaterialManager
    {
        GLEEC_API static void bindColorMaterial(Material* material);
        GLEEC_API static void bindTextureMaterial(Material* material);
    };
}
