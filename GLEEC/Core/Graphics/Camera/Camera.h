#pragma once

#include "math/utility/defines.h"

#include "Core/Graphics/Buffer.h"

namespace GLEEC::Graphics
{
    struct Camera
    {
        math::fmat4 projection = {};
        math::fmat4 view = {};

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Buffer matrixBuffer = {};

        uint32_t offset = 0;
#endif
    };

    struct CameraFPS final : Camera
    {
        math::fvec3 pos = {};
        math::fvec3 up = {};
        math::fvec3 front = {};
    };

    struct Camera2D final : Camera
    {
        // nothing special
    };

    struct Cameras
    {
        std::vector<CameraFPS> camerasFPS = {};
        std::vector<Camera2D> cameras2D = {};
    };
}
