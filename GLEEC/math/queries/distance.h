#pragma once

#include "query.h"

namespace GLEEC::math::query
{
    template <typename T>
    T distance2(const point<T>& p1, const point<T>& p2)
    {
        return math::length2(p1 - p2);
    }

    template <typename T>
    T distance(const point<T>& p1, const point<T>& p2)
    {
        return sqrt(distance2(p1, p2));
    }

    template <typename T>
    T distance2(const point<T>& p, const ray<T>& r)
    {
        abort();
    }
    
    template <typename T>
    T distance2(const ray<T>& r, const point<T>& p)
    {
        return distance2(p, r);
    }

    template <typename T>
    T distance(const point<T>& p, const ray<T>& r)
    {
        return sqrt(distance2(p, r));
    }

    template <typename T>
    T distance(const ray<T>& r, const point<T>& p)
    {
        return sqrt(distance2(r, p));
    }

    template <typename T>
    T distance2(const point<T>& p, const line_segment<T>& s)
    {
        // source: http://www.r-5.org/files/books/computers/algo-list/realtime-3d/Christer_Ericson-Real-Time_Collision_Detection-EN.pdf

        const vec<3, T>& a = s.a;
        const vec<3, T>& b = s.b;
        const vec<3, T>& c = p;

        const vec<3, T> ab = b - a;
        const vec<3, T> ac = c - a;
        const vec<3, T> bc = c - b;

        const T e = math::dot(ac, ab);
        if (e <= T(0)) return math::dot(ac, ac);
        const T f = math::dot(ab, ab);
        if (e >= f) return math::dot(bc, bc);
        return math::dot(ac, ac) - e * e / f;
    }

    template <typename T>
    T distance2(const line_segment<T>& s, const point<T>& p)
    {
        return distance2(p, s);
    }

    template <typename T>
    T distance(const point<T>& p, const line_segment<T>& s)
    {
        return sqrt(distance2(p, s));
    }

    template <typename T>
    T distance(const line_segment<T>& s, const point<T>& p)
    {
        return sqrt(distance2(s, p));
    }

    template <typename T>
    T distance2(const point<T>& p, const aabb<T>& box)
    {
        return distance2(p, clamp(p,
            box.pos - box.half_extent,
            box.pos + box.half_extent));
    }

    template <typename T>
    T distance2(const aabb<T>& box, const point<T>& p)
    {
        return distance2(p, box);
    }

    template <typename T>
    T distance(const point<T>& p, const aabb<T>& box)
    {
        return sqrt(distance2(p, box));
    }

    template <typename T>
    T distance(const aabb<T>& box, const point<T>& p)
    {
        return sqrt(distance2(box, p));
    }

    template <typename T>
    T distance2(const point<T>& p, const obb<T>& box)
    {
        matrix<4, 4, T> mat = box.orientation;
        mat[3] = vec4(box.pos, T(1));
        const point<T> transformed = mat * vec4(p, T(1));

        return distance2(transformed, math::clamp(transformed,
            -box.half_extent,
             box.half_extent));
    }

    template <typename T>
    T distance2(const obb<T>& box, const point<T>& p)
    {
        return distance2(p, box);
    }

    template <typename T>
    T distance(const point<T>& p, const obb<T>& box)
    {
        return sqrt(distance2(p, box));
    }

    template <typename T>
    T distance(const obb<T>& box, const point<T>& p)
    {
        return sqrt(distance2(box, p));
    }

    template <typename T>
    T distanceS(const point<T>& p, const plane3d<T>& plane)
    {
        return math::dot(p, plane.normal) - plane.d;
    }

    template <typename T>
    T distanceS(const plane3d<T>& plane, const point<T>& p)
    {
        return distanceS(p, plane);
    }

    template <typename T>
    T distanceU(const point<T>& p, const plane3d<T>& plane)
    {
        return math::abs(distanceS(p, plane));
    }

    template <typename T>
    T distanceU(const plane3d<T>& plane, const point<T>& p)
    {
        return distanceU(p, plane);
    }

    template <typename T>
    T distance(const point<T>& p, const plane3d<T>& plane)
    {
        return distanceU(p, plane);
    }

    template <typename T>
    T distance(const plane3d<T>& plane, const point<T>& p)
    {
        return distance(p, plane);
    }

    template <typename T>
    T distance2(const point<T>& p, const plane3d<T>& plane)
    {
        const T dist = distance(p, plane);
        return dist * dist;
    }

    template <typename T>
    T distance2(const plane3d<T>& plane, const point<T>& p)
    {
        const T dist = distance(p, plane);
        return dist * dist;
    }

    template <typename T>
    T distance2(const ray<T>& r1, const ray<T>& r2)
    {
        abort();
    }

    template <typename T>
    T distance(const ray<T>& r1, const ray<T>& r2)
    {
        return sqrt(distance2(r1, r2));
    }

    template <typename T>
    T distance2(const ray<T>& r, const line_segment<T>& s)
    {
        abort();
    }

    template <typename T>
    T distance2(const line_segment<T>& s, const ray<T>& r)
    {
        return distance2(r, s);
    }

    template <typename T>
    T distance(const ray<T>& r, const line_segment<T>& s)
    {
        return sqrt(distance(r, s));
    }

    template <typename T>
    T distance(const line_segment<T>& s, const ray<T>& r)
    {
        return sqrt(distance(r, s));
    }

    template <typename T>
    T distance2(const ray<T>& r, const aabb<T>& box)
    {
        abort();
    }

    template <typename T>
    T distance2(const aabb<T>& box, const ray<T>& r)
    {
        return distance2(r, box);
    }

    template <typename T>
    T distance(const ray<T>& r, const aabb<T>& box)
    {
        return sqrt(distance2(r, box));
    }

    template <typename T>
    T distance(const aabb<T>& box, const ray<T>& r)
    {
        return sqrt(distance2(box, r));
    }

    template <typename T>
    T distance2(const ray<T>& r, const obb<T>& box)
    {
        abort();
    }

    template <typename T>
    T distance2(const obb<T>& box, const ray<T>& r)
    {
        return distance2(r, box);
    }

    template <typename T>
    T distance(const ray<T>& r, const obb<T>& box)
    {
        return sqrt(distance2(r, box));
    }

    template <typename T>
    T distance(const obb<T>& box, const ray<T>& r)
    {
        return sqrt(distance2(r, box));
    }

    template <typename T>
    T distance2(const line_segment<T>& s1, const line_segment<T>& s2)
    {
        // source: https://math.stackexchange.com/questions/1036959/midpoint-of-the-shortest-distance-between-2-rays-in-3d
        // adjusted to work with line segments by clamping t and s

        // a + tb
        // c + sd

        const vec<3, T> a = s1.a;
        const vec<3, T> b = math::normalize(s1.b - s1.a);

        const vec<3, T> c = s2.a;
        const vec<3, T> d = math::normalize(s2.b - s2.a);

        const T denomdenom = math::dot(b, d) * math::dot(b, d) - T(1);

        // they lie on the same line?
        // i think so since the dot product would equal 1 if b and d are the same
        if (denomdenom == T(0))
        {
            return std::min(math::length2(s1.a - s2.b), math::length2(s1.b - s2.a));
        }

        const T denom = T(1) / denomdenom;

        T t = math::dot(b, d) * (math::dot(c, d) - math::dot(a, d)) -
            math::dot(b, c) * math::dot(a, b);
        t *= denom;
        T s = math::dot(b, d) * (math::dot(a, d) - math::dot(b, c)) -
            math::dot(a, d) * math::dot(c, d);
        s *= denom;

        t = math::clamp(t, T(0), T(1));
        s = math::clamp(s, T(0), T(1));

        // closest points computed, find squared length
        return math::length2(a + b * t - c + d * s);
    }

    template <typename T>
    T distance(const line_segment<T>& s1, const line_segment<T>& s2)
    {
        return sqrt(distance2(s1, s2));
    }

    template <typename T>
    T distance2(const line_segment<T>& s, const aabb<T>& box)
    {
        T dist = T(0);

        for (int i = 0; i < 3; ++i)
        {
            T axisDist = clamp(s.a[i], (box.pos - box.half_extent)[i], (box.pos + box.half_extent)[i]) - s.a[i];
            dist += axisDist * axisDist;
        }

        return dist;
        /* scalar t = ???;
        t = clamp(t, scalar(0), scalar(1));

        return distance2(box, normalize(s.b - s.a) * t);  */
    }

    template <typename T>
    T distance2(const aabb<T>& box, const line_segment<T>& s)
    {
        return distance2(s, box);
    }

    template <typename T>
    T distance(const line_segment<T>& s, const aabb<T>& box)
    {
        return sqrt(distance2(s, box));
    }

    template <typename T>
    T distance(const aabb<T>& box, const line_segment<T>& s)
    {
        return sqrt(distance2(box, s));
    }

    template <typename T>
    T distance2(const line_segment<T>& s, const obb<T>& box)
    {
        abort();
        // I am going to prefer the GJK over this bc I can't get it to work
    }

    template <typename T>
    T distance2(const obb<T>& box, const line_segment<T>& s)
    {
        return distance2(s, box);
    }

    template <typename T>
    T distance(const line_segment<T>& s, const obb<T>& box)
    {
        return sqrt(distance2(s, box));
    }

    template <typename T>
    T distance(const obb<T>& box, const line_segment<T>& s)
    {
        return sqrt(distance2(box, s));
    }

    template <typename T>
    T distance2(const aabb<T>& box1, const aabb<T>& box2)
    {
        abort();
    }

    template <typename T>
    T distance(const aabb<T>& box1, const aabb<T>& box2)
    {
        return sqrt(distance2(box1, box2));
    }

    template <typename T>
    T distance2(const aabb<T>& box1, const obb<T>& box2)
    {
        abort();
    }

    template <typename T>
    T distance2(const obb<T>& box1, const aabb<T>& box2)
    {
        return distance2(box2, box1);
    }

    template <typename T>
    T distance(const aabb<T>& box1, const obb<T>& box2)
    {
        return sqrt(distance2(box1, box2));
    }

    template <typename T>
    T distance(const obb<T>& box1, const aabb<T>& box2)
    {
        return sqrt(distance2(box1, box2));
    }

    template <typename T>
    T distance2(const obb<T>& box1, const obb<T>& box2)
    {
        abort();
    }

    template <typename T>
    T distance(const obb<T>& box1, const obb<T>& box2)
    {
        return sqrt(distance2(box1, box2));
    }
}
