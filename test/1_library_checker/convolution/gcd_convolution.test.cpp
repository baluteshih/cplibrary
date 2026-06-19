#define PROBLEM "https://judge.yosupo.jp/problem/gcd_convolution"
#include "assumption.hpp"

#include "Convolution/gcd_convolution.hpp"
#include "Numeric/Modint.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<mint> arr(n), brr(n);
    for (auto &i : arr) std::cin >> i;
    for (auto &i : brr) std::cin >> i;
    arr.insert(arr.begin(), 0), brr.insert(brr.begin(), 0);
    auto res = gcd_convolution(arr, brr);
    for (int i = 1; i <= n; ++i)
        std::cout << res[i] << " \n"[i == n]; 
}
