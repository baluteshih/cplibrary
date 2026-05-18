#pragma once

#include "Graph/base.hpp"

// there exists bipolar orientation iff the graph is biconnected after adding the edge (s, t)
template<typename Edge, typename Vertex>
std::vector<int> bipolar_orientation(Graph<false, Edge, Vertex> &G, int s, int t) {
    assert(s != t);
    assert(G.m() > 0);
    int n = G.n();
    assert(0 <= s && s < n);
    assert(0 <= t && t < n);
    G[s].insert(G[s].begin(), std::make_pair(t, -1));
    std::vector<int> vis(n), low(n), pa(n, -1), sgn(n), ord;
    auto dfs = [&](auto self, int u) -> void {
        ord.push_back(u);
        low[u] = vis[u] = ord.size();
        for (auto [v, eid] : G[u])
            if (!vis[v])
                pa[v] = u, self(self, v), low[u] = std::min(low[u], low[v]);
            else
                low[u] = std::min(low[u], vis[v]);
    };
    dfs(dfs, s);
    std::vector<int> nxt(n + 1, n), prv = nxt;
    nxt[s] = t, prv[t] = s, sgn[s] = -1;
    for (int i : ord)
        if (i != s && i != t) {
            int p = pa[i], l = ord[low[i] - 1];
            if (sgn[l] > 0)
                nxt[i] = nxt[prv[i] = p], nxt[p] = prv[nxt[p]] = i;
            else
                prv[i] = prv[nxt[i] = p], prv[p] = nxt[prv[p]] = i;
            sgn[p] = -sgn[l];
        }
    std::vector<int> res;
    for (int x = s; x != n; x = nxt[x]) res.push_back(x);
    G[s].erase(G[s].begin());
    return res;
}
