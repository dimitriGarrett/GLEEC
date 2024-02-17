#include "SoundManager.h"
#include "Internal/Log/Log.h"

#include <sndfile.hh>

namespace GLEEC::Audio
{
    std::unordered_map<size_t, Sound> SoundManager::sounds = {};

    inline SoundInfo SoundManager::loadSound(std::string_view filepath)
    {
        SndfileHandle handle(filepath.data());

        if (!handle.rawHandle())
        {
            LOG_WARNING("Failed to load sound file requested at: {}", filepath); return {};
        }

        SoundInfo temp;
        temp.channels = handle.channels();
        temp.sampleRate = handle.samplerate();

        temp.data = std::vector<short>(handle.frames() * temp.channels * sizeof(short));
        sf_readf_short(handle.rawHandle(), temp.data.data(), handle.frames());

        return temp;
    }

    inline void SoundManager::unloadSound(SoundInfo& soundInfo)
    {
        soundInfo.data.clear(); // it should be in the audio card ram or something
                                // like that, so unload it from ram
    }
}
