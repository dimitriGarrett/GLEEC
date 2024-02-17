#include "Init/Init.h"

#include "Core/Input/Remapping/Remapper.h"
#include "Core/Input/Update.h"
#include "Core/Audio/Helper.h"

using namespace GLEEC;

int main()
{
    GLEEC::init();

    Window::WindowInfo info = {};
    info.dim = { 1280, 720 };
    info.name = "Hello World!";
    info.monitor = {};

    info.vSync = false;
    info.resizable = true;

    auto win = Window::WindowManager::createWindow(info);

    Audio::playSound("C:/dev/GLEEC_RESTART/assets/sounds/background.wav");

    Input::Remapper::currentPreset().map(KEY_A, KEY_B);

    LOCALE(ES);
    LOG_INFO("{}", TR(HELLO));

    LOCALE(EN);
    LOG_INFO("{}", TR(HELLO));

    while (Window::WindowManager::anyOpen())
    {
        Input::update();
    }

    GLEEC::terminate();
}
