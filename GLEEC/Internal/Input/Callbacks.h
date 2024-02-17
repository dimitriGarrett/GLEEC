#pragma once

#include "Backend.h"
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "GLFW/Callbacks.h"
#else
#error "Unknown Window backend for GLEEC!"
#endif
