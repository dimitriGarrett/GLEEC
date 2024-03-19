#include "MeshManager.h"

#include "Core/Graphics/BufferManager.h"
#include "Core/Graphics/ShaderManager.h"
#include "Core/Graphics/FrameManager.h"

namespace GLEEC::Graphics
{
    void MeshManager::drawMesh(const FrameData& frame, const Mesh& mesh)
    {
    }

    void MeshManager::drawMesh(const Frame& frame, const Mesh& mesh)
    {
#if GLEEC_USE_FRAMES_IN_FLIGHT
        drawMesh(frame.frames[FrameManager::activeFrame], mesh);
#else
        drawMesh(frame.frame, mesh);
#endif
    }

    void MeshManager::drawMesh(size_t i, const Mesh& mesh)
    {
        drawMesh(FrameManager::frames[i], mesh);
    }
}
