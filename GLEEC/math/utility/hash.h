#pragma once

#include "defines.h"
#include <string>

namespace GLEEC::math
{
    template <length_t l, typename T>
    std::size_t hash(const vec<l, T>& v)
    {
        std::string s = "";
    
        for (length_t i = 0; i < l; ++i)
        {
            s += v[i];
            s += "|";
        }

        return std::hash<std::string>()(s);
    }

    template <typename T>
    std::size_t hash(const vec<2, T>& v)
    {
        return std::hash<std::string>()(std::to_string(v[0]) + "|" + std::to_string(v[1]));
    }

    template <typename T>
    std::size_t hash(const vec<3, T>& v)
    {
        return std::hash<std::string>()(
                std::to_string(v[0]) + "|" + std::to_string(v[1]) + "|" + std::to_string(v[2]));
    }

    template <typename T>
    std::size_t hash(const vec<4, T>& v)
    {
        return std::hash<std::string>()(
                std::to_string(v[0]) + "|" + std::to_string(v[1]) + "|" +
                std::to_string(v[2]) + "|" + std::string(v[3]));
    }
}

namespace std
{
    template <GLEEC::math::length_t l, typename T>
    struct hash<GLEEC::math::vec<l, T>>
    {
        size_t operator() (const GLEEC::math::vec<l, T>& vec) const
        {
            return GLEEC::math::hash<l, T>(vec);
        }
    };
}
