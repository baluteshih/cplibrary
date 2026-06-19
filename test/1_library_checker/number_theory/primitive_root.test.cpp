#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"
#include "default_code.hpp"

#include "Numeric/primitive_root.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int q;
    std::cin >> q;
    while (q--) {
        long long p;
        std::cin >> p;
        std::cout << primitive_root(p) << "\n";
    }
}
