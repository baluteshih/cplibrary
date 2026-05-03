#pragma once

#include "Graph/base.hpp"

template<typename T, typename C = T>
struct CostFlowWeight {
    T cap;
    C cost;
    T flow;
    CostFlowWeight() : cap(0), cost(0), flow(0) {}
    CostFlowWeight(T c, C w, T f = 0) : cap(c), cost(w), flow(f) {}
    friend ostream& operator<<(ostream& os, const CostFlowWeight &v) {
        os << "[" << v.cap << ", " << v.cost << ", " << v.flow << "]";
        return os;
    }
};

template<typename T, typename C = T>
class min_cost_max_flow : public Graph<true, CostFlowWeight<T, C>, void> { // 0-base
public:
    using super = Graph<true, CostFlowWeight<T, C>, void>;
    std::vector<int> past;
    std::vector<C> dis, pot;
    std::vector<T> up;
    template<bool bellmanford = true>
    bool shortest_path(int s, int t) {
        std::vector<int> inq(this->n());
        std::ranges::fill(dis, std::numeric_limits<C>::max());
        std::conditional_t<bellmanford, std::queue<int>, std::priority_queue<std::pair<C, int>, std::vector<std::pair<C, int>>, std::greater<std::pair<C, int>>>> q;
        auto relax = [&](int u, C d, T cap, int eid) {
            if (cap > 0 && dis[u] > d) {
                dis[u] = d, up[u] = cap, past[u] = eid;
                if constexpr (!bellmanford) q.emplace(dis[u], u);
                else if (!inq[u]) inq[u] = 1, q.push(u);
            }
        };
        relax(s, 0, std::numeric_limits<T>::max(), -1);
        while (!q.empty()) {
            C d;
            int u;
            if constexpr (bellmanford) u = q.front();
            else std::tie(d, u) = q.top();
            q.pop();
            if constexpr (bellmanford) inq[u] = 0;
            else if (dis[u] != d) continue;
            for (auto [v, eid] : this->G[u]) {
                auto &w = this->edges[eid].weight;
                C d2 = dis[u] + w.cost + pot[u] - pot[v];
                relax(v, d2, std::min(up[u], w.cap - w.flow), eid);
            }
        }
        return dis[t] != std::numeric_limits<C>::max();
    }
    min_cost_max_flow(int _n) : super(_n), past(_n), dis(_n), pot(_n), up(_n) {} 
    template<bool bellmanford = true, bool neg = true>
    std::pair<T, C> solve(int s, int t) {
        T flow = 0;
        C cost = 0;
        if constexpr (neg) shortest_path<true>(s, t), dis = pot;
        for (; shortest_path<bellmanford>(s, t); dis = pot) {
            for (int i = 0; i < this->n(); ++i) dis[i] += pot[i] - pot[s];
            flow += up[t], cost += dis[t] * up[t];
            for (int i = t; past[i] != -1; i = this->edges[past[i]].from) {
                this->edges[past[i]].weight.flow += up[t];
                this->edges[past[i] ^ 1].weight.flow -= up[t];
            }
        }
        return std::make_pair(flow, cost);
    }
    void add_edge(int a, int b, T cap, C cost) {
        super::add_edge(a, b, CostFlowWeight(cap, cost, T(0)));
        super::add_edge(b, a, CostFlowWeight(T(0), -cost, T(0)));
    }
};
