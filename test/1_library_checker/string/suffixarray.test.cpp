#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "default_code.hpp"

#include "String/sais.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    string s;
    cin >> s;
    auto suffix = Suffix(s);
    for (int i = 0; i < SZ(s); ++i)
        cout << suffix.sa[i] << " \n"[i + 1 == SZ(s)];
}
