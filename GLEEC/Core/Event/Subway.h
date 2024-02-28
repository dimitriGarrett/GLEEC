#pragma once

#include "Bus.h"
#include "Internal/utility/ctti.h"

#include <unordered_map>
#include <memory>

namespace GLEEC::Event
{
    struct SubwayBusBase
    {
        virtual ~SubwayBusBase() = default;
    };

    template <typename E, template <typename> typename B>
    struct SubwayBus final : SubwayBusBase
    {
        B<E> bus = {};
    };

    struct Subway
    {
        GLEEC_API static std::unordered_map<Internal::utility::hash_t, std::unique_ptr<SubwayBusBase>> buses;

        template <typename E, template <typename> typename B>
        static B<E>& bus()
        {
            return static_cast<SubwayBus<E, B>*>(buses.at(Internal::utility::type_hash<E>()).get())->bus;
        }

        template <typename E, template <typename> typename B>
        static B<E>& create_bus()
        {
            buses[Internal::utility::type_hash<E>()] = std::make_unique<SubwayBus<E, B>>();
            return bus<E, B>();
        }
    };

    template <typename E, typename T>
    void addListener(const delegate<T>& d, size_t priority = back)
    {
        return Subway::create_bus<E, Bus>().addListener(d, priority);
    }

    template <typename E, typename T>
    void addListener(T fun, size_t priority = back)
    {
        return addListener<E>(make_delegate(fun), priority);
    }

    template <typename E, typename... Args>
    size_t fireEvent(Args... args)
    {
        return (Subway::buses.contains(Internal::utility::type_hash<E>())
            ? Subway::bus<E, Bus>().fireEvent(args...) : -1);
    }
}
