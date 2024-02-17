#pragma once

namespace GLEEC::Internal::Events
{
    struct WindowPosEvent {};
    struct WindowResizeEvent {};
    struct WindowCloseEvent {};
    struct WindowRefreshEvent {};
    struct WindowFocusEvent {};
    struct WindowLostFocusEvent {};
    struct WindowIconifyEvent {};
    struct WindowRestoreEvent {};
    struct WindowMaximizeEvent {};
    struct WindowUnmaximizeEvent {};
    struct FramebufferSizeEvent {};
    struct WindowContentScaleEvent {};

    struct GLFWErrorEvent {};

    struct MonitorConnectedEvent {};
    struct MonitorDisconnectedEvent {};

    struct WindowCreated;
}
