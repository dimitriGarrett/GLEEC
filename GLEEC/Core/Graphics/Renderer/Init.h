#pragma once

#include "Model/ModelManager.h"
#include "Model/GeometryManager.h"

namespace GLEEC::Graphics
{
    inline void initRenderer()
    {
        ModelManager::init();
    }

    inline void destroyRenderer()
    {
        GeometryManager::destroy();
        ModelManager::destroy();
    }
}
