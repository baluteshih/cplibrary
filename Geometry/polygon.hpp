#pragma once

#include "Geometry/base.hpp"
#include "Geometry/line.hpp"

template<typename T, T eps = get_default_eps<T>(), typename MulT = T>
class Polygon : public std::vector<Pt<T, eps, MulT>>, public Geometry<MulT, eps> {
    using Point = Pt<T, eps, MulT>;
    using Line = Ln<T, eps, MulT>;
    using std::vector<Pt<T, eps, MulT>>::vector;
    using Geometry<MulT, eps>::sign;
    using Geometry<MulT, eps>::cmp;
public:
    Polygon(const std::vector<Point> &vec) : Polygon(vec.begin(), vec.end()) {} 
    template <typename U, U _eps, typename _MulT>
    Polygon(const Polygon<U, _eps, _MulT>& other) : Polygon(other.begin(), other.end()) {}
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
    Line edge(int index) const {
        return Ln(at(index), at(index + 1));
    }
    // return twice of the true direct area
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
    template <typename Ret = DefaultFloat<T>>
    friend Ret polyUnionArea(const std::vector<Polygon> &poly) {
        auto rat = [&](const Point &a, const Point &b) {
            return sign(b.x) ? Ret(a.x) / Ret(b.x) : Ret(a.y) / Ret(b.y);
        };
        Ret res = 0;
        for (auto &p : poly)
            for (int a = 0; a < int(p.size()); ++a) {
                Point A = p[a], B = p[(a + 1) % int(p.size())];
                std::vector<std::pair<Ret, int>> segs;
                segs.emplace_back(Ret(0), 0);
                segs.emplace_back(Ret(1), 0);
                for (auto &q : poly) {
                    if (&p == &q) continue;
                    for (int b = 0; b < int(q.size()); ++b) {
                        Point C = q[b], D = q[(b + 1) % int(q.size())];
                        int sc = side(A, B, C), sd = side(A, B, D);
                        if (sc != sd && std::min(sc, sd) < 0) {
                            Ret sa = cross(D - C, A - C), sb = cross(D - C, B - C);
                            segs.emplace_back(sa / (sa - sb), Geometry<int>::sign(sc - sd));
                        }
                        if (!sc && !sd && &q < &p && sign(dot(B - A, D - C)) > 0) {
                            segs.emplace_back(rat(C - A, B - A), 1);
                            segs.emplace_back(rat(D - A, B - A), -1);
                        }
                    }
                }
                std::ranges::sort(segs);
                for (auto &s : segs) s.first = std::clamp(s.first, Ret(0), Ret(1));
                Ret sum = 0;
                int cnt = segs[0].second;
                for (int j = 1; j < int(segs.size()); ++j) {
                    if (!cnt) sum += segs[j].first - segs[j - 1].first;
                    cnt += segs[j].second;
                }
                res += Ret(cross(A, B)) * sum;
            }
        return res / 2;
    }
};

template <typename PointType>
struct PolygonType;

template <typename T, T eps, typename MulT>
struct PolygonType<Pt<T, eps, MulT>> {
    using type = Polygon<T, eps, MulT>;
};
