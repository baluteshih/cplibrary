#pragma once
#include "exact_geometry.hpp"

struct Hull {
    std::map<Plane, std::vector<int>> facets;
    Wide volume6 = 0;
};

std::vector<int> projected_hull(const std::vector<Point> &p, std::vector<int> ids, int drop) {
    int x = (drop + 1) % 3, y = (drop + 2) % 3;
    auto coordinates = [&](int i) { return std::make_pair(p[i][x], p[i][y]); };
    std::sort(ids.begin(), ids.end(), [&](int a, int b) { return coordinates(a) < coordinates(b); });
    ids.erase(std::unique(ids.begin(), ids.end(), [&](int a, int b) { return coordinates(a) == coordinates(b); }), ids.end());
    std::vector<int> result;
    auto append = [&](int i, std::size_t floor) {
        while (result.size() >= floor + 2) {
            int a = result[result.size() - 2], b = result.back();
            Wide turn = (Wide(p[b][x]) - p[a][x]) * (Wide(p[i][y]) - p[a][y])
                      - (Wide(p[b][y]) - p[a][y]) * (Wide(p[i][x]) - p[a][x]);
            if (turn > 0) break;
            result.pop_back();
        }
        result.push_back(i);
    };
    for (int i : ids) append(i, 0);
    std::size_t floor = result.size() - 1;
    for (int i = int(ids.size()) - 2; i >= 0; --i) append(ids[i], floor);
    result.pop_back();
    return result;
}

Hull gift_wrapping(const std::vector<Point> &p) {
    int n = int(p.size());
    auto pivot = [&](int a, int b) {
#ifdef CUBIC_PIVOT
        for (int c = 0; c < n; ++c) {
            if (zero(cross(difference(p[b], p[a]), difference(p[c], p[a])))) continue;
            Plane f = plane(p[a], p[b], p[c]);
            bool valid = true;
            for (const auto &q : p) valid &= side(f, q) <= 0;
            if (valid) return f;
        }
        assert(false);
        return Plane{};
#else
        auto edge = difference(p[b], p[a]);
        int c = 0;
        while (c < n && zero(cross(edge, difference(p[c], p[a])))) ++c;
        assert(c < n);
        auto normal = cross(edge, difference(p[c], p[a]));
        for (int i = 0; i < n; ++i) {
            if (dot(normal, difference(p[i], p[a])) > 0) {
                c = i;
                normal = cross(edge, difference(p[c], p[a]));
            }
        }
        return plane(p[a], p[b], p[c]);
#endif
    };
    std::vector<int> ids(n);
    std::iota(ids.begin(), ids.end(), 0);
    auto projection = projected_hull(p, ids, 2);
    assert(projection.size() >= 3);
    int a = projection[0], b = projection[1];
    Wide nx = Wide(p[b][1]) - p[a][1], ny = Wide(p[a][0]) - p[b][0];
    Wide g = gcd_wide(nx, ny);
    Plane initial{nx / g, ny / g, 0, (nx * p[a][0] + ny * p[a][1]) / g};
    std::vector<int> on;
    for (int i = 0; i < n; ++i) if (side(initial, p[i]) == 0) on.push_back(i);
    bool facet = false;
    for (int i : on) if (!zero(cross(difference(p[b], p[a]), difference(p[i], p[a])))) facet = true;
    if (!facet) initial = pivot(on.front(), on.back());
    Hull result;
    std::vector<Plane> queue{initial};
    std::set<Plane> discovered{initial};
    std::set<std::pair<int, int>> edges;
    for (std::size_t head = 0; head < queue.size(); ++head) {
        const Plane f = queue[head];
        on.clear();
        for (int i = 0; i < n; ++i) {
            Wide value = side(f, p[i]);
            assert(value <= 0);
            if (value == 0) on.push_back(i);
        }
        int drop = f[0] != 0 ? 0 : (f[1] != 0 ? 1 : 2);
        auto polygon = projected_hull(p, on, drop);
        assert(polygon.size() >= 3);
        if (f[drop] < 0) std::reverse(polygon.begin(), polygon.end());
        result.facets.emplace(f, polygon);
        for (std::size_t i = 1; i + 1 < polygon.size(); ++i) {
            const auto &x = p[polygon[0]], &y = p[polygon[i]], &z = p[polygon[i + 1]];
            Vector vx{Wide(x[0]), Wide(x[1]), Wide(x[2])};
            Vector vy{Wide(y[0]), Wide(y[1]), Wide(y[2])};
            Vector vz{Wide(z[0]), Wide(z[1]), Wide(z[2])};
            result.volume6 += dot(vx, cross(vy, vz));
        }
        for (std::size_t i = 0; i < polygon.size(); ++i) {
            int u = polygon[i], v = polygon[(i + 1) % polygon.size()];
            if (!edges.emplace(std::min(u, v), std::max(u, v)).second) continue;
            Plane adjacent = pivot(v, u);
            if (discovered.insert(adjacent).second) queue.push_back(adjacent);
        }
    }
    assert(result.volume6 > 0);
    return result;
}
