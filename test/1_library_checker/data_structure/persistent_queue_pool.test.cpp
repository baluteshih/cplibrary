#define PROBLEM "http://judge.yosupo.jp/problem/persistent_queue"
#include "assumption.hpp"

#include "DataStructure/PoolAllocator.hpp"
#include "DataStructure/Treap.hpp"

using treap = Treap<int, size_v, void, false, PoolAllocator, true>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int q;
    std::cin >> q;
    std::vector<treap> roots(1, treap());
    while (q--) {
        int op, t;
        std::cin >> op >> t;
        roots.push_back(roots[++t]);
        if (op == 0) {
            int x;
            std::cin >> x;
            roots.back().push_back(treap(x, 1));
        }
        else {
            auto lft = roots.back().split_size(1);
            std::cout << lft.get_key() << "\n";
        }
    }
}
