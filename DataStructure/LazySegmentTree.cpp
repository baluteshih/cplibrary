#include "DataStructure/SegmentTree.hpp"

struct Tag {
    int a;
    Tag(int _a = 0): a(_a) {}
    Tag operator+(const Tag &rhs) {
        return Tag(a + rhs.a);
    }
};

struct Value {
    int val;
    Value(int _val = 0): val(_val) {}
    Value operator+(const Value &rhs) {
        return Value(min(val, rhs.val));
    }
    Value operator+(const Tag &tag) {
        return Value(val + tag.a);
    }
    friend ostream& operator<<(ostream& os, const Value &v) {
        os << v.val;
        return os;
    }
    friend istream& operator>>(istream& is, Value &v) {
        is >> v.val;
        return is;
    }
};

// SegmentTree<Value, Tag> seg;
