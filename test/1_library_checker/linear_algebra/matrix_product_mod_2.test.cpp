#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"
#include "assumption.hpp"
#include "pragma.hpp"

#include "Matrix/MatrixF2.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m, k;
    std::cin >> n >> m >> k;
    MatrixF2 A(n, m), B(m, k);
    for (auto &v : A) {
        std::string s;
        std::cin >> s;
        std::ranges::reverse(s);
        v = DynamicBitset(s);
    }
    for (auto &v : B) {
        std::string s;
        std::cin >> s;
        std::ranges::reverse(s);
        v = DynamicBitset(s);
    }
    auto C = A * B;
    for (auto &v : C) {
        std::string s = v.to_string();
        std::ranges::reverse(s);
        std::cout << s << "\n"; 
    }
}
