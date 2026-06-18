#define PROBLEM "https://judge.yosupo.jp/problem/lcm_convolution"
#include "default_code.hpp"

#include "Convolution/lcm_convolution.hpp"
#include "Numeric/Modint.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<mint> arr(n), brr(n);
    for (auto &i : arr) cin >> i;
    for (auto &i : brr) cin >> i;
    arr.insert(arr.begin(), 0), brr.insert(brr.begin(), 0);
    auto res = lcm_convolution(arr, brr);
    for (int i = 1; i <= n; ++i)
        cout << res[i] << " \n"[i == n]; 
}
