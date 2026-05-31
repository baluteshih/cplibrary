#pragma once

#include "Tree/CentroidTree.hpp"

template<typename DS>
class DistanceSolver : public CentroidTree<void, void> {
public:
    using super = CentroidTree<void, void>;
    std::vector<std::vector<int>> c_dist;
    std::vector<DS> tr_self, tr_parent;
    DistanceSolver(int n) : super(n), c_dist(n), tr_self(n, 0), tr_parent(n, 0) {}
    void build() {
        std::vector<int> dis(this->n());
        super::build([&](int u, int f) {
            if (f == -1) dis[u] = 0;
            else dis[u] = dis[f] + 1;
            c_dist[u].push_back(dis[u]);
        }, [&](int c, const std::vector<std::vector<int>> &groups) {
            int mx = 1;
            for (auto &vec : groups)
                for (auto v : vec)
                    mx = std::max(mx, dis[v] + 1);
            tr_self[c] = DS(mx);
            if (int(c_dist[c].size()) >= 2) {
                mx = c_dist[c][int(c_dist[c].size()) - 2] + 1;
                for (auto &vec : groups)
                    for (auto v : vec)
                        mx = std::max(mx, c_dist[v][int(c_dist[v].size()) - 2] + 1);
                tr_parent[c] = DS(mx);
            }
        });
        for (int i = 0; i < this->n(); ++i) std::ranges::reverse(c_dist[i]);
    }
    /*
    action(ds, d, prev)
        - ds: the data structure on the corresponding centroid
        - d: the distance from u to the centroid
        - prev: whether using prev centroid
    */
    template<typename Func>
    void climb(int u, Func action) {
        int jump_steps = 0;
        super::climb(u, [&](int c, int prev_c) {
            action(tr_self[c], c_dist[u][jump_steps], false);
            if (prev_c != -1)
                action(tr_parent[prev_c], c_dist[u][jump_steps], true);
            ++jump_steps;
        });
    }
};
