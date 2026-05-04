#define PROBLEM "https://judge.yosupo.jp/problem/bell_number"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"
#include "Numbers/bell_number.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    auto res = bell_number<mint>(n);
    for (int i = 0; i <= n; ++i)
        cout << res[i] << " \n"[i == n];
}
