#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "assumption.hpp"

#include "string/manacher.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    std::string s;
    std::cin >> s;
    auto z = manacher(s);
    for (int i = 0; i < int(s.size()); ++i) {
        std::cout << get_radius_odd(z, i) * 2 - 1;
        if (i + 1 < int(s.size())) std::cout << " " << get_radius_even(z, i) * 2 << " ";
        else std::cout << "\n";
    }
}
