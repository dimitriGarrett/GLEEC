#include "DeviceManager.h"

namespace GLEEC::Audio
{
    std::vector<std::string> DeviceManager::potentialDevices =
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
    Internal::Audio::OpenAL::enumerateAudioDevices();
#else
    {}
#endif
    ;

    std::unordered_map<size_t, Device> DeviceManager::openDevices = {};
}
