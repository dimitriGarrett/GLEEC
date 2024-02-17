#pragma once

#include "State.h"
#include "Context.h"

namespace GLEEC::Internal::Audio::OpenAL
{
    inline void init(const Context&)
    {
        LOG_INFO("OpenAL vendor: {}", getVendor());
        LOG_INFO("OpenAL version: {}", getVersion());
        LOG_INFO("OpenAL renderer: {}", getRenderer());
        //LOG_INFO("OpenAL extensions: {}", getExtensions());

        LOG_INFO("OpenAL initiliazed!");
    }
}
