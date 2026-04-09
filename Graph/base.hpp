#pragma once

template<bool directed = true, typename Edge = void, typename Vertex = void>
class Graph {
public:
    static constexpr bool hasEdgeWeight = !std::is_same_v<Edge, void>;
    static constexpr bool hasVertexWeight = !std::is_same_v<Vertex, void>;
    struct Empty {};
    struct edge_v {
        int from, to;
        [[no_unique_address]] std::conditional_t<hasEdgeWeight, Edge, Empty> weight;
        edge_v() {}
        edge_v(int u, int v) : from(u), to(v) {}
        template <typename W>
        edge_v(int u, int v, const W &w) requires(hasEdgeWeight) : from(u), to(v), weight(w) {}
        template <typename OtherEdge>
        edge_v(const OtherEdge &other) requires(hasEdgeWeight && requires(OtherEdge o) { o.weight; }) 
            : from(other.from), to(other.to), weight(other.weight) {}
        template <typename OtherEdge>
        edge_v(const OtherEdge &other) requires(!hasEdgeWeight || !requires(OtherEdge o) { o.weight; }) 
            : from(other.from), to(other.to) {} 
        edge_v reversed() const {
            edge_v res(*this);
            std::swap(res.from, res.to);
            return res;
        }
    };
    std::vector<std::vector<std::pair<int, int>>> G;
    std::vector<edge_v> edges;
    [[no_unique_address]] std::conditional_t<hasVertexWeight, std::vector<Vertex>, Empty> weight;
    Graph(int _n) : G(_n) {
        if constexpr (hasVertexWeight) weight.resize(_n);
    }
    int n() const { return G.size(); }
    int m() const { return edges.size(); }
    int opposite(int u, int eid) const { return edges[eid].from ^ edges[eid].to ^ u; }
    auto& edge(int idx) {
        return edges[idx]; 
    }
    auto &vertex(int idx) requires (hasVertexWeight) {
        return weight[idx];
    }
    const auto& edge(int idx) const requires (hasEdgeWeight) {
        return edges[idx]; 
    }
    const auto &vertex(int idx) const requires (hasVertexWeight) {
        return weight[idx];
    }
    auto &vertex_weight() requires (hasVertexWeight) {
        return weight;
    }
    const auto &vertex_weight() const requires (hasVertexWeight) {
        return weight;
    }
    void set_vertex_weight(const auto &vec) {
        for (int i = 0; i < n(); ++i)
            weight[i] = vec[i];
    }
    void add_edge(int u, int v, const auto &w) requires (hasEdgeWeight) {
        G[u].emplace_back(v, edges.size());
        if constexpr (!directed) G[v].emplace_back(u, edges.size());
        edges.emplace_back(u, v, w);
    }
    void add_edge(int u, int v) requires (!hasEdgeWeight) {
        G[u].emplace_back(v, edges.size());
        if constexpr (!directed) G[v].emplace_back(u, edges.size());
        edges.emplace_back(u, v);
    }
    void add_edge(const edge_v &e) {
        G[e.from].emplace_back(e.to, edges.size());
        if constexpr (!directed) G[e.to].emplace_back(e.from, edges.size());
        edges.emplace_back(e);
    }
    std::vector<int> in_degree() {
        std::vector<int> res(n());
        for (auto &e : edges)
            ++res[e.to];
        return res;
    }
    virtual std::vector<int> out_degree() {
        std::vector<int> res(n());
        for (auto &e : edges)
            ++res[e.from];
        return res;
    }
    std::vector<std::pair<int, int>>& adj(int idx) {
        return G[idx];
    }
    const std::vector<std::pair<int, int>>& adj(int idx) const {
        return G[idx];
    }
    Graph reversed() const {
        Graph res(n());
        for (auto &e : edges)
            res.add_edge(e.reversed());
        if constexpr (hasVertexWeight) res.set_vertex_weight(weight);
        return res;
    }
    std::pair<std::vector<int>, std::vector<int>> cycle() {
        std::vector<int> vis(this->n());
        std::vector<int> res_v, res_e;
        int cyc_end = -1;
        auto dfs = [&](auto self, int u, int f) -> int {
            vis[u] = 1;
            for (auto [v, eid] : G[u]) {
                if (eid == f || vis[v] == 2) continue;
                if (vis[v] == 1) {
                    res_v.push_back(u);
                    res_e.push_back(eid);
                    cyc_end = v;
                    return 1;
                }
                int rt = self(self, v, eid);
                if (rt) {
                    if (rt == 1) { 
                        res_e.push_back(eid);
                        res_v.push_back(u);
                    }
                    if (cyc_end == u) rt = 2;
                    return rt;
                }
            }
            vis[u] = 2;
            return 0;
        };
        for (int i = 0; i < this->n(); ++i)
            if (!vis[i] && dfs(dfs, i, -1))
                break;
        std::ranges::reverse(res_v);
        std::ranges::reverse(res_e);
        return std::make_pair(res_v, res_e);
    }
    Graph<true, Edge, Vertex> oriented(const std::vector<int> &rk) const requires (!directed) {
        Graph<true, Edge, Vertex> res(this->n());
        for (auto &e : edges)
            if (rk[e.from] < rk[e.to])
                res.add_edge(e);
            else
                res.add_edge(e.reversed());
        return res;
    }
};

template<typename Edge = void, typename Vertex = void>
class UndirectedGraph : public Graph<false, Edge, Vertex> {
public:
    using Graph<false, Edge, Vertex>::Graph;
};
