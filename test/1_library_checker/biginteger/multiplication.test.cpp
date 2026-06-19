#define PROBLEM "https://judge.yosupo.jp/problem/multiplication_of_big_integers"
#include "assumption.hpp"

#include "Misc/bigint.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int t;
    std::cin >> t;
    while (t--) {
        BigInteger a, b;
        std::cin >> a >> b;
        std::cout << a * b << "\n";
    }
}
