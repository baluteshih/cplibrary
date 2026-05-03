#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"
#include "default_code.hpp"

#include "Misc/i128.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        __int128 a, b;
        cin >> a >> b;
        cout << a + b << "\n";
    }
}
