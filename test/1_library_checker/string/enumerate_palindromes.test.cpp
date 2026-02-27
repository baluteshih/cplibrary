#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "default_code.hpp"

#include "String/manacher.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    string s;
    cin >> s;
    auto z = manacher(s);
    for (int i = 0; i < SZ(s); ++i) {
        cout << get_radius_odd(z, i) * 2 - 1;
        if (i + 1 < SZ(s)) cout << " " << get_radius_even(z, i) * 2 << " ";
        else cout << "\n";
    }
}
