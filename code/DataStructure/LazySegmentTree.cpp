#ifndef __BALU_LAZY_SEGMENT_TREE__
#define __BALU_LAZY_SEGMENT_TREE__
template<class Value = int, 
         class Tag = int,
         Value (*operation)(Value, Value) = [](Value a, Value b) { return a + b; },
         Value (*identity)() = []() { return Value(); },
         Value (*apply)(Value, Tag) = [](Value a, Tag tag) { return a + tag; },
         Tag (*compose)(Tag, Tag) = [](Tag a, Tag b) { return a + b; },
         Tag (*zerotag)() = []() { return Tag(); }
         >
class LazySegTree {
    int n;
    vector<Value> seg;
    vector<Tag> lazy;
    void up(int rt) {
        seg[rt] = operation(seg[rt << 1], seg[rt << 1 | 1]);
    }
    void give_tag(int rt, Tag tag) {
        seg[rt] = apply(seg[rt], tag);
        lazy[rt] = compose(lazy[rt], tag);
    }
    void down(int rt) {
        give_tag(rt << 1, lazy[rt]);
        give_tag(rt << 1 | 1, lazy[rt]);
        lazy[rt] = zerotag();
    }
    void initialize(int l, int r, int rt, const vector<Value> &data) {
        if (r - l == 1) 
            return seg[rt] = data[l], void();
        int mid = (l + r) >> 1;
        initialize(l, mid, rt << 1, data);
        initialize(mid, r, rt << 1 | 1, data);
        up(rt);
    }
    Value get(int x, int l, int r, int rt) {
        if (r - l == 1)
            return seg[rt];
        down(rt);
        int mid = (l + r) >> 1;
        if (x < mid) return get(x, l, mid, rt << 1);
        return get(x, mid, r, rt << 1 | 1);
    }
    Value range_prod(int L, int R, int l, int r, int rt) {
        if (L <= l && R >= r)
            return seg[rt];
        down(rt);
        int mid = (l + r) >> 1;
        if (R <= mid) return range_prod(L, R, l, mid, rt << 1);
        if (L >= mid) return range_prod(L, R, mid, r, rt << 1 | 1);
        return operation(range_prod(L, R, l, mid, rt << 1), range_prod(L, R, mid, r, rt << 1 | 1));
    }
    void modify(int x, int l, int r, int rt, const Value &v) {
        if (r - l == 1)
            return seg[rt] = v, void();
        down(rt);
        int mid = (l + r) >> 1;
        if (x < mid) modify(x, l, mid, rt << 1, v);
        else modify(x, mid, r, rt << 1 | 1, v);
        up(rt);
    }
    void transform(int x, int l, int r, int rt, const auto &func) {
        if (r - l == 1)
            return seg[rt] = func(seg[rt]), void();
        down(rt);
        int mid = (l + r) >> 1;
        if (x < mid) transform(x, l, mid, rt << 1, func);
        else transform(x, mid, r, rt << 1 | 1, func);
        up(rt);
    }
    void range_transform(int L, int R, int l, int r, int rt, const Tag &tag) {
        if (L <= l && R >= r)
            return give_tag(rt, tag);
        down(rt);
        int mid = (l + r) >> 1;
        if (L < mid) range_transform(L, R, l, mid, rt << 1, tag);
        if (R > mid) range_transform(L, R, mid, r, rt << 1 | 1, tag);
        up(rt);
    }
public:
    LazySegTree(const vector<Value> &data): n(data.size()), seg(n << 2), lazy(n << 2, zerotag()) { initialize(0, n, 1, data); }
    LazySegTree(int size): LazySegTree(vector<Value>(size, identity())) {}
    Value get(int x) {
        assert(0 <= x && x < n);
        return get(x, 0, n, 1);
    }
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
    void transform(int x, const auto &func) {
        assert(0 <= x && x < n);
        transform(x, 0, n, 1, func);
    }
    void range_transform(int l, int r, const Tag &tag) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l < r)
            range_transform(l, r, 0, n, 1, tag);
    }
};

#endif // __BALU_SEGMENT_TREE__

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
