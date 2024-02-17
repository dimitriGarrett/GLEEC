#pragma once

#include "SoundManager.h"
#include "SpeakerManager.h"

namespace GLEEC::Audio
{
    inline Sound& loadSound(std::string_view filepath)
    {
        return SoundManager::findSound(filepath);
    }

    inline Speaker& playSound(Sound& sound)
    {
        Speaker& speaker = SpeakerManager::createSpeaker(sound);

        speaker.play();

        return speaker;
    }

    inline void playSound(std::string_view filepath)
    {
        playSound(loadSound(filepath));
    }
}
