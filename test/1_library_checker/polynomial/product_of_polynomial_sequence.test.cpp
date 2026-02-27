#define PROBLEM "https://judge.yosupo.jp/problem/product_of_polynomial_sequence"
#include "default_code.hpp"

#include "Polynomial/Polynomial.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<Poly_t> arr(n);
    for (auto &poly : arr) {
        int k;
        cin >> k;
        poly.resize(k + 1);
        for (auto &i : poly)
            cin >> i;
    }
    arr.push_back(Poly_t(1, 1));
    ++n;
    auto dq = [&](auto _dq, int l, int r) -> Poly_t {
        if (l == r) return arr[l];
        int mid = (l + r) >> 1;
        return _dq(_dq, l, mid) * _dq(_dq, mid + 1, r);
    };

    auto res = dq(dq, 0, n - 1);
    for (int i = 0; i < SZ(res); ++i)
        cout << res[i] << " \n"[i + 1 == SZ(res)]; 
}
