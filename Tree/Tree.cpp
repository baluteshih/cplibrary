#pragma once

#include "Graph/base.hpp"

template<typename Edge = void, typename Vertex = void>
class Tree : public Graph<false, Edge, Vertex> {
    using super = Graph<false, Edge, Vertex>;
    int current_root;
public:
    std::vector<int> pa, dfs_in, dfs_out;
    std::vector<int> preorder, postorder;
    Tree(int n): super(n), current_root(-1) {}
    Tree(const super &graph, const std::vector<int> &edge_index): super(graph.n()), current_root(-1) {
        assert(int(edge_index.size()) + 1 == this->n());
        for (int eid : edge_index)
            this->add_edge(graph.edge(eid));
    }
    void traverse(int root = 0) {
        current_root = root;
        std::vector<int>(this->n()).swap(pa);
        std::vector<int>(this->n()).swap(dfs_in);
        std::vector<int>(this->n()).swap(dfs_out);
        preorder.clear(), preorder.reserve(this->n());
        postorder.clear(), postorder.reserve(this->n());
        int dft = 0;
        auto dfs = [&](auto _dfs, int u, int f) -> void {
            pa[u] = f;
            dfs_in[u] = ++dft;
            preorder.push_back(u);
            for (auto [v, eid] : this->G[u])
                if (eid != f)
                    _dfs(_dfs, v, eid);
            dfs_out[u] = dft;
            postorder.push_back(u);
        };
        dfs(dfs, root, -1);
    }
    bool ancestor(int u, int v) {
        return dfs_in[u] <= dfs_in[v] && dfs_out[v] <= dfs_out[u];
    }
    void run_order(const std::vector<int> &order, const auto &func) {
        for (int i : order)
            func(i, pa[i]);
    }
    void predfs(const auto &func) {
        run_order(preorder, func);
    }
    void postdfs(const auto &func) {
        run_order(postorder, func);
    }
    int parent(int u, int root = 0) {
        if (current_root != root)
            traverse(root);
        if (u == root) return u;
        return this->opposite(u, pa[u]);
    }
    std::vector<int> parents(int root = 0) {
        std::vector<int> res(this->n());
        for (int i = 0; i < this->n(); ++i)
            res[i] = parent(i);
        return res;
    }
    std::vector<int> depth(int root = 0) {
        if (current_root != root)
            traverse(root);
        std::vector<int> res(this->n(), -1);
        predfs([&](int u, int f) {
            res[u] = res[this->opposite(u, f)] + 1;
        });
        return res;
    }
    auto distance_edge(int root = 0) requires (this->hasEdgeWeight) {
        if (current_root != root)
            traverse(root);
        std::vector<Edge> res(this->n());
        predfs([&](int u, int f) {
            if (f != -1)
                res[u] = res[this->opposite(u, f)] + this->edge(f).weight;
        });
        return res;
    }
    std::vector<int> subtree_size(int root = 0) {
        if (current_root != root)
            traverse(root);
        std::vector<int> res(this->n(), 1);
        predfs([&](int u, int f) {
            for (auto [v, eid] : this->G[u])
                if (v != this->opposite(u, f))
                    res[u] += res[v];
        });
        return res;
    }
    std::vector<int> path(int u, int v, int root = 0) {
        if (current_root != root)
            traverse(root);
        std::vector<int> lft, rgt;
        while (!ancestor(v, u)) {
            rgt.push_back(v);
            v = parent(v);
        }
        while (u != v) {
            lft.push_back(u);
            u = parent(u);
        }
        lft.push_back(u);
        lft.insert(lft.end(), rgt.rbegin(), rgt.rend());
        return lft; 
    }
};
