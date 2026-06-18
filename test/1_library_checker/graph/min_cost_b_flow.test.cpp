#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"
#include "assumption.hpp"

#include "Flow/bounded_cost_circulation.hpp"
#include "Misc/i128.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    bounded_cost_circulation<long long, __int128> flow(n);
    for (int i = 0; i < n; ++i) {
        long long demand;
        std::cin >> demand;
        flow.add_demand(i, demand);
    }
    for (int i = 0; i < m; ++i) {
        long long s, t, l, u, c;
        std::cin >> s >> t >> l >> u >> c;
        flow.add_edge(s, t, l, u, c);
    }

    if (!flow.solve(1e12)) {
        std::cout << "infeasible\n";
        return 0;
    }
    
    auto cap = flow.get_cap();
    auto pot = flow.get_potential();
    std::cout << flow.get_cost() << "\n";
    for (int i = 0; i < n; ++i)
        std::cout << pot[i] << '\n';
    for (int i = 0; i < m; ++i)
        std::cout << cap[i] << "\n";
}
