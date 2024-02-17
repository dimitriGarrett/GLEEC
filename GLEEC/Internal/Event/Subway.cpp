#include "Subway.h"

namespace GLEEC::Internal::Event
{
    std::unordered_map<utility::hash_t, std::unique_ptr<SubwayBusBase>> Subway::buses = {};
}
