#define PROBLEM "https://judge.yosupo.jp/problem/general_matching"
#include "default_code.hpp"

#include "Graph/Matching.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    Matching mch(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        mch.add_edge(u, v);
    }
    cout << mch.solve() << "\n";
    for (int i = 0; i < n; ++i)
        if (mch.match[i] > i)
            cout << i << " " << mch.match[i] << "\n";
}
