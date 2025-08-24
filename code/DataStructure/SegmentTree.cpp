#ifndef __BALU_SEGMENT_TREE__
#define __BALU_SEGMENT_TREE__
template<class Value = int, 
         Value (*operation)(Value, Value) = [](Value a, Value b) { return a + b; },
         Value (*identity)() = []() { return Value(); }>
class SegTree {
    int n;
    vector<Value> seg;
    void up(int rt) {
        seg[rt] = operation(seg[rt << 1], seg[rt << 1 | 1]);
    }
    void initialize(int l, int r, int rt, const vector<Value> &data) {
        if (r - l == 1) 
            return seg[rt] = data[l], void();
        int mid = (l + r) >> 1;
        initialize(l, mid, rt << 1, data);
        initialize(mid, r, rt << 1 | 1, data);
        up(rt);
    }
    Value range_prod(int L, int R, int l, int r, int rt) {
        if (L <= l && R >= r)
            return seg[rt];
        int mid = (l + r) >> 1;
        if (R <= mid) return range_prod(L, R, l, mid, rt << 1);
        if (L >= mid) return range_prod(L, R, mid, r, rt << 1 | 1);
        return operation(range_prod(L, R, l, mid, rt << 1), range_prod(L, R, mid, r, rt << 1 | 1));
    }
    void modify(int x, int l, int r, int rt, const Value &v) {
        if (r - l == 1)
            return seg[rt] = v;
        int mid = (l + r) >> 1;
        if (x < mid) modify(x, l, mid, rt << 1, v);
        else modify(x, mid, r, rt << 1 | 1, v);
        up(rt);
    }
public:
    SegTree(const vector<Value> &data): n(data.size()), seg(n << 2) { initialize(0, n, 1, data); }
    SegTree(int size): SegTree(vector<Value>(size, identity())) {}
    Value range_prod(int l, int r) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l == r) return identity();
        return range_prod(l, r, 0, n, 1);
    }
    void modify(int x, const Value &v) {
        assert(0 <= x && x < n);
        modify(x, 0, n, 1, v);
    }
};
#endif // __BALU_SEGMENT_TREE__

struct Value {
    int x;
    Value(int _x = 0): x(_x) {}
    Value operator+(const Value &rhs) {
        return Value(min(x, rhs.x));
    }
};
