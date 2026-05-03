#pragma once

#include "Geometry/Point3D.hpp"

// all points coplanar case will WA, O(n^2)
template<typename T, T eps = get_default_eps<T>(), typename MulT = T>
struct convexHull3D : Geometry<T, eps> {
    using Point = Pt3<T, eps, MulT>; 
    using value_type = T;
    using Geometry<MulT, eps>::sign;
    using Geometry<MulT, eps>::cmp;
    static constexpr T eps_val = eps;
    struct Face {
        int a, b, c;
        Face(int ta, int tb, int tc) : a(ta), b(tb), c(tc) {}
    }; // store the faces with input point indexes
    std::vector<Face> res;
    std::vector<Point> P;
    convexHull3D(const std::vector<Point> &_P) : res(), P(_P) {
        int n = P.size();
        if (n <= 2) return; // be careful about edge case
        // ensure first 4 points are not coplanar
        swap(P[1], *std::ranges::find_if(P, [&](auto p) { return sign(square(P[0] - p)) != 0; }));
        swap(P[2], *std::ranges::find_if(P, [&](auto p) { return sign(square(cross(p, P[0], P[1]))) != 0; }));
        swap(P[3], *std::ranges::find_if(P, [&](auto p) { return sign(volume(P[0], P[1], P[2], p)) != 0; }));
        std::vector<std::vector<int>> flag(n, std::vector<int>(n));
        res.emplace_back(0, 1, 2);
        res.emplace_back(2, 1, 0);
        for (int i = 3; i < n; ++i) {
            std::vector<Face> next;
            for (auto f : res) {
                int d = sign(volume(P[f.a], P[f.b], P[f.c], P[i]));
                if (d <= 0) next.push_back(f);
                int ff = (d > 0) - (d < 0);
                flag[f.a][f.b] = flag[f.b][f.c] = flag[f.c][f.a] = ff;
            }
            for (auto f : res) {
                auto F = [&](int x, int y) {
                    if (flag[x][y] > 0 && flag[y][x] <= 0)
                        next.emplace_back(x, y, i);
                };
                F(f.a, f.b), F(f.b, f.c), F(f.c, f.a);
            }
            res = next;
        }
    }
    bool same(const Face &s, const Face &t) {
        if (sign(volume(P[s.a], P[s.b], P[s.c], P[t.a])) != 0) return 0;
        if (sign(volume(P[s.a], P[s.b], P[s.c], P[t.b])) != 0) return 0;
        if (sign(volume(P[s.a], P[s.b], P[s.c], P[t.c])) != 0) return 0;
        return 1;
    }
    int polygon_face_num() {
        int ans = 0;
        for (int i = 0; i < int(res.size()); ++i)
            ans += std::none_of(res.begin(), res.begin() + i, [&](const Face &g) { return same(res[i], g); });
        return ans;
    }
    // return 6 times the actual volume
    MulT get_volume() {
        MulT ans = 0;
        for (auto f : res)
            ans += volume(Point(0, 0, 0), P[f.a], P[f.b], P[f.c]);
        return ans;
    }
    template <typename Ret = DefaultFloat<T>>
    Ret get_dis(Point p, Face f) {
        Point p1 = P[f.a], p2 = P[f.b], p3 = P[f.c];                    
        Ret a = Ret(p2.y - p1.y) * Ret(p3.z - p1.z) - Ret(p2.z - p1.z) * Ret(p3.y - p1.y); 
        Ret b = Ret(p2.z - p1.z) * Ret(p3.x - p1.x) - Ret(p2.x - p1.x) * Ret(p3.z - p1.z); 
        Ret c = Ret(p2.x - p1.x) * Ret(p3.y - p1.y) - Ret(p2.y - p1.y) * Ret(p3.x - p1.x); 
        Ret d = Ret(0) - Ret(a * p1.x + b * p1.y + c * p1.z); 
        return std::abs(a * Ret(p.x) + b * Ret(p.y) + c * Ret(p.z) + d) / std::sqrt(a * a + b * b + c * c);                    
    }
};
// n^2 delaunay: facets with negative z normal of
// convexhull of (x, y, x^2 + y^2), use a pseudo-point
// (0, 0, inf) to avoid degenerate case
