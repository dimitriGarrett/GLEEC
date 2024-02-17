#pragma once

#include "Internal/Window/Backend.h"

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
#include "Internal/Window/GLFW/Window.h"
#else
#error "Unknown Window backend for GLEEC!"
#endif

#include "WindowInfo.h"
#include "Core/Image/Image.h"

namespace GLEEC::Window
{
    struct Window
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Window::glfw::Window internalWindow = nullptr;
#endif

        Window() = default;

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
#if GLEEC_WINDOW_BACKEND == WIDNOW_BACKEND_GLFW
            Internal::Window::glfw::setWindowMonitor(internalWindow, mom.internalMonitor, pos(), size());
#endif
        }

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Window(WindowInfo info)
        {
            Internal::Window::glfw::windowHint(GLFW_RESIZABLE, info.resizable);

            // we don't use OpenGL around here
            Internal::Window::glfw::windowHint(GLFW_CLIENT_API, GLFW_NO_API);
            // its vulkan time baby

            internalWindow = Internal::Window::glfw::createWindow(info.dim, info.name, info.monitor.internalMonitor);

            if (info.vSync)
            {
                // TODO: THIS NEEDS TO BE HANDLED WITH THE VULKAN WINDOW
            }
        }
#else
        Window(WindowInfo) {}
#endif
    };
}
