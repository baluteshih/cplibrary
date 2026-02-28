#pragma once

#include "Graph/base.hpp"

template<typename Edge = void, typename Vertex = void>
struct ECC : public Graph<false, Edge, Vertex> { // 0-base
    using super = Graph<false, Edge, Vertex>;
    int dft;
    std::vector<int> low, dfn, stk;
    void dfs(int u, int f) {
        dfn[u] = low[u] = ++dft, stk.push_back(u);
        for (auto [v, e] : this->G[u])
            if (!dfn[v])
                dfs(v, e), low[u] = std::min(low[u], low[v]);
            else if (e != f)
                low[u] = std::min(low[u], dfn[v]);
        if (low[u] == dfn[u]) {
            if (f != -1) is_bridge[f] = 1;
            for (; stk.back() != u; stk.pop_back())
                bln[stk.back()] = necc;
            bln[u] = necc++, stk.pop_back();
        }
    }
    int necc;
    std::vector<int> bln, is_bridge;
    ECC(int n): super(n), dft(), low(n), dfn(n), necc(), bln(n) {}
    void solve() {
        necc = dft = 0;
        is_bridge.resize(this->edges.size());
        for (int i = 0; i < this->n(); ++i)
            if (!dfn[i]) dfs(i, -1);
    }
    std::vector<std::vector<int>> components() {
        std::vector<std::vector<int>> res(necc);
        for (int i = 0; i < this->n(); ++i)
            res[bln[i]].push_back(i);
        return res;
    }
}; // ecc_id(i): bln[i]
