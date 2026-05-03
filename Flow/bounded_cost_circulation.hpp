#pragma once

#include "Flow/min_cost_circulation.hpp"

template<typename T, typename C = T>
class bounded_cost_circulation : public min_cost_circulation<T, C> { // 0-base
public:
    using super = min_cost_circulation<T, C>;
    using super::add_edge;
    int real_n;
    std::vector<T> cnt;
    bounded_cost_circulation(int _n) : super(_n + 2), real_n(_n), cnt(real_n + 2) {}
    void add_demand(int u, T d) {
        cnt[u] += d;
    }
    void add_edge(int u, int v, T lcap, T rcap, C cost) {
        cnt[u] -= lcap, cnt[v] += lcap;
        super::super::add_edge(u, v, CostFlowWeight<T, C>(rcap, cost, rcap - lcap));
        super::super::add_edge(v, u, CostFlowWeight<T, C>(T(0), -cost, T(0)));
    }
    bool solve(C inf) {
        T sum = 0, neg_sum = 0;
        int added_cnt = 0;
        for (int i = 0; i < real_n; ++i)
            if (cnt[i] > 0)
                super::add_edge(real_n, i, cnt[i], C(0)), sum += cnt[i], ++added_cnt;
            else if (cnt[i] < 0)
                super::add_edge(i, real_n + 1, -cnt[i], C(0)), neg_sum += cnt[i], ++added_cnt;
        super::add_edge(real_n + 1, real_n, std::numeric_limits<T>::max() / 2, -inf), ++added_cnt;
        super::solve();
        bool res = (sum + neg_sum == 0 && this->edges.back().weight.flow == sum);
        while (added_cnt--) this->pop_edge(), this->pop_edge();
        return res;
    }
    bool solve(int s, int t, C inf) {
        super::add_edge(t, s, std::numeric_limits<T>::max() / 2, -inf);
        bool res = solve(inf);
        this->pop_edge(), this->pop_edge();
        return res;
    }
};
