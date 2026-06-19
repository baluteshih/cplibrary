#define PROBLEM "https://loj.ac/p/115"
#define IGNORE
#include "assumption.hpp"

#include "Flow/bounded_flow.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    bounded_flow<int> flow(n);
    for (int i = 0; i < m; ++i) {
        int u, v, l, r;
        std::cin >> u >> v >> l >> r;
        --u, --v;
        flow.add_edge(u, v, l, r);
    }
    if (!flow.solve()) std::cout << "NO\n";
    else {
        std::cout << "YES\n";
        for (int i = 0; i < 2 * m; i += 2)
            std::cout << flow.edge(i).weight.flow << "\n";
    }
}
