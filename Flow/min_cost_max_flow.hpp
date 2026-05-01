#pragma once

template<typename T>
class min_cost_max_flow { // 0-base
    struct Edge {
        int from, to, rev;
        T cap, flow, cost;
    };
    int n;
    std::vector<Edge*> past;
    std::vector<std::vector<Edge>> G;
    std::vector<T> dis, up, pot;
    template<bool bellmanford = true>
    bool shortest_path(int s, int t) {
        std::vector<int> inq(n);
        std::ranges::fill(dis, std::numeric_limits<T>::max());
        std::conditional_t<bellmanford, std::queue<int>, std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>>> q;
        auto relax = [&](int u, T d, T cap, Edge *e) {
            if (cap > 0 && dis[u] > d) {
                dis[u] = d, up[u] = cap, past[u] = e;
                if constexpr (!bellmanford) q.emplace(dis[u], u);
                else if (!inq[u]) inq[u] = 1, q.push(u);
            }
        };
        relax(s, 0, std::numeric_limits<T>::max(), 0);
        while (!q.empty()) {
            T d;
            int u;
            if constexpr (bellmanford) u = q.front();
            else std::tie(d, u) = q.top();
            q.pop();
            if constexpr (bellmanford) inq[u] = 0;
            else if (dis[u] != d) continue;
            for (auto &e : G[u]) {
                T d2 = dis[u] + e.cost + pot[u] - pot[e.to];
                relax(e.to, d2, std::min(up[u], e.cap - e.flow), &e);
            }
        }
        return dis[t] != std::numeric_limits<T>::max();
    }
public:
    min_cost_max_flow(int _n) : n(_n), past(n), G(n), dis(n), up(n), pot(n) {} 
    template<bool bellmanford = true, bool neg = true>
    std::pair<T, T> solve(int s, int t) {
        T flow = 0, cost = 0;
        if constexpr (neg) shortest_path<true>(s, t), dis = pot;
        for (; shortest_path<bellmanford>(s, t); dis = pot) {
            for (int i = 0; i < n; ++i) dis[i] += pot[i] - pot[s];
            flow += up[t], cost += up[t] * dis[t];
            for (int i = t; past[i]; i = past[i]->from) {
                auto &e = *past[i];
                e.flow += up[t], G[e.to][e.rev].flow -= up[t];
            }
        }
        return std::make_pair(flow, cost);
    }
    void add_edge(int a, int b, T cap, T cost) {
        G[a].push_back(Edge{a, b, int(G[b].size()), cap, 0, cost});
        G[b].push_back(Edge{b, a, int(G[a].size()) - 1, 0, 0, -cost});
    }
};
