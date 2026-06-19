#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "assumption.hpp"

#include "String/z_algo.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    std::string s;
    std::cin >> s;
    auto z = make_z(s);
    for (int i = 0; i < int(s.size()); ++i)
        std::cout << z[i] << " \n"[i + 1 == int(s.size())];
}
