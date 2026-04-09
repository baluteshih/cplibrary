#pragma once

#include "Tree/Tree.hpp"

template<typename Edge = void, typename Vertex = void>
class TreeTools : public Tree<Edge, Vertex> {
public:
    using super = Tree<Edge, Vertex>;
    using super::Tree;
    using super::hasEdgeWeight;
    using super::hasVertexWeight;
    static_assert(!(hasEdgeWeight && hasVertexWeight) || std::is_same_v<Edge, Vertex>, 
                  "Compile Error: Edge and Vertex weights must be the exact same type if both are provided!");
    using WeightType = std::conditional_t<hasEdgeWeight, Edge, Vertex>;
    static constexpr bool hasWeight = !std::is_same_v<WeightType, void>;
    std::vector<int> dep;
    std::vector<std::vector<int>> pa_table;
    struct Empty {};
    [[no_unique_address]] std::conditional_t<hasWeight, std::vector<std::vector<WeightType>>, Empty> data;
    [[no_unique_address]] std::conditional_t<hasWeight, std::vector<std::vector<WeightType>>, Empty> rootpath;
    void build_rootpath(int root = -1) {
        if (this->current_root == -1 || (root != -1 && this->current_root != root)) {
            if (root == -1) root = 0;
            this->traverse(root);
        }
        this->depth().swap(dep);
        if constexpr (hasWeight) {
            this->weighted_distance().swap(rootpath);
        }
    }
    void build_patable(int root = -1) {
        if (this->current_root == -1 || (root != -1 && this->current_root != root)) {
            if (root == -1) root = 0;
            this->traverse(root);
        }
        const int L = std::__lg(this->n()); 
        vector<vector<int>>(L + 1, vector<int>(this->n())).swap(pa_table);
        pa_table[0] = this->parents();
        if constexpr (hasWeight) {
            vector<vector<WeightType>>(L + 1, vector<WeightType>(this->n())).swap(data);
            for (int i = 0; i < this->n(); ++i) {
                if constexpr (this->hasEdgeWeight && this->hasVertexWeight) {
                    data[0][i] = this->weight[i];
                    if (i != root) data[0][i] = this->parent_edge(i).weight + data[0][i]; 
                }
                else if constexpr (this->hasEdgeWeight) {
                    if (i != root) data[0][i] = this->parent_edge(i).weight; 
                }
                else if constexpr (this->hasVertexWeight) {
                    data[0][i] = this->weight[i];
                }
            }
        }
        for (int i = 1; i <= L; ++i)
            for (int j = 0; j < this->n(); ++j) {
                pa_table[i][j] = pa_table[i - 1][pa_table[i - 1][j]];
                if constexpr (hasWeight)
                    data[i][j] = data[i - 1][j] + data[i - 1][pa_table[i - 1][j]];
            }
    }
    int lca(int u, int v) {
        if (this->ancestor(u, v)) return u;
        if (this->ancestor(v, u)) return v;
        int L = __lg(this->n());
        for (int i = L; i >= 0; --i)
            if (!this->ancestor(pa_table[i][u], v))
                u = pa_table[i][u];
        return pa_table[0][u];
    }
    int distance(int u, int v, int _lca = -1) {
        if (dep.empty()) build_rootpath();
        if (_lca == -1) _lca = lca(u, v);
        return dep[u] + dep[v] - dep[_lca] * 2;
    }
    auto weighted_distance(int u, int v, int _lca = -1) requires (hasWeight) {
        if (dep.empty()) build_rootpath();
        if (_lca == -1) _lca = lca(u, v);
        return rootpath[u] + rootpath[v] - rootpath[_lca] * 2;
    }
    int step(int u, int v, int d, int _lca = -1) {
        if (_lca == -1) _lca = lca(u, v);
        if (d > distance(u, v, _lca))
            return -1;
        if (this->ancestor(u, v)) { 
            std::swap(u, v);
            d = distance(u, v, _lca) - d;
        }
        if (this->ancestor(v, u)) {
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
};
