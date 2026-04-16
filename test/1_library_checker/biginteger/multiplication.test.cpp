#define PROBLEM "https://judge.yosupo.jp/problem/multiplication_of_big_integers"
#include "default_code.hpp"

#include "Misc/bigint.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        BigInteger a, b;
        cin >> a >> b;
        cout << a * b << "\n";
    }
}
