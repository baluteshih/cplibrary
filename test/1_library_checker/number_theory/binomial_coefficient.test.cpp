#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"
#include "default_code.hpp"

#include "Numeric/Binomial.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int t, m;
    cin >> t >> m;
    Binomial binom(m);
    while (t--) {
        ll n, k;
        cin >> n >> k;
        cout << binom.C(n, k) << "\n";
    }
}
