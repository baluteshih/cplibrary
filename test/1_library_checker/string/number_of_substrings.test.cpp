#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "default_code.hpp"

#include "String/sais.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    string s;
    cin >> s;
    auto suffix = Suffix(s);
    ll ans = 0;
    for (int i = 0; i < SZ(s); ++i) {
        ans += i + 1;
        if (i) ans -= suffix.hi[i];
    }
    cout << ans << "\n";
}
