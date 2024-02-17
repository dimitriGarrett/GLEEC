#pragma once

#include "Speaker.h"

#include <vector>

namespace GLEEC::Audio
{
    struct SpeakerManager
    {
        static Speaker& createSpeaker(Sound& sound)
        {
            return speakers.emplace_back(sound);
        }

        static Speaker& createSpeaker()
        {
            return speakers.emplace_back();
        }

        static void destroySpeakers()
        {
            speakers.clear();
        }

        GLEEC_API static std::vector<Speaker> speakers;
    };
}
