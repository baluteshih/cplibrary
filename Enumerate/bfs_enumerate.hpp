#pragma once

#include "Algebra/NullFunc.hpp"

template<typename T, typename F_op>
std::vector<std::pair<T, int>> bfs_enumerate(const T &start, F_op oper, int dis_upper = -1, bool sort_by_dis = true) {
    std::map<T, int> dis;
    std::queue<T> q;
    auto relax = [&](const T &u, int d) {
        auto it = dis.find(u);
        if (it != dis.end()) return;
        dis[u] = d;
        if (dis_upper == -1 || d < dis_upper)
            q.push(u);
    };
    relax(start, 0);
    while (!q.empty()) {
        T u = q.front();
        q.pop();
        int d = dis[u];
        for (T v : oper(u))
            relax(v, d + 1);
    }
    std::vector<std::pair<T, int>> res(dis.begin(), dis.end());
    if (sort_by_dis)
        std::ranges::sort(res, [&](auto a, auto b) {
            return a.second < b.second; 
        });
    return res;
}
