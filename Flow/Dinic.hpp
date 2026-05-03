#pragma once

#include "Graph/base.hpp"

template<typename T>
struct FlowWeight {
    T cap, flow;
    FlowWeight() : cap(0), flow(0) {}
    FlowWeight(T c, T f = 0) : cap(c), flow(f) {}
    friend ostream& operator<<(ostream& os, const FlowWeight &v) {
        os << "[" << v.cap << ", " << v.flow << "]";
        return os;
    }
};

template<class T>
class Dinic : public Graph<true, FlowWeight<T>, void> { // 0-base
public:
    using super = Graph<true, FlowWeight<T>, void>;
    std::vector<int> dis, cur;
    T dfs(int u, T push_cap, int t) {
        if (u == t || push_cap == 0) return push_cap;
        for (int &i = cur[u]; i < std::ssize(this->G[u]); ++i) {
            auto [v, eid] = this->G[u][i];
            auto &w = this->edges[eid].weight;
            if (dis[v] == dis[u] + 1 && w.cap > w.flow) {
                T df = dfs(v, std::min(w.cap - w.flow, push_cap), t);
                if (df > T(0)) {
                    w.flow += df;
                    this->edges[eid ^ 1].weight.flow -= df;
                    return df;
                }
            }
        }
        dis[u] = -1;
        return 0;
    }
    bool bfs(int s, int t) {
        std::ranges::fill(dis, -1);
        std::queue<int> q;
        q.push(s);
        dis[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto [v, eid] : this->G[u]) {
                auto &w = this->edges[eid].weight;
                if (dis[v] == -1 && w.cap > w.flow) {
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            }
        }
        return dis[t] != -1;
    }
    Dinic(int _n) : super(_n), dis(_n), cur(_n) {}
    void add_edge(int u, int v, T cap) {
        super::add_edge(u, v, FlowWeight<T>(cap, 0));
        super::add_edge(v, u, FlowWeight<T>(0, 0));
    }
    T maxflow(int s, int t) {
        T flow = 0, df;
        while (bfs(s, t)) {
            std::ranges::fill(cur, 0);
            while ((df = dfs(s, std::numeric_limits<T>::max(), t)) > 0)
                flow += df;
        }
        return flow;
    }
    std::vector<std::pair<T, std::vector<int>>> get_route(int s, int t) {
        std::vector<std::pair<T, std::vector<int>>> res;
        auto backup_edges = this->edges; 
        for (auto &e : this->edges) {
            if (e.weight.cap > 0) e.weight.cap = e.weight.flow;
            e.weight.flow = 0;
        }

        std::vector<int> stk;
        auto route = [&](auto self, int u, T push_cap) -> T {
            if (u == t || push_cap == 0) {
                if (push_cap > 0) stk.push_back(u);
                return push_cap;
            }
            for (int &i = cur[u]; i < std::ssize(this->G[u]); ++i) {
                auto [v, eid] = this->G[u][i];
                auto &w = this->edges[eid].weight;
                if (dis[v] == dis[u] + 1 && w.cap > w.flow) {
                    T df = self(self, v, std::min(w.cap - w.flow, push_cap));
                    if (df > 0) {
                        w.flow += df;
                        stk.push_back(u);
                        return df;
                    }
                }
            }
            dis[u] = -1;
            return 0;
        };

        while (bfs(s, t)) {
            std::ranges::fill(cur, 0);
            T df;
            while ((df = route(route, s, std::numeric_limits<T>::max())) > 0) {
                std::ranges::reverse(stk);
                res.emplace_back(df, stk);
                stk.clear();
            }
        }
        
        this->edges = std::move(backup_edges); 
        return res;
    }
    void reset() {
        for (auto &e : this->edges) e.weight.flow = 0;
    }
    T get_flow(int s) {
        T res = T();
        for (auto [v, eid] : this->G[s])
            res += this->edges[eid].weight.flow;
        return res;
    }
};
