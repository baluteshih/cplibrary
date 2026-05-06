#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary"
#include "default_code.hpp"

#include "Convolution/min_plus_convolution_concave.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int &i : a)
        cin >> i;
    for (int &i : b)
        cin >> i;
    auto c = min_plus_convolution_concave(a, b);
    for (int i = 0; i < SZ(c); ++i)
        cout << c[i] << " \n"[i + 1 == SZ(c)];
}
