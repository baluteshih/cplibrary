#pragma once

#include "Geometry/base.hpp"
#include "Geometry/line.hpp"
#include "Geometry/polygon.hpp"

template<typename T, T eps = get_default_eps<T>(), typename MulT = T>
struct Circle : Geometry<T, eps> {
    using value_type = T;
    using Point = Pt<T, eps, MulT>;
    using Line = Ln<T, eps, MulT>;
    using polygon = Polygon<T, eps, MulT>;
    using Geometry<MulT, eps>::sign;
    using Geometry<MulT, eps>::cmp;
    static constexpr T eps_val = eps;
    Point o;
    T r;
    Circle(Point _o = {}, T _r = 0) : o(_o), r(_r) {}
    template <typename U, U _eps, typename _MulT>
    Circle(const Circle<U, _eps, _MulT>& other) : o(other.o), r(other.r) {}
    // actually counts number of tangent lines
    friend int typeOfCircles(const Circle &c1, const Circle &c2) {
        auto [o1, r1] = c1;
        auto [o2, r2] = c2;
        MulT d2 = dist2(o1, o2);
        int cmpsum = cmp(d2, MulT(r1 + r2) * MulT(r1 + r2));
        if (cmpsum == 1) { return 4; }
        if (cmpsum == 0) { return 3; }
        int cmpdiff = cmp(d2, MulT(r1 - r2) * MulT(r1 - r2));
        if (cmpdiff == 1) { return 2; }
        if (cmpdiff == 0) { return 1; }
        return 0;
    }
    // -1: in, 0: on, 1: out
    friend bool pointToCircle(const Point &p, const Circle &c) {
        MulT x = square(p - c.o), d = x - MulT(c.r) * MulT(c.r);
        return cmp(dist2(c.o, p), MulT(c.r) * MulT(c.r));
    }
    // aligned l.a -> l.b;
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend std::vector<Pt<Ret, _eps, _MulT>> circleLineIntersection(const Circle &c, const Line &l) {
        auto casto = Pt<Ret, _eps, _MulT>(c.o);
        auto p = projection<Ret, _eps, _MulT>(c.o, l);
        _MulT h = c.r * c.r - square(p - casto);
        if (sign(h) < 0) { return {}; }
        auto q = normal<Ret, _eps, _MulT>(direction(l)) * std::sqrt(h);
        return {p - q, p + q};
    }
    bool segCircleIntersect(const Line &l, const Circle &cc) {
        if (l[0] == l[1]) return pointToCircle(l[0], cc) == 0;
        Point dp = direction(l);
        MulT a = square(dp);
        MulT b = 2 * dot(dp, l[0] - cc.o);
        MulT c = square(cc.o) + square(l[0]) - 2 * dot(cc.o, l[0]) - MulT(cc.r) * MulT(cc.r);
        MulT res = b * b - 4 * a * c;
        return sign(res) >= 0;
    }
    // circles shouldn't be identical
    // one intersection dupliacted, aligned c1 counterclockwise
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend std::vector<Pt<Ret, _eps, _MulT>> circleIntersection(const Circle &c1, const Circle &c2) {
        int type = typeOfCircles(c1, c2);
        if (type == 0 || type == 4) { return {}; }
        auto [o1, r1] = c1;
        auto [o2, r2] = c2;
        Ret d = std::clamp(dist(o1, o2), std::abs(Ret(r1 - r2)), Ret(r1 + r2));
        Ret y = (r1 * r1 + d * d - r2 * r2) / (2 * d);
        Ret x = std::sqrt(_MulT(r1) * _MulT(r1) - _MulT(y) * _MulT(y));
        auto dir = normal<Ret, _eps, _MulT>(o2 - o1);
        auto q1 = Pt<Ret, _eps, _MulT>(o1) + dir * y;
        auto q2 = rotate90(dir) * x;
        return {q1 - q2, q1 + q2};
    }
    // counterclockwise, on circle -> no tangent
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend std::vector<Pt<Ret, _eps, _MulT>> pointCircleTangent(const Point &p, const Circle &c) {
        MulT x = square(p - c.o), d = x - MulT(c.r) * MulT(c.r);
        if (sign(d) <= 0) { return {}; }
        auto q1 = Pt<Ret, _eps, _MulT>(c.o) + Pt<Ret, _eps, _MulT>(p - c.o) * (Ret(c.r) * Ret(c.r) / Ret(x));
        auto q2 = Pt<Ret, _eps, _MulT>(rotate90(p - c.o)) * (Ret(c.r) * std::sqrt(Ret(d)) / Ret(x));
        return {q1 - q2, q1 + q2};
    }
    // one-point tangent lines are not returned
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend std::vector<Ln<Ret, _eps, _MulT>> externalTangent(const Circle &c1, const Circle &c2) {
        auto [o1, r1] = Circle<Ret, _eps, _MulT>(c1);
        auto [o2, r2] = Circle<Ret, _eps, _MulT>(c2);
        std::vector<Ln<Ret, _eps, _MulT>> res;
        if (cmp(c1.r, c2.r) == 0) {
            auto dr = rotate90(normal(o2 - o1)) * r1;
            res.emplace_back(o1 + dr, o2 + dr);
            res.emplace_back(o1 - dr, o2 - dr);
        }
        else {
            auto p = (o2 * r1 - o1 * r2) / (r1 - r2);
            auto ps = pointCircleTangent(p, Circle<Ret, _eps, _MulT>(c1)), qs = pointCircleTangent(p, Circle<Ret, _eps, _MulT>(c2));
            for (int i = 0; i < int(std::min(ps.size(), qs.size())); ++i) 
                res.emplace_back(ps[i], qs[i]);
        }
        return res;
    }
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend std::vector<Ln<Ret, _eps, _MulT>> internalTangent(const Circle &c1, const Circle &c2) {
        auto [o1, r1] = Circle<Ret, _eps, _MulT>(c1);
        auto [o2, r2] = Circle<Ret, _eps, _MulT>(c2);
        vector<Ln<Ret, _eps, _MulT>> res;
        auto p = (o1 * r2 + o2 * r1) / (r1 + r2);
        auto ps = pointCircleTangent(p, Circle<Ret, _eps, _MulT>(c1)), qs = pointCircleTangent(p, Circle<Ret, _eps, _MulT>(c2));
        for (int i = 0; i < int(std::min(ps.size(), qs.size())); i++)
            res.emplace_back(ps[i], qs[i]);
        return res;
    }
    // OAB and circle directed area
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    static Ret triangleCircleIntersectionArea(const Point &p1, const Point &p2, Ret r) {
        using FPt = Pt<Ret, _eps, _MulT>;
        auto angle = [&](const FPt &_p1, const FPt &_p2) { 
            return std::atan2(cross(_p1, _p2), dot(_p1, _p2));
        };
        FPt _p1 = p1, _p2 = p2;
        auto v = circleLineIntersection(Circle(FPt(), r), Ln(_p1, _p2));
        if (v.empty()) { return r * r * angle(_p1, _p2) / 2; }
        bool b1 = FPt::cmp(square(_p1), r * r) == 1;
        bool b2 = FPt::cmp(square(_p2), r * r) == 1;
        if (b1 && b2) {
            if (FPt::sign(dot(_p1 - v[0], _p2 - v[0])) <= 0 && FPt::sign(dot(_p1 - v[0], _p2 - v[0])) <= 0)
                return r * r * (angle(_p1, v[0]) + angle(v[1], _p2)) / 2 + cross(v[0], v[1]) / 2;
            return r * r * angle(_p1, _p2) / 2;
        }
        if (b1) return (r * r * angle(_p1, v[0]) + cross(v[0], _p2)) / 2;
        if (b2) return (cross(_p1, v[1]) + r * r * angle(v[1], _p2)) / 2;
        return cross(_p1, _p2) / 2;
    }
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend Ret polyCircleIntersectionArea(const polygon &a, Circle c) {
        int n = a.size();
        Ret ans = 0;
        for (int i = 0; i < n; i++)
            ans += triangleCircleIntersectionArea<Ret, _eps, _MulT>(a[i], a[(i + 1) % n], c.r);
        return ans;
    }
    template <typename Ret = DefaultFloat<T>>
    friend Ret circleIntersectionArea(Circle a, Circle b) {
        int tp = typeOfCircles(a, b);
        if (tp >= 3) return 0;
        if (tp <= 1) {
            Ret r = std::min(a.r, b.r);
            return r * r * std::numbers::pi_v<Ret>;
        }
        Ret res = 0, d = dist<Ret>(a.o, b.o);
        for (int i = 0; i < 2; ++i) {
            Ret alpha = std::acos((b.r * b.r + d * d - a.r * a.r) / (2 * Ret(b.r) * d));
            Ret s = alpha * Ret(b.r) * Ret(b.r);
            Ret t = Ret(b.r) * Ret(b.r) * std::sin(alpha) * std::cos(alpha);
            res += s - t;
            std::swap(a, b);
        }
        return res;
    }
};
