#define PROBLEM "https://loj.ac/p/116"
#define IGNORE
#include "assumption.hpp"

#include "Flow/bounded_flow.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    --s, --t;
    bounded_flow<int> flow(n);
    for (int i = 0; i < m; ++i) {
        int u, v, l, r;
        std::cin >> u >> v >> l >> r;
        --u, --v;
        flow.add_edge(u, v, l, r);
    }
    if (!flow.solve(s, t)) std::cout << "please go home to sleep\n";
    else {
        flow.maxflow(s, t);
        std::cout << flow.get_flow(s) << "\n";
    }
}
