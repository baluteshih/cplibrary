#pragma once

#include "Geometry/base.hpp"

template<typename T, T eps = get_default_eps<T>(), typename MulT = T>
struct Ln : Geometry<T, eps> {
    using Point = Pt<T, eps, MulT>;
    std::array<Point, 2> l;
    using Geometry<MulT, eps>::sign;
    using Geometry<MulT, eps>::cmp;
    Ln() {}
    Ln(const Point &a, const Point &b) : l{a, b} {}
    friend istream& operator>>(istream &is, Ln &p) { return is >> p.l[0] >> p.l[1]; }
    friend ostream& operator<<(ostream &os, const Ln &p) { return os << p.l[0] << ' ' << p.l[1]; }
    template <typename U, U _eps, typename _MulT>
    Ln(const Ln<U, _eps, _MulT>& other) : l{other.l[0], other.l[1]} {}
    friend int side(const Point &p, const Ln &l) { 
        return side(p, l[0], l[1]);
    }
    Point& operator[](int index) {
        return l[index];
    }
    const Point& operator[](int index) const {
        return l[index];
    }
    friend Point direction(const Ln &l) {
        return l[1] - l[0];
    }
    friend bool parallel(const Ln &l1, const Ln &l2) {
        return parallel(direction(l1), direction(l2));
    }
    friend bool sameDirection(const Ln &l1, const Ln &l2) {
        return sameDirection(direction(l1), direction(l2));
    }
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend Pt<Ret, _eps, _MulT> projection(const Point &p, const Ln &l) {
        auto d = direction(l);
        return Pt<Ret, _eps, _MulT>(l[0]) + Pt<Ret, _eps, _MulT>(d) * (Ret(dot(p - l[0], d)) / Ret(square(d)));
    }
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend Pt<Ret, _eps, _MulT> reflection(const Point &p, const Ln &l) {
        return projection<Ret, _eps, _MulT>(p, l) * Ret(2) - Pt<Ret, _eps, _MulT>(p);
    }
    template <typename Ret = DefaultFloat<T>>
    friend Ret pointToLineDist(const Point &p, const Ln &l) {
        if (l[0] == l[1]) { return dist<Ret>(p, l[0]); }
        return std::abs(cross(l[0] - l[1], l[0] - p)) / length<Ret>(direction(l));
    }
    // better use integers if you don't need exact coordinate
    // l <= r is not explicitly required
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend Pt<Ret, _eps, _MulT> lineIntersection(const Ln &l1, const Ln &l2) {
        return Pt<Ret, _eps, _MulT>(l1[0]) - Pt<Ret, _eps, _MulT>(direction(l1)) * (Ret(cross(direction(l2), l1[0] - l2[0])) / Ret(cross(direction(l2), direction(l1))));
    }
    template <typename U>
    static bool between(U m, U l, U r) {
        return cmp(l, m) == 0 || cmp(m, r) == 0 || (l < m) != (r < m);
    }
    friend bool pointOnSeg(const Point &p, const Ln &l) {
        return side(p, l) == 0 && between(p.x, l[0].x, l[1].x) && between(p.y, l[0].y, l[1].y);
    }
    friend bool pointStrictlyOnSeg(const Point &p, const Ln &l) {
        return side(p, l) == 0 && sign(dot(p - l[0], direction(l))) * sign(dot(p - l[1], direction(l))) < 0;
    }
    template <typename U>
    static bool overlap(U l1, U r1, U l2, U r2) {
        if (l1 > r1) { std::swap(l1, r1); }
        if (l2 > r2) { std::swap(l2, r2); }
        return cmp(r1, l2) != -1 && cmp(r2, l1) != -1;
    }
    friend bool segIntersect(const Ln &l1, const Ln &l2) {
        auto [p1, p2] = l1.l;
        auto [q1, q2] = l2.l;
        return overlap(p1.x, p2.x, q1.x, q2.x) && overlap(p1.y, p2.y, q1.y, q2.y) &&
                side(p1, l2) * side(p2, l2) <= 0 &&
                side(q1, l1) * side(q2, l1) <= 0;
    }
    // parallel intersecting is false
    friend bool segStrictlyIntersect(const Ln &l1, const Ln &l2) {
        auto [p1, p2] = l1.l;
        auto [q1, q2] = l2.l;
        return side(p1, l2) * side(p2, l2) < 0 &&
               side(q1, l1) * side(q2, l1) < 0;
    }
    // parallel or intersect at source doesn't count
    friend bool rayIntersect(const Ln &l1, const Ln &l2) {
        int x = sign(cross(l1[1] - l1[0], l2[1] - l2[0]));
        return x == 0 ? false : side(l1[0], l2) == x && side(l2[0], l1) == -x;
    } 
    template <typename Ret = DefaultFloat<T>>
    friend Ret pointToSegDist(const Point &p, const Ln &l) {
        auto d = direction(l);
        if (sign(dot(p - l[0], d)) >= 0 && sign(dot(p - l[1], d)) <= 0)
            return pointToLineDist<Ret>(p, l);
        return std::min(dist<Ret>(p, l[0]), dist<Ret>(p, l[1]));
    }
    template <typename Ret = DefaultFloat<T>>
    friend Ret segDist(const Ln &l1, const Ln &l2) {
        if (segIntersect(l1, l2)) { return Ret(0); }
        return std::min({pointToSegDist<Ret>(l1[0], l2), pointToSegDist<Ret>(l1[1], l2),
                pointToSegDist<Ret>(l2[0], l1), pointToSegDist<Ret>(l2[1], l1)});
    }
};

template <typename PointType>
struct LineType;

template <typename T, T eps, typename MulT>
struct LineType<Pt<T, eps, MulT>> {
    using type = Ln<T, eps, MulT>;
};
