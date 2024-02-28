#pragma once

#include "WindowManager.h"
#include "MonitorManager.h"

namespace GLEEC::Window
{
    inline void init()
    {
        MonitorManager::init();

        WindowManager::init();
    }

    inline void terminate()
    {
        // nothing here (used to be)
        WindowManager::destroy();
    }
}
