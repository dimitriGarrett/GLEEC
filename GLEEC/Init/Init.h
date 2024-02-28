#pragma once

#include "Config/Init.h"
#include "Core/Input/Init.h"
#include "Core/Event/Event.h"
#include "Core/Window/Init.h"
#include "Core/Audio/Init.h"
#include "Core/Config/Configuration.h"
#include "Core/Localization/LanguageManager.h"
#include "Core/Graphics/Init.h"

namespace GLEEC
{
    inline void firstInit()
    {
        printInitString();

        Input::init();
        Window::init();
        Event::init();

        Audio::init();

        Config::Configuration::init();
        Localization::LanguageManager::init();

        Graphics::firstInit();
    }

    inline void init(const std::vector<Window::WindowInfo>& windowInfos)
    {
        if (windowInfos.size() > GLEEC_WINDOW_MAX_WINDOWS)
        {
            LOG_WARNING("Too many windows for GLEEC, requested: {}, but only {} are available, try changing GLEEC_WINDOW_MAX_WINDOWS in WindowManager.h!", windowInfos.size(), GLEEC_WINDOW_MAX_WINDOWS);
        }

        for (const Window::WindowInfo& windowInfo : windowInfos)
        {
            Window::WindowManager::createWindow(windowInfo);
        }

        Graphics::init();
    }

    inline void init(const Window::WindowInfo& windowInfo)
    {
        init(std::vector<Window::WindowInfo>{ windowInfo });
    }

    inline void terminate()
    {
        Audio::terminate();
        Window::terminate();
        Input::terminate();
    }
}
