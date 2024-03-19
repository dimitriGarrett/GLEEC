#pragma once

#include "Mesh.h"
#include "Core/Graphics/Frame.h"

namespace GLEEC::Graphics
{
    struct MeshManager
    {
        GLEEC_API static void drawMesh(const FrameData& frame, const Mesh& mesh);
        GLEEC_API static void drawMesh(const Frame& frame, const Mesh& mesh);

        // index of the window/frame
        GLEEC_API static void drawMesh(size_t index, const Mesh& mesh);

        // the default place to render is the first window (main window)
        static void drawMesh(const Mesh& mesh)
        {
            drawMesh(0, mesh);
        }
/*         GLEEC_API static void drawMesh(const Mesh& mesh); */
    };
}
