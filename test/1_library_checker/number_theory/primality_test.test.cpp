#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"
#include "assumption.hpp"

#include "Numeric/miller_rabin.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int q;
    std::cin >> q;
    while (q--) {
        long long n;
        std::cin >> n;
        if (miller_rabin(n)) std::cout << "Yes\n";
        else std::cout << "No\n";
    }
}
