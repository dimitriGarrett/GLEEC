#include "CameraManager.h"

#include "Core/Event/Events.h"
#include "Core/Event/Subway.h"

#include "Core/Graphics/BufferManager.h"

#include "Core/Graphics/Renderer/ShaderManager.h"
#include "Core/Graphics/Renderer/ShaderResourceManager.h"

#include "Core/Window/WindowManager.h"

#include <cmath>

namespace GLEEC::Graphics
{
    std::unordered_map<Window::Window, Cameras> CameraManager::cameras = {};

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    ShaderResource CameraManager::cameraResource = {};
#endif

    inline void CameraManager::init()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        cameraResource = ShaderResourceManager::createUniformBufferShaderResource(
            ShaderManager::getShaders("cl"), CAMERA_SET);
#endif

        for (uint32_t i : Window::WindowManager::availableWindows())
        {
            Graphics::CameraManager::createCameras(
                Window::WindowManager::windows[i]);
        }

        Event::addListener<Event::FramebufferSize>(+[](Window::Window window,
            int width, int height)
        {
            for (Camera& cam : cameras[window].camerasFPS)
            {
                float aspect = static_cast<float>(width) /
                               static_cast<float>(height);

                Set::aspect(cam, aspect);
            }

            for (Camera& cam : cameras[window].cameras2D)
            {
                float x = static_cast<float>(width);
                float y = static_cast<float>(height);

                cam.projection = math::ortho(0.0f, x, y, 0.0f, 0.1f, 100.0f);
            }
        }, -2);
    }

    inline void CameraManager::destroy()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        for (auto& [_, camerass] : cameras)
        {
            for (Camera& camera : camerass.cameras2D)
            {
                BufferManager::destroyBuffer(camera.matrixBuffer);
            }

            for (Camera& camera : camerass.camerasFPS)
            {
                BufferManager::destroyBuffer(camera.matrixBuffer);
            }
        }
#endif
    }

    inline Camera& CameraManager::defaultFPSCamera(const Window::Window& window)
    {
        return cameras.at(window).camerasFPS.at(0);
    }

    inline Camera& CameraManager::default2DCamera(const Window::Window& window)
    {
        return cameras.at(window).cameras2D.at(0);
    }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    inline const void* getVulkanData(const Camera& camera)
    {
        return &camera.projection;
    }

    inline size_t getVulkanSize(const Camera& camera)
    {
        // projection and view matrices
        return sizeof(math::fmat4) * 2;
    }
#endif

    Camera& CameraManager::createFPSCamera(const Window::Window& window)
    {
        CameraFPS& cam = cameras[window].camerasFPS.emplace_back();

        cam.pos =   { 0.0f, 0.0f, 3.0f };
        cam.up =    { 0.0f, 1.0f,  0.0f };
        cam.front = { 0.0f, 0.0f, -1.0f };

        cam.view = math::lookAtRH(cam.front, cam.pos, cam.up);

        math::fvec2 size = Window::WindowManager::Get::size(window);

        cam.projection = math::perspective(math::radians(90.0f),
            size.x / size.y, 0.1f, 100.0f);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        cam.matrixBuffer = BufferManager::createUniformBuffer(
            getVulkanSize(cam), getVulkanData(cam));

        cam.offset = ShaderResourceManager::addUniformBuffer(cameraResource,
            cam.matrixBuffer);
#endif

        return cam;
    }

    Camera& CameraManager::create2DCamera(const Window::Window& window)
    {
        Camera2D& cam = cameras[window].cameras2D.emplace_back();

        cam.view = math::fmat4(1.0f);

        math::fvec2 size = Window::WindowManager::Get::size(window);

        cam.projection = math::ortho(0.0f, size.x,
            size.y, 0.0f, 0.1f, 100.0f);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        cam.matrixBuffer = BufferManager::createUniformBuffer(
            getVulkanSize(cam), getVulkanData(cam));

        cam.offset = ShaderResourceManager::addUniformBuffer(cameraResource,
            cam.matrixBuffer);
#endif

        return cam;
    }

    inline void CameraManager::createCameras(const Window::Window& window)
    {
        create2DCamera(window);
        createFPSCamera(window);
    }

    // this is where the new rotations and translations are taken into effect
    // also vulkan stuff
    inline void CameraManager::updateCamera(CameraFPS& camera)
    {
        camera.view = math::lookAtRH(camera.front, camera.pos, camera.up);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        memcpy_s(camera.matrixBuffer.buffer.map, getVulkanSize(camera),
            getVulkanData(camera), getVulkanSize(camera));
#endif
    }

    inline void CameraManager::updateCamera(Camera2D& camera)
    {
        // does anything need to be done?
        // usually 2d cameras are one and done
    }

    inline void CameraManager::updateCameras()
    {
        for (auto& [_, cams] : cameras)
        {
            for (CameraFPS& camera : cams.camerasFPS)
            {
                updateCamera(camera);
            }

            for (Camera2D& camera : cams.cameras2D)
            {
                updateCamera(camera);
            }
        }
    }

    // rotate the direction by rotation
    inline void CameraManager::rotateCamera(Camera& camera,
        const math::fquat& rotationQuat)
    {
        abort();
    }

    inline void CameraManager::useCamera(const FrameData& frame, const Camera& camera)
    {
        ShaderResourceManager::use(frame, cameraResource, camera.offset);
    }

    // if you dont know how this was calculated, look at
    // how the perspective matrix was set up

    inline float CameraManager::Get::fov(const math::fmat4& proj)
    {
        return 2.0f * std::atan(-1.0f / proj(1, 1));
    }

    inline float CameraManager::Get::fov(const Camera& camera)
    {
        return fov(camera.projection);
    }

    inline float CameraManager::Get::aspect(const math::fmat4& proj)
    {
        return -proj(1, 1) / proj(0, 0);
    }

    inline float CameraManager::Get::aspect(const Camera& camera)
    {
        return aspect(camera.projection);
    }

    inline float CameraManager::Get::near(const math::fmat4& proj)
    {
        return proj(2, 3) / (proj(2, 2) + 1.0f);
    }

    inline float CameraManager::Get::near(const Camera& camera)
    {
        return near(camera.projection);
    }

    inline float CameraManager::Get::far(const math::fmat4& proj)
    {
        return proj(2, 3) / proj(2, 2);
    }

    inline float CameraManager::Get::far(const Camera& camera)
    {
        return far(camera.projection);
    }

    inline void CameraManager::Set::fov(math::fmat4& proj, float val)
    {
		float g = 1.0f / tan(val * 0.5f);

        proj(0, 0) =  g / Get::aspect(proj);
        proj(1, 1) = -g;
    }

    inline void CameraManager::Set::fov(Camera& camera, float val)
    {
        fov(camera.projection, val);
    }

    inline void CameraManager::Set::aspect(math::fmat4& proj, float val)
    {
		float g = 1.0f / tan(Get::fov(proj) * 0.5f);

        proj(0, 0) = g / val;
    }

    inline void CameraManager::Set::aspect(Camera& camera, float val)
    {
        aspect(camera.projection, val);
    }

    inline void CameraManager::Set::near(math::fmat4& proj, float val)
    {
        float f = Get::far(proj);
        float k = val / (val - f);

        proj(2, 2) = k;
        proj(2, 3) = f * k;
    }

    inline void CameraManager::Set::near(Camera& camera, float val)
    {
        near(camera.projection, val);
    }

    inline void CameraManager::Set::far(math::fmat4& proj, float val)
    {
        float n = Get::near(proj);
        float k = n / (n - val);

        proj(2, 2) = k;
        proj(2, 3) = val * k;
    }

    inline void CameraManager::Set::far(Camera& camera, float val)
    {
        far(camera.projection, val);
    }
}
