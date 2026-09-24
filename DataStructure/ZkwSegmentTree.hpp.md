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
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_rmq_zkw.test.cpp
    title: test/1_library_checker/data_structure/static_rmq_zkw.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/ZkwSegmentTree.hpp\"\n\ntemplate<typename\
    \ Value = int, typename Tag = void, bool pushdown = true>\nclass ZkwSegmentTree\
    \ {\n    static constexpr bool hasTag = !std::is_same_v<Tag, void>;\n    static_assert(pushdown\
    \ || hasTag, \"Lazy tag must exist when pushdown is false\");\n    int n;\n  \
    \  std::vector<Value> seg;\n    struct Empty {};\n    [[no_unique_address]] std::conditional_t<hasTag,\
    \ std::vector<Tag>, Empty> lazy;\n    Value get_val(int rt) {\n        if constexpr\
    \ (pushdown) return seg[rt];\n        else return seg[rt] + lazy[rt];\n    }\n\
    \    void give_tag(int rt, auto tag) requires (hasTag) {\n        if constexpr\
    \ (pushdown) seg[rt] = seg[rt] + tag;\n        lazy[rt] = lazy[rt] + tag;\n  \
    \  }\n    void down(int p) requires (hasTag && pushdown) {\n        p += n;\n\
    \        for (int h = std::__lg(n); h > 0; h--) {\n            int i = p >> h;\n\
    \            give_tag(i << 1, lazy[i]); \n            give_tag(i << 1 | 1, lazy[i]);\n\
    \            lazy[i] = Tag();\n        }\n    }\n    void up(int p) {\n      \
    \  if constexpr (pushdown) {\n            seg[p] = seg[p << 1] + seg[p << 1 |\
    \ 1];\n            if constexpr (hasTag) seg[p] = seg[p] + lazy[p];\n        }\n\
    \        else seg[p] = get_val(p << 1) + get_val(p << 1 | 1);\n    }\n    void\
    \ pull(int l, int r) requires (hasTag) {\n        l += n, r += n - 1;\n      \
    \  for (l >>= 1, r >>= 1; l != r; l >>= 1, r >>= 1)\n            up(l), up(r);\n\
    \        for (; l >= 1; l >>= 1)\n            up(l);\n    }\n    auto tag_prod(int\
    \ p) requires (!pushdown) {\n        Tag res = Tag();\n        for (p += n; p\
    \ >= 1; p >>= 1)\n            res = res + lazy[p];\n        return res;\n    }\n\
    \    void printnode(int rt) {\n        int l = rt, r = rt;\n        while (l <\
    \ n) l <<= 1;\n        while (r < n) r = r << 1 | 1;\n        l -= n, r -= n -\
    \ 1;\n        std::cerr << rt<< \" [\" << l << \", \" << r << \"): \";\n     \
    \   if constexpr (hasTag) std::cerr << \"val = \" << seg[rt] << \", tag = \" <<\
    \ lazy[rt];\n        else std::cerr << seg[rt];\n        std::cerr << \"\\n\"\
    ;\n    }\n    static int ceilpow2(int sz) {\n        int m = 1;\n        while\
    \ (m < sz) m <<= 1;\n        return m;\n    }\npublic:\n    ZkwSegmentTree(const\
    \ std::vector<Value> &data): n(ceilpow2(data.size())), seg(n << 1) { \n      \
    \  if constexpr (hasTag) lazy.resize(n << 1); \n        for (int i = 0; i < int(data.size());\
    \ ++i) seg[i + n] = data[i];\n        for (int i = n - 1; i > 0; --i) up(i);\n\
    \    }\n    ZkwSegmentTree(int size): ZkwSegmentTree(vector<Value>(size)) {}\n\
    \    Value get(int x) {\n        assert(0 <= x && x < n);\n        if constexpr\
    \ (hasTag) {\n            if constexpr (pushdown) down(x);\n            else return\
    \ seg[x + n] + tag_prod(x); \n        }\n        return seg[x + n];\n    }\n \
    \   Value range_prod(int l, int r) {\n        assert(0 <= l && r <= n);\n    \
    \    assert(l <= r);\n        if (l == r) return Value();\n        if constexpr\
    \ (hasTag && pushdown)\n            down(l), down(r - 1);\n        Value resl\
    \ = Value(), resr = Value();\n        int tl = l + n, tr = r + n - 1;\n      \
    \  bool l_valid = false, r_valid = false;\n        for (l += n, r += n; l < r;\
    \ l >>= 1, r >>= 1) {\n            if (l & 1) resl = resl + get_val(l++), l_valid\
    \ = true;\n            if (r & 1) resr = get_val(--r) + resr, r_valid = true;\n\
    \            if constexpr (!pushdown) {\n                tl >>= 1, tr >>= 1;\n\
    \                if (l_valid) resl = resl + lazy[tl];\n                if (r_valid)\
    \ resr = resr + lazy[tr];\n            }\n        }\n        if constexpr (!pushdown)\
    \ {\n            for (tl >>= 1, tr >>= 1; tl >= 1; tl >>= 1, tr >>= 1) {\n   \
    \             if (l_valid) resl = resl + lazy[tl];\n                if (r_valid)\
    \ resr = resr + lazy[tr];\n            }\n        }\n        return resl + resr;\n\
    \    }\n    void modify(int x, Value v) {\n        assert(0 <= x && x < n);\n\
    \        if constexpr (hasTag) {\n            if constexpr (pushdown) down(x);\n\
    \            else v = v - tag_prod(x); \n        }\n        for (seg[x += n] =\
    \ v; x > 1; up(x >>= 1));\n    }\n    void transform(int x, const auto &func)\
    \ {\n        assert(0 <= x && x < n);\n        if constexpr (hasTag && pushdown)\n\
    \            down(x);\n        for (func(seg[x += n]); x > 1; up(x >>= 1));\n\
    \    }\n    void range_transform(int l, int r, const auto &tag) requires (hasTag)\
    \ {\n        assert(0 <= l && r <= n);\n        assert(l <= r);\n        if (l\
    \ < r) {\n            if constexpr (hasTag && pushdown)\n                down(l),\
    \ down(r - 1);\n            int tl = l, tr = r;\n            for (l += n, r +=\
    \ n; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) give_tag(l++, tag);\n\
    \                if (r & 1) give_tag(--r, tag);\n            }\n            pull(tl,\
    \ tr);\n        }\n    }\n    void printinfo(int l, int r) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        std::cerr << \"\\e[1;33mInfo\
    \ [\" << l << \", \" << r << \"):\\n\";\n        if (l < r) {\n            for\
    \ (l += n, r += n; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) printnode(l++);\n\
    \                if (r & 1) printnode(--r);\n            }\n        }\n      \
    \  std::cerr << \"\\e[0m\\n\";\n    }\n    void printall() {\n        std::cerr\
    \ << \"\\e[1;33mInfo all:\\n\";\n        for (int i = 1; i < n + n; ++i)\n   \
    \         printnode(i);\n        std::cerr << \"\\e[0m\\n\";\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename Value = int, typename Tag = void, bool\
    \ pushdown = true>\nclass ZkwSegmentTree {\n    static constexpr bool hasTag =\
    \ !std::is_same_v<Tag, void>;\n    static_assert(pushdown || hasTag, \"Lazy tag\
    \ must exist when pushdown is false\");\n    int n;\n    std::vector<Value> seg;\n\
    \    struct Empty {};\n    [[no_unique_address]] std::conditional_t<hasTag, std::vector<Tag>,\
    \ Empty> lazy;\n    Value get_val(int rt) {\n        if constexpr (pushdown) return\
    \ seg[rt];\n        else return seg[rt] + lazy[rt];\n    }\n    void give_tag(int\
    \ rt, auto tag) requires (hasTag) {\n        if constexpr (pushdown) seg[rt] =\
    \ seg[rt] + tag;\n        lazy[rt] = lazy[rt] + tag;\n    }\n    void down(int\
    \ p) requires (hasTag && pushdown) {\n        p += n;\n        for (int h = std::__lg(n);\
    \ h > 0; h--) {\n            int i = p >> h;\n            give_tag(i << 1, lazy[i]);\
    \ \n            give_tag(i << 1 | 1, lazy[i]);\n            lazy[i] = Tag();\n\
    \        }\n    }\n    void up(int p) {\n        if constexpr (pushdown) {\n \
    \           seg[p] = seg[p << 1] + seg[p << 1 | 1];\n            if constexpr\
    \ (hasTag) seg[p] = seg[p] + lazy[p];\n        }\n        else seg[p] = get_val(p\
    \ << 1) + get_val(p << 1 | 1);\n    }\n    void pull(int l, int r) requires (hasTag)\
    \ {\n        l += n, r += n - 1;\n        for (l >>= 1, r >>= 1; l != r; l >>=\
    \ 1, r >>= 1)\n            up(l), up(r);\n        for (; l >= 1; l >>= 1)\n  \
    \          up(l);\n    }\n    auto tag_prod(int p) requires (!pushdown) {\n  \
    \      Tag res = Tag();\n        for (p += n; p >= 1; p >>= 1)\n            res\
    \ = res + lazy[p];\n        return res;\n    }\n    void printnode(int rt) {\n\
    \        int l = rt, r = rt;\n        while (l < n) l <<= 1;\n        while (r\
    \ < n) r = r << 1 | 1;\n        l -= n, r -= n - 1;\n        std::cerr << rt<<\
    \ \" [\" << l << \", \" << r << \"): \";\n        if constexpr (hasTag) std::cerr\
    \ << \"val = \" << seg[rt] << \", tag = \" << lazy[rt];\n        else std::cerr\
    \ << seg[rt];\n        std::cerr << \"\\n\";\n    }\n    static int ceilpow2(int\
    \ sz) {\n        int m = 1;\n        while (m < sz) m <<= 1;\n        return m;\n\
    \    }\npublic:\n    ZkwSegmentTree(const std::vector<Value> &data): n(ceilpow2(data.size())),\
    \ seg(n << 1) { \n        if constexpr (hasTag) lazy.resize(n << 1); \n      \
    \  for (int i = 0; i < int(data.size()); ++i) seg[i + n] = data[i];\n        for\
    \ (int i = n - 1; i > 0; --i) up(i);\n    }\n    ZkwSegmentTree(int size): ZkwSegmentTree(vector<Value>(size))\
    \ {}\n    Value get(int x) {\n        assert(0 <= x && x < n);\n        if constexpr\
    \ (hasTag) {\n            if constexpr (pushdown) down(x);\n            else return\
    \ seg[x + n] + tag_prod(x); \n        }\n        return seg[x + n];\n    }\n \
    \   Value range_prod(int l, int r) {\n        assert(0 <= l && r <= n);\n    \
    \    assert(l <= r);\n        if (l == r) return Value();\n        if constexpr\
    \ (hasTag && pushdown)\n            down(l), down(r - 1);\n        Value resl\
    \ = Value(), resr = Value();\n        int tl = l + n, tr = r + n - 1;\n      \
    \  bool l_valid = false, r_valid = false;\n        for (l += n, r += n; l < r;\
    \ l >>= 1, r >>= 1) {\n            if (l & 1) resl = resl + get_val(l++), l_valid\
    \ = true;\n            if (r & 1) resr = get_val(--r) + resr, r_valid = true;\n\
    \            if constexpr (!pushdown) {\n                tl >>= 1, tr >>= 1;\n\
    \                if (l_valid) resl = resl + lazy[tl];\n                if (r_valid)\
    \ resr = resr + lazy[tr];\n            }\n        }\n        if constexpr (!pushdown)\
    \ {\n            for (tl >>= 1, tr >>= 1; tl >= 1; tl >>= 1, tr >>= 1) {\n   \
    \             if (l_valid) resl = resl + lazy[tl];\n                if (r_valid)\
    \ resr = resr + lazy[tr];\n            }\n        }\n        return resl + resr;\n\
    \    }\n    void modify(int x, Value v) {\n        assert(0 <= x && x < n);\n\
    \        if constexpr (hasTag) {\n            if constexpr (pushdown) down(x);\n\
    \            else v = v - tag_prod(x); \n        }\n        for (seg[x += n] =\
    \ v; x > 1; up(x >>= 1));\n    }\n    void transform(int x, const auto &func)\
    \ {\n        assert(0 <= x && x < n);\n        if constexpr (hasTag && pushdown)\n\
    \            down(x);\n        for (func(seg[x += n]); x > 1; up(x >>= 1));\n\
    \    }\n    void range_transform(int l, int r, const auto &tag) requires (hasTag)\
    \ {\n        assert(0 <= l && r <= n);\n        assert(l <= r);\n        if (l\
    \ < r) {\n            if constexpr (hasTag && pushdown)\n                down(l),\
    \ down(r - 1);\n            int tl = l, tr = r;\n            for (l += n, r +=\
    \ n; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) give_tag(l++, tag);\n\
    \                if (r & 1) give_tag(--r, tag);\n            }\n            pull(tl,\
    \ tr);\n        }\n    }\n    void printinfo(int l, int r) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        std::cerr << \"\\e[1;33mInfo\
    \ [\" << l << \", \" << r << \"):\\n\";\n        if (l < r) {\n            for\
    \ (l += n, r += n; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) printnode(l++);\n\
    \                if (r & 1) printnode(--r);\n            }\n        }\n      \
    \  std::cerr << \"\\e[0m\\n\";\n    }\n    void printall() {\n        std::cerr\
    \ << \"\\e[1;33mInfo all:\\n\";\n        for (int i = 1; i < n + n; ++i)\n   \
    \         printnode(i);\n        std::cerr << \"\\e[0m\\n\";\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/ZkwSegmentTree.hpp
  requiredBy: []
  timestamp: '2026-06-19 18:28:09+08:00'
  verificationStatus: LIBRARY_ALL_AC
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
