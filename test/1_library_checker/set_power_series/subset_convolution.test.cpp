#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"
#include "Convolution/subset_convolution.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    n = 1 << n;
    vector<mint> arr(n), brr(n);
    for (auto &i : arr)
        cin >> i;
    for (auto &i : brr)
        cin >> i;
    auto crr = subset_convolution(arr, brr);
    for (int i = 0; i < n; ++i)
        cout << crr[i] << " \n"[i + 1 == n]; 
}
