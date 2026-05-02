#define PROBLEM "https://loj.ac/p/101"
#define IGNORE
#include "default_code.hpp"

#include "Flow/Dinic.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s, --t;
    Dinic<ll> flow(n);
    while (m--) {
        int u, v, c;
        cin >> u >> v >> c;
        --u, --v;
        flow.add_edge(u, v, c);
    }
    cout << flow.maxflow(s, t) << "\n";
}
