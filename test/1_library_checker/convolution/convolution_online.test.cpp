#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include "assumption.hpp"

#include "Convolution/OnlineConvolution.hpp"

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
    arr.resize(n + m - 1);
    brr.resize(n + m - 1);
    OnlineConvolution<mint> conv;
    for (int i = 0; i < n + m - 1; ++i)
        std::cout << conv.query(i, arr[i], brr[i]) << " \n"[i + 1 == int(arr.size())];
}
