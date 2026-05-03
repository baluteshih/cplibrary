#pragma once

#include "Graph/base.hpp"

template<typename T, typename C = T>
struct CostCirculationFlowWeight {
    T fcap;
    C cost;
    T cap, flow;
    CostCirculationFlowWeight() : cap(0), fcap(0), cost(0), flow(0) {}
    CostCirculationFlowWeight(T c, C w, T cc = 0, T f = 0) : fcap(c), cost(w), cap(cc), flow(f) {}
    friend ostream& operator<<(ostream& os, const CostCirculationFlowWeight &v) {
        os << "[" << v.fcap << ", " << v.cost << ", " << v.cap << ", " << v.flow << "]";
        return os;
    }
};

// O(VE * ElogC)
template<typename T, typename C = T>
class min_cost_circulation : public Graph<true, CostCirculationFlowWeight<T, C>, void> { // 0-base
public:
    using super = Graph<true, CostCirculationFlowWeight<T, C>, void>;
    std::vector<int> past;
    std::vector<C> dis, pot;
    void BellmanFord(int s) {
        std::vector<int> inq(this->n());
        std::ranges::fill(dis, std::numeric_limits<C>::max());
        std::queue<int> q;
        auto relax = [&](int u, C d, int eid) {
            if (dis[u] > d) {
                dis[u] = d, past[u] = eid;
                if (!inq[u]) inq[u] = 1, q.push(u);
            }
        };
        relax(s, 0, -1);
        while (!q.empty()) {
            int u = q.front();
            q.pop(), inq[u] = 0;
            for (auto [v, eid] : this->G[u]) {
                auto &w = this->edges[eid].weight;
                if (w.cap > w.flow)
                    relax(v, dis[u] + w.cost, eid);
            }
        }
    }
    void try_edge(int eid) {
        auto &cur = this->edges[eid];
        auto &w = cur.weight;
        if (w.cap > w.flow) return ++w.cap, void();
        BellmanFord(cur.to);
        if (dis[cur.from] + w.cost < 0) {
            ++w.flow, --this->edges[eid ^ 1].weight.flow;
            for (int i = cur.from; past[i] != -1; i = this->edges[past[i]].from) {
                ++this->edges[past[i]].weight.flow;
                --this->edges[past[i] ^ 1].weight.flow;
            }
        }
        ++w.cap;
    }
    min_cost_circulation(int _n) : super(_n), past(_n), dis(_n), pot(_n) {} 
    void solve(int mxlg) {
        for (int b = mxlg; b >= 0; --b) {
            for (int i = 0; i < this->n(); ++i)
                for (auto [v, eid] : this->G[i]) {
                    this->edges[eid].weight.cap *= 2;
                    this->edges[eid].weight.flow *= 2;
                }
            for (int i = 0; i < this->n(); ++i)
                for (auto [v, eid] : this->G[i]) {
                    if (this->edges[eid].weight.fcap >> b & 1)
                        try_edge(eid);
                }
        }
    }
    void add_edge(int a, int b, T cap, C cost) {
        super::add_edge(a, b, CostCirculationFlowWeight(cap, cost, T(0)));
        super::add_edge(b, a, CostCirculationFlowWeight(T(0), -cost, T(0)));
    }
    C get_cost() {
        C res = 0;
        for (int i = 0; i < this->n(); ++i) 
            for (auto [v, eid] : this->G[i])
                if (this->edges[eid].weight.flow > 0)
                    res += this->edges[eid].weight.cost * this->edges[eid].weight.flow;
        return res;
    }
};
