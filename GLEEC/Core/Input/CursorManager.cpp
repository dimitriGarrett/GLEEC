#include "CursorManager.h"

#include "Internal/Input/Backend.h"

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
#include "Internal/Input/GLFW/Mode.h"
#include "Internal/Input/GLFW/Cursor.h"
#endif

namespace GLEEC::Input
{
    inline void CursorManager::setPosition(const Cursor& cursor,
        const math::vec2& pos)
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Input::glfw::setCursorPos(cursor.window.internalWindow, pos);
#endif
    }

    inline math::vec2 CursorManager::getPosition(const Cursor& cursor)
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        return Internal::Input::glfw::getCursorPos(cursor.window.internalWindow);
#endif
    }

    inline void CursorManager::hideCursor(const Cursor& cursor)
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(cursor.window.internalWindow,
            GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
#endif
    }

    inline void CursorManager::showCursor(const Cursor& cursor)
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(cursor.window.internalWindow,
            GLFW_CURSOR, GLFW_CURSOR_NORMAL);
#endif
    }

    inline void CursorManager::disableCursor(const Cursor& cursor)
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Input::glfw::setInputMode(cursor.window.internalWindow,
            GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
    }
}
