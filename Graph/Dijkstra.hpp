#pragma once

#include "Graph/base.hpp"

template<class T>
class Dijkstra : public Graph<true, T> { // 0-base, O(mlogn)
    using super = Graph<true, T>;
public:
    std::vector<int> parent; // parent[source] = source
    std::vector<int> parent_edge; // parent_edge[source] = -1 
    std::vector<int> has_path;
    std::vector<T> dis;
    Dijkstra(int n): super(n), parent(n), parent_edge(n), has_path(n), dis(n) {}
    void solve(int source) {
        std::ranges::fill(dis, std::numeric_limits<T>::max());
        std::ranges::fill(has_path, 0);
        std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> pq;
        auto relax = [&](int u, T w, int f, int fedge) {
            if (dis[u] > w) {
                dis[u] = w;
                parent[u] = f;
                parent_edge[u] = fedge;
                pq.emplace(w, u);
            }
        };
        relax(source, 0, source, -1);
        while (!pq.empty()) {
            auto [w, u] = pq.top();
            pq.pop();
            if (dis[u] != w) continue;
            has_path[u] = true;
            for (auto [v, e] : this->G[u])
                relax(v, dis[u] + this->edges[e].weight, u, e);
        }
    }
    std::vector<int> path(int target, bool vertex = true) {
        assert(has_path[target]);
        std::vector<int> res;
        if (vertex) res.push_back(target);
        for (int x = target; parent[x] != x; x = parent[x]) {
            if (vertex) res.push_back(parent[x]);
            else res.push_back(parent_edge[x]);
        }
        std::ranges::reverse(res);
        return res;
    }
};
