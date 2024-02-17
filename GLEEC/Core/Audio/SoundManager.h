#pragma once

#include "SoundInfo.h"
#include "Sound.h"

#include <string_view>
#include <unordered_map>

namespace GLEEC::Audio
{
    struct SoundManager
    {
        static Sound& findSound(std::string_view filepath)
        {
            if (sounds.contains(key(filepath)))
            {
                return sounds.at(key(filepath));
            }

            return createSound(filepath);
        }

        static void destroySounds()
        {
            sounds.clear();
        }

        GLEEC_API static std::unordered_map<size_t, Sound> sounds;

    private:
        static Sound& createSound(std::string_view filepath)
        {
            Sound& sound = sounds[key(filepath)];
            SoundInfo loadedSound = loadSound(filepath);

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::fillSound(sound.internalSound,
                loadedSound.data.data(), loadedSound.channels,
                static_cast<ALint>(loadedSound.data.size()), loadedSound.sampleRate);
#endif

            unloadSound(loadedSound);

            return sound;
        }

        GLEEC_API static SoundInfo loadSound(std::string_view);
        GLEEC_API static void unloadSound(SoundInfo&);

        static size_t key(std::string_view filepath)
        {
            return std::hash<std::string_view>{}(filepath);
        }
    };
}
