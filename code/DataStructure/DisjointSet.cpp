#ifndef __BALU_DISJOINT_SET__
#define __BALU_DISJOINT_SET__
class DisjointSet {
    int n;
    vector<int> boss, sz;
public:
    DisjoinSet(int _n): n(_n), boss(n), sz(n, 1) {
        iota(boss.begin(), boss.end(), 0);
    }
    int leader(int u) {
        if (boss[u] == u) return u;
        return boss[u] = leader(boss[u]);
    }
    int size(int u) {
        return sz[leader(u)];
    }
    bool same(int u, int v) {
        return leader(u) == leader(v);
    }
    bool merge(int u, int v) {
        u = leader(u), v = leader(v);
        if (u == v) return false;
        if (sz[u] > sz[v]) swap(u, v);
        boss[u] = v;
        sz[v] += sz[u];
        return true;
    }
    vector<vector<int>> groups() {
        vector<vector<int>> result(n);
        for (int i = 0; i < n; ++i)
            result[leader(i)].push_back(i);
        result.erase(remove_if(result.begin(), result.end(), [](auto &g) { return g.empty(); }), result.end());
        return result;
    }
};
#endif // __BALU_DISJOINT_SET__
