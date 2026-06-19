---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: DataStructure/DefaultAllocator.hpp
    title: Default Allocator
  - icon: ':heavy_check_mark:'
    path: DataStructure/PointerSegmentTree.hpp
    title: Pointer Segment Tree
  - icon: ':question:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  - icon: ':question:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/persistent_range_affine_range_sum
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_range_affine_range_sum\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp\"\
    \n\n#line 2 \"DataStructure/PointerSegmentTree.hpp\"\n\n#line 2 \"DataStructure/DefaultAllocator.hpp\"\
    \n\ntemplate<typename T>\nstruct DefaultAllocator {\n    template<typename...\
    \ Args>\n    static T* allocate(Args&&... args) { \n        return new T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) { delete p; }\n};\n#line 4 \"DataStructure/PointerSegmentTree.hpp\"\
    \n\ntemplate<typename Value = int, typename Tag = void, bool pushdown = true,\
    \ template<typename> class Allocator = DefaultAllocator, bool dynamic = false,\
    \ bool persistent = false>\nclass PointerSegmentTree {\n    static constexpr bool\
    \ hasTag = !std::is_same_v<Tag, void>;\n    static constexpr bool hasGet = requires(int\
    \ l, int r) { Value::get(l, r); };\n    static_assert(pushdown || hasTag, \"Lazy\
    \ tag must exist when pushdown is false\");\n    int n;\n    struct Empty {};\n\
    \    template <bool Condition, typename T>\n    static auto get_default() {\n\
    \        if constexpr (Condition) return T();\n        else return Empty{};\n\
    \    }\n    struct node {\n        node *l = nullptr, *r = nullptr;\n        Value\
    \ val;\n        [[no_unique_address]] std::conditional_t<hasTag, Tag, Empty> lazy\
    \ = get_default<hasTag, Tag>();\n        Value get_val() {\n            if constexpr\
    \ (pushdown) return val;\n            else return val + lazy;\n        }\n   \
    \     void up() {\n            if constexpr (dynamic) {\n                val =\
    \ Value();\n                if (l) val = l->get_val();\n                if (r)\
    \ val = val + r->get_val();\n            }\n            else {\n             \
    \   val = l->get_val() + r->get_val();\n            }\n        }\n        void\
    \ up(int lft, int rgt) requires (dynamic && hasGet) {\n            if (l) val\
    \ = l->get_val();\n            else val = Value::get(lft, (lft + rgt) / 2);\n\
    \            if (r) val = val + r->get_val();\n            else val = val + Value::get((lft\
    \ + rgt) / 2, rgt);\n        }\n        void give_tag(const auto &tag) requires\
    \ (hasTag) {\n            if constexpr (pushdown) val = val + tag;\n         \
    \   lazy = lazy + tag;\n        }\n        void down(int lbnd, int rbnd) requires\
    \ (hasTag && pushdown) {\n            bool need_tag = false;\n            if constexpr\
    \ (hasTag) { \n                if constexpr (std::equality_comparable<Tag>) need_tag\
    \ = (lazy != Tag());\n                else need_tag = true;\n            }\n \
    \           if (!need_tag) return;\n            if constexpr (dynamic || persistent)\
    \ {\n                int mid = (lbnd + rbnd) >> 1;\n                check_node(l,\
    \ lbnd, mid);\n                check_node(r, mid, rbnd);\n            }\n    \
    \        l->give_tag(lazy);\n            r->give_tag(lazy);\n            lazy\
    \ = Tag();\n        }\n        node() = default;\n        node(const auto &v)\
    \ : val(v) {}\n    };\n    node *root = nullptr;\n    using NodeAlloc = Allocator<node>;\n\
    \    void initialize(int l, int r, node *&p, const std::vector<Value> &data) {\n\
    \        if (r - l == 1) \n            return p = NodeAlloc::allocate(data[l]),\
    \ void();\n        p = NodeAlloc::allocate();\n        int mid = (l + r) >> 1;\n\
    \        initialize(l, mid, p->l, data);\n        initialize(mid, r, p->r, data);\n\
    \        p->up();\n    }\n    static void check_node(node *&p, int l, int r) requires\
    \ (dynamic || persistent) {\n        bool allocated = false; \n        if constexpr\
    \ (dynamic) if (!p) {\n            allocated = true;\n            if constexpr\
    \ (hasGet) p = NodeAlloc::allocate(Value::get(l, r));\n            else p = NodeAlloc::allocate();\n\
    \        }\n        if constexpr (persistent) if (!allocated) p = NodeAlloc::allocate(*p);\n\
    \    }\n    Value range_prod(int L, int R, int l, int r, node *p) {\n        if\
    \ constexpr (dynamic) {\n            if (!p) {\n                if constexpr (hasGet)\
    \ return Value::get(std::max(L, l), std::min(R, r));\n                return Value();\n\
    \            }\n        }\n        if (L <= l && R >= r)\n            return p->get_val();\n\
    \        if constexpr (hasTag && pushdown) p->down(l, r);\n        int mid = (l\
    \ + r) >> 1;\n        if constexpr (pushdown) {\n            if (R <= mid) return\
    \ range_prod(L, R, l, mid, p->l);\n            if (L >= mid) return range_prod(L,\
    \ R, mid, r, p->r);\n            return range_prod(L, R, l, mid, p->l) + range_prod(L,\
    \ R, mid, r, p->r); \n        }\n        else {\n            if (R <= mid) return\
    \ range_prod(L, R, l, mid, p->l) + p->lazy;\n            if (L >= mid) return\
    \ range_prod(L, R, mid, r, p->r) + p->lazy;\n            return range_prod(L,\
    \ R, l, mid, p->l) + range_prod(L, R, mid, r, p->r) + p->lazy;\n        }\n  \
    \  }\n    void update(node *&p, int l, int r) {\n        if constexpr (dynamic\
    \ && hasGet) p->up(l, r);\n        else p->up();\n    }\n    void modify(int x,\
    \ int l, int r, node *&p, const Value &v) {\n        if constexpr (dynamic ||\
    \ persistent) check_node(p, l, r);\n        if (r - l == 1)\n            return\
    \ p->val = v, void();\n        if constexpr (hasTag && pushdown) p->down(l, r);\n\
    \        int mid = (l + r) >> 1;\n        if constexpr (pushdown) {\n        \
    \    if (x < mid) modify(x, l, mid, p->l, v);\n            else modify(x, mid,\
    \ r, p->r, v);\n        }\n        else {\n            if (x < mid) modify(x,\
    \ l, mid, p->l, v - p->lazy);\n            else modify(x, mid, r, p->r, v - p->lazy);\n\
    \        }\n        update(p, l, r);\n    }\n    void transform(int x, int l,\
    \ int r, node *&p, const auto &func) {\n        if constexpr (dynamic || persistent)\
    \ check_node(p, l, r);\n        if (r - l == 1)\n            return func(p->val),\
    \ void();\n        if constexpr (hasTag && pushdown) p->down(l, r);\n        int\
    \ mid = (l + r) >> 1;\n        if (x < mid) transform(x, l, mid, p->l, func);\n\
    \        else transform(x, mid, r, p->r, func);\n        update(p, l, r);\n  \
    \  }\n    void range_transform(int L, int R, int l, int r, node *&p, const auto\
    \ &tag) requires (hasTag) {\n        if constexpr (dynamic || persistent) check_node(p,\
    \ l, r);\n        if (L <= l && R >= r)\n            return p->give_tag(tag);\n\
    \        if constexpr (pushdown) p->down(l, r);\n        int mid = (l + r) >>\
    \ 1;\n        if (L < mid) range_transform(L, R, l, mid, p->l, tag);\n       \
    \ if (R > mid) range_transform(L, R, mid, r, p->r, tag);\n        update(p, l,\
    \ r);\n    }\n    void range_transform_beats(int L, int R, int l, int r, node\
    \ *&p, const auto &tag, const auto &tag_condition, auto... tag_sum) requires (hasTag)\
    \ {\n        if constexpr (dynamic || persistent) check_node(p, l, r);\n     \
    \   if (L <= l && R >= r && tag_condition([&]{ if constexpr(pushdown) return p->val;\
    \ else return p->get_val() + (..., tag_sum); }()))\n            return p->give_tag(tag);\n\
    \        assert(r - l > 1);\n        if constexpr (pushdown) p->down(l, r);\n\
    \        else ((tag_sum = tag_sum + p->lazy), ...);\n        int mid = (l + r)\
    \ >> 1;\n        if (L < mid) range_transform_beats(L, R, l, mid, p->l, tag, tag_condition,\
    \ tag_sum...);\n        if (R > mid) range_transform_beats(L, R, mid, r, p->r,\
    \ tag, tag_condition, tag_sum...);\n        update(p, l, r);\n    }\n    int range_left_search(int\
    \ L, int R, int l, int r, node *p, const auto &condition, auto... tag_sum) {\n\
    \        if constexpr (!dynamic) if (!p) return R;\n        if (r - l == 1) {\n\
    \            if (!condition([&]{ if constexpr(pushdown) return p->val; else return\
    \ p->get_val() + (..., tag_sum); }()))\n                return R;\n          \
    \  return l;\n        }\n        int mid = (l + r) >> 1;\n        if constexpr\
    \ (hasTag && pushdown) p->down(l, r);\n        if constexpr (!pushdown) ((tag_sum\
    \ = tag_sum + p->lazy), ...);\n        if (L <= l && R >= r) {\n            if\
    \ (p->l && condition([&]{ if constexpr(pushdown) return p->l->val; else return\
    \ p->l->get_val() + (..., tag_sum); }()))\n                return range_left_search(L,\
    \ R, l, mid, p->l, condition, tag_sum...);\n            return range_left_search(L,\
    \ R, mid, r, p->r, condition, tag_sum...);\n        }\n        int left = R;\n\
    \        if (L < mid) left = range_left_search(L, R, l, mid, p->l, condition,\
    \ tag_sum...);\n        if (left == R) {\n            if (R > mid) return range_left_search(L,\
    \ R, mid, r, p->r, condition, tag_sum...);\n            return R;\n        }\n\
    \        return left;\n    }\n    int range_right_search(int L, int R, int l,\
    \ int r, node *p, const auto &condition, auto... tag_sum) {\n        if constexpr\
    \ (!dynamic) if (!p) return L - 1;\n        if (r - l == 1) {\n            if\
    \ (!condition([&]{ if constexpr(pushdown) return p->val; else return p->get_val()\
    \ + (..., tag_sum); }()))\n                return L - 1;\n            return l;\n\
    \        }\n        int mid = (l + r) >> 1;\n        if constexpr (hasTag && pushdown)\
    \ p->down(l, r);\n        if constexpr (!pushdown) ((tag_sum = tag_sum + p->lazy),\
    \ ...);\n        if (L <= l && R >= r) {\n            if (p->r && condition([&]{\
    \ if constexpr(pushdown) return p->r->val; else return p->r->get_val() + (...,\
    \ tag_sum); }()))\n                return range_right_search(L, R, mid, r, p->r,\
    \ condition, tag_sum...);\n            return range_right_search(L, R, l, mid,\
    \ p->l, condition, tag_sum...);\n        }\n        int right = L - 1;\n     \
    \   if (R > mid) right = range_right_search(L, R, mid, r, p->r, condition, tag_sum...);\n\
    \        if (right == L - 1) {\n            if (L < mid) return range_right_search(L,\
    \ R, l, mid, p->l, condition, tag_sum...);\n            return L - 1;\n      \
    \  }\n        return right;\n    }\n    Value get(int x, int l, int r, node *p)\
    \ {\n        [[no_unique_address]] std::conditional_t<!pushdown, Tag, Empty> tag;\n\
    \        while (r - l > 1) {\n            if constexpr (hasTag && pushdown) p->down(l,\
    \ r);\n            if constexpr (!pushdown) tag = tag + p->lazy;\n           \
    \ int mid = (l + r) >> 1;\n            if (x < mid) r = mid, p = p->l;\n     \
    \       else l = mid, p = p->r;\n            if constexpr (dynamic || persistent)\
    \ if (!p) {\n                if constexpr (hasGet) return Value::get(x, x + 1)\
    \ + tag;\n                else return Value() + tag;\n            }\n        }\n\
    \        if constexpr (pushdown) return p->val;\n        else return p->get_val()\
    \ + tag;\n    }\n    void range_copy(int L, int R, int l, int r, node *&p, node\
    \ *&q) requires (pushdown && persistent) {\n        if (L <= l && R >= r)\n  \
    \          return p = q, void();\n        if constexpr (dynamic || persistent)\
    \ check_node(p, l, r);\n        if constexpr (hasTag && pushdown) p->down(l, r),\
    \ q->down(l, r);\n        int mid = (l + r) >> 1;\n        if (L < mid) range_copy(L,\
    \ R, l, mid, p->l, q->l);\n        if (R > mid) range_copy(L, R, mid, r, p->r,\
    \ q->r);\n        update(p, l, r);\n    }\n    void printnode(int l, int r, node\
    \ *p) {\n        std::cerr << \"[\" << l << \", \" << r << \"): \";\n        if\
    \ constexpr (hasTag) std::cerr << \"val = \" << p->val << \", tag = \" << p->lazy;\n\
    \        else std::cerr << p->val;\n        std::cerr << \"\\n\";\n    }\n   \
    \ void printinfo(int L, int R, int l, int r, node *p) {\n        printnode(l,\
    \ r, p);\n        if (L <= l && R >= r)\n            return;\n        int mid\
    \ = (l + r) >> 1;\n        if (L < mid) printinfo(L, R, l, mid, p->l);\n     \
    \   if (R > mid) printinfo(L, R, mid, r, p->r);\n    }\n    void printall(int\
    \ l, int r, node *p) {\n        printnode(l, r, p);\n        if (r - l == 1) return;\n\
    \        int mid = (l + r) >> 1;\n        printall(l, mid, p->l);\n        printall(mid,\
    \ r, p->r);\n    }\npublic:\n    PointerSegmentTree(const std::vector<Value> &data):\
    \ n(data.size()), root(nullptr) { \n        initialize(0, n, root, data);\n  \
    \  }\n    PointerSegmentTree(int size) requires (!dynamic) : PointerSegmentTree(vector<Value>(size))\
    \ {}\n    PointerSegmentTree(int size = 0) requires (dynamic || persistent) :\
    \ n(size), root(nullptr) {}\n    Value get(int x) {\n        assert(0 <= x &&\
    \ x < n);\n        return get(x, 0, n, root);\n    }\n    Value range_prod(int\
    \ l, int r) {\n        assert(0 <= l && r <= n);\n        assert(l <= r);\n  \
    \      if (l == r) return Value();\n        return range_prod(l, r, 0, n, root);\n\
    \    }\n    void modify(int x, const Value &v) {\n        assert(0 <= x && x <\
    \ n);\n        modify(x, 0, n, root, v);\n    }\n    void transform(int x, const\
    \ auto &func) {\n        assert(0 <= x && x < n);\n        transform(x, 0, n,\
    \ root, func);\n    }\n    void range_transform(int l, int r, const auto &tag)\
    \ requires (hasTag) {\n        assert(0 <= l && r <= n);\n        assert(l <=\
    \ r);\n        if (l < r)\n            range_transform(l, r, 0, n, root, tag);\n\
    \    }\n    void range_transform_beats(int l, int r, const auto &tag, const auto\
    \ &tag_condition) requires (hasTag) {\n        assert(0 <= l && r <= n);\n   \
    \     assert(l <= r);\n        if (l < r)\n            range_transform_beats(l,\
    \ r, 0, n, root, tag, tag_condition);\n    }\n    /*\n       For the given element\
    \ range [l, r)\n       Perform segment tree binary search within the range with\
    \ left half first \n       return fail if the node is empty\n     */\n    int\
    \ range_left_search(const auto &condition, int l = -1, int r = -1) {\n       \
    \ if (l == -1 && r == -1) l = 0, r = n;\n        assert(0 <= l && r <= n);\n \
    \       assert(l <= r);\n        if (l == r) return r;\n        return range_left_search(l,\
    \ r, 0, n, root, condition);\n    }\n    /*\n       For the given element range\
    \ (l, r]\n       Perform segment tree binary search within the range with right\
    \ half first \n     */\n    int range_right_search(const auto &condition, int\
    \ l = -1, int r = -1) {\n        if (l == -1 && r == -1) l = -1, r = n - 1;\n\
    \        ++l, ++r;\n        assert(0 <= l && r <= n);\n        assert(l <= r);\n\
    \        if (l == r) return l - 1;\n        return range_right_search(l, r, 0,\
    \ n, root, condition);\n    }\n    void range_copy(int l, int r, PointerSegmentTree\
    \ &other) requires (pushdown && persistent) {\n        assert(0 <= l && r <= n);\n\
    \        assert(l <= r);\n        if (l < r)\n            range_copy(l, r, 0,\
    \ n, root, other.root);\n    }\n    void printinfo(int l, int r) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        std::cerr << \"\\e[1;33mInfo\
    \ [\" << l << \", \" << r << \"):\\n\";\n        if (l < r) \n            printinfo(l,\
    \ r, 0, n, root);\n        std::cerr << \"\\e[0m\\n\";\n    }\n    void printall()\
    \ {\n        std::cerr << \"\\e[1;33mInfo all:\\n\";\n        printall(0, n, root);\n\
    \        std::cerr << \"\\e[0m\\n\";\n    }\n};\n#line 5 \"test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp\"\
    \n\n#line 2 \"Numeric/Modint.hpp\"\n\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    #line 2 \"Numeric/internal_math.hpp\"\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    \n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\nconstexpr\
    \ long long safe_mod(long long x, long long m) {\n    x %= m;\n    if (x < 0)\
    \ x += m;\n    return x;\n}\nconstexpr long long pow_mod_constexpr(long long x,\
    \ long long n, int m) {\n    if (m == 1) return 0;\n    unsigned int _m = (unsigned\
    \ int)(m);\n    unsigned long long r = 1;\n    unsigned long long y = safe_mod(x,\
    \ m);\n    while (n) {\n        if (n & 1) r = (r * y) % _m;\n        y = (y *\
    \ y) % _m;\n        n >>= 1;\n    }\n    return r;\n}\nconstexpr bool is_prime_constexpr(int\
    \ n) {\n    if (n <= 1) return false;\n    if (n == 2 || n == 7 || n == 61) return\
    \ true;\n    if (n % 2 == 0) return false;\n    long long d = n - 1;\n    while\
    \ (d % 2 == 0) d /= 2;\n    constexpr long long bases[3] = {2, 7, 61};\n    for\
    \ (long long a : bases) {\n        long long t = d;\n        long long y = pow_mod_constexpr(a,\
    \ t, n);\n        while (t != n - 1 && y != 1 && y != n - 1)\n            y =\
    \ y * y % n, t <<= 1;\n        if (y != n - 1 && t % 2 == 0)\n            return\
    \ false;\n    }\n    return true;\n}\ntemplate <int n> constexpr bool is_prime\
    \ = is_prime_constexpr(n);\nconstexpr std::pair<long long, long long> inv_gcd(long\
    \ long a, long long b) {\n    a = safe_mod(a, b);\n    if (a == 0) return {b,\
    \ 0};\n    long long s = b, t = a, m0 = 0, m1 = 1;\n    while (t) {\n        long\
    \ long u = s / t;\n        s -= t * u, m0 -= m1 * u;\n        auto tmp = s;\n\
    \        s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;\n    }\n    if (m0 < 0)\
    \ m0 += b / s;\n    return {s, m0};\n}\n}  // namespace internal\n\nnamespace\
    \ internal {\n#ifndef _MSC_VER\n    template <class T>\n        using is_signed_int128\
    \ =\n        typename std::conditional<std::is_same<T, __int128_t>::value ||\n\
    \        std::is_same<T, __int128>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using is_unsigned_int128 =\n        typename\
    \ std::conditional<std::is_same<T, __uint128_t>::value ||\n        std::is_same<T,\
    \ unsigned __int128>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using make_unsigned_int128 =\n        typename\
    \ std::conditional<std::is_same<T, __int128_t>::value,\n                 __uint128_t,\n\
    \                 unsigned __int128>;\n    template <class T>\n        using is_integral\
    \ = typename std::conditional<std::is_integral<T>::value ||\n        is_signed_int128<T>::value\
    \ ||\n        is_unsigned_int128<T>::value,\n        std::true_type,\n       \
    \ std::false_type>::type;\n    template <class T>\n        using is_signed_int\
    \ = typename std::conditional<(is_integral<T>::value &&\n                std::is_signed<T>::value)\
    \ ||\n        is_signed_int128<T>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using is_unsigned_int =\n        typename std::conditional<(is_integral<T>::value\
    \ &&\n                std::is_unsigned<T>::value) ||\n        is_unsigned_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<\n        is_signed_int128<T>::value,\n\
    \        make_unsigned_int128<T>,\n        typename std::conditional<std::is_signed<T>::value,\n\
    \        std::make_unsigned<T>,\n        std::common_type<T>>::type>::type;\n\
    #else\n    template <class T> using is_integral = typename std::is_integral<T>;\n\
    \    template <class T>\n        using is_signed_int =\n        typename std::conditional<is_integral<T>::value\
    \ && std::is_signed<T>::value,\n                 std::true_type,\n           \
    \      std::false_type>::type;\n    template <class T>\n        using is_unsigned_int\
    \ =\n        typename std::conditional<is_integral<T>::value &&\n        std::is_unsigned<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<is_signed_int<T>::value,\n\
    \              std::make_unsigned<T>,\n              std::common_type<T>>::type;\n\
    #endif\n    template <class T> using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\n\
    \    template <class T> using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\n\
    \    template <class T> using to_unsigned_t = typename to_unsigned<T>::type;\n\
    \    struct modint_base {};\n    struct static_modint_base : modint_base {};\n\
    \    template <class T> using is_modint = std::is_base_of<modint_base, T>;\n \
    \   template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\
    }  // namespace internal\n#line 5 \"Numeric/Modint.hpp\"\n\ntemplate <int m, std::enable_if_t<(1\
    \ <= m)>* = nullptr>\nstruct static_modint : internal::static_modint_base {\n\
    \    using mint = static_modint;\n\n  public:\n    static constexpr int mod()\
    \ { return m; }\n    static mint raw(int v) {\n        mint x;\n        x._v =\
    \ v;\n        return x;\n    }\n\n    static_modint() : _v(0) {}\n    template\
    \ <class T, internal::is_signed_int_t<T>* = nullptr>\n    static_modint(T v) {\n\
    \        long long x = (long long)(v % (long long)(umod()));\n        if (x <\
    \ 0) x += umod();\n        _v = (unsigned int)(x);\n    }\n    template <class\
    \ T, internal::is_unsigned_int_t<T>* = nullptr>\n    static_modint(T v) {\n  \
    \      _v = (unsigned int)(v % umod());\n    }\n\n    unsigned int val() const\
    \ { return _v; }\n\n    mint& operator++() {\n        _v++;\n        if (_v ==\
    \ umod()) _v = 0;\n        return *this;\n    }\n    mint& operator--() {\n  \
    \      if (_v == 0) _v = umod();\n        _v--;\n        return *this;\n    }\n\
    \    mint operator++(int) {\n        mint result = *this;\n        ++*this;\n\
    \        return result;\n    }\n    mint operator--(int) {\n        mint result\
    \ = *this;\n        --*this;\n        return result;\n    }\n\n    mint& operator+=(const\
    \ mint& rhs) {\n        _v += rhs._v;\n        if (_v >= umod()) _v -= umod();\n\
    \        return *this;\n    }\n    mint& operator-=(const mint& rhs) {\n     \
    \   _v -= rhs._v;\n        if (_v >= umod()) _v += umod();\n        return *this;\n\
    \    }\n    mint& operator*=(const mint& rhs) {\n        unsigned long long z\
    \ = _v;\n        z *= rhs._v;\n        _v = (unsigned int)(z % umod());\n    \
    \    return *this;\n    }\n    mint& operator/=(const mint& rhs) { return *this\
    \ = *this * rhs.inv(); }\n\n    mint operator+() const { return *this; }\n   \
    \ mint operator-() const { return mint() - *this; }\n\n    mint pow(long long\
    \ n) const {\n        assert(0 <= n);\n        mint x = *this, r = 1;\n      \
    \  while (n) {\n            if (n & 1) r *= x;\n            x *= x;\n        \
    \    n >>= 1;\n        }\n        return r;\n    }\n    mint inv() const {\n \
    \       if (prime) {\n            assert(_v);\n            return pow(umod() -\
    \ 2);\n        } else {\n            auto eg = internal::inv_gcd(_v, m);\n   \
    \         assert(eg.first == 1);\n            return eg.second;\n        }\n \
    \   }\n\n    friend mint operator+(const mint& lhs, const mint& rhs) {\n     \
    \   return mint(lhs) += rhs;\n    }\n    friend mint operator-(const mint& lhs,\
    \ const mint& rhs) {\n        return mint(lhs) -= rhs;\n    }\n    friend mint\
    \ operator*(const mint& lhs, const mint& rhs) {\n        return mint(lhs) *= rhs;\n\
    \    }\n    friend mint operator/(const mint& lhs, const mint& rhs) {\n      \
    \  return mint(lhs) /= rhs;\n    }\n    friend bool operator==(const mint& lhs,\
    \ const mint& rhs) {\n        return lhs._v == rhs._v;\n    }\n    friend bool\
    \ operator!=(const mint& lhs, const mint& rhs) {\n        return lhs._v != rhs._v;\n\
    \    }\n    friend std::strong_ordering operator<=>(const mint& lhs, const mint&\
    \ rhs) {\n        return lhs._v <=> rhs._v;\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const mint& v) {\n        os << v._v;\n        return os;\n    }\n    friend\
    \ std::istream& operator>>(std::istream& is, mint& v) {\n        long long x;\n\
    \        is >> x;\n        x %= (long long)(umod());\n        if (x < 0) x +=\
    \ umod();\n        v._v = (unsigned int)(x);\n        return is;\n    }\n\n  private:\n\
    \    unsigned int _v;\n    static constexpr unsigned int umod() { return m; }\n\
    \    static constexpr bool prime = internal::is_prime<m>;\n};\n\nusing modint998244353\
    \ = static_modint<998244353>;\nusing modint1000000007 = static_modint<1000000007>;\n\
    #line 7 \"test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp\"\
    \n\nusing mint = modint998244353;\n\nstruct Tag {\n    mint a, b;\n    Tag(mint\
    \ _a = 1, mint _b = 0): a(_a), b(_b) {}\n    Tag operator+(const Tag &rhs) {\n\
    \        return Tag(a * rhs.a, rhs.a * b + rhs.b);\n    }\n};\n\nstruct Value\
    \ {\n    mint mul;\n    int add;\n    Value(mint a = 0, int b = 1): mul(a), add(b)\
    \ {}\n    Value operator+(const Value &rhs) {\n        return Value(mul + rhs.mul,\
    \ add + rhs.add);\n    }\n    Value operator+(const Tag &tag) {\n        return\
    \ Value(tag.a * mul + tag.b * add, add);\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const Value &v) {\n        os << v.mul;\n        return os;\n    }\n   \
    \ friend std::istream& operator>>(std::istream& is, Value &v) {\n        is >>\
    \ v.mul;\n        v.add = 1;\n        return is;\n    }\n};\n\nusing segtree =\
    \ PointerSegmentTree<Value, Tag, true, DefaultAllocator, false, true>;\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n\
    \    std::cin >> n >> q;\n    std::vector<Value> arr(n);\n    for (auto &v : arr)\n\
    \        std::cin >> v;\n    std::vector<segtree> seg(q + 1);\n    seg[0] = segtree(arr);\n\
    \    for (int i = 1; i <= q; ++i) {\n        int k, t;\n        std::cin >> t\
    \ >> k;\n        ++k;\n        seg[i] = seg[k];\n        if (t == 0) {\n     \
    \       int l, r;\n            Tag tag;\n            std::cin >> l >> r >> tag.a\
    \ >> tag.b;\n            seg[i].range_transform(l, r, tag);\n        }\n     \
    \   else if (t == 1) {\n            int s, l, r;\n            std::cin >> s >>\
    \ l >> r;\n            ++s;\n            if (i != s) seg[i].range_copy(l, r, seg[s]);\n\
    \        }\n        else {\n            int l, r;\n            std::cin >> l >>\
    \ r;\n            std::cout << seg[i].range_prod(l, r) << \"\\n\";\n        }\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_range_affine_range_sum\"\
    \n#include \"assumption.hpp\"\n\n#include \"DataStructure/PointerSegmentTree.hpp\"\
    \n\n#include \"Numeric/Modint.hpp\"\n\nusing mint = modint998244353;\n\nstruct\
    \ Tag {\n    mint a, b;\n    Tag(mint _a = 1, mint _b = 0): a(_a), b(_b) {}\n\
    \    Tag operator+(const Tag &rhs) {\n        return Tag(a * rhs.a, rhs.a * b\
    \ + rhs.b);\n    }\n};\n\nstruct Value {\n    mint mul;\n    int add;\n    Value(mint\
    \ a = 0, int b = 1): mul(a), add(b) {}\n    Value operator+(const Value &rhs)\
    \ {\n        return Value(mul + rhs.mul, add + rhs.add);\n    }\n    Value operator+(const\
    \ Tag &tag) {\n        return Value(tag.a * mul + tag.b * add, add);\n    }\n\
    \    friend std::ostream& operator<<(std::ostream& os, const Value &v) {\n   \
    \     os << v.mul;\n        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, Value &v) {\n        is >> v.mul;\n        v.add = 1;\n        return is;\n\
    \    }\n};\n\nusing segtree = PointerSegmentTree<Value, Tag, true, DefaultAllocator,\
    \ false, true>;\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<Value> arr(n);\n    for\
    \ (auto &v : arr)\n        std::cin >> v;\n    std::vector<segtree> seg(q + 1);\n\
    \    seg[0] = segtree(arr);\n    for (int i = 1; i <= q; ++i) {\n        int k,\
    \ t;\n        std::cin >> t >> k;\n        ++k;\n        seg[i] = seg[k];\n  \
    \      if (t == 0) {\n            int l, r;\n            Tag tag;\n          \
    \  std::cin >> l >> r >> tag.a >> tag.b;\n            seg[i].range_transform(l,\
    \ r, tag);\n        }\n        else if (t == 1) {\n            int s, l, r;\n\
    \            std::cin >> s >> l >> r;\n            ++s;\n            if (i !=\
    \ s) seg[i].range_copy(l, r, seg[s]);\n        }\n        else {\n           \
    \ int l, r;\n            std::cin >> l >> r;\n            std::cout << seg[i].range_prod(l,\
    \ r) << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - DataStructure/PointerSegmentTree.hpp
  - DataStructure/DefaultAllocator.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 18:28:09+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp
- /verify/test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp.html
title: test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp
---
