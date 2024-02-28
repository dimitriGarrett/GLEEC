#pragma once

#include "Internal/Window/Backend.h"

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
#include "Internal/Window/GLFW/Window.h"
#else
#error "Unknown Window backend for GLEEC!"
#endif

#include "Internal/Input/Backend.h"

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/GLFW/Mode.h"
#else
#error "Unknown Input backend for GLEEC!"
#endif

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Surface.h"
#include "Internal/Graphics/vk/Swapchain.h"
#endif

#include "Core/Graphics/InstanceManager.h"
#include "Core/Graphics/GPUManager.h"

#include "WindowInfo.h"
#include "Core/Image/Image.h"

namespace GLEEC::Window
{
    struct Window
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Window::glfw::Window internalWindow = nullptr;
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::Surface surface = {};
        Internal::Graphics::vk::Swapchain swapchain = {};
#endif

        bool vSync = true;

        bool operator==(const Window&) const = default;
        bool operator!=(const Window&) const = default;

        bool isOpen() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            return !Internal::Window::glfw::windowShouldClose(internalWindow);
#else
            return false;
#endif
        }

        void title(std::string_view titl) const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            Internal::Window::glfw::setWindowTitle(internalWindow, titl);
#endif
        }

        void icon(const Image::Image& image) const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            GLFWimage i = {};

            i.pixels = image.data;
            i.width = image.width;
            i.height = image.height;

            Internal::Window::glfw::setWindowIcon(internalWindow, i);
#endif
        }

        math::ivec2 pos() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            return Internal::Window::glfw::getWindowPos(internalWindow);
#else
            return { 0, 0 };
#endif
        }

        void pos(const math::ivec2& position) const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            Internal::Window::glfw::setWindowPos(internalWindow, position);
#endif
        }

        math::ivec2 size() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            return Internal::Window::glfw::getWindowSize(internalWindow);
#else
            return { 0, 0 };
#endif
        }

        void size(const math::ivec2& dim) const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            Internal::Window::glfw::setWindowSize(internalWindow, dim);
#endif
        }

        float opacity() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            return Internal::Window::glfw::getWindowOpacity(internalWindow);
#else
            return 1.0f; // TODO: return 1, 0, or -1?
#endif
        }

        void opacity(float opa)
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            Internal::Window::glfw::setWindowOpacity(internalWindow, opa);
#endif
        }

        void hide() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            Internal::Window::glfw::iconifyWindow(internalWindow);
#endif
        }

        void show() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            Internal::Window::glfw::restoreWindow(internalWindow);
#endif
        }

        void maximize() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            Internal::Window::glfw::maximizeWindow(internalWindow);
#endif
        }

        void focus() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            Internal::Window::glfw::focusWindow(internalWindow);
#endif
        }

        void requestAttention() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            Internal::Window::glfw::requestWindowAttention(internalWindow);
#endif
        }

        Monitor monitor() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            return { Internal::Window::glfw::getWindowMonitor(internalWindow) };
#endif
        }

        void monitor(Monitor mom) const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            Internal::Window::glfw::setWindowMonitor(internalWindow, mom.internalMonitor, pos(), size());
#endif
        }

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Window() = default;
        Window(GLFWwindow* w)
            : internalWindow(w)
        {
        }
#endif

        bool minimized = false;
    };
}
