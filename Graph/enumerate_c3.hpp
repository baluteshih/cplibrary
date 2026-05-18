#pragma once

#include "Graph/base.hpp"

template<typename G>
void enumerate_c3(const G &_graph, auto func) {
    std::vector<int> ord(_graph.n()), rk(_graph.n()), cnt(_graph.n()), vis(_graph.n());
    for (int i = 0; i < _graph.n(); ++i)
        ++cnt[_graph[i].size()];
    std::partial_sum(cnt.rbegin(), cnt.rend(), cnt.rbegin());
    for (int i = 0; i < _graph.n(); ++i)
        ord[rk[i] = --cnt[_graph[i].size()]] = i;
    auto graph = _graph.oriented(rk); 
    for (int x : ord) {
        for (auto [y, _] : graph[x]) vis[y] = 1;
        for (auto [y, _] : graph[x])
            for (auto [z, __] : graph[y])
                if (vis[z])
                    func(x, y, z);
        for (auto [y, _] : graph[x]) vis[y] = 0;
    }
}
