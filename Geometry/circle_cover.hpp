#pragma once

#include "Geometry/base.hpp"
#include "Geometry/circle.hpp"

/*
return area[0], area[1], ... area[n]
area[i] : area covered by at least i circles
area[0] undefined
*/
template<typename Cir, typename Ret = DefaultFloat<typename Cir::value_type>, Ret eps = std::is_same_v<typename Cir::value_type, Ret> ? Cir::eps_val : get_default_eps<Ret>(), typename MulT = Ret>
std::vector<Ret> circle_cover(const std::vector<Cir> &circles) {
    using Point = Pt<Ret, eps, MulT>;
    struct Teve {
        Point p;
        Ret ang;
        int add;
        Teve() {}
        Teve(const Point &_a, const Ret &_b, int _c): p(_a), ang(_b), add(_c){}
        bool operator<(const Teve &a) const {
            return ang < a.ang;
        }
    };
    int n = circles.size();
    std::vector<Ret> area(n + 1);
    std::vector<std::vector<int>> typ(n, std::vector<int>(n));
    std::vector<Teve> eve(n * 2);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            typ[i][j] = typeOfCircles(circles[i], circles[j]);
    for (int i = 0; i < n; ++i) {
        int E = 0, cnt = 1;
        for (int j = 0; j < n; ++j)
            if (j != i && typ[i][j] <= 1 && (Cir::cmp(circles[j].r, circles[i].r) > 0 || (Cir::cmp(circles[j].r, circles[i].r) == 0 && i < j)))
                ++cnt;
        for (int j = 0; j < n; ++j)
            if (i != j && typ[i][j] == 2) {
                auto it = circleIntersection(circles[i], circles[j]);
                Ret A = angle(it[1] - Point(circles[i].o));
                Ret B = angle(it[0] - Point(circles[i].o));
                eve[E++] = Teve(it[0], B, 1);
                eve[E++] = Teve(it[1], A, -1);
                if (B > A) ++cnt;
            }
        if (E == 0) area[cnt] += std::numbers::pi_v<Ret> * Ret(circles[i].r) * Ret(circles[i].r);
        else {
            std::sort(eve.begin(), eve.begin() + E);
            eve[E] = eve[0];
            for (int j = 0; j < E; ++j) {
                cnt += eve[j].add;
                area[cnt] += cross(eve[j].p, eve[j + 1].p) / 2;
                Ret theta = eve[j + 1].ang - eve[j].ang;
                if (theta < 0) theta += std::numbers::pi_v<Ret> * Ret(2);
                area[cnt] += (theta - std::sin(theta)) * circles[i].r * circles[i].r / 2;
            }
        }
    }
    return area;
}
