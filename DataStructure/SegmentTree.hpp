#ifndef __BALU_SEGMENT_TREE__
#define __BALU_SEGMENT_TREE__
template<typename Value = int, typename Tag = void>
class SegmentTree {
    static constexpr bool hasTag = !std::is_same_v<Tag, void>;
    int n;
    vector<Value> seg;
    struct Empty {};
    [[no_unique_address]] std::conditional_t<hasTag, std::vector<Tag>, Empty> lazy;
    void up(int rt) {
        seg[rt] = seg[rt << 1] + seg[rt << 1 | 1];
    }
    void give_tag(int rt, Tag tag) requires (hasTag) {
        seg[rt] = seg[rt] + tag;
        lazy[rt] = lazy[rt] + tag;
    }
    void down(int rt) requires (hasTag) {
        give_tag(rt << 1, lazy[rt]);
        give_tag(rt << 1 | 1, lazy[rt]);
        lazy[rt] = Tag();
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
        if constexpr (hasTag) down(rt);
        int mid = (l + r) >> 1;
        if (R <= mid) return range_prod(L, R, l, mid, rt << 1);
        if (L >= mid) return range_prod(L, R, mid, r, rt << 1 | 1);
        return range_prod(L, R, l, mid, rt << 1) + range_prod(L, R, mid, r, rt << 1 | 1); 
    }
    void modify(int x, int l, int r, int rt, const Value &v) {
        if (r - l == 1)
            return seg[rt] = v, void();
        if constexpr (hasTag) down(rt);
        int mid = (l + r) >> 1;
        if (x < mid) modify(x, l, mid, rt << 1, v);
        else modify(x, mid, r, rt << 1 | 1, v);
        up(rt);
    }
    void transform(int x, int l, int r, int rt, const auto &func) {
        if (r - l == 1)
            return func(seg[rt]), void();
        if constexpr (hasTag) down(rt);
        int mid = (l + r) >> 1;
        if (x < mid) transform(x, l, mid, rt << 1, func);
        else transform(x, mid, r, rt << 1 | 1, func);
        up(rt);
    }
    void range_transform(int L, int R, int l, int r, int rt, const Tag &tag) requires (hasTag) {
        if (L <= l && R >= r)
            return give_tag(rt, tag);
        down(rt);
        int mid = (l + r) >> 1;
        if (L < mid) range_transform(L, R, l, mid, rt << 1, tag);
        if (R > mid) range_transform(L, R, mid, r, rt << 1 | 1, tag);
        up(rt);
    }
    Value get(int x, int l, int r, int rt) {
        while (r - l > 1) {
            if constexpr (hasTag) down(rt);
            int mid = (l + r) >> 1;
            if (x < mid) r = mid, rt = rt << 1;
            else l = mid, rt = rt << 1 | 1;
        }
        return seg[rt];
    }
public:
    SegmentTree(const vector<Value> &data): n(data.size()), seg(n << 2) { 
        if constexpr (hasTag) lazy.resize(n << 2); 
        initialize(0, n, 1, data);
    }
    SegmentTree(int size): SegmentTree(vector<Value>(size)) {}
    Value get(int x) {
        assert(0 <= x && x < n);
        return get(x, 0, n, 1);
    }
    Value range_prod(int l, int r) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l == r) return Value();
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
    void range_transform(int l, int r, const Tag &tag) requires (hasTag) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l < r)
            range_transform(l, r, 0, n, 1, tag);
    }
};
#endif // __BALU_SEGMENT_TREE__
