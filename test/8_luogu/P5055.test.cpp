#define PROBLEM "https://www.luogu.com.cn/problem/P5055"
#define IGNORE
#include "assumption.hpp"

#include "DataStructure/Treap.hpp"

#define POOL_SIZE 17000000
#include "DataStructure/PoolAllocator.hpp"

struct Value {
    long long sum;
    int sz;
    Value(long long x = 0, int sz_ = 0): sum(x), sz(sz_) {}
    Value operator+(const Value &rhs) const {
        return Value(sum + rhs.sum, sz + rhs.sz);
    }
    int size() const {
        return sz; 
    }
    friend std::ostream& operator<<(std::ostream& os, const Value &v) {
        os << v.sum << " " << v.sz;
        return os;
    }
};

using treap = Treap<void, Value, void, true, PoolAllocator, true>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<treap> tree(n + 1);
    long long lastans = 0;
    for (int i = 1; i <= n; ++i) {
        int v, op;
        std::cin >> v >> op;
        tree[i] = tree[v];
        if (op == 1) {
            long long p, x;
            std::cin >> p >> x;
            p ^= lastans, x ^= lastans;
            auto lft = tree[i].split_size(p);
            tree[i].left_merge(treap(Value(x, 1))).left_merge(lft);
        }
        else if (op == 2) {
            long long p;
            std::cin >> p;
            p ^= lastans;
            auto lft = tree[i].split_size(p - 1);
            tree[i].split_size(1);
            tree[i].left_merge(lft);
        }
        else if (op == 3) {
            long long l, r;
            std::cin >> l >> r;
            l ^= lastans, r ^= lastans;
            --l;
            tree[i].range_reverse(l, r);
        }
        else {
            long long l, r;
            std::cin >> l >> r;
            l ^= lastans, r ^= lastans;
            --l;
            lastans = tree[i].range_prod(l, r).sum;
            std::cout << lastans << "\n";
        }
    }
}
