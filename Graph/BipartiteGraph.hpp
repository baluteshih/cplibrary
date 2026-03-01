#pragma once

#include "Graph/base.hpp"

template<typename Edge = void, typename Vertex = void>
class BipartiteGraph : public Graph<true, Edge, Vertex> {
    using super = Graph<true, Edge, Vertex>;
protected:
    int rsize;
public:
    BipartiteGraph(int _l, int _r) : super(_l), rsize(_r) {} 
    int l() const { return this->G.size(); }
    int r() const { return rsize; }
    std::vector<int> out_degree() override {
        std::vector<int> res(rsize);
        for (auto &e : this->edges)
            ++res[e.from];
        return res;
    }
    BipartiteGraph reversed() {
        Graph res(rsize, this->n());
        for (auto &e : this->edges) {
            if constexpr (super::hasEdgeWeight) res.add_edge(e.to, e.from, e.weight);
            else res.add_edge(e.to, e.from);
        }
        if constexpr (super::hasVertexWeight) res.set_vertex_weight(this->weight);
        return res;
    }
    /*
    return a pair of (color, BipartiteGraph),
    where u on the left of the BipartiteGraph iff color[u] == 0
    the new numbering of u will be the count of the number of same color nodes on its left
    */
    static std::optional<std::pair<std::vector<int>, BipartiteGraph>> to_bipartite(Graph<false, Edge, Vertex> &graph) {
        std::vector<int> color(graph.n(), -1), numbering(graph.n());
        auto dfs = [&](auto self, int u, int c) -> bool {
            color[u] = c;
            for (auto [v, eid] : graph.adj(u))
                if (color[v] == -1 && !self(self, v, c ^ 1))
                    return false;
                else if (color[v] == color[u])
                    return false;
            return true;
        };
        int cnt[2] = {};
        for (int i = 0; i < graph.n(); ++i) {
            if (color[i] == -1 && !dfs(dfs, i, 0))
                return std::nullopt; 
            numbering[i] = cnt[color[i]]++;
        }
        BipartiteGraph res(cnt[0], cnt[1]);
        for (int i = 0; i < graph.m(); ++i) {
            const auto &e = graph.edge(i);
            int u = e.from;
            int v = e.to;
            if (color[u] == 1) std::swap(u, v);
            u = numbering[u], v = numbering[v];
            if constexpr (super::hasEdgeWeight) res.add_edge(u, v, e.weight);
            else res.add_edge(u, v);
        }
        if constexpr (super::hasVertexWeight) res.set_vertex_weight(graph.vertex_weight());
        return res;
    }
};
