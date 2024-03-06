#include "WindowManager.h"

#include "Core/Event/Event.h"

#include "Core/Graphics/FrameManager.h"
#include "Core/Graphics/RenderTargetManager.h"
#include "Core/Graphics/GPUManager.h"

namespace GLEEC::Window
{
    size_t WindowManager::openWindows = 0;
    size_t WindowManager::currentWindow = 0;

    std::array<Window, GLEEC_WINDOW_MAX_WINDOWS> WindowManager::windows = {};

    Window& WindowManager::createWindow(const WindowInfo& info)
    {
        if (openWindows >= GLEEC_WINDOW_MAX_WINDOWS)
        {
            LOG_WARNING("Ignoring request to create window, max of: {} already created! Must close one before opening a new one!", GLEEC_WINDOW_MAX_WINDOWS);

            return windows.back();
        }

        Window& window = windows[openWindows++];
        window.vSync = info.vSync;

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Window::glfw::windowHint(GLFW_RESIZABLE, info.resizable);

        // we don't use OpenGL around here
        Internal::Window::glfw::windowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // its vulkan time baby

        window.internalWindow = Internal::Window::glfw::createWindow(
            info.dim, info.name, info.monitor.internalMonitor);
#endif

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_LOCK_KEY_MODS, GLFW_TRUE);
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        window.surface = Internal::Graphics::vk::createSurface(
            Graphics::InstanceManager::instance.instance, window.internalWindow);
#endif

        Event::fireEvent<Event::WindowCreate>(window);

        return window;
    }

    void WindowManager::destroyWindow(Window& window)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::destroySwapchain(
            Graphics::GPUManager::activeGPU.device,
            window.swapchain);
        Internal::Graphics::vk::destroySurface(
            Graphics::InstanceManager::instance.instance,
            window.surface);

        window.swapchain.swapchain = VK_NULL_HANDLE;
        window.surface = VK_NULL_HANDLE;

        window.swapchain.images.clear();
        window.swapchain.imageViews.clear();
#endif

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        glfwDestroyWindow(window.internalWindow);

        window.internalWindow = nullptr;
#endif
    }

    void WindowManager::finalizeWindow(Window& window)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        if (window.vSync)
        {
            window.swapchain = Internal::Graphics::vk::createSwapchain(
                Graphics::GPUManager::activeGPU.device, window.surface,
                Internal::Graphics::vk::swapchainCreation::VSYNC);
        }

        else
        {
            window.swapchain = Internal::Graphics::vk::createSwapchain(
                Graphics::GPUManager::activeGPU.device, window.surface,
                Internal::Graphics::vk::swapchainCreation::NO_VSYNC);
        }
#endif
    }

    inline void WindowManager::swap(Window& a, Window& b)
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        std::swap(a.internalWindow, b.internalWindow);
#endif

        std::swap(a.vSync, b.vSync);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        std::swap(a.surface, b.surface);
        std::swap(a.swapchain.swapchain, b.swapchain.swapchain);
        std::swap(a.swapchain.extent, b.swapchain.extent);
        std::swap(a.swapchain.surfaceFormat, b.swapchain.surfaceFormat);
        std::swap(a.swapchain.images, b.swapchain.images);
        std::swap(a.swapchain.imageViews, b.swapchain.imageViews);
#endif
    }

    void WindowManager::registerCallbacks()
    {
        Event::addListener<Event::WindowClose>(+[](Window w)
        {
            size_t j = findWindowIndex(w);

            if (j == -1) return;

            Graphics::FrameManager::destroyFrame(j);
            Graphics::RenderTargetManager::destroyRenderTarget(j);
            destroyWindow(j);

            // ensure open windows are at the beginning because
            // lots of logic depends on that behaviour
            for (size_t i = j; i < GLEEC_WINDOW_MAX_WINDOWS - 1; ++i)
            {
                if (windows[i].isOpen())
                {
                    swap(windows[j], windows[i]);
                    
                    Graphics::FrameManager::swap(j, i);
                    Graphics::RenderTargetManager::swap(j, i);

                    if (i == currentWindow)
                    {
                        currentWindow = j;
                    }

                    break;
                }
            }

            --WindowManager::openWindows;
        }, -1);

        Event::addListener<Event::WindowOpened>(+[](Window w)
        {
            size_t i = findWindowIndex(w);

            // only if this window is opened sometime during the lifetime of the game and not just during the beginning
            if (Graphics::GPUManager::activeGPU.connected() || i == -1)
                return;

            Graphics::FrameManager::initFrame(i);
            Graphics::RenderTargetManager::initRenderTarget(i);
        }, -1);

        Event::addListener<Event::WindowFocus>(+[](Window w)
        {
            WindowManager::currentWindow = findWindowIndex(w);
        }, -1);

        Event::addListener<Event::WindowIconify>(+[](Window w)
        {
            uint32_t i = findWindowIndex(w);

            if (i == -1)
                return;

            WindowManager::windows[i].minimized = true;
        }, -1);

        // this gets called before framebuffer size,
        // so it will recreate the frame needlessly
        // instead, handle it in framebuffer size instead
        /* Event::addListener<Event::WindowRestore>(+[](Window w)
        {
            uint32_t i = findWindowIndex(w);

            if (i == -1)
                return;

            WindowManager::windows[i].minimized = false;
        }, -1); */

        Event::addListener<Event::FramebufferSize>(+[](Window w, int width, int height)
        {
            uint32_t i = findWindowIndex(w);

            if (i == -1)
                return;

            Window& window = WindowManager::windows[i];

            if (!window.minimized && width != 0 && height != 0)
                Graphics::FrameManager::recreateFrame(i);

            window.minimized = (width == 0 || height == 0);
        }, -1);
    }

    size_t WindowManager::findWindowIndex(Window w)
    {
        for (size_t i = 0; i < openWindows; ++i)
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            if (windows[i].internalWindow == w.internalWindow) return i;
#else
            // this needs to be specialized by
            //if (windows[i] == w) return i;
#error "Implement find window index for different backends!"
#endif
        }

        return -1;
    }
}
