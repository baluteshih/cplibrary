#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum_large_array"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"
#include "DataStructure/PointerSegmentTree.hpp"

using mint = modint998244353;

struct Tag {
    mint a, b;
    Tag(mint _a = 1, mint _b = 0): a(_a), b(_b) {}
    Tag operator+(const Tag &rhs) {
        return Tag(a * rhs.a, rhs.a * b + rhs.b);
    }
};

struct Value {
    mint mul;
    int add;
    Value(mint a = 0, int b = 1): mul(a), add(b) {}
    Value operator+(const Value &rhs) {
        return Value(mul + rhs.mul, add + rhs.add);
    }
    Value operator+(const Tag &tag) {
        return Value(tag.a * mul + tag.b * add, add);
    }
    static Value get(int l, int r) {
        return Value(0, r - l);
    }
    friend std::ostream& operator<<(std::ostream& os, const Value &v) {
        os << v.mul;
        return os;
    }
};


int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    PointerSegmentTree<Value, Tag, true, DefaultAllocator, true> seg(n);
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int l, r;
            Tag tag;
            std::cin >> l >> r >> tag.a >> tag.b;
            seg.range_transform(l, r, tag);
        }
        else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg.range_prod(l, r) << "\n";
        }
    }
}
