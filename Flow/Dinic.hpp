#pragma once

template<class T>
class Dinic { // 0-base
    struct edge {
        int to, rev;
        T cap, flow;
    };
    int n, s, t;
    std::vector<int> dis, cur;
    std::vector<std::vector<edge>> G;
    T dfs(int u, T cap) {
        if (u == t || !cap) return cap;
        for (int &i = cur[u]; i < std::ssize(G[u]); ++i) {
            edge &e = G[u][i];
            if (dis[e.to] == dis[u] + 1 && e.flow != e.cap) {
                T df = dfs(e.to, std::min(e.cap - e.flow, cap));
                if (df) {
                    e.flow += df;
                    G[e.to][e.rev].flow -= df;
                    return df;
                }
            }
        }
        dis[u] = -1;
        return 0;
    }
    bool bfs() {
        std::fill(dis.begin(), dis.end(), -1);
        std::queue<int> q;
        q.push(s), dis[s] = 0;
        while (!q.empty()) {
            int tmp = q.front();
            q.pop();
            for (auto &u : G[tmp])
                if (!~dis[u.to] && u.flow != u.cap) {
                    q.push(u.to);
                    dis[u.to] = dis[tmp] + 1;
                }
        }
        return dis[t] != -1;
    }
public:
    Dinic(int _n): n(_n), s(0), t(0), dis(n), cur(n), G(n) {} 
    void add_edge(int u, int v, T cap) {
        G[u].push_back(edge{v, int(size(G[v])), cap, T(0)});
        G[v].push_back(edge{u, int(size(G[u])) - 1, T(0), T(0)});
    }
    T maxflow(int _s, int _t) {
        s = _s, t = _t;
        T flow = 0, df;
        while (bfs()) {
            std::fill(cur.begin(), cur.end(), 0);
            while ((df = dfs(s, std::numeric_limits<T>::max()))) flow += df;
        }
        return flow;
    }
    std::vector<std::pair<T, std::vector<int>>> get_route() {
        std::vector<std::pair<T, std::vector<int>>> res;
        std::vector<std::vector<edge>> backup(G);
        for (int i = 0; i < n; ++i)
            for (auto &e : G[i]) {
                if (e.cap > 0) e.cap = e.flow;
                e.flow = 0;
            }
        std::vector<int> stk;
        auto route = [&](auto _dfs, int u, T cap) -> T {
            if (u == t || cap == 0) {
                if (cap != 0) stk.push_back(u);
                return cap;
            }
            for (int &i = cur[u]; i < std::ssize(G[u]); ++i) {
                edge &e = G[u][i];
                if (dis[e.to] == dis[u] + 1 && e.flow != e.cap) {
                    T df = _dfs(_dfs, e.to, std::min(e.cap - e.flow, cap));
                    if (df) {
                        e.flow += df;
                        stk.push_back(u);
                        return df;
                    }
                }
            }
            dis[u] = -1;
            return 0;
        };
        while (bfs()) {
            std::fill(cur.begin(), cur.end(), 0);
            T df;
            while ((df = route(route, s, std::numeric_limits<T>::max()))) {
                std::reverse(stk.begin(), stk.end());
                res.emplace_back(df, stk);
                stk.clear();
            }
        }
        G.swap(backup);
        return res;
    }
    std::vector<edge> &adj(int u) {
        return G[u];
    }
};
