#pragma once

template<typename Value = int, typename Tag = void, bool pushdown = true>
class ZkwSegmentTree {
    static constexpr bool hasTag = !std::is_same_v<Tag, void>;
    static_assert(pushdown || hasTag, "Lazy tag must exist when pushdown is false");
    int n, sz, lg;
    std::vector<Value> seg;
    struct Empty {};
    [[no_unique_address]] std::conditional_t<hasTag, std::vector<Tag>, Empty> lazy;
    using SearchTag = std::conditional_t<!pushdown, Tag, Empty>;

    decltype(auto) get_val(int rt) {
        if constexpr (pushdown) return static_cast<const Value&>(seg[rt]);
        else return seg[rt] + lazy[rt];
    }
    decltype(auto) search_val(int rt, const SearchTag &tag) {
        if constexpr (pushdown) return static_cast<const Value&>(seg[rt]);
        else return get_val(rt) + tag;
    }
    void give_tag(int rt, const auto &tag) requires (hasTag) {
        if constexpr (pushdown) seg[rt] = seg[rt] + tag;
        lazy[rt] = lazy[rt] + tag;
    }
    void push(int rt) requires (hasTag && pushdown) {
        give_tag(rt << 1, lazy[rt]);
        give_tag(rt << 1 | 1, lazy[rt]);
        lazy[rt] = Tag();
    }
    void down(int p) requires (hasTag && pushdown) {
        p += n;
        for (int h = lg; h > 0; --h)
            push(p >> h);
    }
    void down(int l, int r) requires (hasTag && pushdown) {
        l += n, r += n;
        for (int h = lg; h > 0; --h) {
            int a = l >> h, b = r >> h;
            push(a);
            if (a != b) push(b);
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

    int descend_left(int rt, const auto &condition) requires (pushdown) {
        while (rt < n) {
            if constexpr (hasTag) push(rt);
            rt <<= 1;
            if (!condition(seg[rt])) ++rt;
        }
        return rt - n;
    }
    int descend_right(int rt, const auto &condition) requires (pushdown) {
        while (rt < n) {
            if constexpr (hasTag) push(rt);
            rt = rt << 1 | 1;
            if (!condition(seg[rt])) --rt;
        }
        return rt - n;
    }
    int range_left_search_iter(int L, int R, const auto &condition) requires (pushdown) {
        if constexpr (hasTag) down(L, R - 1);
        int right[32], rn = 0;
        for (L += n, R += n; L < R; L >>= 1, R >>= 1) {
            if (L & 1) {
                if (condition(seg[L])) return descend_left(L, condition);
                ++L;
            }
            if (R & 1) right[rn++] = --R;
        }
        while (rn--)
            if (condition(seg[right[rn]]))
                return descend_left(right[rn], condition);
        return -1;
    }
    int range_right_search_iter(int L, int R, const auto &condition) requires (pushdown) {
        if constexpr (hasTag) down(L, R - 1);
        int left[32], ln = 0;
        for (L += n, R += n; L < R; L >>= 1, R >>= 1) {
            if (L & 1) left[ln++] = L++;
            if (R & 1) {
                --R;
                if (condition(seg[R])) return descend_right(R, condition);
            }
        }
        while (ln--)
            if (condition(seg[left[ln]]))
                return descend_right(left[ln], condition);
        return -1;
    }
    int range_left_search_rec(int L, int R, int l, int r, int rt, const auto &condition, SearchTag tag) requires (!pushdown) {
        if (R <= l || r <= L) return R;
        if (L <= l && r <= R && !condition(search_val(rt, tag))) return R;
        if (r - l == 1) return l;
        tag = tag + lazy[rt];
        int mid = (l + r) >> 1;
        int res = range_left_search_rec(L, R, l, mid, rt << 1, condition, tag);
        if (res != R) return res;
        return range_left_search_rec(L, R, mid, r, rt << 1 | 1, condition, tag);
    }
    int range_right_search_rec(int L, int R, int l, int r, int rt, const auto &condition, SearchTag tag) requires (!pushdown) {
        if (R <= l || r <= L) return L - 1;
        if (L <= l && r <= R && !condition(search_val(rt, tag))) return L - 1;
        if (r - l == 1) return l;
        tag = tag + lazy[rt];
        int mid = (l + r) >> 1;
        int res = range_right_search_rec(L, R, mid, r, rt << 1 | 1, condition, tag);
        if (res != L - 1) return res;
        return range_right_search_rec(L, R, l, mid, rt << 1, condition, tag);
    }
    void printnode(int rt) {
        int l = rt, r = rt;
        while (l < n) l <<= 1;
        while (r < n) r = r << 1 | 1;
        l -= n, r -= n - 1;
        std::cerr << rt << " [" << l << ", " << r << "): ";
        if constexpr (hasTag) std::cerr << "val = " << seg[rt] << ", tag = " << lazy[rt];
        else std::cerr << seg[rt];
        std::cerr << "\n";
    }
public:
    ZkwSegmentTree(const std::vector<Value> &data):
        n(std::bit_ceil(data.size())), sz(data.size()), lg(std::__lg(n)), seg(n << 1) {
        if constexpr (hasTag) lazy.resize(n << 1);
        std::copy(data.begin(), data.end(), seg.begin() + n);
        for (int i = n - 1; i > 0; --i) up(i);
    }
    ZkwSegmentTree(int size):
        n(std::bit_ceil((unsigned int)size)), sz(size), lg(std::__lg(n)), seg(n << 1) {
        if constexpr (hasTag) lazy.resize(n << 1);
    }
    Value get(int x) {
        assert(0 <= x && x < sz);
        if constexpr (hasTag) {
            if constexpr (pushdown) down(x);
            else return seg[x + n] + tag_prod(x);
        }
        return seg[x + n];
    }
    Value all_prod() {
        return get_val(1);
    }
    Value range_prod(int l, int r) {
        assert(0 <= l && r <= sz);
        assert(l <= r);
        if (l == r) return Value();
        if constexpr (hasTag && pushdown)
            down(l, r - 1);
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
        assert(0 <= x && x < sz);
        if constexpr (hasTag) {
            if constexpr (pushdown) down(x);
            else v = v - tag_prod(x);
        }
        for (seg[x += n] = std::move(v); x > 1; up(x >>= 1));
    }
    void transform(int x, const auto &func) {
        assert(0 <= x && x < sz);
        if constexpr (hasTag && pushdown)
            down(x);
        for (func(seg[x += n]); x > 1; up(x >>= 1));
    }
    void range_transform(int l, int r, const auto &tag) requires (hasTag) {
        assert(0 <= l && r <= sz);
        assert(l <= r);
        if (l < r) {
            if constexpr (pushdown)
                down(l, r - 1);
            int tl = l, tr = r;
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if (l & 1) give_tag(l++, tag);
                if (r & 1) give_tag(--r, tag);
            }
            pull(tl, tr);
        }
    }
    int range_left_search(const auto &condition, int l = -1, int r = -1) {
        if (l == -1 && r == -1) l = 0, r = sz;
        assert(0 <= l && r <= sz);
        assert(l <= r);
        if (l == r) return r;
        if constexpr (pushdown) {
            int res = range_left_search_iter(l, r, condition);
            return res == -1 ? r : res;
        }
        else return range_left_search_rec(l, r, 0, n, 1, condition, SearchTag());
    }
    int range_right_search(const auto &condition, int l = -1, int r = -1) {
        if (l == -1 && r == -1) l = -1, r = sz - 1;
        ++l, ++r;
        assert(0 <= l && r <= sz);
        assert(l <= r);
        if (l == r) return l - 1;
        if constexpr (pushdown) {
            int res = range_right_search_iter(l, r, condition);
            return res == -1 ? l - 1 : res;
        }
        else return range_right_search_rec(l, r, 0, n, 1, condition, SearchTag());
    }
    int descend(const auto &go_left) {
        int rt = 1;
        SearchTag tag = SearchTag();
        while (rt < n) {
            if constexpr (hasTag && pushdown) push(rt);
            if constexpr (!pushdown) tag = tag + lazy[rt];
            int lc = rt << 1, rc = lc | 1;
            rt = go_left(search_val(lc, tag), search_val(rc, tag)) ? lc : rc;
        }
        return rt - n;
    }
    void printinfo(int l, int r) {
        assert(0 <= l && r <= sz);
        assert(l <= r);
        std::cerr << "\e[1;33mInfo [" << l << ", " << r << "):\n";
        if (l < r) {
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if (l & 1) printnode(l++);
                if (r & 1) printnode(--r);
            }
        }
        std::cerr << "\e[0m\n";
    }
    void printall() {
        std::cerr << "\e[1;33mInfo all:\n";
        for (int i = 1; i < n + n; ++i)
            printnode(i);
        std::cerr << "\e[0m\n";
    }
};
