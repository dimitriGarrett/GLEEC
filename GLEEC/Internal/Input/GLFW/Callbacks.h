#pragma once

#include "Internal/Event/Subway.h"
#include "Internal/Input/Events.h"

#include "Internal/Window/Window.h"
#include "Internal/Input/Keyboard.h"
#include "Internal/Input/Joystick.h"

#include "Internal/Log/EnableInternalLogging"

#if GLEEC_ALL_INTERNAL_LOGGING
#include "Internal/Log/Log.h"
#endif

namespace GLEEC::Internal::Input::glfw
{
    using MouseButtonCallback = void(*)(GLFWwindow*, int, int, int);
    using CursorPosCallback = void(*)(GLFWwindow*, double, double);
    using CursorEnterCallback = void(*)(GLFWwindow*, int);
    using ScrollCallback = void(*)(GLFWwindow*, double, double);
    using KeyCallback = void(*)(GLFWwindow*, int, int, int, int);
    using CharCallback = void(*)(GLFWwindow*, unsigned int);
    using CharModsCallback = void(*)(GLFWwindow*, unsigned int, int);
    using DropCallback = void(*)(GLFWwindow*, int, const char**);
    using JoystickCallback = void(*)(int, int);

    inline void setMouseButtonCallback(Window::glfw::Window window)
    {
        glfwSetMouseButtonCallback(window, +[](GLFWwindow* w, int button, int action, int mods)
        {
            if (action)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) mouse button pressed: {}, mods: {}", static_cast<void*>(w), button, mods);
#endif
                Event::fireEvent<Events::MousePressedEvent>(button, mods);
            }
            
            else
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) mouse button released: {}, mods: {}", static_cast<void*>(w), button, mods);
#endif
            }
                Event::fireEvent<Events::MouseReleasedEvent>(button, mods);
        });
    }

    inline void setCursorPosCallback(Window::glfw::Window window)
    {
        glfwSetCursorPosCallback(window, +[](GLFWwindow* w, double x, double y)
        {
#if GLEEC_ALL_INTERNAL_LOGGING
            LOG_INFO("(Window: {}) cursor moved, x: {}, y: {}", static_cast<void*>(w), x, y);
#endif
            Event::fireEvent<Events::CursorPosEvent>(x, y);
        });
    }

    inline void setCursorEnterCallback(Window::glfw::Window window)
    {
        glfwSetCursorEnterCallback(window, +[](GLFWwindow* w, int enter)
        {
            if (enter)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) cursor entered!", static_cast<void*>(w));
#endif
                Event::fireEvent<Events::CursorEnterEvent>();
            }

            else
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) cursor left!", static_cast<void*>(w));
#endif
                Event::fireEvent<Events::CursorLeaveEvent>();
            }
        });
    }

    inline void setScrollCallback(Window::glfw::Window window)
    {
        glfwSetScrollCallback(window, +[](GLFWwindow* w, double x, double y)
        {
#if GLEEC_ALL_INTERNAL_LOGGING
            LOG_INFO("(Window: {}) mouse scrolled, offX: {}, offY: {}", static_cast<void*>(w), x, y);
#endif
            Event::fireEvent<Events::ScrollEvent>(x, y);
        });
    }

    inline void setKeyCallback(Window::glfw::Window window)
    {
        glfwSetKeyCallback(window, +[](GLFWwindow* w, int key, int scancode, int action, int mods)
        {
            if (action == GLFW_PRESS)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) key pressed, key: \"{}\", scancode: {}, mods: {}", static_cast<void*>(w), key, scancode, mods);
#endif
                Event::fireEvent<Events::KeyPressedEvent>(key, scancode, mods);
            }

            else if (action == GLFW_REPEAT)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) key repeated, key: \"{}\", scancode: {}, mods: {}", static_cast<void*>(w), key, scancode, mods);
#endif
                Event::fireEvent<Events::KeyRepeatEvent>(key, scancode, mods);
            }

            else
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) key released, key: \"{}\", scancode: {}, mods: {}", static_cast<void*>(w), key, scancode, mods);
#endif
                Event::fireEvent<Events::KeyReleasedEvent>(key, scancode, mods);
            }
        });
    }

    inline void setCharCallback(Window::glfw::Window window)
    {
        glfwSetCharCallback(window, +[](GLFWwindow* w, unsigned int codepoint)
        {
#if GLEEC_ALL_INTERNAL_LOGGING
            LOG_INFO("(Window: {}) character pressed, codepoint: {}", static_cast<void*>(w), codepoint);
#endif
            Event::fireEvent<Events::CharEvent>(codepoint);
        });
    }

    inline void setCharModsCallback(Window::glfw::Window window)
    {
        glfwSetCharModsCallback(window, +[](GLFWwindow* w, unsigned int codepoint, int mods)
        {
#if GLEEC_ALL_INTERNAL_LOGGING
            LOG_INFO("(Window: {}) character pressed, codepoint: {}, mods: {}", static_cast<void*>(w), codepoint, mods);
#endif
            Event::fireEvent<Events::CharModsEvent>(codepoint, mods);
        });
    }

    inline void setDropCallback(Window::glfw::Window window)
    {
        glfwSetDropCallback(window, +[](GLFWwindow* w, int count, const char** paths)
        {
#if GLEEC_ALL_INTERNAL_LOGGING
            LOG_INFO("(Window: {}) had paths dropped:", static_cast<void*>(w));
            for (int i = 0; i < count; ++i)
                LOG_INFO("\t\"{}\"", paths[i]);
#endif
            std::vector<const char*> temp(paths, paths + count);
            Event::fireEvent<Events::DropEvent>(Window::glfw::Window{ w }, temp);
        });
    }

    inline void setJoystickCallback()
    {
        glfwSetJoystickCallback(+[](int jid, int event)
        {
            if (event == GLFW_CONNECTED)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("Joystick (jid: {}) connected!", jid);

                if (!Input::glfw::joystickIsGamepad(jid))
                {
                    LOG_ERROR("Joystick (jid: {}) does not have a gamepad mapping, don't know what to do!", jid);
                }
#endif
                Event::fireEvent<Events::JoystickConnectedEvent>(jid);
            }

            else
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("Joystick (jid: {}) disconnected!", jid);
#endif
                Event::fireEvent<Events::JoystickDisconnectedEvent>(jid);
            }
        });
    }

    inline void setAllCallbacks(Window::glfw::Window window)
    {
        setMouseButtonCallback(window);
        setCursorPosCallback(window);
        setCursorEnterCallback(window);
        setScrollCallback(window);
        setKeyCallback(window);
        setCharCallback(window);
        setCharModsCallback(window);
        setDropCallback(window);
        setJoystickCallback(); // doesn't depend on window
                                      // but it needs to be called
                                      // at least once. oh well :|
    }
}
