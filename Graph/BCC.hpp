#pragma once

struct BCC { // 0-base
    int n, dft, nbcc;
    std::vector<int> low, dfn, bln, stk, is_ap, cir;
    std::vector<std::vector<int>> G, bcc, nG;
    void make_bcc(int u) {
        bcc.emplace_back(1, u); 
        for (; stk.back() != u; stk.pop_back())
            bln[stk.back()] = nbcc, bcc[nbcc].push_back(stk.back());
        stk.pop_back(), bln[u] = nbcc++;
    }
    void dfs(int u, int f) {
        int child = 0;
        low[u] = dfn[u] = ++dft, stk.push_back(u);
        for (int v : G[u])
            if (!dfn[v]) {
                dfs(v, u), ++child;
                low[u] = std::min(low[u], low[v]);
                if (dfn[u] <= low[v]) {
                    is_ap[u] = 1, bln[u] = nbcc;
                    make_bcc(v), bcc.back().push_back(u);
                }
            } else if (dfn[v] < dfn[u] && v != f)
                low[u] = std::min(low[u], dfn[v]);
        if (f == -1 && child < 2) is_ap[u] = 0;
        if (f == -1 && child == 0) make_bcc(u);
    }
    BCC(int _n): n(_n), dft(), nbcc(), low(n), dfn(n), bln(n), is_ap(n), G(n) {}
    void add_edge(int u, int v) {
        G[u].push_back(v), G[v].push_back(u);
    }
    void solve() {
        for (int i = 0; i < n; ++i)
            if (!dfn[i]) dfs(i, -1);
    }
    void block_cut_tree() {
        cir.resize(nbcc);
        for (int i = 0; i < n; ++i)
            if (is_ap[i])
                bln[i] = nbcc++;
        cir.resize(nbcc, 1), nG.resize(nbcc);
        for (int i = 0; i < nbcc && !cir[i]; ++i)
            for (int j : bcc[i])
                if (is_ap[j])
                    nG[i].push_back(bln[j]), nG[bln[j]].push_back(i);
    } // up to 2 * n - 2 nodes!! bln[i] for id
};
