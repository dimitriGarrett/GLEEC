#include "Core/Config/Configuration.h"
#include "Core/Graphics/BufferManager.h"
#include "Core/Graphics/Renderer/Model/Index.h"
#include "Core/Graphics/Renderer/Model/Mesh.h"
#include "Core/Graphics/Renderer/Model/MeshManager.h"
#include "Core/Graphics/Renderer/Model/Model.h"
#include "Core/Graphics/Renderer/Model/ModelManager.h"
#include "Core/Graphics/Renderer/Model/Vertex.h"
#include "Core/Graphics/ShaderManager.h"
#include "Core/Input/InputManager.h"
#include "Core/Input/Key.h"
#include "Init/Init.h"

#include "Core/Input/Remapping/Remapper.h"
#include "Core/Audio/Helper.h"

#include "Core/Graphics/Frame.h"

#include "Internal/Graphics/vk/Buffer.h"
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

    LOG_MESSAGE("TODO: NEED DEPTH BUFFERING SOON");
    LOG_MESSAGE("TODO: NEED MULTISAMPLING SOON");
    LOG_MESSAGE("TODO: NEED MIPMAPPING SOON");

    Graphics::Model model = Graphics::ModelManager::createModel(
        Config::Configuration::gets("cwd") + "assets/models/sphere.obj");

    while (Window::WindowManager::anyOpen())
    {
        this_frame = glfwGetTime();

        Graphics::FrameManager::begin();

        static size_t i = 0;

        if (Input::InputManager::keyPressed(KEY_C))
        {
            i = (i + 1) % 2;
        }

        if (!Window::WindowManager::windows[i].minimized)
        {
            Graphics::ModelManager::renderModels();
        }

        Graphics::FrameManager::end();

        double frameTime = glfwGetTime() - this_frame;
        double fps = 1.0 / frameTime;

        /* Window::WindowManager::activeWindow().title(
            std::format("FPS: {}", fps)); */

        Input::InputManager::update();
    }

    GLEEC::destroy();
}
