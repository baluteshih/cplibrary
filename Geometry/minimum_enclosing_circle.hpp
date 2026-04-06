#pragma once

#include "Geometry/base.hpp"
#include "Geometry/circle.hpp"
#include "Geometry/centers.hpp"

template<typename Point, typename T = DefaultFloat<typename Point::value_type>, T eps = std::is_same_v<typename Point::value_type, T> ? Point::eps_val : get_default_eps<T>(), typename MulT = T>
Circle<T, eps, MulT> minimum_enclosing_circle(const std::vector<Point> &_dots) {
    static std::mt19937 rng(880301);
    std::vector<Pt<T, eps, MulT>> dots(_dots.begin(), _dots.end());
    std::ranges::shuffle(dots, rng);
    Circle<T, eps, MulT> res(dots[0], 0);
    for (int i = 1; i < SZ(dots); ++i) 
        if (dist(dots[i], res.o) > res.r) {
            res.o = dots[i], res.r = 0;
            for (int j = 0; j < i; ++j)
                if (dist(dots[j], res.o) > res.r) {
                    res.o = (dots[i] + dots[j]) / 2;
                    res.r = dist(dots[i], res.o);
                    for (int k = 0; k < j; ++k)
                        if (dist(dots[k], res.o) > res.r) {
                            res.o = circumcenter(dots[i], dots[j], dots[k]);
                            res.r = dist(dots[i], res.o);
                        }
                }
        }
    return res;
}
