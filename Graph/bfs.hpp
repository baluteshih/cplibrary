#pragma once

#include "Graph/base.hpp"

// return (dis[u], parent[u])
// parent[u] is the bfs parent of u, parent[root] = root
// if not reachable from root, dis[u] = parent[u] = -1
template<typename graph>
std::pair<std::vector<int>, std::vector<int>> bfs(const graph &G, int root) {
    std::vector<int> parent(G.n(), -1), dis(G.n(), -1);
    std::queue<int> q;
    auto relax = [&](int u, int d, int f) {
        if (dis[u] == -1) {
            dis[u] = d;
            parent[u] = f;
            q.push(u);
        }
    };
    relax(root, 0, root);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, eid] : G[u])
            relax(v, dis[u] + 1, u);
    }
    return std::make_pair(dis, parent);
}
