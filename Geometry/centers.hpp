#pragma once

#include "Geometry/base.hpp"
#include "Geometry/line.hpp"

// radius: (a + b + c) * r / 2 = A or pointToLineDist
template<typename Point, typename T = DefaultFloat<typename Point::value_type>, T eps = std::is_same_v<typename Point::value_type, T> ? Point::eps_val : get_default_eps<T>(), typename MulT = T>
Pt<T, eps, MulT> incenter(const Point &a, const Point &b, const Point &c) {
    T la = length(b - c), lb = length(c - a), lc = length(a - b);
    return (Pt<T, eps, MulT>(a) * la + Pt<T, eps, MulT>(b) * lb + Pt<T, eps, MulT>(c) * lc) / (la + lb + lc);
}

template<typename Point, typename T = DefaultFloat<typename Point::value_type>, T eps = std::is_same_v<typename Point::value_type, T> ? Point::eps_val : get_default_eps<T>(), typename MulT = T>
Pt<T, eps, MulT> circumcenter(const Point &a, const Point &b, const Point &c) {
    Pt<T, eps, MulT> ba = b - a, ca = c - a;
    T db = square(ba), dc = square(ca), d = 2 * cross(ba, ca);
    return Pt<T, eps, MulT>(a) - Pt<T, eps, MulT>(ba.y * dc - ca.y * db, ca.x * db - ba.x * dc) / d;
}

template<typename Point, typename T = DefaultFloat<typename Point::value_type>, T eps = std::is_same_v<typename Point::value_type, T> ? Point::eps_val : get_default_eps<T>(), typename MulT = T>
Pt<T, eps, MulT> orthocenter(const Point &a, const Point &b, const Point &c) {
    Ln<T, eps, MulT> u(c, Pt<T, eps, MulT>(c.x - a.y + b.y, c.y + a.x - b.x));
    Ln<T, eps, MulT> v(b, Pt<T, eps, MulT>(b.x - a.y + c.y, b.y + a.x - c.x));
    return lineIntersection(u, v);
}

// -1: in, 0: on, 1: out, C^4
template<typename Point, typename MulT = typename Point::value_type, MulT eps = std::is_same_v<typename Point::value_type, MulT> ? Point::eps_val : get_default_eps<MulT>()>
int pointInCircumCircle(const Point &a, const Point &b, const Point &c, const Point &q) {
    MulT det = 0;
    det += MulT(square(a) - square(q)) * MulT(cross(b - q, c - q));
    det += MulT(square(b) - square(q)) * MulT(cross(c - q, a - q));
    det += MulT(square(c) - square(q)) * MulT(cross(a - q, b - q));
    return Geometry<MulT, eps>::sign(det);
}
