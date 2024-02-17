#pragma once

#include "Monitor.h"

namespace GLEEC::Window
{
    struct WindowInfo
    {
        math::ivec2 dim = {};

        std::string name = "";

        Monitor monitor = {};

        bool vSync = true;
        bool resizable = false; // default is false until vulkan is working
                                // TODO: change this to true
    };
}
