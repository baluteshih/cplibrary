#include "exact_geometry.hpp"
#include <cmath>
#include <iomanip>
#include <limits>

Wide scalar(const Point &a, const Point &b) {
    return Wide(a[0]) * b[0] + Wide(a[1]) * b[1] + Wide(a[2]) * b[2];
}
struct Support {
    Wide d;
    std::vector<Point> points;
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<Point> p(n);
    for (auto &x : p) std::cin >> x[0] >> x[1] >> x[2];
    std::map<Point, Support> cache;
    std::cout << std::fixed << std::setprecision(18);
    while (q--) {
        Point normal, query;
        std::cin >> normal[0] >> normal[1] >> normal[2] >> query[0] >> query[1] >> query[2];
        if (!cache.count(normal)) {
            Wide d = scalar(normal, p[0]);
            for (const auto &x : p) {
#ifdef MIN_SUPPORT
                d = std::min(d, scalar(normal, x));
#else
                d = std::max(d, scalar(normal, x));
#endif
            }
            Support value{d, {}};
            for (const auto &x : p) if (scalar(normal, x) == d) value.points.push_back(x);
            cache.emplace(normal, std::move(value));
        }
        const auto &support = cache.at(normal);
        Wide numerator = scalar(normal, query) - support.d;
#ifdef NARROW_DOT
        numerator = static_cast<long long>(numerator);
#endif
        long double value = static_cast<long double>(numerator);
#ifndef SIGNED_DISTANCE
        value = std::fabs(value);
#endif
        Wide length2 = scalar(normal, normal);
        long double denominator = std::sqrt(static_cast<long double>(length2));
#ifdef NO_NORMALIZATION
        denominator = 1;
#endif
#ifdef SQUARED_NORMALIZATION
        denominator = static_cast<long double>(length2);
#endif
#ifdef FLOAT_ARITHMETIC
        float sum = 0, square = 0;
        for (int i = 0; i < 3; ++i) {
            sum += float(normal[i]) * float(query[i]);
            square += float(normal[i]) * float(normal[i]);
        }
        value = std::fabs(sum - float(support.d));
        denominator = std::sqrt(square);
#endif
#ifdef NEAREST_VERTEX
        value = std::numeric_limits<long double>::infinity();
        for (const auto &x : support.points) {
            auto delta = difference(x, query);
            value = std::min(value, std::sqrt(static_cast<long double>(dot(delta, delta))));
        }
        denominator = 1;
#endif
        std::cout << value / denominator << '\n';
    }
}
