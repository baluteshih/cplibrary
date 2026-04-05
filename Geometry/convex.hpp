#pragma once

#include "Geometry/base.hpp"
#include "Geometry/line.hpp"
#include "Geometry/polygon.hpp"
#include "Misc/cyc_bitonic_search.hpp"

template <typename Point>
PolygonType<Point>::type convexHull(std::vector<Point> dots, bool sort_and_unique = true) {
    if (sort_and_unique) {
        std::ranges::sort(dots);
        dots.erase(ranges::unique(dots).begin(), dots.end());
    }
    int n = dots.size();
    if (n <= 1) { return dots; }
    std::vector<Point> res(2 * n);
    int j = 0;
    for (int i = 0; i < n; res[j++] = dots[i++]) {
        while (j >= 2 && side(res[j - 2], res[j - 1], dots[i]) <= 0) { j--; }
    }
    for (int i = n - 2, k = j; i >= 0; res[j++] = dots[i--]) {
        while (j > k && side(res[j - 2], res[j - 1], dots[i]) <= 0) { j--; }
    }
    res.resize(j - 1);
    return res;
}

template <typename Point>
std::pair<typename PolygonType<Point>::type, typename PolygonType<Point>::type> convexHullParts(std::vector<Point> dots, bool sort_and_unique = true) {
    if (sort_and_unique) {
        std::ranges::sort(dots);
        dots.erase(ranges::unique(dots).begin(), dots.end());
    }
    int n = dots.size();
    if (n <= 1) { return std::make_pair(dots, dots); }
    std::vector<Point> res(2 * n);
    int j = 0;
    for (int i = 0; i < n; res[j++] = dots[i++]) {
        while (j >= 2 && side(res[j - 2], res[j - 1], dots[i]) <= 0) { j--; }
    }
    int k = j;
    for (int i = n - 2; i >= 0; res[j++] = dots[i--]) {
        while (j > k && side(res[j - 2], res[j - 1], dots[i]) <= 0) { j--; }
    }
    std::vector<Point> lower(res.begin(), res.begin() + k);
    std::vector<Point> upper(res.begin() + k - 1, res.begin() + j);
    std::ranges::reverse(upper);
    return std::make_pair(lower, upper);
}

// warning : if all point on same line will return {1, 2, 3, 2}
template <typename Point>
PolygonType<Point>::type convexHullNonstrict(std::vector<Point> dots, bool sort_and_unique = true) {
    if (sort_and_unique) {
        std::ranges::sort(dots);
        dots.erase(ranges::unique(dots).begin(), dots.end());
    }
    int n = dots.size();
    if (n <= 1) { return dots; }
    std::vector<Point> res(2 * n);
    int j = 0;
    for (int i = 0; i < n; res[j++] = dots[i++]) {
        while (j >= 2 && side(res[j - 2], res[j - 1], dots[i]) < 0) { j--; }
    }
    for (int i = n - 2, k = j; i >= 0; res[j++] = dots[i--]) {
        while (j > k && side(res[j - 2], res[j - 1], dots[i]) < 0) { j--; }
    }
    res.resize(j - 1);
    return res;
}

// a and b are nonempty, need reorder
template <typename polygon>
polygon convexMinkowski(polygon a, polygon b) {
    a = convexHull(a), b = convexHull(b);
    int n = a.size(), m = b.size();
    if (n != 1) { std::swap(n, m), std::swap(a, b); }
    if (n == 1) {
        for (auto &p : b) { p = p + a[0]; }
        return b;
    }
    a.push_back(a[0]), a.push_back(a[1]);
    b.push_back(b[0]), b.push_back(b[1]);
    polygon c;
    for (int i = 0, j = 0; i < n || j < m; ) {
        c.push_back(a[i] + b[j]);
        int s = sign(cross(a[i + 1] - a[i], b[j + 1] - b[j]));
        if (i < n && s >= 0) { i++; }
        if (j < m && s <= 0) { j++; }
    }
    return c;
}

// 1: in, 0: on, -1: out
template <typename Point>
int pointInConvex(const Point &p, const typename PolygonType<Point>::type &a) {
    int n = a.size();
    if (n < 3) { return pointOnSeg(p, Ln(a[0], a.back())) ? 0 : -1; }
    if (side(p, a[1], a[0]) >= 0) {
        return pointOnSeg(p, Ln(a[1], a[0])) ? 0 : -1;
    }
    if (side(p, a[0], a.back()) >= 0) {
        return pointOnSeg(p, Ln(a[0], a.back())) ? 0 : -1;
    }
    int l = 1, r = n - 2;
    while (l < r) {
        int m = (l + r + 1) >> 1;
        if (side(p, a[0], a[m]) >= 0) l = m;
        else r = m - 1;
    }
    return side(p, a[l], a[l + 1]);
}

/* The point should be strictly out of hull
   return arbitrary point on the tangent line */
template <typename Point>
std::pair<int, int> tangentLineToConvex(const Point &p, const typename PolygonType<Point>::type &a) {
    auto gao = [&](int s) {
        return cyc_bitonic_search(a.size(), 
        [&](int x, int y) { return side(p, a[x], a[y]) == s; });
    };
    return std::make_pair(gao(1), gao(-1));
}

template <typename Point>
int tangentDirection(const Point &dir, const typename PolygonType<Point>::type &C) {
  return cyc_bitonic_search(SZ(C), [&](int a, int b) {
    return Point::cmp(cross(dir, C[a]), cross(dir, C[b])) > 0;
  });
}

template<typename T, T eps = get_default_eps<T>(), typename MulT = T>
std::pair<int, int> lineIntersectConvex(const Ln<T, eps, MulT> &ln, const Polygon<T, eps, MulT> &C) {
    auto cmpL = [&](int i) {
        return Ln<T, eps, MulT>::sign(cross(C[i] - ln[0], direction(ln)));
    };
    int A = tangentDirection(-direction(ln), C);
    int B = tangentDirection(direction(ln), C);
    int n = SZ(C);
    if (cmpL(A) < 0 || cmpL(B) > 0)
        return std::make_pair(-1, -1); // no collision
    auto gao = [&](int l, int r) {
        for (int t = l; (l + 1) % n != r; ) {
            int m = ((l + r + (l < r ? 0 : n)) / 2) % n;
            (cmpL(m) == cmpL(t) ? l : r) = m;
        }
        return (l + !cmpL(r)) % n;
    };
    std::pair<int, int> res = std::make_pair(gao(B, A), gao(A, B)); // (i, j)
    if (res.first == res.second) // touching the corner i
        return std::make_pair(res.first, -1);
    if (!cmpL(res.first) && !cmpL(res.second)) // along side i, i+1
        switch ((res.first - res.second + n + 1) % n) {
            case 0: return std::make_pair(res.first, res.first);
            case 2: return std::make_pair(res.second, res.second);
        }
    /* crossing sides (i, i+1) and (j, j+1)
       crossing corner i is treated as side (i, i+1)
       returned in the same order as the line hits the convex */
    return res;
} // convex cut: (r, l]
