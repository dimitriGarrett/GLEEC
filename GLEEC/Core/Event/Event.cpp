#include "Event.h"

#include "Core/Window/WindowManager.h"
#include "Core/Input/Remapping/Remapper.h"

#include "Events.h"
#include "Internal/Input/Events.h"

#include "Internal/Window/Monitor.h"

#include "Core/Input/Joystick.h"

namespace GLEEC::Event
{
    inline void init()
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        addListener<Internal::Events::MonitorConnectedEvent>(+[](Internal::Window::glfw::Monitor m)
        {
            fireEvent<MonitorConnected>(Window::Monitor{ m });
        });

        addListener<Internal::Events::MonitorDisconnectedEvent>(+[](Internal::Window::glfw::Monitor m)
        {
            fireEvent<MonitorDisconnected>(Window::Monitor{ m });
        });

        addListener<Internal::Events::WindowPosEvent>(+[](Internal::Window::glfw::Window w, int x, int y)
        {
            fireEvent<WindowPos>(
                Window::WindowManager::findWindow(w), x, y);
        });

        addListener<Internal::Events::WindowResizeEvent>(+[](Internal::Window::glfw::Window w, int x, int y)
        {
            fireEvent<WindowResize>(
                Window::WindowManager::findWindow(w), x, y);
        });

        addListener<Internal::Events::WindowCloseEvent>(+[](Internal::Window::glfw::Window w)
        {
            fireEvent<WindowClose>(
                Window::WindowManager::findWindow(w));
        });

        addListener<Internal::Events::WindowRefreshEvent>(+[](Internal::Window::glfw::Window w)
        {
            fireEvent<WindowRefresh>(
                Window::WindowManager::findWindow(w));
        });

        addListener<Internal::Events::WindowFocusEvent>(+[](Internal::Window::glfw::Window w)
        {
            fireEvent<WindowFocus>(
                Window::WindowManager::findWindow(w));
        });

        addListener<Internal::Events::WindowLostFocusEvent>(+[](Internal::Window::glfw::Window w)
        {
            fireEvent<WindowLostFocus>(
                Window::WindowManager::findWindow(w));
        });

        addListener<Internal::Events::WindowIconifyEvent>(+[](Internal::Window::glfw::Window w)
        {
            fireEvent<WindowIconify>(
                Window::WindowManager::findWindow(w));
        });

        addListener<Internal::Events::WindowRestoreEvent>(+[](Internal::Window::glfw::Window w)
        {
            fireEvent<WindowRestore>(
                Window::WindowManager::findWindow(w));
        });

        addListener<Internal::Events::WindowMaximizeEvent>(+[](Internal::Window::glfw::Window w)
        {
            fireEvent<WindowMaximize>(
                    Window::WindowManager::findWindow(w));
        });

        addListener<Internal::Events::WindowUnmaximizeEvent>(+[](Internal::Window::glfw::Window w)
        {
            fireEvent<WindowUnmaximize>(
                Window::WindowManager::findWindow(w));
        });

        addListener<Internal::Events::FramebufferSizeEvent>(+[](Internal::Window::glfw::Window w, int width, int height)
        {
            fireEvent<FramebufferSize>(
                Window::WindowManager::findWindow(w), width, height);
        });

        addListener<Internal::Events::WindowContentScaleEvent>(+[](Internal::Window::glfw::Window w, int width, int height)
        {
            fireEvent<WindowContentScale>(
                Window::WindowManager::findWindow(w), width, height);
        });

        addListener<Internal::Events::CursorEnterEvent>(+[](Internal::Window::glfw::Window w)
        {
            fireEvent<CursorEnter>();
        });

        addListener<Internal::Events::CursorLeaveEvent>(+[](Internal::Window::glfw::Window w)
        {
            fireEvent<CursorLeave>();
        });

        addListener<Internal::Events::DropEvent>(+[](Internal::Window::glfw::Window w, const std::vector<const char*>& paths)
        {
            fireEvent<Drop>(
                Window::WindowManager::findWindow(w), paths);
        });
#endif

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW && GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        addListener<Internal::Events::MousePressedEvent>(+[](int button, int mods)
        {
            Input::Remapper& rp = Input::Remapper::currentPreset();

            fireEvent<MousePressed>(rp.remap({ mods, button }).state, rp.remap({ mods, button }).mods);
        });

        addListener<Internal::Events::MouseReleasedEvent>(+[](int button, int mods)
        {
            Input::Remapper& rp = Input::Remapper::currentPreset();

            fireEvent<MouseReleased>(rp.remap({ mods, button }).state, rp.remap({ mods, button }).mods);
        });

        addListener<Internal::Events::CursorPosEvent>(+[](double x, double y)
        {
            fireEvent<CursorPos>(x, y);
        });

        addListener<Internal::Events::ScrollEvent>(+[](double x, double y)
        {
            fireEvent<Scroll>(x, y);
        });

        addListener<Internal::Events::KeyPressedEvent>(+[](int key, int scancode, int mods)
        {
            Input::Remapper& rp = Input::Remapper::currentPreset();

            fireEvent<KeyPressed>(rp.remap({ mods, key }).state, scancode, rp.remap({ mods, key }).mods);
        });

        addListener<Internal::Events::KeyRepeatEvent>(+[](int key, int scancode, int mods)
        {
            Input::Remapper& rp = Input::Remapper::currentPreset();

            fireEvent<KeyRepeat>(rp.remap({ mods, key }).state, scancode, rp.remap({ mods, key }).mods);
        });

        addListener<Internal::Events::KeyReleasedEvent>(+[](int key, int scancode, int mods)
        {
            Input::Remapper& rp = Input::Remapper::currentPreset();

            fireEvent<KeyReleased>(rp.remap({ mods, key }).state, scancode, rp.remap({ mods, key }).mods);
        });

        addListener<Internal::Events::CharEvent>(+[](int codepoint)
        {
            // no remapping because the whole point is for text input
            fireEvent<Char>(codepoint);
        });

        addListener<Internal::Events::CharModsEvent>(+[](int codepoint, int mods)
        {
            // no remapping because the whole point is for text input
            fireEvent<CharMods>(codepoint, mods);
        });

        addListener<Internal::Events::JoystickConnectedEvent>(+[](int jid)
        {
            fireEvent<JoystickConnected>(Input::Joystick(jid));
        });

        addListener<Internal::Events::JoystickDisconnectedEvent>(+[](int jid)
        {
            fireEvent<JoystickDisconnected>(Input::Joystick(jid));
        });
#endif
    }
}
