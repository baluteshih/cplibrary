#pragma once

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
    void give_tag(int rt, auto tag) requires (hasTag) {
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
    void range_transform(int L, int R, int l, int r, int rt, const auto &tag) requires (hasTag) {
        if (L <= l && R >= r)
            return give_tag(rt, tag);
        down(rt);
        int mid = (l + r) >> 1;
        if (L < mid) range_transform(L, R, l, mid, rt << 1, tag);
        if (R > mid) range_transform(L, R, mid, r, rt << 1 | 1, tag);
        up(rt);
    }
    void range_transform_beats(int L, int R, int l, int r, int rt, const auto &tag, const auto &tag_condition) requires (hasTag) {
        if (L <= l && R >= r && tag_condition(seg[rt]))
            return give_tag(rt, tag);
        assert(r - l > 1);
        down(rt);
        int mid = (l + r) >> 1;
        if (L < mid) range_transform_beats(L, R, l, mid, rt << 1, tag, tag_condition);
        if (R > mid) range_transform_beats(L, R, mid, r, rt << 1 | 1, tag, tag_condition);
        up(rt);
    }
    int range_left_search(int L, int R, int l, int r, int rt, const auto &condition) {
        if (r - l == 1) {
            if (!condition(seg[rt])) return R;
            return l;
        }
        int mid = (l + r) >> 1;
        if constexpr (hasTag) down(rt);
        if (L <= l && R >= r) {
            if (condition(seg[rt << 1])) return range_left_search(L, R, l, mid, rt << 1, condition);
            return range_left_search(L, R, mid, r, rt << 1 | 1, condition);
        }
        int left = R;
        if (L < mid) left = range_left_search(L, R, l, mid, rt << 1, condition);
        if (left == R) {
            if (R > mid) return range_left_search(L, R, mid, r, rt << 1 | 1, condition);
            return R;
        }
        return left;
    }
    int range_right_search(int L, int R, int l, int r, int rt, const auto &condition) {
        if (r - l == 1) {
            if (!condition(seg[rt])) return L - 1;
            return l;
        }
        int mid = (l + r) >> 1;
        if constexpr (hasTag) down(rt);
        if (L <= l && R >= r) {
            if (condition(seg[rt << 1 | 1])) return range_right_search(L, R, mid, r, rt << 1 | 1, condition);
            return range_right_search(L, R, l, mid, rt << 1, condition);
        }
        int right = L - 1;
        if (R > mid) right = range_right_search(L, R, mid, r, rt << 1 | 1, condition);
        if (right == L - 1) {
            if (L < mid) return range_right_search(L, R, l, mid, rt << 1, condition);
            return L - 1;
        }
        return right;
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
    void printnode(int l, int r, int rt) {
        std::cerr << "[" << l << ", " << r << "): ";
        if constexpr (hasTag) std::cerr << "val = " << seg[rt] << ", tag = " << lazy[rt];
        else std::cerr << seg[rt];
        std::cerr << "\n";
    }
    void printinfo(int L, int R, int l, int r, int rt) {
        printnode(l, r, rt);
        if (L <= l && R >= r)
            return;
        int mid = (l + r) >> 1;
        if (L < mid) printinfo(L, R, l, mid, rt << 1);
        if (R > mid) printinfo(L, R, mid, r, rt << 1 | 1);
    }
    void printall(int l, int r, int rt) {
        printnode(l, r, rt);
        if (r - l == 1) return;
        int mid = (l + r) >> 1;
        printall(l, mid, rt << 1);
        printall(mid, r, rt << 1 | 1);
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
    void range_transform(int l, int r, const auto &tag) requires (hasTag) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l < r)
            range_transform(l, r, 0, n, 1, tag);
    }
    void range_transform_beats(int l, int r, const auto &tag, const auto &tag_condition) requires (hasTag) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l < r)
            range_transform_beats(l, r, 0, n, 1, tag, tag_condition);
    }
    /*
    For the given element range [l, r)
    Perform segment tree binary search within the range with left half first 
    */
    int range_left_search(const auto &condition, int l = -1, int r = -1) {
        if (l == -1 && r == -1) l = 0, r = n;
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l == r) return r;
        return range_left_search(l, r, 0, n, 1, condition);
    }
    /*
    For the given element range (l, r]
    Perform segment tree binary search within the range with right half first 
    */
    int range_right_search(const auto &condition, int l = -1, int r = -1) {
        if (l == -1 && r == -1) l = -1, r = n - 1;
        ++l, ++r;
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l == r) return l - 1;
        return range_right_search(l, r, 0, n, 1, condition);
    }
    void printinfo(int l, int r) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        std::cerr << "\e[1;33mInfo [" << l << ", " << r << "):\n";
        if (l < r) 
            printinfo(l, r, 0, n, 1);
        cerr << "\e[0m\n";
    }
    void printall() {
        std::cerr << "\e[1;33mInfo all:\n";
        printall(0, n, 1);
        cerr << "\e[0m\n";
    }
};
