#pragma once

#include "Tree/Tree.hpp"

template<typename Edge = void, typename Vertex = void>
class HeavyLightDecomposition : public Tree<Edge, Vertex> {
public:
    using super = Tree<Edge, Vertex>;
    HeavyLightDecomposition(int n): super(n) {} 
    HeavyLightDecomposition(const super &tree): super(tree) {}
    std::vector<int> sz, top, dep, tail;
    void build(int root = 0) {
        this->current_root = root;
        std::vector<int>(this->n()).swap(this->pa);
        std::vector<int>(this->n()).swap(this->dfs_in);
        std::vector<int>(this->n()).swap(this->dfs_out);
        std::vector<int>(this->n(), 1).swap(sz);
        std::vector<int>(this->n()).swap(top);
        std::vector<int>(this->n()).swap(dep);
        std::vector<int>(this->n()).swap(tail);
        this->preorder.clear(), this->preorder.reserve(this->n());
        this->postorder.clear(), this->postorder.reserve(this->n());
        auto dfs_sz = [&](auto& self, int u, int f) -> void {
            int max_sub = 0;
            for (int i = 0; i < int(this->G[u].size()); ++i) {
                auto [v, eid] = this->G[u][i];
                if (eid == f) continue;
                self(self, v, eid);
                sz[u] += sz[v];
                if (sz[v] > max_sub) {
                    max_sub = sz[v];
                    std::swap(this->G[u][0], this->G[u][i]); 
                }
            }
        };
        dfs_sz(dfs_sz, root, -1);
        this->traverse(root);
        this->predfs([&](int u) {
            int f = this->parent(u);
            if (u == f || this->opposite(f, this->G[f][0].second) != u)
                top[u] = u;
            else
                top[u] = top[f];
            tail[top[u]] = u;
            if (u != f) dep[u] = dep[f] + 1;
        });
    }
    int lca(int u, int v) const {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) u = this->parent(top[u]);
            else v = this->parent(top[v]);
        }
        return dep[u] < dep[v] ? u : v;
    }
    // func(int l, int r, bool is_up), intervals are [l, r), is_up is true if the interval is towarding to the root
    template <bool is_edge, class F>
    void work_path(int u, int v, F func) const {
        std::vector<std::pair<int, int>> up_path, down_path;
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                up_path.emplace_back(this->dfs_in[top[u]], this->dfs_in[u] + 1);
                u = this->parent(top[u]);
            }
            else {
                down_path.emplace_back(this->dfs_in[top[v]], this->dfs_in[v] + 1);
                v = this->parent(top[v]);
            }
        }
        if (dep[u] < dep[v])
            down_path.emplace_back(this->dfs_in[u] + is_edge, this->dfs_in[v] + 1);
        else if (dep[u] > dep[v] || !is_edge)
            up_path.emplace_back(this->dfs_in[v] + is_edge, this->dfs_in[u] + 1);
        for (auto [l, r] : up_path) func(l, r, true);
        std::reverse(down_path.begin(), down_path.end());
        for (auto [l, r] : down_path) func(l, r, false);
    }
    // func(int l, int r), intervals are [l, r), intervals could be empty
    template <bool is_edge, class F>
    void work_subtree(int u, F func) const {
        func(this->dfs_in[u] + is_edge, this->dfs_out[u] + 1);
    }
};
