#pragma once

class ECC { // 0-base
    int n, dft, ecnt;
    std::vector<int> low, dfn, stk;
    std::vector<std::vector<std::pair<int, int>>> G;
    void dfs(int u, int f) {
        dfn[u] = low[u] = ++dft, stk.push_back(u);
        for (auto [v, e] : G[u])
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
public:
    int necc;
    std::vector<int> bln, is_bridge;
    ECC(int _n): n(_n), dft(), ecnt(), low(n), dfn(n), G(n), necc(), bln(n) {}
    void add_edge(int u, int v) {
        G[u].emplace_back(v, ecnt);
        G[v].emplace_back(u, ecnt++);
    }
    void solve() {
        necc = dft = 0;
        is_bridge.resize(ecnt);
        for (int i = 0; i < n; ++i)
            if (!dfn[i]) dfs(i, -1);
    }
    std::vector<std::vector<int>> components() {
        std::vector<std::vector<int>> res(necc);
        for (int i = 0; i < n; ++i)
            res[bln[i]].push_back(i);
        return res;
    }
}; // ecc_id(i): bln[i]
