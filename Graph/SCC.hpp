#ifndef __BALU_SCC__
#define __BALU_SCC__
struct SCC { // 0-base
    int n, dft, nscc;
    std::vector<int> low, dfn, bln, instack, stk;
    std::vector<std::vector<int>> G;
    void dfs(int u) {
        low[u] = dfn[u] = ++dft;
        instack[u] = 1, stk.push_back(u);
        for (int v : G[u])
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
    SCC(int _n): n(_n), dft(), nscc(), low(n), dfn(n), bln(n), instack(n), G(n) {}
    void add_edge(int u, int v) {
        G[u].push_back(v);
    }
    void solve() {
        for (int i = 0; i < n; ++i)
            if (!dfn[i]) dfs(i);
    }
}; // scc_id(i): bln[i]
#endif // __BALU_SCC__
