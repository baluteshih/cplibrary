#ifndef __BALU_TREE__
#define __BALU_TREE__
struct Tree {
    int n;
    vector<vector<int>> G;
public:
    vector<int> pa, dep, dfs_in, dfs_out;
    vector<vector<int>> pa_table;
    Tree(int _n): n(_n), G(n) {}
    void traverse(int root = 0) {
        vector<int>(n).swap(pa);
        vector<int>(n).swap(dep);
        vector<int>(n).swap(dfs_in);
        vector<int>(n).swap(dfs_out);
        int dft = 0;
        auto dfs = [&](auto _dfs, int u, int f) -> void {
            pa[u] = f;
            dfs_in[u] = ++dft;
            dep[u] = dep[f] + 1;
            for (int i : G[u])
                if (i != f)
                    _dfs(_dfs, i, u);
            dfs_out[u] = dft;
        };
        dep[root] = -1;
        dfs(dfs, root, root);
    }
    bool ancestor(int u, int v) {
        return dfs_in[u] <= dfs_in[v] && dfs_out[v] <= dfs_out[u];
    }
    void build_patable() {
        int L = __lg(n);
        vector<vector<int>>(L + 1, vector<int>(n)).swap(pa_table);
        pa_table[0] = pa;
        for (int i = 1; i <= L; ++i)
            for (int j = 0; j < n; ++j)
                pa_table[i][j] = pa_table[i - 1][pa_table[i - 1][j]];
    }
    int lca(int u, int v) {
        if (ancestor(u, v)) return u;
        if (ancestor(v, u)) return v;
        int L = __lg(n);
        for (int i = L; i >= 0; --i)
            if (!ancestor(pa_table[i][u], v))
                u = pa_table[i][u];
        return pa_table[0][u];
    }
    int distance(int u, int v, int _lca = -1) {
        if (_lca == -1) _lca = lca(u, v);
        return dep[u] + dep[v] - 2 * dep[_lca];
    }
    int step(int u, int v, int d, int _lca = -1) {
        if (_lca == -1) _lca = lca(u, v);
        if (d > distance(u, v, _lca))
            return -1;
        if (ancestor(u, v)) { 
            swap(u, v);
            d = distance(u, v, _lca) - d;
        }
        if (ancestor(v, u)) {
            for (int i = 0; d; d >>= 1, ++i)
                if (d & 1)
                    u = pa_table[i][u];
            return u;
        }
        if (d <= distance(u, _lca, _lca))
            return step(u, _lca, d, _lca);
        d -= distance(u, _lca, _lca);
        return step(v, _lca, distance(v, _lca, _lca) - d, _lca);
    }
    vector<int> &adj(int u) {
        return G[u];
    }
    void add_edge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }
};
#endif // __BALU_TREE__
