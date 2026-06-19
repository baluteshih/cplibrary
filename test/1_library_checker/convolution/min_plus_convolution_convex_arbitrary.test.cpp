#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary"
#include "assumption.hpp"

#include "Convolution/min_plus_convolution.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), b(m);
    for (int &i : a)
        std::cin >> i;
    for (int &i : b)
        std::cin >> i;
    auto c = min_plus_convolution(a, b);
    for (int i = 0; i < int(c.size()); ++i)
        std::cout << c[i] << " \n"[i + 1 == int(c.size())];
}
