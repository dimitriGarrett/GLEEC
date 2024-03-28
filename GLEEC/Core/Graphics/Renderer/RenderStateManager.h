#pragma once

#include "RenderState.h"
#include "Frame.h"

#include <vector>

namespace GLEEC::Graphics
{
    struct RenderStateManager
    {
        GLEEC_API static std::vector<RenderState> renderStatePresets;
        GLEEC_API static size_t activeRenderState;

        static RenderState& renderState()
        {
            return renderStatePresets[activeRenderState];
        }

        GLEEC_API static void prepareState(FrameData& frame, size_t index, RenderState& currentState = renderState());
    };
}
