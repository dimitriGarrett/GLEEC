#include "Remapper.h"

namespace GLEEC::Input
{
    size_t Remapper::activePreset = 0;

    // there should be a default remapper
    // and this circumvents having to have an init function
    std::vector<Remapper> Remapper::presets = { Remapper() };
}
