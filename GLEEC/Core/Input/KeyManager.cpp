#include "KeyManager.h"

#include "Internal/Input/Backend.h"

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/GLFW/Keyboard.h"
#endif

namespace GLEEC::Input
{
    inline std::string_view KeyManager::keyName(Key key)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return Internal::Input::glfw::getKeyName(key);
#endif
    }
}
