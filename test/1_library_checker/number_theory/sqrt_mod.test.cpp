#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"
#include "default_code.hpp"

#include "Numeric/QuadraticResidue.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int y, p;
        cin >> y >> p;
        dynamic_modint<-1> v;
        v.set_mod(p);
        v = v.raw(y);
        bool succ;
        auto res = QuadraticResidue(v, succ);
        if (!succ) cout << "-1\n";
        else cout << res << "\n";
    }
}
