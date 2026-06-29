#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"
#include "assumption.hpp"

#include "Sequence/occur_position.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> arr(n);
    for (int &i : arr) std::cin >> i;
    auto pos = occur_position(arr);
    while (q--) {
        int l, r, x;
        std::cin >> l >> r >> x;
        auto it = pos.find(x);
        if (it == pos.end()) std::cout << "0\n";
        else std::cout << std::ranges::lower_bound(it->second, r) - std::ranges::lower_bound(it->second, l) << "\n"; 
    }
}
