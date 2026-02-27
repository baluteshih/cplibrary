#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"
#include "default_code.hpp"

#include "Polynomial/linear_recursion.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    ll m;
    cin >> n >> m;
    vector<mint> a(n), coef(n);
    for (auto &i : a)
        cin >> i;
    for (auto &i : coef)
        cin >> i;
    cout << linear_recursion(a, coef, m) << "\n";
}

