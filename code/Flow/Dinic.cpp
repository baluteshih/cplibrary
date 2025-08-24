#ifndef __BALU_DINIC__
#define __BALU_DINIC__
template<class T>
class MaxFlow { // 0-base
    struct edge {
        int to, rev;
        T cap, flow;
    };
    int n, s, t;
    T mxcap;
    vector<int> dis, cur;
    vector<vector<edge>> G;
    T dfs(int u, T cap) {
        if (u == t || !cap) return cap;
        for (int &i = cur[u]; i < ssize(G[u]); ++i) {
            edge &e = G[u][i];
            if (dis[e.to] == dis[u] + 1 && e.flow != e.cap) {
                T df = dfs(e.to, min(e.cap - e.flow, cap));
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
        fill(ALL(dis), -1);
        queue<int> q;
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
    MaxFlow(int _n): n(_n), s(0), t(0), mxcap(0), dis(n), cur(n), G(n) {} 
    void reset() {
        for (int i = 0; i < n; ++i)
            for (auto &j : G[i])
                j.flow = 0;
    }
    void add_edge(int u, int v, T cap) {
        mxcap = max(mxcap, cap);
        G[u].pb(edge{v, int(size(G[v])), cap, T(0)});
        G[v].pb(edge{u, int(size(G[u])) - 1, T(0), T(0)});
    }
    T maxflow(int _s, int _t) {
        s = _s, t = _t;
        T flow = 0, df;
        while (bfs()) {
            fill(ALL(cur), 0);
            while ((df = dfs(s, mxcap))) flow += df;
        }
        return flow;
    }
    vector<vector<int>> get_route() {
        vector<int> stk;
        auto route = [&](auto _route, int u) -> bool {
            stk.pb(u);
            if (u == t) return true;
            for (int &i = cur[u]; cur[u] < ssize(G[u]);) {
                auto &e = G[u][i++];
                if (e.flow > 0) {
                    --e.flow;
                    return _route(_route, e.to);
                }
            }
            return false;
        };
        vector<vector<int>> res;
        while (true) {
            stk.clear();
            fill(ALL(cur), 0);
            if (!route(route, s)) break;
            res.pb(stk);
        }
        return res;
    }
    vector<int> get_mincut() { // 0: s, 1: t
        vector<int> state(n);
        for (int i = 0; i < n; ++i)
            state[i] = (dis[i] == -1);
        return state;
    }
    vector<edge> &adj(int u) {
        return G[u];
    }
};
#endif // __BALU_DINIC__
