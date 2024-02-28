#pragma once

#include "Internal/utility/pack.h"

#include <cassert>

#if GLEEC_DEBUG
#include "Internal/Log/Log.h"

#define delegate_error()\
        LOG_ERROR("delegate was nullptr somewhere!")
#else
#define delegate_error()
#endif

namespace GLEEC
{
    namespace detail
    {
        // ensure that the delegate actually is holding a lambda by examining operator()
        // if it wasn't a lambda with an operator() it is a custom class type which is held successfully
        // (in theory, haven't tested)
        template <typename T> struct lambda_delegate {};
    }

    template <typename T>
    struct delegate final : detail::lambda_delegate<decltype(&T::operator())>
    {
        using dad = delegate<decltype(&T::operator())>;

        using functor_t = T;

        using return_t = typename dad::return_t;
        using class_t = typename dad::class_t;

        template <size_t N>
        using arg_t = typename dad::template arg_t<N>;

        delegate(const T& Lambda)
            : lambda(Lambda)
        {
        }

        bool empty() const
        {
            return false;
        }

        operator bool() const
        {
            return empty();
        }

        template <typename... Args>
        return_t operator() (Args&&... args) const
        {
            return lambda(std::forward<Args>(args)...);
        }

        bool operator== (const delegate& rhs) const
        {
            return lambda == rhs.lambda;
        }

        bool operator!= (const delegate& rhs) const
        {
            return !(*this == rhs);
        }

    private:
        T lambda;
    };

    template <typename R, typename... Args>
    struct delegate<R(*)(Args...)>
    {
        using functor_t = R(*)(Args...);

        using return_t = R;
        using class_t = void;
        
        template <size_t N>
        using arg_t = typename Internal::utility::nth_type<N, Args...>;

        delegate() = default;
        delegate(decltype(nullptr)) {}

        delegate(functor_t func)
            : functor(func)
        {
        }

        bool empty() const
        {
            return functor == nullptr;
        }

        operator bool() const
        {
            return !empty();
        }

        R operator() (Args... args) const
        {
#if GLEEC_DEBUG
            assert(!empty());
#endif
            return functor(args...);
        }

        bool operator== (const delegate& rhs) const
        {
            return functor == rhs.functor;
        }

        bool operator!= (const delegate& rhs) const
        {
            return !(*this == rhs);
        }

    private:
        functor_t functor = nullptr;
    };

    template <typename R, typename... Args>
    struct delegate<R(Args...)> final : public delegate<R(*)(Args...)>
    {
        using delegate<R(*)(Args...)>::delegate;

        using return_t = typename delegate<R(*)(Args...)>::return_t;
        
        template <size_t N>
        using arg_t = typename Internal::utility::nth_type<N, Args...>;

        using functor_t = R(Args...);
    };

    template <typename R, typename C, typename... Args>
    struct delegate<R(C::*)(Args...)> final
    {
        using functor_t = R(C::*)(Args...);

        using return_t = R;
        using class_t = C;
        
        template <size_t N>
        using arg_t = typename Internal::utility::nth_type<N, Args...>;

        delegate() = default;
        delegate(decltype(nullptr)) {}

        delegate(C* member, functor_t Functor)
            : functor(Functor), mb(member)
        {
        }

        delegate(C& member, functor_t functor)
            : delegate(&member, functor)
        {
        }

        delegate(functor_t functor)
            : delegate(nullptr, functor)
        {
        }

        bool empty() const
        {
            return mb == nullptr || functor == nullptr;
        }

        operator bool() const
        {
            return !empty();
        }

        R operator() (Args... args) const
        {
#if GLEEC_DEBUG
            assert(!empty());
#endif
            return (mb->*functor)(args...);
        }

        R operator() (C* member, Args... args) const
        {
#if GLEEC_DEBUG
            assert(functor != nullptr && member != nullptr);
#endif
            return (member->*functor)(args...);
        }

        R operator() (C& member, Args... args) const
        {
            return operator() (&member, args...);
        }

        bool operator== (const delegate& rhs) const
        {
            return functor == rhs.functor && mb == rhs.mb;
        }

        bool operator!= (const delegate& rhs) const
        {
            return !(*this == rhs);
        }

    private:
        functor_t functor = nullptr;
        C* mb = nullptr;
    };

    template <typename R, typename C, typename... Args>
    struct delegate<R(C::*)(Args...) const> final
    {
        using functor_t = R(C::*)(Args...) const;

        using return_t = R;
        using class_t = C;
        
        template <size_t N>
        using arg_t = typename Internal::utility::nth_type<N, Args...>;

        delegate() = default;
        delegate(decltype(nullptr)) {}

        delegate(const C* member, functor_t Functor)
            : functor(Functor), mb(member)
        {
        }

        delegate(const C& member, functor_t functor)
            : delegate(&member, functor)
        {
        }

        delegate(functor_t functor)
            : delegate(nullptr, functor)
        {
        }

        bool empty() const
        {
            return mb == nullptr || functor == nullptr;
        }

        operator bool() const
        {
            return !empty();
        }

        R operator() (Args... args) const
        {
#if GLEEC_DEBUG
            assert(!empty());
#endif
            return (mb->*functor)(args...);
        }

        R operator() (const C* member, Args... args) const
        {
#if GLEEC_DEBUG
            assert(functor != nullptr && member != nullptr);
#endif
            return (member->*functor)(args...);
        }

        R operator() (const C& member, Args... args) const
        {
            return operator() (&member, args...);
        }

        bool operator== (const delegate& rhs) const
        {
            return functor == rhs.functor && mb == rhs.mb;
        }

        bool operator!= (const delegate& rhs) const
        {
            return !(*this == rhs);
        }

    private:
        functor_t functor = nullptr;
        const C* mb = nullptr;
    };

	// lambda
	template <typename T>
	delegate<T> make_delegate(T lambda)
	{
		return delegate<T>(lambda);
	}

	// free functions
	template <typename R, typename... Args>
	delegate<R(Args...)> make_delegate(R(*func)(Args...))
	{
		return delegate<R(Args...)>(func);
	}

	// non-const member function
	template <typename R, typename C, typename... Args>
	delegate<R(C::*)(Args...)> make_delegate(C* object, R(C::* func)(Args...))
	{
		return delegate<R(C::*)(Args...)>(object, func);
	}

	// non-const member function
	template <typename R, typename C, typename... Args>
	delegate<R(C::*)(Args...)> make_delegate(R(C::* func)(Args...))
	{
		return delegate<R(C::*)(Args...)>(func);
	}

	// const member function
	template <typename R, typename C, typename... Args>
	delegate<R(C::*)(Args...) const> make_delegate(const C* object, R(C::* func)(Args...) const)
	{
		return delegate<R(C::*)(Args...) const>(object, func);
	}

	// const member function
	template <typename R, typename C, typename... Args>
	delegate<R(C::*)(Args...) const> make_delegate(R(C::* func)(Args...) const)
	{
		return delegate<R(C::*)(Args...) const>(func);
	}
}
