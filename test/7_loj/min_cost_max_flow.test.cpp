#define PROBLEM "https://loj.ac/p/102"
#define IGNORE

#include "default_code.hpp"
#include "Flow/min_cost_max_flow.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    min_cost_max_flow<int, ll> mcmf(n);

    while (m--) {
        int u, v, c, d;
        cin >> u >> v >> c >> d;
        --u, --v;
        mcmf.add_edge(u, v, c, d);
    }

    auto [flow, cost] = mcmf.solve<true>(0, n - 1);
    cout << flow << " " << cost << "\n";
}
