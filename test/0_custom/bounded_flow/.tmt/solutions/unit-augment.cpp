// Ford-Fulkerson written like bipartite matching: every DFS augments a single unit, so the
// running time is proportional to the total demand (up to ~1e9).
#include <iostream>
#include <vector>

struct Edge {
    int to;
    long long cap;
};

std::vector<Edge> edges;
std::vector<std::vector<int>> graph;
std::vector<int> visited;
int stamp = 0;

int add_edge(int from, int to, long long cap) {
    int id = static_cast<int>(edges.size());
    edges.push_back({to, cap});
    graph[from].push_back(id);
    edges.push_back({from, 0});
    graph[to].push_back(id + 1);
    return id;
}

bool augment(int u, int t) {
    if (u == t) {
        return true;
    }
    visited[u] = stamp;
    for (int id : graph[u]) {
        Edge &e = edges[id];
        if (e.cap > 0 && visited[e.to] != stamp && augment(e.to, t)) {
            e.cap -= 1;
            edges[id ^ 1].cap += 1;
            return true;
        }
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    int source = n;
    int sink = n + 1;
    graph.assign(n + 2, {});
    visited.assign(n + 2, 0);
    std::vector<long long> lower(m);
    std::vector<int> edge_id(m);
    std::vector<long long> demand(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long upper;
        std::cin >> u >> v >> lower[i] >> upper;
        --u;
        --v;
        edge_id[i] = add_edge(u, v, upper - lower[i]);
        demand[v] += lower[i];
        demand[u] -= lower[i];
    }

    long long required = 0;
    for (int v = 0; v < n; ++v) {
        if (demand[v] > 0) {
            add_edge(source, v, demand[v]);
            required += demand[v];
        }
        else if (demand[v] < 0) {
            add_edge(v, sink, -demand[v]);
        }
    }

    long long flow = 0;
    while (true) {
        ++stamp;
        if (!augment(source, sink)) {
            break;
        }
        ++flow;
    }

    if (flow != required) {
        std::cout << "NO\n";
        return 0;
    }

    std::cout << "YES\n";
    for (int i = 0; i < m; ++i) {
        std::cout << lower[i] + edges[edge_id[i] ^ 1].cap << '\n';
    }
    return 0;
}
