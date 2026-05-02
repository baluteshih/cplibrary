#pragma once

#include "Flow/Dinic.hpp"

template<class T>
class bounded_flow : public Dinic<T> { // 0-base
    int real_n;
public:
    using super = Dinic<T>;
    std::vector<T> cnt;
    bounded_flow(int _n) : super(_n + 2), real_n(_n), cnt(real_n + 2) {}
    void add_edge(int u, int v, T lcap, T rcap) {
        cnt[u] -= lcap, cnt[v] += lcap;
        super::super::add_edge(u, v, FlowWeight<T>(rcap, lcap));
        super::super::add_edge(v, u, FlowWeight<T>(0, 0));
    }
    bool solve() {
        T sum = 0;
        int added_cnt = 0;
        bool res = true;
        for (int i = 0; i < real_n; ++i)
            if (cnt[i] > 0)
                super::add_edge(real_n, i, cnt[i]), sum += cnt[i], ++added_cnt;
            else if (cnt[i] < 0)
                super::add_edge(i, real_n + 1, -cnt[i]), ++added_cnt;
        if (sum != this->maxflow(real_n, real_n + 1)) res = false;
        while (added_cnt--) this->pop_edge(), this->pop_edge();
        return res;
    }
    bool solve(int s, int t) {
        super::add_edge(t, s, std::numeric_limits<T>::max());
        bool res = solve();
        this->pop_edge(), this->pop_edge();
        return res;
    }
};
