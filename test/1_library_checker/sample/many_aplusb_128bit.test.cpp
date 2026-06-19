#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"
#include "assumption.hpp"

#include "Misc/i128.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int t;
    std::cin >> t;
    while (t--) {
        __int128 a, b;
        std::cin >> a >> b;
        std::cout << a + b << "\n";
    }
}
