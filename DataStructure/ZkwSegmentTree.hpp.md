---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_add_range_min_zkw.test.cpp
    title: test/1_library_checker/data_structure/range_add_range_min_zkw.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_add_range_min_zkw2.test.cpp
    title: test/1_library_checker/data_structure/range_add_range_min_zkw2.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/data_structure/static_rmq_zkw.test.cpp
    title: test/1_library_checker/data_structure/static_rmq_zkw.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/ZkwSegmentTree.hpp\"\n\ntemplate<typename\
    \ Value = int, typename Tag = void, bool pushdown = true>\nclass ZkwSegmentTree\
    \ {\n    static constexpr bool hasTag = !std::is_same_v<Tag, void>;\n    static_assert(pushdown\
    \ || hasTag, \"Lazy tag must exist when pushdown is false\");\n    int n, sz,\
    \ lg;\n    std::vector<Value> seg;\n    struct Empty {};\n    [[no_unique_address]]\
    \ std::conditional_t<hasTag, std::vector<Tag>, Empty> lazy;\n    using SearchTag\
    \ = std::conditional_t<!pushdown, Tag, Empty>;\n\n    decltype(auto) get_val(int\
    \ rt) {\n        if constexpr (pushdown) return static_cast<const Value&>(seg[rt]);\n\
    \        else return seg[rt] + lazy[rt];\n    }\n    decltype(auto) search_val(int\
    \ rt, const SearchTag &tag) {\n        if constexpr (pushdown) return static_cast<const\
    \ Value&>(seg[rt]);\n        else return get_val(rt) + tag;\n    }\n    void give_tag(int\
    \ rt, const auto &tag) requires (hasTag) {\n        if constexpr (pushdown) seg[rt]\
    \ = seg[rt] + tag;\n        lazy[rt] = lazy[rt] + tag;\n    }\n    void push(int\
    \ rt) requires (hasTag && pushdown) {\n        give_tag(rt << 1, lazy[rt]);\n\
    \        give_tag(rt << 1 | 1, lazy[rt]);\n        lazy[rt] = Tag();\n    }\n\
    \    void down(int p) requires (hasTag && pushdown) {\n        p += n;\n     \
    \   for (int h = lg; h > 0; --h)\n            push(p >> h);\n    }\n    void down(int\
    \ l, int r) requires (hasTag && pushdown) {\n        l += n, r += n;\n       \
    \ for (int h = lg; h > 0; --h) {\n            int a = l >> h, b = r >> h;\n  \
    \          push(a);\n            if (a != b) push(b);\n        }\n    }\n    void\
    \ up(int p) {\n        if constexpr (pushdown) {\n            seg[p] = seg[p <<\
    \ 1] + seg[p << 1 | 1];\n            if constexpr (hasTag) seg[p] = seg[p] + lazy[p];\n\
    \        }\n        else seg[p] = get_val(p << 1) + get_val(p << 1 | 1);\n   \
    \ }\n    void pull(int l, int r) requires (hasTag) {\n        l += n, r += n -\
    \ 1;\n        for (l >>= 1, r >>= 1; l != r; l >>= 1, r >>= 1)\n            up(l),\
    \ up(r);\n        for (; l >= 1; l >>= 1)\n            up(l);\n    }\n    auto\
    \ tag_prod(int p) requires (!pushdown) {\n        Tag res = Tag();\n        for\
    \ (p += n; p >= 1; p >>= 1)\n            res = res + lazy[p];\n        return\
    \ res;\n    }\n\n    int descend_left(int rt, const auto &condition) requires\
    \ (pushdown) {\n        while (rt < n) {\n            if constexpr (hasTag) push(rt);\n\
    \            rt <<= 1;\n            if (!condition(seg[rt])) ++rt;\n        }\n\
    \        return rt - n;\n    }\n    int descend_right(int rt, const auto &condition)\
    \ requires (pushdown) {\n        while (rt < n) {\n            if constexpr (hasTag)\
    \ push(rt);\n            rt = rt << 1 | 1;\n            if (!condition(seg[rt]))\
    \ --rt;\n        }\n        return rt - n;\n    }\n    int range_left_search_iter(int\
    \ L, int R, const auto &condition) requires (pushdown) {\n        if constexpr\
    \ (hasTag) down(L, R - 1);\n        int right[32], rn = 0;\n        for (L +=\
    \ n, R += n; L < R; L >>= 1, R >>= 1) {\n            if (L & 1) {\n          \
    \      if (condition(seg[L])) return descend_left(L, condition);\n           \
    \     ++L;\n            }\n            if (R & 1) right[rn++] = --R;\n       \
    \ }\n        while (rn--)\n            if (condition(seg[right[rn]]))\n      \
    \          return descend_left(right[rn], condition);\n        return -1;\n  \
    \  }\n    int range_right_search_iter(int L, int R, const auto &condition) requires\
    \ (pushdown) {\n        if constexpr (hasTag) down(L, R - 1);\n        int left[32],\
    \ ln = 0;\n        for (L += n, R += n; L < R; L >>= 1, R >>= 1) {\n         \
    \   if (L & 1) left[ln++] = L++;\n            if (R & 1) {\n                --R;\n\
    \                if (condition(seg[R])) return descend_right(R, condition);\n\
    \            }\n        }\n        while (ln--)\n            if (condition(seg[left[ln]]))\n\
    \                return descend_right(left[ln], condition);\n        return -1;\n\
    \    }\n    int range_left_search_rec(int L, int R, int l, int r, int rt, const\
    \ auto &condition, SearchTag tag) requires (!pushdown) {\n        if (R <= l ||\
    \ r <= L) return R;\n        if (L <= l && r <= R && !condition(search_val(rt,\
    \ tag))) return R;\n        if (r - l == 1) return l;\n        tag = tag + lazy[rt];\n\
    \        int mid = (l + r) >> 1;\n        int res = range_left_search_rec(L, R,\
    \ l, mid, rt << 1, condition, tag);\n        if (res != R) return res;\n     \
    \   return range_left_search_rec(L, R, mid, r, rt << 1 | 1, condition, tag);\n\
    \    }\n    int range_right_search_rec(int L, int R, int l, int r, int rt, const\
    \ auto &condition, SearchTag tag) requires (!pushdown) {\n        if (R <= l ||\
    \ r <= L) return L - 1;\n        if (L <= l && r <= R && !condition(search_val(rt,\
    \ tag))) return L - 1;\n        if (r - l == 1) return l;\n        tag = tag +\
    \ lazy[rt];\n        int mid = (l + r) >> 1;\n        int res = range_right_search_rec(L,\
    \ R, mid, r, rt << 1 | 1, condition, tag);\n        if (res != L - 1) return res;\n\
    \        return range_right_search_rec(L, R, l, mid, rt << 1, condition, tag);\n\
    \    }\n    void printnode(int rt) {\n        int l = rt, r = rt;\n        while\
    \ (l < n) l <<= 1;\n        while (r < n) r = r << 1 | 1;\n        l -= n, r -=\
    \ n - 1;\n        std::cerr << rt << \" [\" << l << \", \" << r << \"): \";\n\
    \        if constexpr (hasTag) std::cerr << \"val = \" << seg[rt] << \", tag =\
    \ \" << lazy[rt];\n        else std::cerr << seg[rt];\n        std::cerr << \"\
    \\n\";\n    }\npublic:\n    ZkwSegmentTree(const std::vector<Value> &data):\n\
    \        n(std::bit_ceil(data.size())), sz(data.size()), lg(std::__lg(n)), seg(n\
    \ << 1) {\n        if constexpr (hasTag) lazy.resize(n << 1);\n        std::copy(data.begin(),\
    \ data.end(), seg.begin() + n);\n        for (int i = n - 1; i > 0; --i) up(i);\n\
    \    }\n    ZkwSegmentTree(int size):\n        n(std::bit_ceil((unsigned int)size)),\
    \ sz(size), lg(std::__lg(n)), seg(n << 1) {\n        if constexpr (hasTag) lazy.resize(n\
    \ << 1);\n    }\n    Value get(int x) {\n        assert(0 <= x && x < sz);\n \
    \       if constexpr (hasTag) {\n            if constexpr (pushdown) down(x);\n\
    \            else return seg[x + n] + tag_prod(x);\n        }\n        return\
    \ seg[x + n];\n    }\n    Value all_prod() {\n        return get_val(1);\n   \
    \ }\n    Value range_prod(int l, int r) {\n        assert(0 <= l && r <= sz);\n\
    \        assert(l <= r);\n        if (l == r) return Value();\n        if constexpr\
    \ (hasTag && pushdown)\n            down(l, r - 1);\n        Value resl = Value(),\
    \ resr = Value();\n        int tl = l + n, tr = r + n - 1;\n        bool l_valid\
    \ = false, r_valid = false;\n        for (l += n, r += n; l < r; l >>= 1, r >>=\
    \ 1) {\n            if (l & 1) resl = resl + get_val(l++), l_valid = true;\n \
    \           if (r & 1) resr = get_val(--r) + resr, r_valid = true;\n         \
    \   if constexpr (!pushdown) {\n                tl >>= 1, tr >>= 1;\n        \
    \        if (l_valid) resl = resl + lazy[tl];\n                if (r_valid) resr\
    \ = resr + lazy[tr];\n            }\n        }\n        if constexpr (!pushdown)\
    \ {\n            for (tl >>= 1, tr >>= 1; tl >= 1; tl >>= 1, tr >>= 1) {\n   \
    \             if (l_valid) resl = resl + lazy[tl];\n                if (r_valid)\
    \ resr = resr + lazy[tr];\n            }\n        }\n        return resl + resr;\n\
    \    }\n    void modify(int x, Value v) {\n        assert(0 <= x && x < sz);\n\
    \        if constexpr (hasTag) {\n            if constexpr (pushdown) down(x);\n\
    \            else v = v - tag_prod(x);\n        }\n        for (seg[x += n] =\
    \ std::move(v); x > 1; up(x >>= 1));\n    }\n    void transform(int x, const auto\
    \ &func) {\n        assert(0 <= x && x < sz);\n        if constexpr (hasTag &&\
    \ pushdown)\n            down(x);\n        for (func(seg[x += n]); x > 1; up(x\
    \ >>= 1));\n    }\n    void range_transform(int l, int r, const auto &tag) requires\
    \ (hasTag) {\n        assert(0 <= l && r <= sz);\n        assert(l <= r);\n  \
    \      if (l < r) {\n            if constexpr (pushdown)\n                down(l,\
    \ r - 1);\n            int tl = l, tr = r;\n            for (l += n, r += n; l\
    \ < r; l >>= 1, r >>= 1) {\n                if (l & 1) give_tag(l++, tag);\n \
    \               if (r & 1) give_tag(--r, tag);\n            }\n            pull(tl,\
    \ tr);\n        }\n    }\n    int range_left_search(const auto &condition, int\
    \ l = -1, int r = -1) {\n        if (l == -1 && r == -1) l = 0, r = sz;\n    \
    \    assert(0 <= l && r <= sz);\n        assert(l <= r);\n        if (l == r)\
    \ return r;\n        if constexpr (pushdown) {\n            int res = range_left_search_iter(l,\
    \ r, condition);\n            return res == -1 ? r : res;\n        }\n       \
    \ else return range_left_search_rec(l, r, 0, n, 1, condition, SearchTag());\n\
    \    }\n    int range_right_search(const auto &condition, int l = -1, int r =\
    \ -1) {\n        if (l == -1 && r == -1) l = -1, r = sz - 1;\n        ++l, ++r;\n\
    \        assert(0 <= l && r <= sz);\n        assert(l <= r);\n        if (l ==\
    \ r) return l - 1;\n        if constexpr (pushdown) {\n            int res = range_right_search_iter(l,\
    \ r, condition);\n            return res == -1 ? l - 1 : res;\n        }\n   \
    \     else return range_right_search_rec(l, r, 0, n, 1, condition, SearchTag());\n\
    \    }\n    int descend(const auto &go_left) {\n        int rt = 1;\n        SearchTag\
    \ tag = SearchTag();\n        while (rt < n) {\n            if constexpr (hasTag\
    \ && pushdown) push(rt);\n            if constexpr (!pushdown) tag = tag + lazy[rt];\n\
    \            int lc = rt << 1, rc = lc | 1;\n            rt = go_left(search_val(lc,\
    \ tag), search_val(rc, tag)) ? lc : rc;\n        }\n        return rt - n;\n \
    \   }\n    void printinfo(int l, int r) {\n        assert(0 <= l && r <= sz);\n\
    \        assert(l <= r);\n        std::cerr << \"\\e[1;33mInfo [\" << l << \"\
    , \" << r << \"):\\n\";\n        if (l < r) {\n            for (l += n, r += n;\
    \ l < r; l >>= 1, r >>= 1) {\n                if (l & 1) printnode(l++);\n   \
    \             if (r & 1) printnode(--r);\n            }\n        }\n        std::cerr\
    \ << \"\\e[0m\\n\";\n    }\n    void printall() {\n        std::cerr << \"\\e[1;33mInfo\
    \ all:\\n\";\n        for (int i = 1; i < n + n; ++i)\n            printnode(i);\n\
    \        std::cerr << \"\\e[0m\\n\";\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename Value = int, typename Tag = void, bool\
    \ pushdown = true>\nclass ZkwSegmentTree {\n    static constexpr bool hasTag =\
    \ !std::is_same_v<Tag, void>;\n    static_assert(pushdown || hasTag, \"Lazy tag\
    \ must exist when pushdown is false\");\n    int n, sz, lg;\n    std::vector<Value>\
    \ seg;\n    struct Empty {};\n    [[no_unique_address]] std::conditional_t<hasTag,\
    \ std::vector<Tag>, Empty> lazy;\n    using SearchTag = std::conditional_t<!pushdown,\
    \ Tag, Empty>;\n\n    decltype(auto) get_val(int rt) {\n        if constexpr (pushdown)\
    \ return static_cast<const Value&>(seg[rt]);\n        else return seg[rt] + lazy[rt];\n\
    \    }\n    decltype(auto) search_val(int rt, const SearchTag &tag) {\n      \
    \  if constexpr (pushdown) return static_cast<const Value&>(seg[rt]);\n      \
    \  else return get_val(rt) + tag;\n    }\n    void give_tag(int rt, const auto\
    \ &tag) requires (hasTag) {\n        if constexpr (pushdown) seg[rt] = seg[rt]\
    \ + tag;\n        lazy[rt] = lazy[rt] + tag;\n    }\n    void push(int rt) requires\
    \ (hasTag && pushdown) {\n        give_tag(rt << 1, lazy[rt]);\n        give_tag(rt\
    \ << 1 | 1, lazy[rt]);\n        lazy[rt] = Tag();\n    }\n    void down(int p)\
    \ requires (hasTag && pushdown) {\n        p += n;\n        for (int h = lg; h\
    \ > 0; --h)\n            push(p >> h);\n    }\n    void down(int l, int r) requires\
    \ (hasTag && pushdown) {\n        l += n, r += n;\n        for (int h = lg; h\
    \ > 0; --h) {\n            int a = l >> h, b = r >> h;\n            push(a);\n\
    \            if (a != b) push(b);\n        }\n    }\n    void up(int p) {\n  \
    \      if constexpr (pushdown) {\n            seg[p] = seg[p << 1] + seg[p <<\
    \ 1 | 1];\n            if constexpr (hasTag) seg[p] = seg[p] + lazy[p];\n    \
    \    }\n        else seg[p] = get_val(p << 1) + get_val(p << 1 | 1);\n    }\n\
    \    void pull(int l, int r) requires (hasTag) {\n        l += n, r += n - 1;\n\
    \        for (l >>= 1, r >>= 1; l != r; l >>= 1, r >>= 1)\n            up(l),\
    \ up(r);\n        for (; l >= 1; l >>= 1)\n            up(l);\n    }\n    auto\
    \ tag_prod(int p) requires (!pushdown) {\n        Tag res = Tag();\n        for\
    \ (p += n; p >= 1; p >>= 1)\n            res = res + lazy[p];\n        return\
    \ res;\n    }\n\n    int descend_left(int rt, const auto &condition) requires\
    \ (pushdown) {\n        while (rt < n) {\n            if constexpr (hasTag) push(rt);\n\
    \            rt <<= 1;\n            if (!condition(seg[rt])) ++rt;\n        }\n\
    \        return rt - n;\n    }\n    int descend_right(int rt, const auto &condition)\
    \ requires (pushdown) {\n        while (rt < n) {\n            if constexpr (hasTag)\
    \ push(rt);\n            rt = rt << 1 | 1;\n            if (!condition(seg[rt]))\
    \ --rt;\n        }\n        return rt - n;\n    }\n    int range_left_search_iter(int\
    \ L, int R, const auto &condition) requires (pushdown) {\n        if constexpr\
    \ (hasTag) down(L, R - 1);\n        int right[32], rn = 0;\n        for (L +=\
    \ n, R += n; L < R; L >>= 1, R >>= 1) {\n            if (L & 1) {\n          \
    \      if (condition(seg[L])) return descend_left(L, condition);\n           \
    \     ++L;\n            }\n            if (R & 1) right[rn++] = --R;\n       \
    \ }\n        while (rn--)\n            if (condition(seg[right[rn]]))\n      \
    \          return descend_left(right[rn], condition);\n        return -1;\n  \
    \  }\n    int range_right_search_iter(int L, int R, const auto &condition) requires\
    \ (pushdown) {\n        if constexpr (hasTag) down(L, R - 1);\n        int left[32],\
    \ ln = 0;\n        for (L += n, R += n; L < R; L >>= 1, R >>= 1) {\n         \
    \   if (L & 1) left[ln++] = L++;\n            if (R & 1) {\n                --R;\n\
    \                if (condition(seg[R])) return descend_right(R, condition);\n\
    \            }\n        }\n        while (ln--)\n            if (condition(seg[left[ln]]))\n\
    \                return descend_right(left[ln], condition);\n        return -1;\n\
    \    }\n    int range_left_search_rec(int L, int R, int l, int r, int rt, const\
    \ auto &condition, SearchTag tag) requires (!pushdown) {\n        if (R <= l ||\
    \ r <= L) return R;\n        if (L <= l && r <= R && !condition(search_val(rt,\
    \ tag))) return R;\n        if (r - l == 1) return l;\n        tag = tag + lazy[rt];\n\
    \        int mid = (l + r) >> 1;\n        int res = range_left_search_rec(L, R,\
    \ l, mid, rt << 1, condition, tag);\n        if (res != R) return res;\n     \
    \   return range_left_search_rec(L, R, mid, r, rt << 1 | 1, condition, tag);\n\
    \    }\n    int range_right_search_rec(int L, int R, int l, int r, int rt, const\
    \ auto &condition, SearchTag tag) requires (!pushdown) {\n        if (R <= l ||\
    \ r <= L) return L - 1;\n        if (L <= l && r <= R && !condition(search_val(rt,\
    \ tag))) return L - 1;\n        if (r - l == 1) return l;\n        tag = tag +\
    \ lazy[rt];\n        int mid = (l + r) >> 1;\n        int res = range_right_search_rec(L,\
    \ R, mid, r, rt << 1 | 1, condition, tag);\n        if (res != L - 1) return res;\n\
    \        return range_right_search_rec(L, R, l, mid, rt << 1, condition, tag);\n\
    \    }\n    void printnode(int rt) {\n        int l = rt, r = rt;\n        while\
    \ (l < n) l <<= 1;\n        while (r < n) r = r << 1 | 1;\n        l -= n, r -=\
    \ n - 1;\n        std::cerr << rt << \" [\" << l << \", \" << r << \"): \";\n\
    \        if constexpr (hasTag) std::cerr << \"val = \" << seg[rt] << \", tag =\
    \ \" << lazy[rt];\n        else std::cerr << seg[rt];\n        std::cerr << \"\
    \\n\";\n    }\npublic:\n    ZkwSegmentTree(const std::vector<Value> &data):\n\
    \        n(std::bit_ceil(data.size())), sz(data.size()), lg(std::__lg(n)), seg(n\
    \ << 1) {\n        if constexpr (hasTag) lazy.resize(n << 1);\n        std::copy(data.begin(),\
    \ data.end(), seg.begin() + n);\n        for (int i = n - 1; i > 0; --i) up(i);\n\
    \    }\n    ZkwSegmentTree(int size):\n        n(std::bit_ceil((unsigned int)size)),\
    \ sz(size), lg(std::__lg(n)), seg(n << 1) {\n        if constexpr (hasTag) lazy.resize(n\
    \ << 1);\n    }\n    Value get(int x) {\n        assert(0 <= x && x < sz);\n \
    \       if constexpr (hasTag) {\n            if constexpr (pushdown) down(x);\n\
    \            else return seg[x + n] + tag_prod(x);\n        }\n        return\
    \ seg[x + n];\n    }\n    Value all_prod() {\n        return get_val(1);\n   \
    \ }\n    Value range_prod(int l, int r) {\n        assert(0 <= l && r <= sz);\n\
    \        assert(l <= r);\n        if (l == r) return Value();\n        if constexpr\
    \ (hasTag && pushdown)\n            down(l, r - 1);\n        Value resl = Value(),\
    \ resr = Value();\n        int tl = l + n, tr = r + n - 1;\n        bool l_valid\
    \ = false, r_valid = false;\n        for (l += n, r += n; l < r; l >>= 1, r >>=\
    \ 1) {\n            if (l & 1) resl = resl + get_val(l++), l_valid = true;\n \
    \           if (r & 1) resr = get_val(--r) + resr, r_valid = true;\n         \
    \   if constexpr (!pushdown) {\n                tl >>= 1, tr >>= 1;\n        \
    \        if (l_valid) resl = resl + lazy[tl];\n                if (r_valid) resr\
    \ = resr + lazy[tr];\n            }\n        }\n        if constexpr (!pushdown)\
    \ {\n            for (tl >>= 1, tr >>= 1; tl >= 1; tl >>= 1, tr >>= 1) {\n   \
    \             if (l_valid) resl = resl + lazy[tl];\n                if (r_valid)\
    \ resr = resr + lazy[tr];\n            }\n        }\n        return resl + resr;\n\
    \    }\n    void modify(int x, Value v) {\n        assert(0 <= x && x < sz);\n\
    \        if constexpr (hasTag) {\n            if constexpr (pushdown) down(x);\n\
    \            else v = v - tag_prod(x);\n        }\n        for (seg[x += n] =\
    \ std::move(v); x > 1; up(x >>= 1));\n    }\n    void transform(int x, const auto\
    \ &func) {\n        assert(0 <= x && x < sz);\n        if constexpr (hasTag &&\
    \ pushdown)\n            down(x);\n        for (func(seg[x += n]); x > 1; up(x\
    \ >>= 1));\n    }\n    void range_transform(int l, int r, const auto &tag) requires\
    \ (hasTag) {\n        assert(0 <= l && r <= sz);\n        assert(l <= r);\n  \
    \      if (l < r) {\n            if constexpr (pushdown)\n                down(l,\
    \ r - 1);\n            int tl = l, tr = r;\n            for (l += n, r += n; l\
    \ < r; l >>= 1, r >>= 1) {\n                if (l & 1) give_tag(l++, tag);\n \
    \               if (r & 1) give_tag(--r, tag);\n            }\n            pull(tl,\
    \ tr);\n        }\n    }\n    int range_left_search(const auto &condition, int\
    \ l = -1, int r = -1) {\n        if (l == -1 && r == -1) l = 0, r = sz;\n    \
    \    assert(0 <= l && r <= sz);\n        assert(l <= r);\n        if (l == r)\
    \ return r;\n        if constexpr (pushdown) {\n            int res = range_left_search_iter(l,\
    \ r, condition);\n            return res == -1 ? r : res;\n        }\n       \
    \ else return range_left_search_rec(l, r, 0, n, 1, condition, SearchTag());\n\
    \    }\n    int range_right_search(const auto &condition, int l = -1, int r =\
    \ -1) {\n        if (l == -1 && r == -1) l = -1, r = sz - 1;\n        ++l, ++r;\n\
    \        assert(0 <= l && r <= sz);\n        assert(l <= r);\n        if (l ==\
    \ r) return l - 1;\n        if constexpr (pushdown) {\n            int res = range_right_search_iter(l,\
    \ r, condition);\n            return res == -1 ? l - 1 : res;\n        }\n   \
    \     else return range_right_search_rec(l, r, 0, n, 1, condition, SearchTag());\n\
    \    }\n    int descend(const auto &go_left) {\n        int rt = 1;\n        SearchTag\
    \ tag = SearchTag();\n        while (rt < n) {\n            if constexpr (hasTag\
    \ && pushdown) push(rt);\n            if constexpr (!pushdown) tag = tag + lazy[rt];\n\
    \            int lc = rt << 1, rc = lc | 1;\n            rt = go_left(search_val(lc,\
    \ tag), search_val(rc, tag)) ? lc : rc;\n        }\n        return rt - n;\n \
    \   }\n    void printinfo(int l, int r) {\n        assert(0 <= l && r <= sz);\n\
    \        assert(l <= r);\n        std::cerr << \"\\e[1;33mInfo [\" << l << \"\
    , \" << r << \"):\\n\";\n        if (l < r) {\n            for (l += n, r += n;\
    \ l < r; l >>= 1, r >>= 1) {\n                if (l & 1) printnode(l++);\n   \
    \             if (r & 1) printnode(--r);\n            }\n        }\n        std::cerr\
    \ << \"\\e[0m\\n\";\n    }\n    void printall() {\n        std::cerr << \"\\e[1;33mInfo\
    \ all:\\n\";\n        for (int i = 1; i < n + n; ++i)\n            printnode(i);\n\
    \        std::cerr << \"\\e[0m\\n\";\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/ZkwSegmentTree.hpp
  requiredBy: []
  timestamp: '2026-09-30 16:19:43+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/1_library_checker/data_structure/static_rmq_zkw.test.cpp
  - test/1_library_checker/data_structure/range_add_range_min_zkw2.test.cpp
  - test/1_library_checker/data_structure/range_add_range_min_zkw.test.cpp
documentation_of: DataStructure/ZkwSegmentTree.hpp
layout: document
title: Zkw Segment Tree
---

An efficient, non-recursive (Zkw) $0$-based Segment Tree supporting point/range updates and range queries.

## Template Parameters

```cpp
template<typename Value = int, typename Tag = void, bool pushdown = true>
class ZkwSegmentTree;
```

* `Value`: The type of elements.
    * Must support associative property `operator+` for merging two `Value` objects (commutative or non-commutative depending on usage).
    * Must have a default constructor `Value()` acting as the identity element.
* `Tag`: The type of lazy tags. Use `void` if no lazy propagation is needed.
    * Must support `operator+` for tag composition (`Tag + Tag`) and applying to a value (`Value + Tag`).
    * Must have a default constructor `Tag()` acting as the identity tag.
* `pushdown`: If `true`, uses standard lazy propagation. If `false`, uses tag permanentization (requires commutative operations in some cases).

---

## Constructor (Size)

```cpp
ZkwSegmentTree(int size);
```

* $O(N)$ time

Constructs a Zkw Segment Tree of given size.

---

## Constructor (Array)

```cpp
ZkwSegmentTree(const vector<Value> &data);
```

* $O(N)$ time

Constructs a Zkw Segment Tree from an existing array.

---

## get

```cpp
Value get(int x);
```

* $O(\log N)$ if `Tag` is not `void`; $O(1)$ otherwise.

Returns the value at index `x`.

---

## range_prod

```cpp
Value range_prod(int l, int r);
```

* `l` and `r` are $0$-indexed, representing the half-open interval `[l, r)`.
* $O(\log N)$ time

Returns the product of the range `[l, r)`.

---

## modify

```cpp
void modify(int x, Value v);
```

* `x` is $0$-indexed.
* $O(\log N)$ time

Sets the value at index `x` to `v`.

---

## transform

```cpp
void transform(int x, const auto &func);
```

* `x` is $0$-indexed.
* `func` is a callable (e.g., lambda) that takes a `Value&`.
* $O(\log N)$ time

Applies `func` to the leaf node at index `x`.

---

## range_transform

```cpp
void range_transform(int l, int r, const Tag &tag);
```

* Requires `Tag` not to be `void`.
* $O(\log N)$ time

Applies the lazy tag `tag` to the range `[l, r)`.

---

## Debugging Methods

### printinfo
```cpp
void printinfo(int l, int r);
```
Prints detailed information (values and tags) for nodes covering the range `[l, r)`.

### printall
```cpp
void printall();
```
Prints information for all nodes in the Segment Tree.
