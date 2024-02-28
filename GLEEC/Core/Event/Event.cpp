#include "Event.h"

#include "Core/Window/WindowManager.h" 

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/Keyboard.h"
#include "Internal/Input/Joystick.h"
#endif

#include "Core/Input/Remapping/Remapper.h"

#include "Internal/Log/EnableInternalLogging"

namespace GLEEC::Event
{
    void init()
    {
        addListener<WindowCreate>(+[](Window::Window window)
        {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
            glfwSetMouseButtonCallback(window.internalWindow, +[](GLFWwindow* w, int button, int action, int mods)
            {
                Input::Remapper& rp = Input::Remapper::currentPreset();

                if (action == GLFW_PRESS)
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) mouse button pressed: {}, mods: {}", static_cast<void*>(w), button, mods);
#endif
                    Event::fireEvent<MousePressed>(
                        rp.remap({ mods, button }).state,
                        rp.remap({ mods, button }).mods);
                }

                else if (action == GLFW_REPEAT)
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) mouse button repeated: {}, mods: {}", static_cast<void*>(w), button, mods);
#endif
                    Event::fireEvent<MouseRepeat>(
                        rp.remap({ mods, button }).state,
                        rp.remap({ mods, button}).mods);
                }
                
                else
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) mouse button released: {}, mods: {}", static_cast<void*>(w), button, mods);
#endif
                    Event::fireEvent<MouseReleased>(
                        rp.remap({ mods, button }).state,
                        rp.remap({ mods, button }).mods);
                }
            });

            glfwSetCursorPosCallback(window.internalWindow, +[](GLFWwindow* w, double x, double y)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) cursor moved, x: {}, y: {}", static_cast<void*>(w), x, y);
#endif
                Event::fireEvent<CursorPos>(x, y);
            });

            glfwSetCursorEnterCallback(window.internalWindow, +[](GLFWwindow* w, int enter)
            {
                if (enter)
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) cursor entered!", static_cast<void*>(w));
#endif
                    Event::fireEvent<CursorEnter>();
                }

                else
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) cursor left!", static_cast<void*>(w));
#endif
                    Event::fireEvent<CursorLeave>();
                }
            });

            glfwSetScrollCallback(window.internalWindow, +[](GLFWwindow* w, double x, double y)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) mouse scrolled, offX: {}, offY: {}", static_cast<void*>(w), x, y);
#endif
                Event::fireEvent<Scroll>(x, y);
            });
            
            glfwSetKeyCallback(window.internalWindow, +[](GLFWwindow* w, int key, int scancode, int action, int mods)
            {
                Input::Remapper& rp = Input::Remapper::currentPreset();
                if (action == GLFW_PRESS)
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) key pressed, key: \"{}\", scancode: {}, mods: {}", static_cast<void*>(w), key, scancode, mods);
#endif
                    Event::fireEvent<KeyPressed>(
                        rp.remap({ mods, key }).state,
                        scancode,
                        rp.remap({ mods, key }).mods);
                }

                else if (action == GLFW_REPEAT)
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) key repeated, key: \"{}\", scancode: {}, mods: {}", static_cast<void*>(w), key, scancode, mods);
#endif
                    Event::fireEvent<KeyRepeat>(
                        rp.remap({ mods, key }).state,
                        scancode,
                        rp.remap({ mods, key}).mods);
                }

                else
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) key released, key: \"{}\", scancode: {}, mods: {}", static_cast<void*>(w), key, scancode, mods);
#endif
                    Event::fireEvent<KeyReleased>(
                        rp.remap({ mods, key }).state,
                        scancode,
                        rp.remap({ mods, key }).mods);
                }
            });

            glfwSetCharCallback(window.internalWindow, +[](GLFWwindow* w, unsigned int codepoint)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) character pressed, codepoint: {}", static_cast<void*>(w), codepoint);
#endif
                Event::fireEvent<Char>(codepoint);
            });

            glfwSetCharModsCallback(window.internalWindow, +[](GLFWwindow* w, unsigned int codepoint, int mods)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) character pressed, codepoint: {}, mods: {}", static_cast<void*>(w), codepoint, mods);
#endif
                Event::fireEvent<CharMods>(codepoint, mods);
            });

            glfwSetDropCallback(window.internalWindow, +[](GLFWwindow* w, int count, const char** paths)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) had paths dropped:", static_cast<void*>(w));
                for (int i = 0; i < count; ++i)
                    LOG_INFO("\t\"{}\"", paths[i]);
#endif
                Event::fireEvent<Drop>(Window::Window{ w },
                    std::vector<const char*>(paths, paths + count));
            });

            glfwSetJoystickCallback(+[](int jid, int event)
            {
                if (event == GLFW_CONNECTED)
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("Joystick (jid: {}) connected!", jid);

                    if (!Internal::Input::glfw::joystickIsGamepad(jid))
                    {
                        LOG_ERROR("Joystick (jid: {}) does not have a gamepad mapping, don't know what to do!", jid);
                    }
#endif
                    Event::fireEvent<JoystickConnected>(jid);
                }

                else
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("Joystick (jid: {}) disconnected!", jid);
#endif
                    Event::fireEvent<JoystickDisconnected>(jid);
                }
            });
#endif

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            glfwSetWindowPosCallback(window.internalWindow, +[](GLFWwindow* w, int x, int y)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) pos: ({}, {})", static_cast<void*>(w), x, y);
#endif
                Event::fireEvent<WindowPos>(Window::Window{ w }, x, y);
            });

            glfwSetWindowSizeCallback(window.internalWindow, +[](GLFWwindow* w, int x, int y)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) size: ({}, {})", static_cast<void*>(w), x, y);
#endif
                Event::fireEvent<WindowResize>(Window::Window{ w }, x, y);
            });

            glfwSetWindowCloseCallback(window.internalWindow, +[](GLFWwindow* w)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) closed!", static_cast<void*>(w));
#endif
                Event::fireEvent<WindowClose>(Window::Window{ w });

                // having this here makes it hard to predict what will happen
                // with resources and other window stuff, so it is moved to
                // windowManager::destroyWindow
                // destroyWindow(w);
            });

            glfwSetWindowRefreshCallback(window.internalWindow, +[](GLFWwindow* w)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) refreshed!", static_cast<void*>(w));
#endif
                Event::fireEvent<WindowRefresh>(Window::Window{ w });
            });

            glfwSetWindowFocusCallback(window.internalWindow, +[](GLFWwindow* w, int focus)
            {
                if (focus)
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) gained focus!", static_cast<void*>(w));
#endif
                    Event::fireEvent<WindowFocus>(Window::Window{ w });
                }

                else
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) lost focus!", static_cast<void*>(w));
#endif
                    Event::fireEvent<WindowLostFocus>(Window::Window{ w });
                }
            });

            glfwSetWindowIconifyCallback(window.internalWindow, +[](GLFWwindow* w, int iconified)
            {
                if (iconified)
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) iconified!", static_cast<void*>(w));
#endif
                    Event::fireEvent<WindowIconify>(Window::Window{ w });
                }

                else
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) restored!", static_cast<void*>(w));
#endif
                    Event::fireEvent<WindowRestore>(Window::Window{ w });
                }
            });

            glfwSetWindowMaximizeCallback(window.internalWindow, +[](GLFWwindow* w, int maximized)
            {
                if (maximized)
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) maximized!", static_cast<void*>(w));
#endif
                    Event::fireEvent<WindowMaximize>(Window::Window{ w });
                }

                else
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Window: {}) unmaximized!", static_cast<void*>(w));
#endif
                    Event::fireEvent<WindowUnmaximize>(Window::Window{ w });
                }
            });

            glfwSetFramebufferSizeCallback(window.internalWindow, +[](GLFWwindow* w, int width, int height)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) framebuffer size: ({}, {})", static_cast<void*>(w), width, height);
#endif
                Event::fireEvent<FramebufferSize>(Window::Window{ w }, width, height);
            });

            glfwSetWindowContentScaleCallback(window.internalWindow, +[](GLFWwindow* w, float width, float height)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) content scale: ({}, {})", static_cast<void*>(w), width, height);
#endif
                Event::fireEvent<WindowContentScale>(Window::Window{ w }, width, height);
            });

            glfwSetMonitorCallback([](GLFWmonitor* m, int event)
            {
                if (event == GLFW_CONNECTED)
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Monitor: {}): \"{}\" connected!", static_cast<void*>(m), 
                        Internal::Window::glfw::getMonitorName(m));
#endif
                    Event::fireEvent<MonitorConnected>(Window::Monitor{ m });
                }

                else
                {
#if GLEEC_ALL_INTERNAL_LOGGING
                    LOG_INFO("(Monitor: {}): \"{}\" disconnected!", static_cast<void*>(m),
                        Internal::Window::glfw::getMonitorName(m));
#endif
                    Event::fireEvent<MonitorDisconnected>(Window::Monitor{ m });
                }
            });
#endif
        });
    }
}
