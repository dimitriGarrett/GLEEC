#pragma once

#include "Platform.h"

// if not on windows don't need to worry about this
// TODO: need to test on another platform
// which should be done soon on linux for
// reflection support but who knows how long thatll take

#if GLEEC_WINDOWS
    #ifdef GLEEC_EXPORT
        #define GLEEC_API __declspec(dllexport)
    #else
        #define GLEEC_API __declspec(dllimport)
    #endif

    #define GLEEC_API_EXTERN GLEEC_API extern
#else
    #define GLEEC_API extern
    #define GLEEC_API_EXTERN GLEEC_API
#endif
