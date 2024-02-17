#pragma once

#include "Backend.h"

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
#include "OpenAL/Init.h"
#else
#error "Unkown Audio backend for GLEEC!"
#endif
