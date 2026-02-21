#include "default_code.hpp"

#include "DataStructure/PotentialDisjointSet.hpp"

#include "Numeric/Modint.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    PotentialDisjointSet<mint> djs(n);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 0) {
            bool succ = true;
            mint x;
            cin >> x;
            if (djs.same(u, v)) succ = (djs.diff(u, v) == x);
            else djs.merge(u, v, x);
            cout << succ << "\n";
        }
        else {
            if (djs.same(u, v)) cout << djs.diff(u, v) << "\n";
            else cout << "-1\n";
        }
    }
}
