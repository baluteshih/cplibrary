#pragma once

#include "Graph/eulerian_trail.hpp"
#include "Graph/count_spanning_tree.hpp"

template<typename T, typename graph>
T count_eulerian_circuits(const graph &G) {
    auto [vertices, edges] = eulerian_trail<true>(G);
    if (vertices.empty()) return T(0);
    std::ranges::sort(vertices);
    vertices.erase(std::ranges::unique(vertices).begin(), vertices.end());
    auto in_degree = G.in_degree();
    int mx = *std::ranges::max_element(in_degree);
    std::vector<T> fac(mx, 1);
    for (int i = 2; i < mx; ++i) fac[i] = fac[i - 1] * i;
    T ans = 1;
    for (int i = 0; i < G.n(); ++i)
        if (in_degree[i] > 0)
            ans *= fac[in_degree[i] - 1];
    ans *= count_spanning_tree<T>(G.induced(vertices));
    return ans;
}
