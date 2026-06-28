#pragma once

#include "Graph/base.hpp"

// parent[u] is the bfs parent of u, parent[root] = root
template<typename graph>
std::vector<int> complement_bfs(const graph &G, int start = -1) {
    std::vector<int> vis(G.n()), cur(G.n()), parent(G.n());
    int vcnt = 0;
    std::iota(cur.begin(), cur.end(), 0);
    if (start != -1) std::swap(cur[start], cur.back());
    while (!cur.empty()) {
        std::queue<int> q;
        parent[cur.back()] = cur.back();
        q.push(cur.back());
        cur.pop_back();
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ++vcnt;
            for (auto [v, eid] : G[u])
                vis[v] = vcnt;
            std::vector<int> nxt;
            for (int i : cur)
                if (vis[i] == vcnt) nxt.push_back(i);
                else q.push(i), parent[i] = u;
            cur.swap(nxt);
        }
    }
    return parent;
}
