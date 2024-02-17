#pragma once

#include "Bus.h"
#include "Internal/utility/ctti.h"

#include <unordered_map>
#include <memory>

namespace GLEEC::Internal::Event
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
        GLEEC_API static std::unordered_map<utility::hash_t, std::unique_ptr<SubwayBusBase>> buses;

        template <typename E, template <typename> typename B>
        static B<E>& bus()
        {
            return static_cast<SubwayBus<E, B>*>(buses.at(utility::type_hash<E>()).get())->bus;
        }

        template <typename E, template <typename> typename B>
        static B<E>& create_bus()
        {
            buses[utility::type_hash<E>()] = std::make_unique<SubwayBus<E, B>>();
            return bus<E, B>();
        }
    };

    template <typename E, typename T>
    void addListener(const delegate<T>& d)
    {
        return Subway::create_bus<E, Bus>().addListener(d);
    }

    template <typename E, typename T>
    void addListener(T fun)
    {
        return addListener<E>(make_delegate(fun));
    }

template <typename E, typename... Args>
    size_t fireEvent(Args... args)
    {
        return (Subway::buses.contains(utility::type_hash<E>()) ? Subway::bus<E, Bus>().fireEvent(args...) : -1);
    }
}
