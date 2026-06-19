#define PROBLEM "https://codeforces.com/gym/106033/problem/E"
#define IGNORE
#include "assumption.hpp"

#include "Flow/Dinic.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    Dinic<long long> dinic(n);
    while (m--) {
        int u, v, c;
        std::cin >> u >> v >> c;
        --u, --v;
        dinic.add_edge(u, v, c);
    }
    long long res = dinic.maxflow(0, n - 1);
    std::cout << res << "\n";
    auto route = dinic.get_route(0, n - 1); 
    std::cout << route.size() << "\n";
    for (auto [w, v] : route) {
        std::cout << w << " " << v.size();
        for (int i : v)
            std::cout << " " << i + 1;
        std::cout << "\n";
    }
}
