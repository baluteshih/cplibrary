#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"
#include "Convolution/and_convolution.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    n = 1 << n;
    std::vector<mint> arr(n), brr(n);
    for (auto &i : arr)
        std::cin >> i;
    for (auto &i : brr)
        std::cin >> i;
    auto crr = and_convolution(arr, brr);
    for (int i = 0; i < n; ++i)
        std::cout << crr[i] << " \n"[i + 1 == n]; 
}
