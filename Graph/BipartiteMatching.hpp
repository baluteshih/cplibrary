#pragma once

#include "Graph/BipartiteGraph.hpp"

/*
match_left, match_right
-1 implies no match
*/
struct BipartiteMatching : public BipartiteGraph<void, void>  { // 0-base
    using super = BipartiteGraph<void, void>;
    std::vector<int> match_right, match_left;
    std::vector<int> dis, cur;
    BipartiteMatching(int l, int r) : super(l, r), match_right(l), match_left(r), dis(l + 1), cur(l) {} 
    bool dfs(int u) {
        for (int &i = cur[u]; i < ssize((*this)[u]); ++i) {
            int e = (*this)[u][i].first;
            if (match_left[e] == this->n() || (dis[match_left[e]] == dis[u] + 1 && dfs(match_left[e])))
                return match_right[match_left[e] = u] = e, 1;
        }
        return dis[u] = -1, 0;
    }
    bool bfs() {
        std::queue<int> q;
        std::ranges::fill(dis, -1);
        for (int i = 0; i < this->n(); ++i)
            if (!~match_right[i])
                q.push(i), dis[i] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == this->n()) continue;
            for (auto [e, eid] : (*this)[u])
                if (!~dis[match_left[e]])
                    q.push(match_left[e]), dis[match_left[e]] = dis[u] + 1;
        }
        return dis[this->n()] != -1;
    }
    int matching() {
        int res = 0;
        std::ranges::fill(match_right, -1);
        std::ranges::fill(match_left, this->n());
        while (bfs()) {
            std::ranges::fill(cur, 0);
            for (int i = 0; i < this->n(); ++i)
                res += (!~match_right[i] && dfs(i));
        }
        std::ranges::replace(match_left, this->n(), -1);
        return res;
    }
};
