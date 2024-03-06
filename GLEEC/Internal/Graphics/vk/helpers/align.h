#pragma once

namespace GLEEC::Internal::Graphics::vk
{
    // don't ask me how it works
    template <typename T>
    inline T alignedSize(T size, T alignment)
    {
        return (size + alignment - 1) & ~(alignment - 1);
    }
}
