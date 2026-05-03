#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"
#include "default_code.hpp"

#include "Flow/bounded_cost_circulation.hpp"
#include "Misc/i128.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    bounded_cost_circulation<ll, __int128> flow(n);
    for (int i = 0; i < n; ++i) {
        ll demand;
        cin >> demand;
        flow.add_demand(i, demand);
    }
    for (int i = 0; i < m; ++i) {
        ll s, t, l, u, c;
        cin >> s >> t >> l >> u >> c;
        flow.add_edge(s, t, l, u, c);
    }

    if (!flow.solve(1e12)) {
        cout << "infeasible\n";
        return 0;
    }
    
    auto cap = flow.get_cap();
    auto pot = flow.get_potential();
    cout << flow.get_cost() << "\n";
    for (int i = 0; i < n; ++i)
        cout << pot[i] << '\n';
    for (int i = 0; i < m; ++i)
        cout << cap[i] << "\n";
}
