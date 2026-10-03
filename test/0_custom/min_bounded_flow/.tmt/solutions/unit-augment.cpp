// Ford-Fulkerson written like bipartite matching: every DFS augments a single unit, so the
// running time is proportional to the total flow (up to ~1e9).
#include <iostream>
#include <vector>

const long long INF = 1'000'000'000'000'000'000LL;

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

long long max_flow(int s, int t) {
    long long flow = 0;
    while (true) {
        ++stamp;
        if (!augment(s, t)) {
            return flow;
        }
        ++flow;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    --s;
    --t;

    int super_source = n;
    int super_sink = n + 1;
    graph.assign(n + 2, {});
    visited.assign(n + 2, 0);
    std::vector<long long> demand(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long lower, upper;
        std::cin >> u >> v >> lower >> upper;
        --u;
        --v;
        add_edge(u, v, upper - lower);
        demand[v] += lower;
        demand[u] -= lower;
    }
    int back_edge = add_edge(t, s, INF);

    long long required = 0;
    for (int v = 0; v < n; ++v) {
        if (demand[v] > 0) {
            add_edge(super_source, v, demand[v]);
            required += demand[v];
        }
        else if (demand[v] < 0) {
            add_edge(v, super_sink, -demand[v]);
        }
    }

    if (max_flow(super_source, super_sink) != required) {
        std::cout << "please go home to sleep\n";
        return 0;
    }

    long long base_flow = edges[back_edge ^ 1].cap;
    edges[back_edge].cap = 0;
    edges[back_edge ^ 1].cap = 0;
    std::cout << base_flow - max_flow(t, s) << '\n';
    return 0;
}
