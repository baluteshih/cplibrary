#pragma once

#include "Graph/base.hpp"

template<bool circuits = false, bool remove_isolate_vertices = true, typename graph = Graph<true, void, void>>
std::pair<std::vector<int>, std::vector<int>> eulerian_trail(const graph &G) {
    int s = -1, t = -1;
    auto in_degree = G.in_degree();
    if constexpr (G.is_directed) {
        auto out_degree = G.out_degree();
        for (int i = 0; i < G.n(); ++i)
            if (in_degree[i] != out_degree[i]) {
                if (in_degree[i] + 1 == out_degree[i]) {
                    if (s == -1) s = i;
                    else return {};
                }
                else if (in_degree[i] == out_degree[i] + 1) {
                    if (t == -1) t = i;
                    else return {};
                }
                else return {};
            }
    }
    else {
        for (int i = 0; i < G.n(); ++i)
            if (in_degree[i] % 2 != 0) {
                if (s == -1) s = i;
                else if (t == -1) t = i;
                else return {};
            }
    }
    if (int(s == -1) ^ int(t == -1)) return {};
    if constexpr (circuits) if (s != -1) return {};
    std::vector<int> vis(G.n()), vis_edge(G.m()), cur(G.n()), res_v, res_e;
    if (s == -1) {
        s = std::ranges::find_if(in_degree, [&](int d) { return d > 0; }) - in_degree.begin();
        if (s == G.n()) s = 0;
        t = s;
    }
    if constexpr (remove_isolate_vertices)
        for (int i = 0; i < G.n(); ++i)
            if (in_degree[i] == 0 && i != s)
                vis[i] = 1;
    auto dfs = [&](auto self, int u, int f) -> void {
        vis[u] = 1;
        if (f != -1) vis_edge[f] = 1;
        for (int &i = cur[u]; i < int(G[u].size());) {
            auto [v, eid] = G[u][i++];
            if (!vis_edge[eid]) self(self, v, eid); 
        }
        res_v.push_back(u);
        if (f != -1) res_e.push_back(f);
    };
    dfs(dfs, s, -1);
    if (std::ranges::find(vis, 0) != vis.end() || std::ranges::find(vis_edge, 0) != vis_edge.end())
        return {};
    if constexpr (G.is_directed) std::ranges::reverse(res_v), std::ranges::reverse(res_e);
    return {res_v, res_e};
}
