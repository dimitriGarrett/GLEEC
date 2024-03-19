#pragma once

// just because?
#include "PP/Version.h"

// idek why
#define GLEEC_CPP 1

#define GLEEC_VERSION_MAJOR 0
#define GLEEC_VERSION_MINOR 1
#define GLEEC_VERSION_PATCH 0

// copy of VK_MAKE_API_VERSION
#define MAKE_API_VERSION(major, minor, patch) \
((((uint32_t)(major)) << 22U) | (((uint32_t)(minor)) << 12U) | ((uint32_t)(patch)))

#define GLEEC_VERSION \
MAKE_API_VERSION(GLEEC_VERSION_MAJOR, GLEEC_VERSION_MINOR, GLEEC_VERSION_PATCH)
