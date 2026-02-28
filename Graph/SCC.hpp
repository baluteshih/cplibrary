#pragma once

#include "Graph/base.hpp"

template<typename Edge = void, typename Vertex = void>
struct SCC : public Graph<true, Edge, Vertex>  { // 0-base
    using super = Graph<true, Edge, Vertex>;
    int dft, nscc;
    std::vector<int> low, dfn, bln, instack, stk;
    void dfs(int u) {
        low[u] = dfn[u] = ++dft;
        instack[u] = 1, stk.push_back(u);
        for (auto [v, eid] : this->G[u])
            if (!dfn[v])
                dfs(v), low[u] = std::min(low[u], low[v]);
            else if (instack[v] && dfn[v] < dfn[u])
                low[u] = std::min(low[u], dfn[v]);
        if (low[u] == dfn[u]) {
            for (; stk.back() != u; stk.pop_back())
                bln[stk.back()] = nscc, instack[stk.back()] = 0;
            instack[u] = 0, bln[u] = nscc++, stk.pop_back();
        }
    }
    SCC(int n): super(n), dft(), nscc(), low(n), dfn(n), bln(n), instack(n) {}
    void solve() {
        for (int i = 0; i < this->n(); ++i)
            if (!dfn[i]) dfs(i);
    }
    std::vector<std::vector<int>> components() {
        std::vector<std::vector<int>> res(nscc);
        for (int i = 0; i < this->n(); ++i)
            res[bln[i]].push_back(i);
        std::ranges::reverse(res);
        return res;
    }
}; // scc_id(i): bln[i]
