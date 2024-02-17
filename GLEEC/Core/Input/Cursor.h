#pragma once

#include "Internal/Input/Backend.h"

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/GLFW/Cursor.h"
#else
#error "Unknown Input backend for GLEEC!"
#endif

#include "Core/Window/WindowManager.h"

namespace GLEEC::Input
{
    inline math::dvec2 pos()
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return Internal::Input::glfw::getCursorPos(
            Window::WindowManager::activeWindow().internalWindow);
#else
        return { -1.0, -1.0 };
#endif
    }

    inline void pos(const math::dvec2& position)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::setCursorPos(
            Window::WindowManager::activeWindow().internalWindow,
            position);
#endif
    }
}
