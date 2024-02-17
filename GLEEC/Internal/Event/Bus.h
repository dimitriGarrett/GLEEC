#pragma once

#include "Listener.h"

#include <memory>

namespace GLEEC::Internal::Event
{
    template <typename E>
    struct Bus
    {
        template <typename T>
        static std::vector<delegate<T>>& delegates()
        {
            static std::vector<delegate<T>> v = {};
            return v;
        }

        template <typename T>
        void addListener(const delegate<T>& d)
        {
            addListenerLambdaInternal<T>(d, static_cast<decltype(&T::operator())>(nullptr));
        }

        template <typename T>
        void addListener(T f)
        {
            return addListener(make_delegate(f));
        }

        template <typename R, typename... Args>
        void addListener(const delegate<R(Args...)>& d)
        {
            return addListenerInternal<R(Args...), Args...>(d);
        }

        template <typename R, typename... Args>
        void addListener(R(*func)(Args...))
        {
            return addListenerInternal<R(Args...), Args...>(func);
        }

        template <typename R, typename C, typename... Args>
        void addListener(const delegate<R(C::*)(Args...)>& d)
        {
            return addListenerInternal<R(C::*)(Args...), Args...>(d);
        }

        template <typename R, typename C, typename... Args>
        void addListener(R(C::*func)(Args...))
        {
            return addListenerInternal<R(C::*)(Args...), Args...>(func);
        }

        template <typename R, typename C, typename... Args>
        void addListener(const delegate<R(C::*)(Args...) const>& d)
        {
            return addListenerInternal<R(C::*)(Args...) const, Args...>(d);
        }

        template <typename R, typename C, typename... Args>
        void addListener(R(C::*func)(Args...) const)
        {
            return addListenerInternal<R(C::*)(Args...) const, Args...>(func);
        }

        // returns the index of the listener that captured the input,
        // or -1 if there was none
        template <typename... Args>
        size_t fireEvent(Args... args) const
        {
            if (listeners.empty()) return -1;

            for (size_t i = 0; i < listeners.size(); ++i)
            {
                if (static_cast<Listenerer<Args...>*>(listeners[i].get())->call(args...)) return i;
            }

            return -1;
        }

        std::vector<std::unique_ptr<Listener>> listeners = {};

    private:
        template <typename T, typename R, typename C, typename... Args>
        void addListenerLambdaInternal(const delegate<T>& d, R(C::*)(Args...) const)
        {
            return addListenerInternal<T, Args...>(d);
        }

        template <typename T, typename... Args>
        void addListenerInternal(const delegate<T>& d)
        {
            listeners.push_back(std::make_unique<Listenerer<Args...>>());
            Listenerer<Args...>* l = static_cast<Listenerer<Args...>*>(listeners.back().get());
            l->index = delegates<T>().size();
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
