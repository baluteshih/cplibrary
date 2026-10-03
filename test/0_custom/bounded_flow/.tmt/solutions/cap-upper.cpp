// Gives each reduced edge capacity upper instead of upper - lower, so flows may exceed upper.
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct Dinic {
    struct Edge {
        int to;
        long long cap;
    };

    int n;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> graph;
    std::vector<int> level;
    std::vector<int> iter;

    explicit Dinic(int size) : n(size), graph(size), level(size), iter(size) {}

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
            flow += dfs(s, t, static_cast<long long>(4e18));
        }
        return flow;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    int source = n;
    int sink = n + 1;
    Dinic dinic(n + 2);
    std::vector<long long> lower(m);
    std::vector<int> edge_id(m);
    std::vector<long long> demand(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long upper;
        std::cin >> u >> v >> lower[i] >> upper;
        --u;
        --v;
        edge_id[i] = dinic.add_edge(u, v, upper);
        demand[v] += lower[i];
        demand[u] -= lower[i];
    }

    long long required = 0;
    for (int v = 0; v < n; ++v) {
        if (demand[v] > 0) {
            dinic.add_edge(source, v, demand[v]);
            required += demand[v];
        }
        else if (demand[v] < 0) {
            dinic.add_edge(v, sink, -demand[v]);
        }
    }

    if (dinic.max_flow(source, sink) != required) {
        std::cout << "NO\n";
        return 0;
    }

    std::cout << "YES\n";
    for (int i = 0; i < m; ++i) {
        std::cout << lower[i] + dinic.edges[edge_id[i] ^ 1].cap << '\n';
    }
    return 0;
}
