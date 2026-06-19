#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"
#include "assumption.hpp"

#include "DataStructure/Treap.hpp"

using treap = Treap<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    treap tree;

    auto insert = [&](int x) {
        auto lft = tree.split_key_lt(x);
        if (!tree.empty() && tree.begin()->key == x)
            return tree.left_merge(lft), false;
        return tree.left_merge(treap(x, 1)).left_merge(lft), true;
    };
    
    auto erase = [&](int x) {
        auto lft = tree.split_key_lt(x);
        if (tree.empty() || tree.begin()->key != x)
            return tree.left_merge(lft), false;
        tree.split_size(1).destruct();
        return tree.left_merge(lft), true;
    };

    while (n--) {
        int x;
        std::cin >> x;
        insert(x);
    }
    while (q--) {
        int op, x;
        std::cin >> op >> x;
        if (op == 0) insert(x);
        else if (op == 1) erase(x);
        else if (op == 2) {
            if (tree.size() < x) std::cout << "-1\n";
            else std::cout << tree.kth(x - 1)->key << "\n";
        }
        else if (op == 3) {
            std::cout << tree.prefix_product_key_leq(x) << "\n";
        }
        else if (op == 4) {
            auto it = tree.upper_bound(x);
            if (it == tree.begin()) std::cout << "-1\n";
            else std::cout << std::prev(it)->key << "\n";
        }
        else {
            auto it = tree.lower_bound(x);
            if (it == tree.end()) std::cout << "-1\n";
            else std::cout << it->key << "\n";
        }
    }
}
