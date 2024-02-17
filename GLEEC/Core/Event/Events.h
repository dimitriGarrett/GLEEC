#pragma once

namespace GLEEC::Event
{
    struct WindowPos {};
    struct WindowResize {};
    struct WindowClose {};
    struct WindowRefresh {};
    struct WindowFocus {};
    struct WindowLostFocus {};
    struct WindowIconify {};
    struct WindowRestore {};
    struct WindowMaximize {};
    struct WindowUnmaximize {};
    struct FramebufferSize {};
    struct WindowContentScale {};

    struct MousePressed {};
    struct MouseReleased {};
    struct CursorPos {};
    struct CursorEnter {};
    struct CursorLeave {};
    struct Scroll {};
    struct KeyPressed {};
    struct KeyRepeat {};
    struct KeyReleased {};
    struct Char {};
    struct CharMods {};
    struct Drop {};
    struct JoystickConnected {};
    struct JoystickDisconnected {};

    struct GLFWError {};

    struct MonitorConnected {};
    struct MonitorDisconnected {};
}
