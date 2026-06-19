#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"
#include "Convolution/convolution.hpp"

using mint = modint1000000007;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<mint> a(n), b(m);
    for (auto &i : a)
        std::cin >> i;
    for (auto &i : b)
        std::cin >> i;
    auto c = convolution<3>(a, b);
    for (int i = 0; i < int(c.size()); ++i)
        std::cout << c[i] << " \n"[i + 1 == int(c.size())]; 
}
