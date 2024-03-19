#pragma once

#include "Core/Graphics/Renderer/Model/Geometry.h"

namespace GLEEC::Graphics::parsers
{
    GLEEC_API_EXTERN void mtl(std::string_view filepath, Geometry& model);
}
