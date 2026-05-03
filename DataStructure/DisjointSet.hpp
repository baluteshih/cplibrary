#pragma once

template<typename T = void, bool undo_tag = false>
class DisjointSet {
protected:
    static constexpr bool hasT = !std::is_same_v<T, void>;
    int n;
    std::vector<int> boss, sz;
    struct Empty {};
    [[no_unique_address]] std::conditional_t<hasT, std::vector<T>, Empty> data;
    [[no_unique_address]] std::conditional_t<undo_tag, std::vector<std::pair<int*, int>>, Empty> cache;
    [[no_unique_address]] std::conditional_t<undo_tag && hasT, std::vector<std::pair<T*, T>>, Empty> data_cache;
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
        if constexpr (undo_tag) return leader(boss[u]);
        else return boss[u] = leader(boss[u]);
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
        if constexpr (undo_tag) {
            cache.emplace_back(&boss[v], boss[v]); 
            cache.emplace_back(&sz[u], sz[v]); 
            if constexpr (hasT)
                data_cache.emplace_back(&data[u], data[u]);
        }
        boss[v] = u;
        sz[u] += sz[v];
        if constexpr (hasT) {
            data[u] = data[u] + data[v]; 
        }
        return true;
    }
    size_t version() requires (undo_tag && !hasT) {
        return cache.size();
    }
    std::pair<size_t, size_t> version() requires (undo_tag && hasT) {
        return std::make_pair(cache.size(), data_cache.size());
    }
    void undo(auto req_version) requires (undo_tag) {
        while (version() != req_version) {
            if constexpr (!hasT) {
                *cache.back().first = cache.back().second;
                cache.pop_back();
            }
            else {
                if (cache.size() > req_version.first) {
                    *cache.back().first = cache.back().second;
                    cache.pop_back();
                }
                else {
                    *data_cache.back().first = data_cache.back().second;
                    data_cache.pop_back();
                }
            }
        }
    }
    auto& getdata(int u) requires (hasT) {
        return data[leader(u)];
    }
    void data_transform(int u, auto func) requires (hasT) {
        auto &cur = getdata(u);
        if constexpr (undo_tag)
            data_cache.emplace_back(&cur, cur);
        func(cur);
    }
    std::vector<std::vector<int>> groups() {
        std::vector<std::vector<int>> result(n);
        for (int i = 0; i < n; ++i)
            result[leader(i)].push_back(i);
        result.erase(remove_if(result.begin(), result.end(), [](auto &g) { return g.empty(); }), result.end());
        return result;
    }
};
