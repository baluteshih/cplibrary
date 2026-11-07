#pragma once

#include "Graph/base.hpp"

// return (dis[u], parent[u])
// parent[u] is the bfs parent of u, parent[root] = root
// if not reachable from root, dis[u] = parent[u] = -1
template<typename graph>
std::pair<std::vector<int>, std::vector<int>> bfs01(const graph &G, int root) {
    assert(0 <= root && root < G.n());
    std::vector<int> parent(G.n(), -1), dis(G.n(), -1);
    std::deque<std::pair<int, int>> q;
    dis[root] = 0, parent[root] = root;
    q.emplace_front(root, 0);
    while (!q.empty()) {
        auto [u, d] = q.front();
        q.pop_front();
        if (d != dis[u]) continue;
        for (auto [v, eid] : G[u]) {
            auto w = G.edge(eid).weight;
            int nd = d + int(w);
            if (dis[v] != -1 && dis[v] <= nd) continue;
            dis[v] = nd;
            parent[v] = u;
            if (w == 0) q.emplace_front(v, nd);
            else q.emplace_back(v, nd);
        }
    }
    return {dis, parent};
}
