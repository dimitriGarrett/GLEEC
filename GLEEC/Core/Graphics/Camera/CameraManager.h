#pragma once

#include "Config/Export.h"

#include "Camera.h"

#include "Core/Window/Window.h"

#include "Core/Graphics/Renderer/ShaderResource.h"
#include "Core/Graphics/Renderer/Frame.h"

#include <unordered_map>

namespace GLEEC::Graphics
{
    struct CameraManager
    {
        GLEEC_API static Camera& defaultFPSCamera(const Window::Window& window);
        GLEEC_API static Camera& default2DCamera(const Window::Window& window);

        GLEEC_API static void init();
        GLEEC_API static void destroy();

        GLEEC_API static Camera& createFPSCamera(const Window::Window& window);
        GLEEC_API static Camera& create2DCamera(const Window::Window& window);

        GLEEC_API static void createCameras(const Window::Window& window);

    private:
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static ShaderResource cameraResource;
#endif

        GLEEC_API static std::unordered_map<Window::Window, Cameras> cameras;
    public:

        GLEEC_API static void useCamera(const FrameData& frame, const Camera& camera);

        GLEEC_API static void updateCamera(CameraFPS& camera);
        GLEEC_API static void updateCamera(Camera2D& camera);

        GLEEC_API static void updateCameras();

        GLEEC_API static void rotateCamera(Camera& camera,
            const math::fquat& rotationQuat);

        struct Get
        {
            // returned in radians
            GLEEC_API static float fov(const Camera& camera);

            // returned in radians
            GLEEC_API static float fov(const math::fmat4& proj);

            GLEEC_API static float aspect(const Camera& camera);
            GLEEC_API static float aspect(const math::fmat4& proj);

            GLEEC_API static float near(const Camera& camera);
            GLEEC_API static float near(const math::fmat4& proj);

            GLEEC_API static float far(const Camera& camera);
            GLEEC_API static float far(const math::fmat4& proj);
        };

        struct Set
        {
            GLEEC_API static void fov(Camera& camera, float val);
            GLEEC_API static void fov(math::fmat4& proj, float val);

            GLEEC_API static void aspect(Camera& camera, float val);
            GLEEC_API static void aspect(math::fmat4& proj, float val);

            GLEEC_API static void near(Camera& camera, float val);
            GLEEC_API static void near(math::fmat4& proj, float val);

            GLEEC_API static void far(Camera& camera, float val);
            GLEEC_API static void far(math::fmat4& proj, float val);
        };
    };
}
