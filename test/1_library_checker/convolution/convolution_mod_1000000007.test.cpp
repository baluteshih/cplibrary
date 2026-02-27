#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"
#include "Polynomial/convolution_any_mod.hpp"

using mint = modint1000000007;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    vector<mint> a(n), b(m);
    for (auto &i : a)
        cin >> i;
    for (auto &i : b)
        cin >> i;
    auto c = convolution_any_mod(a, b);
    for (int i = 0; i < SZ(c); ++i)
        cout << c[i] << " \n"[i + 1 == SZ(c)]; 
}
