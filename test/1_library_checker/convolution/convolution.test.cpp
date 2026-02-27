#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include "default_code.hpp"

#include "Polynomial/NTT.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<mint> arr(n), brr(m);
    for (auto &i : arr)
        cin >> i;
    for (auto &i : brr)
        cin >> i;
    arr = NTT<mint>::convolution(arr, brr);
    for (int i = 0; i < SZ(arr); ++i)
        cout << arr[i] << " \n"[i + 1 == SZ(arr)];
}
