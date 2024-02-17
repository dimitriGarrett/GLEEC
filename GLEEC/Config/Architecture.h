#include "PP/Architecture.h"

#if PP_ARCHITECTURE_64
    #define GLEEC64 1
#elif PP_ARCHITECTURE_32
    #define GLEEC32 1
#else
#error "Unknown architecture for GLEEC!"
#endif
