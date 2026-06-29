#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"
#include "assumption.hpp"

#include "Numeric/pi_count.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    long long n;
    std::cin >> n;
    std::cout << pi_count(n) << "\n";
}
