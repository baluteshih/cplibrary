#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex"
#include "default_code.hpp"

#include "Sequence/SMAWK.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int &i : a)
        cin >> i;
    for (int &i : b)
        cin >> i;
    auto f = [&](int i, int j) {
        if (0 <= i - j && i - j < n)
            return b[j] + a[i - j];
        return 2100000000 + (i - j); 
    };
    auto c = SMAWK(n + m - 1, m, f);
    for (int i = 0; i < SZ(c); ++i)
        cout << f(i, c[i]) << " \n"[i + 1 == SZ(c)];
}
