#pragma once

#include "Listener.h"

#include "Internal/utility/callable.h"

#include <memory>
#include <vector>

namespace GLEEC::Event
{
    // inserts at the end, which is the default
    inline constexpr size_t back = 0;

    // this should be used instead of -1 explicitly by the user because
    // internal listeners should be first, and then all user stuff
    // (internal listeners register with -1)
    inline constexpr size_t front = -2;

    template <typename E>
    struct Bus
    {
        template <typename T>
        void addListener(const delegate<T>& d, size_t priority = back)
            requires Internal::utility::is_callable<T>
        {
            addListenerLambdaInternal<T>(d, priority, static_cast<decltype(&T::operator())>(nullptr));
        }

        template <typename T>
        void addListener(T f, size_t priority = back)
            requires Internal::utility::is_callable<T>
        {
            return addListener(make_delegate(f), priority);
        }

        template <typename R, typename... Args>
        void addListener(const delegate<R(Args...)>& d, size_t priority = back)
        {
            return addListenerInternal<R(Args...), Args...>(d, priority);
        }

        template <typename R, typename... Args>
        void addListener(R(*func)(Args...), size_t priority = back)
        {
            return addListenerInternal<R(Args...), Args...>(func, priority);
        }

        template <typename R, typename C, typename... Args>
        void addListener(const delegate<R(C::*)(Args...)>& d, size_t priority = back)
        {
            return addListenerInternal<R(C::*)(Args...), Args...>(d, priority);
        }

        template <typename R, typename C, typename... Args>
        void addListener(R(C::*func)(Args...), size_t priority = back)
        {
            return addListenerInternal<R(C::*)(Args...), Args...>(func, priority);
        }

        template <typename R, typename C, typename... Args>
        void addListener(const delegate<R(C::*)(Args...) const>& d, size_t priority = back)
        {
            return addListenerInternal<R(C::*)(Args...) const, Args...>(d, priority);
        }

        template <typename R, typename C, typename... Args>
        void addListener(R(C::*func)(Args...) const, size_t priority = back)
        {
            return addListenerInternal<R(C::*)(Args...) const, Args...>(func, priority);
        }

        // returns the index of the listener that captured the input,
        // or -1 if there was no listener that captured and returned true
        template <typename... Args>
        size_t fireEvent(Args... args) const
        {
            if (listeners.empty()) return -1;

            for (size_t i = 0; i < listeners.size(); ++i)
            {
                if (static_cast<Listenerer<Args...>*>(listeners[i].get())->call(args...))
                    return i;
            }

            return -1;
        }

        std::vector<std::unique_ptr<Listener>> listeners = {};

    private:
        template <typename T>
        static std::vector<delegate<T>>& delegates()
        {
            static std::vector<delegate<T>> v = {};
            return v;
        }

        template <typename T, typename R, typename C, typename... Args>
        void addListenerLambdaInternal(const delegate<T>& d, size_t p, R(C::*)(Args...) const)
        {
            return addListenerInternal<T, Args...>(d, p);
        }

        template <typename... Args>
        Listenerer<Args...>* addListenerToDelegates(size_t p)
        {
            // internal front
            if (p == -1)
            {
                return static_cast<Listenerer<Args...>*>(listeners.emplace(
                    listeners.begin(),
                    std::make_unique<Listenerer<Args...>>())->get());
            }

            if (p == back)
            {
                return static_cast<Listenerer<Args...>*>(listeners.emplace_back(
                    std::make_unique<Listenerer<Args...>>()).get());
            }

            for (size_t i = 0; i < listeners.size(); ++i)
            {
                if (p > static_cast<Listenerer<Args...>*>(listeners[i].get())->priority)
                {
                    return static_cast<Listenerer<Args...>*>(listeners.emplace(
                        listeners.begin() + i,
                        std::make_unique<Listenerer<Args...>>())->get());
                }
            }

            // too lazy to write out this
            return addListenerToDelegates<Args...>(back);
        }

        template <typename T, typename... Args>
        void addListenerInternal(const delegate<T>& d, size_t p)
        {
            Listenerer<Args...>* l = addListenerToDelegates<Args...>(p);

            l->index = delegates<T>().size();
            l->priority = p;

            l->func = make_delegate(+[](size_t i, Args... args) -> bool
            {
                if constexpr (std::is_same_v<typename delegate<T>::return_t, bool>)
                {
                    return delegates<T>().at(i)(args...);
                }

                delegates<T>().at(i)(args...); return false;
            });

            delegates<T>().push_back(d);
        }
    };
}
