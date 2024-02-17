#pragma once

#include "Internal/Input/Backend.h"

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
#include "Internal/Input/GLFW/Mode.h"
#else
#error "Unknown Input backend for GLEEC!"
#endif

#include "Core/Window/WindowManager.h"

namespace GLEEC::Input
{
    inline bool rawMouseMotionSupported()
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return glfwRawMouseMotionSupported();
#else
        return false;
#endif
    }

    inline void hideCursor(Window::Window window)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
#endif
    }

    inline void showCursor(Window::Window window)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_CURSOR, GLFW_CURSOR_NORMAL);
#endif
    }

    inline void disableCursor(Window::Window window)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#else
        hideCursor(window);
#endif
    }

    inline void enableStickyKeys(Window::Window window)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_STICKY_KEYS, GLFW_TRUE);
#endif
    }

    inline void disableStickyKeys(Window::Window window)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_STICKY_KEYS, GLFW_FALSE);
#endif
    }

    inline void enableStickyMouseButtons(Window::Window window)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
#endif
    }

    inline void disableStickyMouseButtons(Window::Window window)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_STICKY_MOUSE_BUTTONS, GLFW_FALSE);
#endif
    }

    inline void enableLockKeyMods(Window::Window window)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_LOCK_KEY_MODS, GLFW_TRUE);
#endif
    }

    inline void disableLockKeyMods(Window::Window window)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_LOCK_KEY_MODS, GLFW_FALSE);
#endif
    }

    inline void enableRawMouseMotion(Window::Window window)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        if (!rawMouseMotionSupported())
        {
            LOG_ERROR("Raw mouse motion is not supported!");
        }

        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
#endif
    }

    inline void disableRawMouseMotion(Window::Window window)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(window.internalWindow,
            GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
#endif
    }

    inline void hideCursor()
    {
        for (const Window::Window& window : Window::WindowManager::windows)
        {
            hideCursor(window);
        }
    }

    inline void showCursor()
    {
        for (const Window::Window& window : Window::WindowManager::windows)
        {
            showCursor(window);
        }
    }

    inline void disableCursor()
    {
        for (const Window::Window& window : Window::WindowManager::windows)
        {
            disableCursor(window);
        }
    }

    inline void enableStickyKeys()
    {
        for (const Window::Window& window : Window::WindowManager::windows)
        {
            enableStickyKeys(window);
        }
    }

    inline void disableStickyKeys()
    {
        for (const Window::Window& window : Window::WindowManager::windows)
        {
            disableStickyKeys(window);
        }
    }

    inline void enableStickyMouseButtons()
    {
        for (const Window::Window& window : Window::WindowManager::windows)
        {
            enableStickyMouseButtons(window);
        }
    }

    inline void disableStickyMouseButtons()
    {
        for (const Window::Window& window : Window::WindowManager::windows)
        {
            disableStickyMouseButtons(window);
        }
    }

    inline void enableLockKeyMods()
    {
        for (const Window::Window& window : Window::WindowManager::windows)
        {
            enableLockKeyMods(window);
        }
    }

    inline void disableLockKeyMods()
    {
        for (const Window::Window& window : Window::WindowManager::windows)
        {
            disableLockKeyMods(window);
        }
    }

    inline void enableRawMouseMotion()
    {
        for (const Window::Window& window : Window::WindowManager::windows)
        {
            enableRawMouseMotion(window);
        }
    }

    inline void disableRawMouseMotion()
    {
        for (const Window::Window& window : Window::WindowManager::windows)
        {
            disableRawMouseMotion(window);
        }
    }

    inline void hideCursorActiveWindow()
    {
        hideCursor(Window::WindowManager::activeWindow());
    }

    inline void showCursorActiveWindow()
    {
        showCursor(Window::WindowManager::activeWindow());
    }

    inline void disableCursorActiveWindow()
    {
        disableCursor(Window::WindowManager::activeWindow());
    }

    inline void enableStickyKeysActiveWindow()
    {
        enableStickyKeys(Window::WindowManager::activeWindow());
    }

    inline void disableStickyKeysActiveWindow()
    {
        disableStickyKeys(Window::WindowManager::activeWindow());
    }

    inline void enableStickyMouseButtonsActiveWindow()
    {
        enableStickyMouseButtons(Window::WindowManager::activeWindow());
    }

    inline void disableStickyMouseButtonsActiveWindow()
    {
        disableStickyMouseButtons(Window::WindowManager::activeWindow());
    }

    inline void enableLockKeyModsActiveWindow()
    {
        enableLockKeyMods(Window::WindowManager::activeWindow());
    }

    inline void disableLockKeyModsActiveWindow()
    {
        disableLockKeyMods(Window::WindowManager::activeWindow());
    }

    inline void enableRawMouseMotionActiveWindow()
    {
        enableRawMouseMotion(Window::WindowManager::activeWindow());
    }

    inline void disableRawMouseMotionActiveWindow()
    {
        disableRawMouseMotion(Window::WindowManager::activeWindow());
    }
}
