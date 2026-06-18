#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"
#include "assumption.hpp"

#include "Flow/min_cost_max_flow.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m, f;
    std::cin >> n >> m >> f;
    min_cost_max_flow<int> mcmf(n + 1);
    while (m--) {
        int u, v, c, d;
        std::cin >> u >> v >> c >> d;
        mcmf.add_edge(u, v, c, d);
    }
    mcmf.add_edge(n, 0, f, 0);
    auto [flow, cost] = mcmf.solve<false>(n, n - 1);
    if (flow != f) std::cout << "-1\n";
    else std::cout << cost << "\n";
}
