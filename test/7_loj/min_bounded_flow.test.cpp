#define PROBLEM "https://loj.ac/p/117"
#define IGNORE
#include "default_code.hpp"

#include "Flow/bounded_flow.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s, --t;
    bounded_flow<ll> flow(n);
    for (int i = 0; i < m; ++i) {
        int u, v, l, r;
        cin >> u >> v >> l >> r;
        --u, --v;
        flow.add_edge(u, v, l, r);
    }
    if (!flow.solve(s, t)) cout << "please go home to sleep\n";
    else {
        flow.maxflow(t, s);
        cout << flow.get_flow(s) << "\n";
    }
}
