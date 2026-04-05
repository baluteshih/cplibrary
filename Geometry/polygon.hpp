#pragma once

#include "Geometry/base.hpp"
#include "Geometry/line.hpp"

template<typename T, T eps = get_default_eps<T>(), typename MulT = T>
class Polygon : public std::vector<Pt<T, eps, MulT>>, public Geometry<MulT, eps> {
    using Point = Pt<T, eps, MulT>;
    using std::vector<Pt<T, eps, MulT>>::vector;
    using Geometry<MulT, eps>::sign;
    using Geometry<MulT, eps>::cmp;
public:
    Polygon(const std::vector<Point> &vec) : Polygon(vec.begin(), vec.end()) {} 
    Point& at(int index) {
        index %= this->size();
        if (index < 0) index += this->size();
        return (*this)[index];
    }
    const Point& at(int index) const {
        index %= this->size();
        if (index < 0) index += this->size();
        return (*this)[index];
    }
    MulT area() {
        MulT res = 0;
        int n = this->size();
        for (int i = 0; i < n; ++i)
            res += cross((*this)[i], (*this)[(i + 1) % n]);
        return res;
    }
    int polygon_dir() {
        return sign(area());
    }
    friend bool pointInPoly(const Point &p, const Polygon &a, bool strict = false) {
        int n = a.size(), res = 0;
        for (int i = 0; i < n; i++) {
            Point u = a[i], v = a[(i + 1) % n];
            if (pointOnSeg(p, Ln(u, v))) { return !strict; }
            if (cmp(u.y, v.y) <= 0) { std::swap(u, v); }
            if (cmp(p.y, u.y) > 0 || cmp(p.y, v.y) <= 0) { continue; }
            res ^= sign(cross(p, u, v)) > 0;
        }
        return res;
    }
    friend bool pointStrictlyInPoly(const Point &p, const Polygon &a) {
        return pointInPoly(p, a, true);
    }
};

template <typename PointType>
struct PolygonType;

template <typename T, T eps, typename MulT>
struct PolygonType<Pt<T, eps, MulT>> {
    using type = Polygon<T, eps, MulT>;
};
