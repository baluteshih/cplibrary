#define PROBLEM "https://www.luogu.com.cn/problem/P3835"
#define IGNORE
#include "default_code.hpp"

#include "DataStructure/Treap.hpp"

#define POOL_SIZE 30000000
#include "DataStructure/PoolAllocator.hpp"

using treap = Treap<int, size_v, void, false, PoolAllocator, true>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<treap> tree(n + 1);
    for (int i = 1; i <= n; ++i) {
        int v, op, x;
        cin >> v >> op >> x;
        tree[i] = tree[v];
        if (op == 1) {
            auto lft = tree[i].split_key_lt(x);
            tree[i].left_merge(treap(x, 1)).left_merge(lft);
        }
        else if (op == 2) {
            auto lft = tree[i].split_key_lt(x);
            if (!tree[i].empty()) {
                auto it = tree[i].begin();
                if (it->key == x) tree[i].split_size(1);
            }
            tree[i].left_merge(lft);
        }
        else if (op == 3) {
            cout << tree[i].prefix_product_key_lt(x).size() + 1 << "\n"; 
        }
        else if (op == 4) {
            cout << tree[i].kth(x)->key << "\n";
        }
        else if (op == 5) {
            auto lft = tree[i].split_key_lt(x);
            if (!lft.empty()) cout << lft.rbegin()->key << "\n";
            else cout << -2147483647 << "\n";
            tree[i].left_merge(lft);
        }
        else {
            auto it = tree[i].upper_bound(x);
            if (it != tree[i].end()) cout << it->key << "\n";
            else cout << 2147483647 << "\n";
        }
    }
}
