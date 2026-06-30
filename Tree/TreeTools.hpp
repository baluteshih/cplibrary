#pragma once

#include "Tree/Tree.hpp"
#include "DataStructure/Doubling.hpp"
#include "Algebra/ValidOperation.hpp"

template<typename Edge = void, typename Vertex = void>
class TreeTools : public Tree<Edge, Vertex> {
public:
    using super = Tree<Edge, Vertex>;
    using super::Tree;
    using super::hasEdgeWeight;
    using super::hasVertexWeight;
    using typename super::WeightType;
    static constexpr bool hasWeight = !std::is_same_v<WeightType, void>;
    static constexpr bool hasAddition = ((!hasEdgeWeight || !hasVertexWeight) && Addable<WeightType, WeightType>) || 
                                        ((hasEdgeWeight && hasVertexWeight) && Addable<Vertex, Edge>); 
    static constexpr bool hasSubtract = Subtractable<WeightType, WeightType>; 
    std::vector<int> dep;
    Doubling<std::conditional_t<hasAddition, WeightType, void>, false> pa_table;
    struct Empty {};
    [[no_unique_address]] std::conditional_t<hasWeight, std::vector<std::vector<WeightType>>, Empty> data;
    [[no_unique_address]] std::conditional_t<hasWeight, std::vector<std::vector<WeightType>>, Empty> rootpath;
    void build_rootpath(int root = -1) {
        if (this->current_root == -1 || (root != -1 && this->current_root != root)) {
            if (root == -1) root = 0;
            this->traverse(root);
        }
        this->depth().swap(dep);
        if constexpr (hasAddition) {
            this->weighted_distance().swap(rootpath);
        }
    }
    void build_patable(int root = -1) {
        if (this->current_root == -1 || (root != -1 && this->current_root != root)) {
            if (root == -1) root = 0;
            this->traverse(root);
        }
        if constexpr (hasAddition) pa_table = decltype(pa_table)(this->n(), this->parents(), std::views::iota(0, this->n()) | std::views::transform([&](int i) {
            WeightType res = WeightType();
            if constexpr (this->hasEdgeWeight && this->hasVertexWeight) {
                res = this->weight[i];
                if (i != root) res = res + this->parent_edge(i).weight;
            }
            else if constexpr (this->hasEdgeWeight) {
                if (i != root) res = this->parent_edge(i).weight; 
            }
            else if constexpr (this->hasVertexWeight) {
                res = this->weight[i];
            }
            return res;
        }));
        else pa_table = decltype(pa_table)(this->n(), this->parents()); 
    }
    int lca(int u, int v) {
        if (this->ancestor(u, v)) return u;
        if (this->ancestor(v, u)) return v;
        u = pa_table.maximal_prefix(u, [&](int x) { return !this->ancestor(x, v); });
        return pa_table.nxt[0][u];
    }
    // be aware of difference in reverse direction edges, this function only support this when v is an ancestor of u
    WeightType path_weight(int u, int v) requires (hasAddition) {
        assert(pa_table.n > 0);
        WeightType res = WeightType();
        if (!this->ancestor(u, v)) {
            std::tie(res, u) = pa_table.maximal_prefix_prod(u, [&](int x) { return !this->ancestor(x, v); });
            res = res + pa_table.val[0][u];
            u = pa_table.nxt[0][u];
        }
        if constexpr (hasVertexWeight) res = res + this->weight[u];
        if (!this->ancestor(v, u)) {
            auto [oppo, _v] = pa_table.maximal_prefix_prod(v, [&](int x) { return !this->ancestor(x, u); });
            res = res + oppo + pa_table.val[0][_v];
        }
        return res;
    }
    int distance(int u, int v, int _lca = -1) {
        if (dep.empty()) build_rootpath();
        if (_lca == -1) _lca = lca(u, v);
        return dep[u] + dep[v] - dep[_lca] * 2;
    }
    auto weighted_distance(int u, int v, int _lca = -1) requires (hasAddition && hasSubtract) {
        if (dep.empty()) build_rootpath();
        if (_lca == -1) _lca = lca(u, v);
        WeightType res = rootpath[u] + rootpath[v] - rootpath[_lca] - rootpath[_lca];
        if constexpr (hasVertexWeight) res = res + this->weight[_lca];
        return res;
    }
    int step(int u, int v, int d, int _lca = -1) {
        if (_lca == -1) _lca = lca(u, v);
        if (d > distance(u, v, _lca))
            return -1;
        if (this->ancestor(u, v)) { 
            std::swap(u, v);
            d = distance(u, v, _lca) - d;
        }
        if (this->ancestor(v, u)) return pa_table.step(u, d);
        if (d <= distance(u, _lca, _lca))
            return step(u, _lca, d, _lca);
        d -= distance(u, _lca, _lca);
        return step(v, _lca, distance(v, _lca, _lca) - d, _lca);
    }
};
