#include "Core/Graphics/ShaderManager.h"
#include "Init/Init.h"

#include "Core/Input/Remapping/Remapper.h"
#include "Core/Input/Update.h"
#include "Core/Audio/Helper.h"

#include "Core/Graphics/Frame.h"

#include "Internal/Graphics/vk/Extensions.h"
#include "Internal/Graphics/vk/Shader.h"
#include "Internal/Time/Time.h"
#include "vulkan/vulkan_core.h"

using namespace GLEEC;

int main()
{
    // firstInit allows for choosing a monitor in the windowInfo,
    // if that isn't needed than oh well, it is just an option
    GLEEC::firstInit();

    Window::WindowInfo info = {};
    info.dim = { 1280, 720 };
    info.name = "Hello World!";
    info.monitor = {};

    info.vSync = false;
    info.resizable = true;

    Window::WindowInfo info2 = {};
    info2.dim = { 1280, 720 };
    info2.name = "Hello World2!";
    info2.monitor = {};

    info2.vSync = false;
    info2.resizable = true;

    GLEEC::init({ info, info2 });
    //GLEEC::init({ info });

    Audio::playSound("C:/dev/GLEEC/assets/sounds/background.wav");

    Input::Remapper::currentPreset().map(KEY_A, KEY_B);

    LOCALE(ES);
    LOG_INFO("{}", TR(HELLO));

    LOCALE(EN);
    LOG_INFO("{}", TR(HELLO));

    double this_frame = 0.0;

    Graphics::ShaderManager::init(
    {
        // these shaders needed linked together
        {
            "vert.spv", "frag.spv"
        }
    });

    while (Window::WindowManager::anyOpen())
    {
        this_frame = glfwGetTime();

        Graphics::FrameManager::begin();

        Graphics::FrameData& frame = Graphics::FrameManager::frames[0].frames[
            Graphics::FrameManager::activeFrame];

        vkCmdDraw(frame.commandBuffer, 3, 1, 0, 0);

        Graphics::FrameManager::end();

        double frameTime = glfwGetTime() - this_frame;
        double fps = 1.0 / frameTime;

        /* Window::WindowManager::activeWindow().title(
            std::format("FPS: {}", fps)); */

        Input::update();
    }

    GLEEC::terminate();
}
