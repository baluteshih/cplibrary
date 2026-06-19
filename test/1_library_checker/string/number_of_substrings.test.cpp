#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "assumption.hpp"

#include "String/sais.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    std::string s;
    std::cin >> s;
    auto suffix = Suffix(s);
    long long ans = 0;
    for (int i = 0; i < int(s.size()); ++i) {
        ans += i + 1;
        if (i) ans -= suffix.hi[i];
    }
    std::cout << ans << "\n";
}
