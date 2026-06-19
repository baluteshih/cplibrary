#define PROBLEM "https://judge.yosupo.jp/problem/range_add_range_min"
#include "assumption.hpp"

#include "DataStructure/SegmentTree.hpp"

struct Tag {
    long long a;
    Tag(long long _a = 0): a(_a) {}
    Tag operator+(const Tag &rhs) {
        return Tag(a + rhs.a);
    }
};

struct Value {
    long long val;
    Value(long long _val = 1e18): val(_val) {}
    Value operator+(const Value &rhs) {
        return Value(std::min(val, rhs.val));
    }
    Value operator+(const Tag &tag) {
        return Value(val + tag.a);
    }
    Value operator-(const Tag &tag) {
        return Value(val - tag.a);
    }
    friend std::ostream& operator<<(std::ostream& os, const Value &v) {
        os << v.val;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Value &v) {
        is >> v.val;
        return is;
    }
};

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<Value> arr(n);
    for (auto &v : arr)
        std::cin >> v;
    SegmentTree<Value, Tag, false> seg(arr);
    while (q--) {
        int type, l, r;
        std::cin >> type >> l >> r;
        if (type == 0) {
            int x;
            std::cin >> x;
            seg.range_transform(l, r, Tag(x));
        }
        else {
            std::cout << seg.range_prod(l, r) << "\n";
        }
    }
}
