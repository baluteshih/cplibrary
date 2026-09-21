#pragma once

template<typename W>
struct edge_data {
    int from, to;
    W weight;
    edge_data() = default;
    edge_data(int u, int v, const W &w) : from(u), to(v), weight(w) {}
};
template<>
struct edge_data<void> { 
    int from, to; 
    edge_data() = default;
    edge_data(int u, int v) : from(u), to(v) {}
};

template<bool directed = true, typename Edge = void, typename Vertex = void>
class Graph {
public:
    static constexpr bool is_directed = directed;
    static constexpr bool hasEdgeWeight = !std::is_same_v<Edge, void>;
    static constexpr bool hasVertexWeight = !std::is_same_v<Vertex, void>;
    static constexpr bool hasEdgeWeightReverse = requires(Edge v) { v.reverse(); };
    using edge_value_type = Edge;
    using vertex_value_type = Vertex;
    struct Empty {};
    struct edge_v : public edge_data<Edge> {
        using edge_data<Edge>::edge_data;
        template <typename OtherEdge>
        edge_v(const OtherEdge &other) requires(hasEdgeWeight && requires(OtherEdge o) { o.weight; })
            : edge_data<Edge>(other.from, other.to, other.weight) {}
        template <typename OtherEdge>
        edge_v(const OtherEdge &other) requires(!hasEdgeWeight || !requires(OtherEdge o) { o.weight; })
            : edge_data<Edge>(other.from, other.to) {}
        edge_v reversed() const {
            edge_v res(*this);
            std::swap(res.from, res.to);
            if constexpr (hasEdgeWeightReverse) res.weight.reverse();
            return res;
        }
        friend std::ostream& operator<<(std::ostream& os, const edge_v &v) {
            os << "(" << v.from << "->" << v.to;
            if constexpr (hasEdgeWeight) os << ", " << v.weight;
            os << ")";
            return os;
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
    const auto& edge(int idx) const {
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
    void pop_edge() {
        G[edges.back().from].pop_back();
        if constexpr (!directed) G[edges.back().to].pop_back();
        edges.pop_back();
    }
    std::vector<int> in_degree() const {
        std::vector<int> res(n());
        for (auto &e : edges) {
            if constexpr (!is_directed) ++res[e.from];
            ++res[e.to];
        }
        return res;
    }
    virtual std::vector<int> out_degree() const {
        std::vector<int> res(n());
        for (auto &e : edges) {
            if constexpr (!is_directed) ++res[e.to];
            ++res[e.from];
        }
        return res;
    }
    std::vector<std::pair<int, int>>& operator[](int idx) {
        return G[idx];
    }
    const std::vector<std::pair<int, int>>& operator[](int idx) const {
        return G[idx];
    }
    Graph reversed() const {
        Graph res(n());
        for (auto &e : edges)
            res.add_edge(e.reversed());
        if constexpr (hasVertexWeight) res.set_vertex_weight(weight);
        return res;
    }
    std::pair<std::vector<int>, std::vector<int>> cycle() const {
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
    Graph induced(const std::vector<int> &subset) const {
        std::vector<int> idx(n(), -1);
        for (int cnt = 0; int i : subset) idx[i] = cnt++;
        Graph res(subset.size());
        for (auto e : edges) {
            e.from = idx[e.from], e.to = idx[e.to];
            if (e.to == -1 || e.from == -1) continue;
            res.add_edge(e);
        }
        return res;
    }
    std::vector<int> reachable(int s) const {
        std::vector<int> res, vis(n());
        auto dfs = [&](auto self, int u) -> void {
            vis[u] = 1;
            for (auto [v, eid] : G[u])
                if (!vis[v])
                    self(self, v);
            res.push_back(u);
        };
        dfs(dfs, s);
        return res;
    }
};

template<typename Edge = void, typename Vertex = void>
class UndirectedGraph : public Graph<false, Edge, Vertex> {
public:
    using Graph<false, Edge, Vertex>::Graph;
    std::vector<std::vector<int>> components() {
        std::vector<std::vector<int>> res;
        std::vector<bool> vis(this->n());
        auto dfs = [&](auto self, int u) -> void {
            vis[u] = true;
            res.back().push_back(u);
            for (auto [v, eid] : this->G[u])
                if (!vis[v])
                    self(self, v);
        };
        for (int i = 0; i < this->n(); ++i) {
            if (vis[i]) continue;
            res.emplace_back();
            dfs(dfs, i);
        }
        return res;
    }
    bool is_connected() {
        return components().size() == 1;
    }
};
