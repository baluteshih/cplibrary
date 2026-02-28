#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"
#include "default_code.hpp"

#include "Numeric/miller_rabin.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int q;
    cin >> q;
    while (q--) {
        ll n;
        cin >> n;
        if (miller_rabin(n)) cout << "Yes\n";
        else cout << "No\n";
    }
}
