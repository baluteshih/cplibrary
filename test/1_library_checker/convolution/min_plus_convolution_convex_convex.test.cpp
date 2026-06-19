#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex"
#include "assumption.hpp"

#include "Sequence/SMAWK.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), b(m);
    for (int &i : a)
        std::cin >> i;
    for (int &i : b)
        std::cin >> i;
    auto f = [&](int i, int j) {
        if (0 <= i - j && i - j < n)
            return b[j] + a[i - j];
        return 2100000000 + (i - j); 
    };
    auto c = SMAWK(n + m - 1, m, f);
    for (int i = 0; i < int(c.size()); ++i)
        std::cout << f(i, c[i]) << " \n"[i + 1 == int(c.size())];
}
