#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"
#include "default_code.hpp"

#include "Flow/min_cost_circulation.hpp"

namespace std {
    ostream &operator<<(ostream &os, const __int128 &x) {
        if (x < 0) return os << '-' << -x;
        if (x < 10) return os << int(x % 10);
        return os << x / 10 << int(x % 10);
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<ll> b(n);
    for (ll &i : b)
        cin >> i;
    vector<array<int, 5>> edges(m);
    __int128 lbound_cost = 0;
    for (auto &[s, t, l, u, c] : edges) {
        cin >> s >> t >> l >> u >> c;
        b[s] -= l;
        b[t] += l;
        lbound_cost += 1ll * l * c;
    }
    const int S = n, T = n + 1, N = T + 1;
    min_cost_circulation<ll, __int128> flow(N);

    ll p_sum = 0, n_sum = 0;
    for (const auto &[s, t, l, u, c] : edges)
        flow.add_edge(s, t, u - l, c);
    for (int i = 0; i < n; ++i) {
        if (b[i] > 0) {
            flow.add_edge(S, i, b[i], 0);
            p_sum += b[i];
        }
        else {
            flow.add_edge(i, T, -b[i], 0);
            n_sum += b[i];
        }
    }
    
    ll LARGE = 1e12;
    flow.add_edge(T, S, LARGE, -LARGE);
    flow.solve();
    auto cap = flow.get_cap();
    if (cap.back() != p_sum) {
        cout << "infeasible\n";
        return 0;
    }
    auto pot = flow.get_potential();
    cout << flow.get_cost() + __int128(LARGE) * p_sum + lbound_cost << "\n";
    for (int i = 0; i < n; ++i)
        cout << pot[i] << '\n';
    for (int i = 0; i < m; ++i) {
        auto [s, t, l, u, c] = edges[i];
        cout << cap[i] + l << "\n";
    }
}
