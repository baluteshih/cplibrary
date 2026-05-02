#define PROBLEM "https://loj.ac/p/115"
#define IGNORE
#include "default_code.hpp"

#include "Flow/bounded_flow.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    bounded_flow<int> flow(n);
    for (int i = 0; i < m; ++i) {
        int u, v, l, r;
        cin >> u >> v >> l >> r;
        --u, --v;
        flow.add_edge(u, v, l, r);
    }
    if (!flow.solve()) cout << "NO\n";
    else {
        cout << "YES\n";
        for (int i = 0; i < 2 * m; i += 2)
            cout << flow.edge(i).weight.flow << "\n";
    }
}
