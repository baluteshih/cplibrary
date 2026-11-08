#include "judge_geometry.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

int turn(const Dual &p, const Dual &q, const Dual &r) {
#ifdef FLOAT_TURN
    double x1 = double(q.a) / q.c - double(p.a) / p.c;
    double y1 = double(q.b) / q.c - double(p.b) / p.c;
    double x2 = double(r.a) / r.c - double(p.a) / p.c;
    double y2 = double(r.b) / r.c - double(p.b) / p.c;
    double value = x1 * y2 - y1 * x2;
    return (value > 1e-12) - (value < -1e-12);
#else
    auto value = determinant(p, q, r);
#ifdef NARROW_TURN
    value = static_cast<long long>(value);
#endif
    return (value > 0) - (value < 0);
#endif
}
std::vector<Dual> hull(std::vector<Dual> p) {
    std::sort(p.begin(), p.end(), less_point);
    p.erase(std::unique(p.begin(), p.end(), [](const Dual &a, const Dual &b) {
        return !less_point(a, b) && !less_point(b, a);
    }), p.end());
#ifdef GIFT_WRAP
    std::vector<Dual> result;
    int current = 0, n = int(p.size());
    do {
        result.push_back(p[current]);
        int next = (current + 1) % n;
        for (int i = 0; i < n; ++i) {
            if (i == current) continue;
            int side = turn(p[current], p[next], p[i]);
            bool farther = less_point(p[current], p[next]) ? less_point(p[next], p[i]) : less_point(p[i], p[next]);
            if (side < 0 || (side == 0 && farther)) next = i;
        }
        current = next;
    } while (current != 0);
    return result;
#else
    std::vector<Dual> result;
    auto append = [&](const Dual &x, std::size_t floor) {
        while (result.size() >= floor + 2) {
            int side = turn(result[result.size() - 2], result.back(), x);
#ifdef KEEP_COLLINEAR
            if (side >= 0) break;
#else
            if (side > 0) break;
#endif
            result.pop_back();
        }
        result.push_back(x);
    };
    for (const auto &x : p) append(x, 0);
    std::size_t floor = result.size() - 1;
    for (int i = int(p.size()) - 2; i >= 0; --i) append(p[i], floor);
    result.pop_back();
    return result;
#endif
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, bound;
    std::cin >> n >> bound;
    std::vector<Dual> p;
    for (int i = 1; i <= n; ++i) {
        long long x, y, u, v;
        std::cin >> x >> y >> u >> v;
        p.push_back(make_dual(x, y, u, v, i));
    }
#ifdef LOOSE_PARALLEL
    std::map<std::pair<long long, long long>, Dual> chosen;
    for (const auto &x : p) {
        Key k = key(x);
        auto direction = std::make_pair(k[0], k[1]);
        if (!chosen.count(direction) || key(chosen[direction])[2] < k[2]) chosen[direction] = x;
    }
    p.clear();
    for (const auto &[direction, x] : chosen) p.push_back(x);
#endif
    auto result = hull(p);
#ifdef INPUT_ORDER
    std::sort(result.begin(), result.end(), [](const Dual &a, const Dual &b) { return a.id < b.id; });
#endif
#ifdef REVERSED
    std::reverse(result.begin(), result.end());
#endif
    std::cout << result.size() << '\n';
    for (std::size_t i = 0; i < result.size(); ++i) std::cout << result[i].id << (i + 1 == result.size() ? '\n' : ' ');
}
