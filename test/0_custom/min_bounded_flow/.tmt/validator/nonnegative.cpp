#include "testlib.h"

#include <algorithm>
#include <queue>
#include <vector>

// Data guarantee (not stated in the statement): if any feasible flow exists, the minimum
// flow value over ALL feasible flows, negative ones included, is >= 0. Such inputs give
// the same answer under the standard "t->s infinite edge" method and under the general
// definition, so the expected output is unambiguous.

const long long INF = 1'000'000'000'000'000'000LL;

struct Dinic {
    struct Edge {
        int to;
        long long cap;
    };

    std::vector<Edge> edges;
    std::vector<std::vector<int>> graph;
    std::vector<int> level;
    std::vector<int> iter;

    explicit Dinic(int size) : graph(size), level(size), iter(size) {}

    int add_edge(int from, int to, long long cap) {
        int id = static_cast<int>(edges.size());
        edges.push_back({to, cap});
        graph[from].push_back(id);
        edges.push_back({from, 0});
        graph[to].push_back(id + 1);
        return id;
    }

    bool bfs(int s, int t) {
        std::fill(level.begin(), level.end(), -1);
        std::queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int id : graph[u]) {
                const Edge &e = edges[id];
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[u] + 1;
                    que.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    long long dfs(int u, int t, long long limit) {
        if (u == t) {
            return limit;
        }
        long long pushed = 0;
        for (int &i = iter[u]; i < static_cast<int>(graph[u].size()); ++i) {
            int id = graph[u][i];
            Edge &e = edges[id];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                long long got = dfs(e.to, t, std::min(limit - pushed, e.cap));
                if (got > 0) {
                    e.cap -= got;
                    edges[id ^ 1].cap += got;
                    pushed += got;
                    if (pushed == limit) {
                        return pushed;
                    }
                }
            }
        }
        level[u] = -1;
        return pushed;
    }

    long long max_flow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            std::fill(iter.begin(), iter.end(), 0);
            flow += dfs(s, t, INF);
        }
        return flow;
    }
};

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int n = inf.readInt();
    inf.readSpace();
    int m = inf.readInt();
    inf.readSpace();
    int s = inf.readInt() - 1;
    inf.readSpace();
    int t = inf.readInt() - 1;
    inf.readEoln();

    Dinic dinic(n + 2);
    std::vector<long long> demand(n, 0);
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt() - 1;
        inf.readSpace();
        int v = inf.readInt() - 1;
        inf.readSpace();
        long long lower = inf.readInt();
        inf.readSpace();
        long long upper = inf.readInt();
        inf.readEoln();
        dinic.add_edge(u, v, upper - lower);
        demand[v] += lower;
        demand[u] -= lower;
    }
    inf.readEof();

    int back_edge = dinic.add_edge(t, s, INF);
    int forward_edge = dinic.add_edge(s, t, INF);
    int super_source = n;
    int super_sink = n + 1;
    long long required = 0;
    for (int v = 0; v < n; ++v) {
        if (demand[v] > 0) {
            dinic.add_edge(super_source, v, demand[v]);
            required += demand[v];
        }
        else if (demand[v] < 0) {
            dinic.add_edge(v, super_sink, -demand[v]);
        }
    }

    if (dinic.max_flow(super_source, super_sink) == required) {
        long long value = dinic.edges[back_edge ^ 1].cap - dinic.edges[forward_edge ^ 1].cap;
        for (int id : {back_edge, forward_edge}) {
            dinic.edges[id].cap = 0;
            dinic.edges[id ^ 1].cap = 0;
        }
        long long min_value = value - dinic.max_flow(t, s);
        ensuref(min_value >= 0, "minimum flow over all feasible flows is negative (%lld)", min_value);
    }

    return 42;
}
