#pragma once

#include "Config/Export.h"
#include "Remap.h"

#include <vector>
#include <unordered_map>

namespace GLEEC::Input
{
    struct Remapper
    {
        static Remapper& addPreset()
        {
            return presets.emplace_back();
        }

        static Remapper& addActivePreset()
        {
            activePreset = presets.size();
            return presets.emplace_back();
        }

        static Remapper& currentPreset()
        {
            return presets.at(activePreset);
        }

        void reset()
        {
            remaps.clear();
            unmaps.clear();
        }

        void map(const Remap& remap)
        {
            // to be honest, i forget what this all does. works though

            if (remaps.contains(remap.from))
                unmaps[remaps.at(remap.from)] = {};

            remaps[remap.from] = remap.to;
            unmaps[remap.to] = remap.from;

            if (!unmaps.contains(remap.from))
                unmaps[remap.from] = {};
        }

        void map(const RemapState& from, const RemapState& to)
        {
            map({ from, to });
        }

        void map(const uint32_t from, const uint32_t to)
        {
            map({ 0U, from }, { 0U, to });
        }

        // takes in raw key, returns remapped, or unaffected if no remap
        RemapState remap(const RemapState& state) const
        {
            return remaps.contains(state) ? remaps.at(state) : state;
        }

        // takes in raw key, returns remapped, or unaffected if no remap
        RemapState remap(const uint32_t key) const
        {
            return remap({ 0U, key });
        }

        // takes in remapped key, returns raw key, or unaffected if no remap
        RemapState unmap(const RemapState& state) const
        {
            return unmaps.contains(state) ? unmaps.at(state) : state;
        }

        // takes in remapped key, returns raw key, or unaffected if no remap
        RemapState unmap(const uint32_t key) const
        {
            return unmap({ 0U, key });
        }

        // (translated key) -> (remapped key) (events)
        std::unordered_map<RemapState, RemapState> remaps = {};

        // (remapped key) -> (translated key) (polling)
        std::unordered_map<RemapState, RemapState> unmaps = {};

        GLEEC_API static size_t activePreset;
        GLEEC_API static std::vector<Remapper> presets;
    };
}
