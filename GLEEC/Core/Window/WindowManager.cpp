#include "WindowManager.h"

#include "Core/Event/Event.h"

namespace GLEEC::Window
{
    int WindowManager::openWindows = 0;
    std::array<Window, GLEEC_WINDOW_MAX_WINDOWS> WindowManager::windows = {};

    inline void swap(Window& a, Window& b)
    {
        Window&& c = std::move(b);
        b = std::move(a);
        a = std::move(c);
    }

    void WindowManager::registerCallbacks()
    {
/*         need to add core event stuff */

        Event::addListener<Event::WindowClose>(+[](Window w)
        {
            // why this is needed: for example:
            // if you close a window that was the first one created
            // and you created the max amount of windows, 
            // and create another one, it will overwrite an active window
            // instead of overwriting the just closed window
            //
            // this swaps the closed window with the last
            // window to make sure this doesn't happen
            // 
            // also ignores if the window list isn't full
            if (WindowManager::openWindows + 1 == GLEEC_WINDOW_MAX_WINDOWS && w != WindowManager::windows.back())
            {
                for (int i = 0; i < GLEEC_WINDOW_MAX_WINDOWS - 1; ++i)
                {
                    if (WindowManager::windows.at(i) == w)
                    {
                        swap(WindowManager::windows.at(i), WindowManager::windows.back());
                        break;
                    }
                }
            }

            --WindowManager::openWindows;
        });

        Event::addListener<Event::WindowFocus>(+[](Window w)
        {
            if (w == WindowManager::windows[0])
            {
                return;
            }

            for (int i = 1; i < GLEEC_WINDOW_MAX_WINDOWS; ++i)
            {
                if (WindowManager::windows.at(i) == w)
                {
                    swap(WindowManager::windows.at(i), WindowManager::windows.front());
                    break;
                }
            }
        });

        // TODO: add framebuffer resize event listener for vulkan
        Event::addListener<Event::FramebufferSize>(+[](Window w, int width, int height)
        {
            // TODO: implement
        });
    }
}
