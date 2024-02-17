#pragma once

#include "Backend.h"
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
#include "GLFW/Callbacks/Register.h"
#else
#error "Unknown Window backend for GLEEC!"
#endif
