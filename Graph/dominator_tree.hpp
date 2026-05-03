#pragma once

#include "Graph/base.hpp"

template<typename Edge = void, typename Vertex = void>
std::vector<int> dominator_tree(const Graph<true, Edge, Vertex> &G, int root) {
    int n = G.n();
    auto rG = G.reversed();
    std::vector<std::vector<int>> tree(n);
    int Time;
    std::vector<int> pa(n), dfn(n, -1), id(n), semi(n), idom(n), best(n);
    auto dfs = [&](auto self, int u) -> void {
        id[dfn[u] = Time++] = u;
        for (auto [v, eid] : G.adj(u))
            if (dfn[v] == -1)
                self(self, v), pa[dfn[v]] = dfn[u];
    };
    auto find = [&](auto self, int y, int x) -> int {
        if (y <= x) return y;
        int tmp = self(self, pa[y], x);
        if (semi[best[y]] > semi[best[pa[y]]])
            best[y] = best[pa[y]];
        return pa[y] = tmp;
    };
    Time = 0;
    std::iota(best.begin(), best.end(), 0);
    std::iota(semi.begin(), semi.end(), 0);
    dfs(dfs, root);
    for (int i = Time - 1; i > 0; --i) {
        int u = id[i];
        for (auto [v, eid] : rG.adj(u))
            if ((v = dfn[v]) != -1) {
                find(find, v, i);
                semi[i] = std::min(semi[i], semi[best[v]]);
            }
        tree[semi[i]].push_back(i);
        for (auto v : tree[pa[i]]) {
            find(find, v, pa[i]);
            idom[v] = semi[best[v]] == pa[i] ? pa[i] : best[v];
        }
        tree[pa[i]].clear();
    }
    for (int i = 1; i < Time; ++i) {
        if (idom[i] != semi[i]) idom[i] = idom[idom[i]];
        tree[id[idom[i]]].push_back(id[i]);
    }
    std::vector<int> res(n, -1);
    for (int i = 0; i < n; ++i)
        for (int j : tree[i])
            res[j] = i;
    res[root] = root;
    return res;
}
