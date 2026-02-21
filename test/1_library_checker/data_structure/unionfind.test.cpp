#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "default_code.hpp"

#include "DataStructure/DisjointSet.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    DisjointSet djs(n);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 0)
            djs.merge(u, v);
        else
            cout << djs.same(u, v) << "\n";
    }
}
