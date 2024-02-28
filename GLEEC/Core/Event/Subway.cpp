#include "Subway.h"

namespace GLEEC::Event
{
    std::unordered_map<Internal::utility::hash_t, std::unique_ptr<SubwayBusBase>> Subway::buses = {};
}
