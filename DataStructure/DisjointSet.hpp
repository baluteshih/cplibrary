#ifndef __BALU_DISJOINT_SET__
#define __BALU_DISJOINT_SET__
template<typename T = void>
class DisjointSet {
protected:
    static constexpr bool hasT = !std::is_same_v<T, void>;
    int n;
    std::vector<int> boss, sz;
    struct Empty {};
    [[no_unique_address]] std::conditional_t<hasT, std::vector<T>, Empty> data;
public:
    DisjointSet(int n_): n(n_), boss(n), sz(n, 1) {
        std::iota(boss.begin(), boss.end(), 0);
        if constexpr (hasT) data.resize(n);
    }
    DisjointSet(const std::vector<T> &data_) requires (hasT) : n(data_.size()), boss(n), sz(n, 1), data(data_) {
        std::iota(boss.begin(), boss.end(), 0);
    }
    virtual int leader(int u) {
        if (boss[u] == u) return u;
        return boss[u] = leader(boss[u]);
    }
    int size(int u) {
        return sz[leader(u)];
    }
    bool same(int u, int v) {
        return leader(u) == leader(v);
    }
    bool merge(int u, int v, bool force = false) {
        u = leader(u), v = leader(v);
        if (u == v) return false;
        if (sz[u] < sz[v] && !force) std::swap(u, v);
        boss[v] = u;
        sz[u] += sz[v];
        if constexpr (hasT) {
            data[u] = data[u] + data[v]; 
        }
        return true;
    }
    auto& getdata(int u) requires (hasT) {
        return data[leader(u)];
    }
    std::vector<std::vector<int>> groups() {
        std::vector<std::vector<int>> result(n);
        for (int i = 0; i < n; ++i)
            result[leader(i)].push_back(i);
        result.erase(remove_if(result.begin(), result.end(), [](auto &g) { return g.empty(); }), result.end());
        return result;
    }
};
#endif // __BALU_DISJOINT_SET__
