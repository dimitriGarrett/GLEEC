#include <iostream>

#include "Config/Init.h"

#include "Internal/Event/Bus.h"
#include "Internal/Event/Subway.h"
#include "Internal/Input/GLFW/Init.h"
#include "Internal/Window/Callbacks.h"
#include "Internal/Window/GLFW/Monitor.h"
#include "Internal/Window/Window.h"
#include "Internal/utility/string.h"

#include "Internal/Input/GLFW/Update.h"

#include "Internal/Audio/Init.h"
#include "Internal/Audio/OpenAL/Speaker.h"

#include "Core/Audio/Audio.h"

#include "Internal/Localization/Locale.h"

#include "Core/Window/WindowManager.h"
#include "Core/Window/MonitorManager.h"
#include "Core/Event/Event.h"

#include "Core/Window/Init.h"
#include "Core/Input/Remapping/Remapper.h"

#include "Core/Input/JoystickManager.h"
#include "Core/Input/Init.h"

#include "Core/Input/Keyboard.h"

using namespace GLEEC;

int main()
{
    GLEEC::printInitString();

    std::cout << "Hello World!" << std::endl;

    Input::init();
    Event::init();

    Window::init();

    Window::WindowInfo info = {};
    info.dim = { 1280, 720 };
    info.name = "Hello World!";
    info.monitor = {};

    info.vSync = false;
    info.resizable = true;

    auto win = Window::WindowManager::createWindow(info);

    Audio::init();

    /* Internal::Localization::Locale::init();

    LOCALE_SP();

    LOCALIZE(EN, MORE, "More!");
    LOCALIZE(SP, MORE, "Más!");

    LOG_INFO("{}", LOCALIZED(MORE)); */

    Audio::playSound("C:/dev/GLEEC_RESTART/assets/sounds/background.wav");

    Input::Remapper::currentPreset().map(KEY_A, KEY_B);

    //Internal::Sound::OpenAL::init();

    Event::addListener<Event::KeyPressed>(+[](int key, int, int mods)
    {
        LOG_INFO("key: {}", key);
    });

    Event::addListener<Event::JoystickConnected>(+[](Input::Joystick j)
    {
        LOG_INFO("Joystick: {} connected!", j.internalJoystick);
    });

    Event::addListener<Event::JoystickDisconnected>(+[](Input::Joystick j)
    {
        LOG_INFO("Joystick: {} disconnected!", j.internalJoystick);
    });

    /* make sure everything builds properly and test polling, and then see if i can get it running on linux and start working on reflection,

         or just do localization but loading from files, which needs done either way

        maybe find a way to auto generate locale files by using a translation api, and parses the english file and generates the other one

        THE FORMAT:

    hash: "translation";

    then can easily parse and use potentially google translate api
*/
    while (Window::WindowManager::anyOpen())
    {
        Internal::Input::glfw::pollEvents();
    }

    Audio::terminate();
    Window::terminate();
    Input::terminate();
}
