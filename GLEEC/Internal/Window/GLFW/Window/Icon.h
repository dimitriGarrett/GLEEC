#pragma once

#include "Window.h"

#include <vector>

namespace GLEEC::Internal::Window::glfw
{
    inline void setWindowIcon(Window window, const std::vector<GLFWimage>& images)
    {
            glfwSetWindowIcon(window, static_cast<int>(images.size()),
                                      images.data());
    }

    inline void setWindowIcon(Window window, const GLFWimage& image)
    {
        glfwSetWindowIcon(window, 1, &image);
    }
}
