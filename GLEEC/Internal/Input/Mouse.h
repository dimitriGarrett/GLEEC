#pragma once

#include "Backend.h"
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "GLFW/Mouse.h"
#else
#error "Unknown Input backend for GLEEC!"
#endif
