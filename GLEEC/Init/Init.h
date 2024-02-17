#pragma once

#include "Config/Init.h"
#include "Core/Input/Init.h"
#include "Core/Event/Event.h"
#include "Core/Window/Init.h"
#include "Core/Audio/Init.h"
#include "Core/Config/Configuration.h"
#include "Core/Localization/LanguageManager.h"

namespace GLEEC
{
    inline void init()
    {
        printInitString();

        Input::init();
        Event::init();
        
        Window::init();

        Audio::init();

        Config::Configuration::init();
        Localization::LanguageManager::init();
    }

    inline void terminate()
    {
        Audio::terminate();
        Window::terminate();
        Input::terminate();
    }
}
