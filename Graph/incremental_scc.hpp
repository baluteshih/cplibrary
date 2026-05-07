#pragma once

#include "Graph/SCC.hpp"

// the order of the edges are the inserted order
// return an array t of length m
// t[i] := the time when edge i belongs to an scc, t[i] = m if never
template <typename GraphType>
std::vector<int> incremental_scc(const GraphType &G) {
    int n = G.n(), m = G.m();
    std::vector<int> res(m, m);

    std::vector<int> idx(n, -1);
    auto dc = [&](auto &self, std::vector<std::array<int, 3>> &event, int l, int r) -> void {
        if (r - l == 1 || event.empty()) return;
        int mid = (l + r) >> 1;
        int cnt = 0;
        for (auto& [i, a, b] : event) {
            if (idx[a] == -1) idx[a] = cnt++;
            if (idx[b] == -1) idx[b] = cnt++;
        }
        SCC scc(cnt);
        for (auto& [i, a, b] : event)
            if (i <= mid)
                scc.add_edge(idx[a], idx[b]);
        scc.solve();
        std::vector<std::array<int, 3>> lft, rgt;
        for (auto [i, a, b] : event) {
            a = idx[a], b = idx[b];
            if (i <= mid && scc.bln[a] == scc.bln[b]) {
                    res[i] = std::min(res[i], mid);
                    lft.push_back({i, a, b});
            }
            else rgt.push_back({i, scc.bln[a], scc.bln[b]});
        }
        for (auto &[i, a, b] : event) idx[a] = idx[b] = -1;
        self(self, lft, l, mid), self(self, rgt, mid, r);
    };

    std::vector<std::array<int, 3>> event;
    for (int i = 0; i < m; ++i) {
        auto &e = G.edge(i);
        event.push_back({i, e.from, e.to});
    }
    dc(dc, event, 0, m);
    return res;
}
