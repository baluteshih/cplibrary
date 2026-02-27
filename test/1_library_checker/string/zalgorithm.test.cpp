#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "default_code.hpp"

#include "String/z_algo.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    string s;
    cin >> s;
    auto z = make_z(s);
    for (int i = 0; i < SZ(s); ++i)
        cout << z[i] << " \n"[i + 1 == SZ(s)];
}
