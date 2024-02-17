#pragma once

#include "PP/Build.h"

// GLEEC_DEBUG and GLEEC_RELEASE are defined by premake, this is just a sanity check

#if (!defined(GLEEC_DEBUG) && !defined(GLEEC_RELEASE))
#error "Unknown build type for GLEEC!"
#endif
