#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include "assumption.hpp"

#include "Convolution/convolution.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<mint> arr(n), brr(m);
    for (auto &i : arr)
        std::cin >> i;
    for (auto &i : brr)
        std::cin >> i;
    arr = convolution(arr, brr);
    for (int i = 0; i < int(arr.size()); ++i)
        std::cout << arr[i] << " \n"[i + 1 == int(arr.size())];
}
