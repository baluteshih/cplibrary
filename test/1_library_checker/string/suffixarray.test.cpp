#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "assumption.hpp"

#include "String/sais.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    std::string s;
    std::cin >> s;
    auto suffix = Suffix(s);
    for (int i = 0; i < int(s.size()); ++i)
        std::cout << suffix.sa[i] << " \n"[i + 1 == int(s.size())];
}
