#define PROBLEM "https://codeforces.com/gym/106033/problem/E"
#define IGNORE
#include "default_code.hpp"

#include "Flow/Dinic.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    Dinic<ll> dinic(n);
    while (m--) {
        int u, v, c;
        cin >> u >> v >> c;
        --u, --v;
        dinic.add_edge(u, v, c);
    }
    ll res = dinic.maxflow(0, n - 1);
    cout << res << "\n";
    auto route = dinic.get_route(); 
    cout << route.size() << "\n";
    for (auto [w, v] : route) {
        cout << w << " " << v.size();
        for (int i : v)
            cout << " " << i + 1;
        cout << "\n";
    }
}
