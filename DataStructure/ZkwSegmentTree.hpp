#pragma once

template<typename Value = int, typename Tag = void, bool pushdown = true>
class ZkwSegmentTree {
    static constexpr bool hasTag = !std::is_same_v<Tag, void>;
    static_assert(pushdown || hasTag, "Lazy tag must exist when pushdown is false");
    int n;
    vector<Value> seg;
    struct Empty {};
    [[no_unique_address]] std::conditional_t<hasTag, std::vector<Tag>, Empty> lazy;
    Value get_val(int rt) {
        if constexpr (pushdown) return seg[rt];
        else return seg[rt] + lazy[rt];
    }
    void give_tag(int rt, auto tag) requires (hasTag) {
        if constexpr (pushdown) seg[rt] = seg[rt] + tag;
        lazy[rt] = lazy[rt] + tag;
    }
    void down(int p) requires (hasTag && pushdown) {
        p += n;
        for (int h = std::__lg(n); h > 0; h--) {
            int i = p >> h;
            give_tag(i << 1, lazy[i]); 
            give_tag(i << 1 | 1, lazy[i]);
            lazy[i] = Tag();
        }
    }
    void up(int p) {
        if constexpr (pushdown) {
            seg[p] = seg[p << 1] + seg[p << 1 | 1];
            if constexpr (hasTag) seg[p] = seg[p] + lazy[p];
        }
        else seg[p] = get_val(p << 1) + get_val(p << 1 | 1);
    }
    void pull(int l, int r) requires (hasTag) {
        l += n, r += n - 1;
        for (l >>= 1, r >>= 1; l != r; l >>= 1, r >>= 1)
            up(l), up(r);
        for (; l >= 1; l >>= 1)
            up(l);
    }
    auto tag_prod(int p) requires (!pushdown) {
        Tag res = Tag();
        for (p += n; p >= 1; p >>= 1)
            res = res + lazy[p];
        return res;
    }
    void printnode(int rt) {
        int l = rt, r = rt;
        while (l < n) l <<= 1;
        while (r < n) r = r << 1 | 1;
        l -= n, r -= n - 1;
        std::cerr << rt<< " [" << l << ", " << r << "): ";
        if constexpr (hasTag) std::cerr << "val = " << seg[rt] << ", tag = " << lazy[rt];
        else std::cerr << seg[rt];
        std::cerr << "\n";
    }
    static int ceilpow2(int sz) {
        int m = 1;
        while (m < sz) m <<= 1;
        return m;
    }
public:
    ZkwSegmentTree(const vector<Value> &data): n(ceilpow2(data.size())), seg(n << 1) { 
        if constexpr (hasTag) lazy.resize(n << 1); 
        for (int i = 0; i < int(data.size()); ++i) seg[i + n] = data[i];
        for (int i = n - 1; i > 0; --i) up(i);
    }
    ZkwSegmentTree(int size): ZkwSegmentTree(vector<Value>(size)) {}
    Value get(int x) {
        assert(0 <= x && x < n);
        if constexpr (hasTag) {
            if constexpr (pushdown) down(x);
            else return seg[x + n] + tag_prod(x); 
        }
        return seg[x + n];
    }
    Value range_prod(int l, int r) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l == r) return Value();
        if constexpr (hasTag && pushdown)
            down(l), down(r - 1);
        Value resl = Value(), resr = Value();
        int tl = l + n, tr = r + n - 1;
        bool l_valid = false, r_valid = false;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = resl + get_val(l++), l_valid = true;
            if (r & 1) resr = get_val(--r) + resr, r_valid = true;
            if constexpr (!pushdown) {
                tl >>= 1, tr >>= 1;
                if (l_valid) resl = resl + lazy[tl];
                if (r_valid) resr = resr + lazy[tr];
            }
        }
        if constexpr (!pushdown) {
            for (tl >>= 1, tr >>= 1; tl >= 1; tl >>= 1, tr >>= 1) {
                if (l_valid) resl = resl + lazy[tl];
                if (r_valid) resr = resr + lazy[tr];
            }
        }
        return resl + resr;
    }
    void modify(int x, Value v) {
        assert(0 <= x && x < n);
        if constexpr (hasTag) {
            if constexpr (pushdown) down(x);
            else v = v - tag_prod(x); 
        }
        for (seg[x += n] = v; x > 1; up(x >>= 1));
    }
    void transform(int x, const auto &func) {
        assert(0 <= x && x < n);
        if constexpr (hasTag && pushdown)
            down(x);
        for (func(seg[x += n]); x > 1; up(x >>= 1));
    }
    void range_transform(int l, int r, const auto &tag) requires (hasTag) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l < r) {
            if constexpr (hasTag && pushdown)
                down(l), down(r - 1);
            int tl = l, tr = r;
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if (l & 1) give_tag(l++, tag);
                if (r & 1) give_tag(--r, tag);
            }
            pull(tl, tr);
        }
    }
    void printinfo(int l, int r) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        std::cerr << "\e[1;33mInfo [" << l << ", " << r << "):\n";
        if (l < r) {
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if (l & 1) printnode(l++);
                if (r & 1) printnode(--r);
            }
        }
        cerr << "\e[0m\n";
    }
    void printall() {
        std::cerr << "\e[1;33mInfo all:\n";
        for (int i = 1; i < n + n; ++i)
            printnode(i);
        cerr << "\e[0m\n";
    }
};
