#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"
#include "default_code.hpp"

#include "Numeric/Combination.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int t, m;
    cin >> t >> m;
    modint v;
    v.set_mod(m);
    Combination<modint> comb(min(10000000, m - 1), v);
    while (t--) {
        int n, k;
        cin >> n >> k;
        cout << comb.C(n, k) << "\n";
    }
}
