#pragma once

template<bool directed = true, typename Edge = void, typename Vertex = void>
class Graph {
protected:
    static constexpr bool hasEdgeWeight = !std::is_same_v<Edge, void>;
    static constexpr bool hasVertexWeight = !std::is_same_v<Vertex, void>;
    struct Empty {};
    struct edge {
        int from, to;
        [[no_unique_address]] std::conditional_t<hasEdgeWeight, Edge, Empty> weight;
        edge() {}
        edge(int u, int v) : from(u), to(v) {}
        edge(int u, int v, const auto &w) requires(hasEdgeWeight) : from(u), to(v), weight(w) {}
    };
    std::vector<std::vector<std::pair<int, int>>> G;
    std::vector<edge> edges;
    [[no_unique_address]] std::conditional_t<hasVertexWeight, std::vector<Vertex>, Empty> weight;
public:
    Graph(int _n) : G(_n) {
        if constexpr (hasVertexWeight) weight.resize(_n);
    }
    int n() const { return G.size(); }
    int m() const { return edges.size(); }
    auto& edge(int idx) requires (hasEdgeWeight) {
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
    void add_edge(int u, int v) {
        G[u].emplace_back(v, edges.size());
        if constexpr (!directed) G[v].emplace_back(u, edges.size());
        edges.emplace_back(u, v);
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
    Graph reversed() {
        Graph res(n());
        for (auto &e : edges) {
            if constexpr (hasEdgeWeight) res.add_edge(e.to, e.from, e.weight);
            else res.add_edge(e.to, e.from);
        }
        if constexpr (hasVertexWeight) res.set_vertex_weight(weight);
        return res;
    }
};
