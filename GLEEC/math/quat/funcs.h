#pragma once

#include "operators.h"
#include "../constants.h"

namespace GLEEC::math
{
    template <typename T>
    T real(const quaternion<T>& q)
    {
        return q.w;
    }

    template <typename T>
    vec<3, T> imaginary(const quaternion<T>& q)
    {
        return { q.x, q.y, q.z };
    }

    template <typename T>
    quaternion<T> conjugate(const quaternion<T>& q)
    {
        return { q.w, -q.x, -q.y, -q.z };
    }

    template <typename T>
    T dot(const quaternion<T>& q1, const quaternion<T>& q2)
    {
        return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
    }

    template <typename T>
    T length2(const quaternion<T>& q)
    {
        return dot(q, q);
    }

    template <typename T>
    T length(const quaternion<T>& q)
    {
        return sqrt(length2(q));
    }

    template <typename T>
    T mag2(const quaternion<T>& q)
    {
        return length2(q);
    }

    template <typename T>
    T mag(const quaternion<T>& q)
    {
        return length(q);
    }

    template <typename T>
    T norm(const quaternion<T>& q)
    {
        return length(q);
    }

    template <typename T>
    bool unit(const quaternion<T>& q)
    {
        return length2(q) == T(1);
    }

    template <typename T>
    bool pure(const quaternion<T>& q)
    {
        return q.w == T(0);
    }

    template <typename T>
    quaternion<T> normalize(const quaternion<T>& q)
    {
        return q / length(q);
    }

    template <typename T>
    quaternion<T> inverse(const quaternion<T>& q)
    {
        return conjugate(q) / length2(q);
    }

    template <typename T>
    T pitch(const quaternion<T>& q)
    {
        return asin(T(2) * (q.w * q.y - q.x * q.z));
    }

    template <typename T>
    T yaw(const quaternion<T>& q)
    {
        const T p = pitch(q);
        if (p - piovertwo <= 0.001)
        {
            return T(-2) * atan2(q.x, q.w);
        }

        else if (p + piovertwo <= -0.0001)
        {
            return T(2) * atan2(q.x, q.w);
        }

        return atan2(T(2) * (q.w * q.z + q.x * q.y), q.w * q.w -
                q.x * q.x - q.y * q.y - q.z * q.z);
    }

    template <typename T>
    T roll(const quaternion<T>& q)
    {
        if (abs(pitch(q)) - piovertwo <= 0.001)
        {
            return 0;
        }

        return atan2(T(2) * (q.w * q.x + q.y * q.z), q.w * q.w -
                q.x * q.x - q.y * q.y - q.z * q.z);
    }

    template <typename T>
    vec<3, T> eulerAngles(const quaternion<T>& q)
    {
        return { yaw(q), pitch(q), roll(q) };
    }

    template <typename T>
    quaternion<T> angleAxis(const T angle, const vec<3, T>& axis)
    {
        return quaternion<T>(angle, axis);
    }

    template <typename T>
    T angle(const quaternion<T>& q)
    {
        return static_cast<T>(2) * acos(q.w);
    }

    template <typename T>
    vec<3, T> axis(const quaternion<T>& q)
    {
        if (q == quaternion<T>{ 1.0f, 0.0f, 0.0f, 0.0f })
            return { 1.0f, 0.0f, 0.0f };

        T s = T(1) / sin(angle(q) * T(0.5));
        return { q.x * s, q.y * s, q.z * s };
    }

    template <typename T>
    T angleDifference(const quaternion<T>& q1, const quaternion<T>& q2)
    {
        // could be the inverse but since they are
        // rotation quaternions they are already
        // normalized
        return conjugate(q1) * q2;
    }

    template <typename T>
    quaternion<T> exp(const quaternion<T>& q)
    {
        if (unit(q))
        {
            const T t = angle(q);

            return { cos(t), sin(t) * axis(q) };
        }

        const T t = length(imaginary(q));
        return exp(q.w) * (cos(t) + (imaginary(q) / length(imaginary(q))) * sin(t));
    }

    template <typename T>
    quaternion<T> log(const quaternion<T>& q)
    {
        if (unit(q))
            return { T(0), angle(q) * axis(q) };

        const T l = length(q);
        return { log(l), imaginary(q) * (acos(q.w / l) / length(imaginary(q))) };
    }

    template <typename T>
    quaternion<T> pow(const quaternion<T>& q, const T power)
    {
        return exp(power * log(q));
    }

    template <typename T>
    vec<3, T> rotate(const vec<3, T>& v, const quaternion<T>& q)
    {
        // source: https://fgiesen.wordpress.com/2019/02/09/rotating-a-single-vector-using-a-quaternion/
        // returns q * v * (q*), but that can be simplified like below:

        vec<3, T> t = cross(T(2) * imaginary(q), v);
        return v + real(q) * t + cross(imaginary(q), t);
        //return imaginary(conjugate(q) * v * q);
    }

    template <typename T>
    quaternion<T> lerpFast(const quaternion<T>& q1, const quaternion<T>& q2, const T t)
    {
        return q1 * (static_cast<T>(1) - t) + (q2 * t);
    }

    template <typename T>
    quaternion<T> nlerpFast(const quaternion<T>& q1, const quaternion<T>& q2, const T t)
    {
        return normalize(lerp(q1, q2, t));
    }

    template <typename T>
    quaternion<T> slerpFast(const quaternion<T>& q1, const quaternion<T>& q2, const T t)
    {
    	//source: http://number-none.com/product/Understanding%20Slerp,%20Then%20Not%20Using%20It/

		T cosineTheta = dot(q1, q2);

		// If the two quaternions are really close
		constexpr T THRESHOLD = static_cast<T>(1.0) - static_cast<T>(0.001);

		if (cosineTheta > THRESHOLD)
		{
			return nlerp(q1, q2, t);
		}

		cosineTheta = clamp(cosineTheta, static_cast<T>(-1), static_cast<T>(1));
		T theta = acos(cosineTheta) * t;

		return q1 * cos(theta) + normalize(q2 - q1 * cosineTheta) * sin(theta);
    }

    template <typename T>
    quaternion<T> lerpShortestPath(const quaternion<T>& q1, const quaternion<T>& q2, const T t)
    {
        return lerpFast(q1, dot(q1, q2) < T(0) ? -q2 : q2, t);
    }

    template <typename T>
    quaternion<T> nlerpShortestPath(const quaternion<T>& q1, const quaternion<T>& q2, const T t)
    {
        return normalize(lerpShortestPath(q1, q2, t));
    }

    template <typename T>
    quaternion<T> slerpShortestPath(const quaternion<T>& q1, const quaternion<T>& q2, const T t)
    {
        return slerpFast(q1, dot(q1, q2) < T(0) ? -q2 : q2, t);
    }

#define MATH_QUAT_LERP_DEFAULT_SHORTEST_PATH 1 // just cause why not
    template <typename T>
    quaternion<T> lerp(const quaternion<T>& q1, const quaternion<T>& q2, const T t)
    {
#if MATH_QUAT_LERP_DEFAULT_SHORTEST_PATH
        return lerpShortestPath(q1, q2, t);
#else
        return lerpFast(q1, q2, t);
#endif
    }

    template <typename T>
    quaternion<T> nlerp(const quaternion<T>& q1, const quaternion<T>& q2, const T t)
    {
#if MATH_QUAT_LERP_DEFAULT_SHORTEST_PATH
        return nlerpShortestPath(q1, q2, t);
#else
        return nlerpFast(q1, q2, t);
#endif
    }

    template <typename T>
    quaternion<T> slerp(const quaternion<T>& q1, const quaternion<T>& q2, const T t)
    {
#if MATH_QUAT_LERP_DEFAULT_SHORTEST_PATH
        return slerpShortestPath(q1, q2, t);
#else
        return slerpFast(q1, q2, t);
#endif
    }
}
