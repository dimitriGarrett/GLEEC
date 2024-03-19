#pragma once

#include "Core/Graphics/Buffer.h"
#include "Geometry.h"

#include "math/utility/defines.h"

namespace GLEEC::Graphics
{
    struct Model
    {
        Geometry* geometry = nullptr;

        math::fmat4 model = {};

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        // for the descriptor buffer in model manager
        VkDeviceSize bufferIndex = static_cast<VkDeviceSize>(-1);

        Buffer uniformBuffer = {};
#endif
    };
}
