#define PROBLEM "https://loj.ac/p/101"
#define IGNORE
#include "assumption.hpp"

#include "Flow/Dinic.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    --s, --t;
    Dinic<long long> flow(n);
    while (m--) {
        int u, v, c;
        std::cin >> u >> v >> c;
        --u, --v;
        flow.add_edge(u, v, c);
    }
    std::cout << flow.maxflow(s, t) << "\n";
}
