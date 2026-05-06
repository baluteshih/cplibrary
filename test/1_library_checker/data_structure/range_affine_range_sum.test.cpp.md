---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/SegmentTree.hpp
    title: DataStructure/SegmentTree.hpp
  - icon: ':question:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  - icon: ':question:'
    path: default_code.hpp
    title: default_code.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/range_affine_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n\
    #line 2 \"default_code.hpp\"\n\n#include <bits/stdc++.h>\nusing namespace std;\n\
    typedef long long ll;\ntypedef pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n\
    #define X first\n#define Y second\n#define SZ(a) ((int)a.size())\n#define ALL(v)\
    \ v.begin(), v.end()\ntemplate<class A, class B>\nostream& operator<<(ostream&\
    \ os, const pair<A, B> &a) {\n    os << \"(\" << a.first << \", \" << a.second\
    \ << \")\";\n    return os;\n}\ntemplate <typename T>\nconcept PrintableContainer\
    \ = requires(T& a) {\n    a.begin();\n    a.end();\n} && !std::same_as<std::remove_cvref_t<T>,\
    \ std::string> &&\n     !std::same_as<std::remove_cvref_t<T>, std::string_view>\
    \ &&\n     !std::is_convertible_v<T, const char*>;\ntemplate <PrintableContainer\
    \ T>\nstd::ostream& operator<<(std::ostream& os, const T& a) {\n    os << \"[\
    \ \";\n    bool first = true;\n    for (const auto& item : a) {\n        if (!first)\
    \ os << \", \";\n        os << item;\n        first = false;\n    }\n    return\
    \ os << \" ]\";\n}\n#ifdef bbq\n#include <experimental/iterator>\n#define safe\
    \ cerr<<__PRETTY_FUNCTION__<<\" line \"<<__LINE__<<\" safe\\n\"\n#define sepline\
    \ sepline_() \n#define debug(a...) debug_(#a, a)\n#define orange(a...) orange_(#a,\
    \ a)\nvoid debug_(auto s, auto ...a) {\n    cerr << \"\\e[1;32m(\" << s << \"\
    ) = (\";\n    int f = 0;\n    (..., (cerr << (f++ ? \", \" : \"\") << a));\n \
    \   cerr << \")\\e[0m\\n\";\n}\nvoid orange_(auto s, auto L, auto R) {\n    cerr\
    \ << \"\\e[1;33m[ \" << s << \" ] = [ \";\n    using namespace experimental;\n\
    \    copy(L, R, make_ostream_joiner(cerr, \", \"));\n    cerr << \" ]\\e[0m\\\
    n\";\n}\nvoid sepline_(int length = 50) {\n    cerr << \"\\e[1;35m\";\n    cerr\
    \ << string(length, '=');\n    cerr << \"\\e[0m\\n\";\n}\n#else\n#define safe\
    \ ((void)0)\n#define sepline safe\n#define debug(...) safe\n#define orange(...)\
    \ safe\n#endif\n\nvoid chmax(auto &x, auto val) {\n    x = max(x, val);\n}\n\n\
    void chmin(auto &x, auto val) {\n    x = min(x, val);\n}\n\nvector<int> count_array(const\
    \ auto &container, int sz = -1) {\n    if (sz == -1) sz = *ranges::max_element(container)\
    \ + 1;\n    vector<int> res(sz);\n    for (auto x : container) ++res[x];\n   \
    \ return res;\n}\n\ntemplate<class T>\nvoid discretization(vector<T> &vals) {\n\
    \    ranges::sort(vals);\n    vals.erase(ranges::unique(vals).begin(), vals.end());\n\
    }\n#line 3 \"test/1_library_checker/data_structure/range_affine_range_sum.test.cpp\"\
    \n\n#line 2 \"DataStructure/SegmentTree.hpp\"\n\ntemplate<typename Value = int,\
    \ typename Tag = void, bool pushdown = true>\nclass SegmentTree {\n    static\
    \ constexpr bool hasTag = !std::is_same_v<Tag, void>;\n    static_assert(pushdown\
    \ || hasTag, \"Lazy tag must exist when pushdown is false\");\n    int n;\n  \
    \  vector<Value> seg;\n    struct Empty {};\n    [[no_unique_address]] std::conditional_t<hasTag,\
    \ std::vector<Tag>, Empty> lazy;\n    Value get_val(int rt) {\n        if constexpr\
    \ (pushdown) return seg[rt];\n        else return seg[rt] + lazy[rt];\n    }\n\
    \    void up(int rt) {\n        seg[rt] = get_val(rt << 1) + get_val(rt << 1 |\
    \ 1);\n    }\n    void give_tag(int rt, auto tag) requires (hasTag) {\n      \
    \  if constexpr (pushdown) seg[rt] = seg[rt] + tag;\n        lazy[rt] = lazy[rt]\
    \ + tag;\n    }\n    void down(int rt) requires (hasTag && pushdown) {\n     \
    \   give_tag(rt << 1, lazy[rt]);\n        give_tag(rt << 1 | 1, lazy[rt]);\n \
    \       lazy[rt] = Tag();\n    }\n    void initialize(int l, int r, int rt, const\
    \ vector<Value> &data) {\n        if (r - l == 1) \n            return seg[rt]\
    \ = data[l], void();\n        int mid = (l + r) >> 1;\n        initialize(l, mid,\
    \ rt << 1, data);\n        initialize(mid, r, rt << 1 | 1, data);\n        up(rt);\n\
    \    }\n    Value range_prod(int L, int R, int l, int r, int rt) {\n        if\
    \ (L <= l && R >= r)\n            return get_val(rt);\n        if constexpr (hasTag\
    \ && pushdown) down(rt);\n        int mid = (l + r) >> 1;\n        if constexpr\
    \ (pushdown) {\n            if (R <= mid) return range_prod(L, R, l, mid, rt <<\
    \ 1);\n            if (L >= mid) return range_prod(L, R, mid, r, rt << 1 | 1);\n\
    \            return range_prod(L, R, l, mid, rt << 1) + range_prod(L, R, mid,\
    \ r, rt << 1 | 1); \n        }\n        else {\n            if (R <= mid) return\
    \ range_prod(L, R, l, mid, rt << 1) + lazy[rt];\n            if (L >= mid) return\
    \ range_prod(L, R, mid, r, rt << 1 | 1) + lazy[rt];\n            return range_prod(L,\
    \ R, l, mid, rt << 1) + range_prod(L, R, mid, r, rt << 1 | 1) + lazy[rt];\n  \
    \      }\n    }\n    void modify(int x, int l, int r, int rt, const Value &v)\
    \ {\n        if (r - l == 1)\n            return seg[rt] = v, void();\n      \
    \  if constexpr (hasTag && pushdown) down(rt);\n        int mid = (l + r) >> 1;\n\
    \        if constexpr (pushdown) {\n            if (x < mid) modify(x, l, mid,\
    \ rt << 1, v);\n            else modify(x, mid, r, rt << 1 | 1, v);\n        }\n\
    \        else {\n            if (x < mid) modify(x, l, mid, rt << 1, v - lazy[rt]);\n\
    \            else modify(x, mid, r, rt << 1 | 1, v - lazy[rt]);\n        }\n \
    \       up(rt);\n    }\n    void transform(int x, int l, int r, int rt, const\
    \ auto &func) {\n        if (r - l == 1)\n            return func(seg[rt]), void();\n\
    \        if constexpr (hasTag && pushdown) down(rt);\n        int mid = (l + r)\
    \ >> 1;\n        if (x < mid) transform(x, l, mid, rt << 1, func);\n        else\
    \ transform(x, mid, r, rt << 1 | 1, func);\n        up(rt);\n    }\n    void range_transform(int\
    \ L, int R, int l, int r, int rt, const auto &tag) requires (hasTag) {\n     \
    \   if (L <= l && R >= r)\n            return give_tag(rt, tag);\n        if constexpr\
    \ (pushdown) down(rt);\n        int mid = (l + r) >> 1;\n        if (L < mid)\
    \ range_transform(L, R, l, mid, rt << 1, tag);\n        if (R > mid) range_transform(L,\
    \ R, mid, r, rt << 1 | 1, tag);\n        up(rt);\n    }\n    void range_transform_beats(int\
    \ L, int R, int l, int r, int rt, const auto &tag, const auto &tag_condition,\
    \ auto... tag_sum) requires (hasTag) {\n        if (L <= l && R >= r && tag_condition([&]{\
    \ if constexpr(pushdown) return seg[rt]; else return get_val(rt) + (..., tag_sum);\
    \ }()))\n            return give_tag(rt, tag);\n        assert(r - l > 1);\n \
    \       if constexpr (pushdown) down(rt);\n        else ((tag_sum = tag_sum +\
    \ lazy[rt]), ...);\n        int mid = (l + r) >> 1;\n        if (L < mid) range_transform_beats(L,\
    \ R, l, mid, rt << 1, tag, tag_condition, tag_sum...);\n        if (R > mid) range_transform_beats(L,\
    \ R, mid, r, rt << 1 | 1, tag, tag_condition, tag_sum...);\n        up(rt);\n\
    \    }\n    int range_left_search(int L, int R, int l, int r, int rt, const auto\
    \ &condition, auto... tag_sum) {\n        if (r - l == 1) {\n            if (!condition([&]{\
    \ if constexpr(pushdown) return seg[rt]; else return get_val(rt) + (..., tag_sum);\
    \ }()))\n                return R;\n            return l;\n        }\n       \
    \ int mid = (l + r) >> 1;\n        if constexpr (hasTag && pushdown) down(rt);\n\
    \        if constexpr (!pushdown) ((tag_sum = tag_sum + lazy[rt]), ...);\n   \
    \     if (L <= l && R >= r) {\n            if (condition([&]{ if constexpr(pushdown)\
    \ return seg[rt << 1]; else return get_val(rt << 1) + (..., tag_sum); }()))\n\
    \                return range_left_search(L, R, l, mid, rt << 1, condition, tag_sum...);\n\
    \            return range_left_search(L, R, mid, r, rt << 1 | 1, condition, tag_sum...);\n\
    \        }\n        int left = R;\n        if (L < mid) left = range_left_search(L,\
    \ R, l, mid, rt << 1, condition, tag_sum...);\n        if (left == R) {\n    \
    \        if (R > mid) return range_left_search(L, R, mid, r, rt << 1 | 1, condition,\
    \ tag_sum...);\n            return R;\n        }\n        return left;\n    }\n\
    \    int range_right_search(int L, int R, int l, int r, int rt, const auto &condition,\
    \ auto... tag_sum) {\n        if (r - l == 1) {\n            if (!condition([&]{\
    \ if constexpr(pushdown) return seg[rt]; else return get_val(rt) + (..., tag_sum);\
    \ }()))\n                return L - 1;\n            return l;\n        }\n   \
    \     int mid = (l + r) >> 1;\n        if constexpr (hasTag && pushdown) down(rt);\n\
    \        if constexpr (!pushdown) ((tag_sum = tag_sum + lazy[rt]), ...);\n   \
    \     if (L <= l && R >= r) {\n            if (condition([&]{ if constexpr(pushdown)\
    \ return seg[rt << 1 | 1]; else return get_val(rt << 1 | 1) + (..., tag_sum);\
    \ }()))\n                return range_right_search(L, R, mid, r, rt << 1 | 1,\
    \ condition, tag_sum...);\n            return range_right_search(L, R, l, mid,\
    \ rt << 1, condition, tag_sum...);\n        }\n        int right = L - 1;\n  \
    \      if (R > mid) right = range_right_search(L, R, mid, r, rt << 1 | 1, condition,\
    \ tag_sum...);\n        if (right == L - 1) {\n            if (L < mid) return\
    \ range_right_search(L, R, l, mid, rt << 1, condition, tag_sum...);\n        \
    \    return L - 1;\n        }\n        return right;\n    }\n    Value get(int\
    \ x, int l, int r, int rt) {\n        [[no_unique_address]] std::conditional_t<!pushdown,\
    \ Tag, Empty> tag;\n        while (r - l > 1) {\n            if constexpr (hasTag\
    \ && pushdown) down(rt);\n            if constexpr (!pushdown) tag = tag + lazy[rt];\n\
    \            int mid = (l + r) >> 1;\n            if (x < mid) r = mid, rt = rt\
    \ << 1;\n            else l = mid, rt = rt << 1 | 1;\n        }\n        if constexpr\
    \ (pushdown) return seg[rt];\n        else return get_val(rt) + tag;\n    }\n\
    \    void printnode(int l, int r, int rt) {\n        std::cerr << \"[\" << l <<\
    \ \", \" << r << \"): \";\n        if constexpr (hasTag) std::cerr << \"val =\
    \ \" << seg[rt] << \", tag = \" << lazy[rt];\n        else std::cerr << seg[rt];\n\
    \        std::cerr << \"\\n\";\n    }\n    void printinfo(int L, int R, int l,\
    \ int r, int rt) {\n        printnode(l, r, rt);\n        if (L <= l && R >= r)\n\
    \            return;\n        int mid = (l + r) >> 1;\n        if (L < mid) printinfo(L,\
    \ R, l, mid, rt << 1);\n        if (R > mid) printinfo(L, R, mid, r, rt << 1 |\
    \ 1);\n    }\n    void printall(int l, int r, int rt) {\n        printnode(l,\
    \ r, rt);\n        if (r - l == 1) return;\n        int mid = (l + r) >> 1;\n\
    \        printall(l, mid, rt << 1);\n        printall(mid, r, rt << 1 | 1);\n\
    \    }\n    public:\n    SegmentTree(const vector<Value> &data): n(data.size()),\
    \ seg(n << 2) { \n        if constexpr (hasTag) lazy.resize(n << 2); \n      \
    \  initialize(0, n, 1, data);\n    }\n    SegmentTree(int size): SegmentTree(vector<Value>(size))\
    \ {}\n    Value get(int x) {\n        assert(0 <= x && x < n);\n        return\
    \ get(x, 0, n, 1);\n    }\n    Value range_prod(int l, int r) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        if (l == r) return Value();\n\
    \        return range_prod(l, r, 0, n, 1);\n    }\n    void modify(int x, const\
    \ Value &v) {\n        assert(0 <= x && x < n);\n        modify(x, 0, n, 1, v);\n\
    \    }\n    void transform(int x, const auto &func) {\n        assert(0 <= x &&\
    \ x < n);\n        transform(x, 0, n, 1, func);\n    }\n    void range_transform(int\
    \ l, int r, const auto &tag) requires (hasTag) {\n        assert(0 <= l && r <=\
    \ n);\n        assert(l <= r);\n        if (l < r)\n            range_transform(l,\
    \ r, 0, n, 1, tag);\n    }\n    void range_transform_beats(int l, int r, const\
    \ auto &tag, const auto &tag_condition) requires (hasTag) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        if (l < r)\n            range_transform_beats(l,\
    \ r, 0, n, 1, tag, tag_condition);\n    }\n    /*\n       For the given element\
    \ range [l, r)\n       Perform segment tree binary search within the range with\
    \ left half first \n     */\n    int range_left_search(const auto &condition,\
    \ int l = -1, int r = -1) {\n        if (l == -1 && r == -1) l = 0, r = n;\n \
    \       assert(0 <= l && r <= n);\n        assert(l <= r);\n        if (l == r)\
    \ return r;\n        return range_left_search(l, r, 0, n, 1, condition);\n   \
    \ }\n    /*\n       For the given element range (l, r]\n       Perform segment\
    \ tree binary search within the range with right half first \n     */\n    int\
    \ range_right_search(const auto &condition, int l = -1, int r = -1) {\n      \
    \  if (l == -1 && r == -1) l = -1, r = n - 1;\n        ++l, ++r;\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        if (l == r) return l - 1;\n\
    \        return range_right_search(l, r, 0, n, 1, condition);\n    }\n    void\
    \ printinfo(int l, int r) {\n        assert(0 <= l && r <= n);\n        assert(l\
    \ <= r);\n        std::cerr << \"\\e[1;33mInfo [\" << l << \", \" << r << \"):\\\
    n\";\n        if (l < r) \n            printinfo(l, r, 0, n, 1);\n        cerr\
    \ << \"\\e[0m\\n\";\n    }\n    void printall() {\n        std::cerr << \"\\e[1;33mInfo\
    \ all:\\n\";\n        printall(0, n, 1);\n        cerr << \"\\e[0m\\n\";\n   \
    \ }\n};\n#line 5 \"test/1_library_checker/data_structure/range_affine_range_sum.test.cpp\"\
    \n\n#line 2 \"Numeric/Modint.hpp\"\n\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    #line 2 \"Numeric/internal_math.hpp\"\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    \n#line 7 \"Numeric/internal_math.hpp\"\n#include <type_traits>\n\n#ifdef _MSC_VER\n\
    #include <intrin.h>\n#endif\n\nnamespace internal {\n\n// @param m `1 <= m`\n\
    // @return x mod m\nconstexpr long long safe_mod(long long x, long long m) {\n\
    \    x %= m;\n    if (x < 0) x += m;\n    return x;\n}\n\n// Fast modular multiplication\
    \ by barrett reduction\n// Reference: https://en.wikipedia.org/wiki/Barrett_reduction\n\
    // NOTE: reconsider after Ice Lake\nstruct barrett {\n    unsigned int _m;\n \
    \   unsigned long long im;\n    explicit barrett(unsigned int m) : _m(m), im((unsigned\
    \ long long)(-1) / m + 1) {}\n    unsigned int umod() const { return _m; }\n \
    \   unsigned int modulo(unsigned long long z) const {\n        if (_m == 1) return\
    \ 0;\n#ifdef _MSC_VER\n        unsigned long long x;\n        _umul128(z, im,\
    \ &x);\n#else\n        unsigned long long x = (unsigned long long)(((unsigned\
    \ __int128)(z)*im) >> 64);\n#endif\n        unsigned long long y = x * _m;\n \
    \       return (z - y + (z < y ? _m : 0));\n    }\n    unsigned int mul(unsigned\
    \ int a, unsigned int b) const {\n        return modulo((unsigned long long)a\
    \ * b);\n    }\n    unsigned long long floor(unsigned long long z) const {\n \
    \       if (_m == 1) return z;\n        unsigned long long x = (unsigned long\
    \ long)(((unsigned __int128)(z)*im) >> 64);\n        unsigned long long y = x\
    \ * _m;\n        return (z < y ? x - 1 : x);\n    }\n    std::pair<unsigned long\
    \ long, unsigned int> divmod(unsigned long long z) const {\n        if (_m ==\
    \ 1) return {z, 0};\n        unsigned long long x = (unsigned long long)(((unsigned\
    \ __int128)(z)*im) >> 64);\n        unsigned long long y = x * _m;\n        if\
    \ (z < y) return {x - 1, z - y + _m};\n        return {x, z - y};\n    }\n};\n\
    \n// @param n `0 <= n`\n// @param m `1 <= m`\n// @return `(x ** n) % m`\nconstexpr\
    \ long long pow_mod_constexpr(long long x, long long n, int m) {\n    if (m ==\
    \ 1) return 0;\n    unsigned int _m = (unsigned int)(m);\n    unsigned long long\
    \ r = 1;\n    unsigned long long y = safe_mod(x, m);\n    while (n) {\n      \
    \  if (n & 1) r = (r * y) % _m;\n        y = (y * y) % _m;\n        n >>= 1;\n\
    \    }\n    return r;\n}\n\n// Reference:\n// M. Forisek and J. Jancina,\n// Fast\
    \ Primality Testing for Integers That Fit into a Machine Word\n// @param n `0\
    \ <= n`\nconstexpr bool is_prime_constexpr(int n) {\n    if (n <= 1) return false;\n\
    \    if (n == 2 || n == 7 || n == 61) return true;\n    if (n % 2 == 0) return\
    \ false;\n    long long d = n - 1;\n    while (d % 2 == 0) d /= 2;\n    constexpr\
    \ long long bases[3] = {2, 7, 61};\n    for (long long a : bases) {\n        long\
    \ long t = d;\n        long long y = pow_mod_constexpr(a, t, n);\n        while\
    \ (t != n - 1 && y != 1 && y != n - 1) {\n            y = y * y % n;\n       \
    \     t <<= 1;\n        }\n        if (y != n - 1 && t % 2 == 0) {\n         \
    \   return false;\n        }\n    }\n    return true;\n}\ntemplate <int n> constexpr\
    \ bool is_prime = is_prime_constexpr(n);\n\n// @param b `1 <= b`\n// @return pair(g,\
    \ x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g\nconstexpr std::pair<long\
    \ long, long long> inv_gcd(long long a, long long b) {\n    a = safe_mod(a, b);\n\
    \    if (a == 0) return {b, 0};\n\n    // Contracts:\n    // [1] s - m0 * a =\
    \ 0 (mod b)\n    // [2] t - m1 * a = 0 (mod b)\n    // [3] s * |m1| + t * |m0|\
    \ <= b\n    long long s = b, t = a;\n    long long m0 = 0, m1 = 1;\n\n    while\
    \ (t) {\n        long long u = s / t;\n        s -= t * u;\n        m0 -= m1 *\
    \ u;  // |m1 * u| <= |m1| * s <= b\n\n        // [3]:\n        // (s - t * u)\
    \ * |m1| + t * |m0 - m1 * u|\n        // <= s * |m1| - t * u * |m1| + t * (|m0|\
    \ + |m1| * u)\n        // = s * |m1| + t * |m0| <= b\n\n        auto tmp = s;\n\
    \        s = t;\n        t = tmp;\n        tmp = m0;\n        m0 = m1;\n     \
    \   m1 = tmp;\n    }\n    // by [3]: |m0| <= b/g\n    // by g != b: |m0| < b/g\n\
    \    if (m0 < 0) m0 += b / s;\n    return {s, m0};\n}\n}  // namespace internal\n\
    \nnamespace internal {\n\n#ifndef _MSC_VER\n    template <class T>\n        using\
    \ is_signed_int128 =\n        typename std::conditional<std::is_same<T, __int128_t>::value\
    \ ||\n        std::is_same<T, __int128>::value,\n        std::true_type,\n   \
    \     std::false_type>::type;\n\n    template <class T>\n        using is_unsigned_int128\
    \ =\n        typename std::conditional<std::is_same<T, __uint128_t>::value ||\n\
    \        std::is_same<T, unsigned __int128>::value,\n        std::true_type,\n\
    \        std::false_type>::type;\n\n    template <class T>\n        using make_unsigned_int128\
    \ =\n        typename std::conditional<std::is_same<T, __int128_t>::value,\n \
    \                __uint128_t,\n                 unsigned __int128>;\n\n    template\
    \ <class T>\n        using is_integral = typename std::conditional<std::is_integral<T>::value\
    \ ||\n        is_signed_int128<T>::value ||\n        is_unsigned_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using is_signed_int = typename std::conditional<(is_integral<T>::value\
    \ &&\n                std::is_signed<T>::value) ||\n        is_signed_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using is_unsigned_int =\n        typename std::conditional<(is_integral<T>::value\
    \ &&\n                std::is_unsigned<T>::value) ||\n        is_unsigned_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<\n        is_signed_int128<T>::value,\n\
    \        make_unsigned_int128<T>,\n        typename std::conditional<std::is_signed<T>::value,\n\
    \        std::make_unsigned<T>,\n        std::common_type<T>>::type>::type;\n\n\
    #else\n\n    template <class T> using is_integral = typename std::is_integral<T>;\n\
    \n    template <class T>\n        using is_signed_int =\n        typename std::conditional<is_integral<T>::value\
    \ && std::is_signed<T>::value,\n                 std::true_type,\n           \
    \      std::false_type>::type;\n\n    template <class T>\n        using is_unsigned_int\
    \ =\n        typename std::conditional<is_integral<T>::value &&\n        std::is_unsigned<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<is_signed_int<T>::value,\n\
    \              std::make_unsigned<T>,\n              std::common_type<T>>::type;\n\
    \n#endif\n\n    template <class T>\n        using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\n\
    \n    template <class T>\n        using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\n\
    \n    template <class T> using to_unsigned_t = typename to_unsigned<T>::type;\n\
    \n}  // namespace internal\n\n#line 229 \"Numeric/internal_math.hpp\"\n\n#ifdef\
    \ _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\n\n    struct\
    \ modint_base {};\n    struct static_modint_base : modint_base {};\n\n    template\
    \ <class T> using is_modint = std::is_base_of<modint_base, T>;\n    template <class\
    \ T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\n}  // namespace\
    \ internal\n#line 5 \"Numeric/Modint.hpp\"\n\ntemplate <int m, std::enable_if_t<(1\
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
    \ rhs) {\n        return lhs._v <=> rhs._v;\n    }\n    friend ostream& operator<<(ostream&\
    \ os, const mint& v) {\n        os << v._v;\n        return os;\n    }\n    friend\
    \ istream& operator>>(istream& is, mint& v) {\n        long long x;\n        is\
    \ >> x;\n        x %= (long long)(umod());\n        if (x < 0) x += umod();\n\
    \        v._v = (unsigned int)(x);\n        return is;\n    }\n\n  private:\n\
    \    unsigned int _v;\n    static constexpr unsigned int umod() { return m; }\n\
    \    static constexpr bool prime = internal::is_prime<m>;\n};\n\nusing modint998244353\
    \ = static_modint<998244353>;\nusing modint1000000007 = static_modint<1000000007>;\n\
    #line 7 \"test/1_library_checker/data_structure/range_affine_range_sum.test.cpp\"\
    \n\nusing mint = modint998244353;\n\nstruct Tag {\n    mint a, b;\n    Tag(mint\
    \ _a = 1, mint _b = 0): a(_a), b(_b) {}\n    Tag operator+(const Tag &rhs) {\n\
    \        return Tag(a * rhs.a, rhs.a * b + rhs.b);\n    }\n};\n\nstruct Value\
    \ {\n    mint mul;\n    int add;\n    Value(mint a = 0, int b = 1): mul(a), add(b)\
    \ {}\n    Value operator+(const Value &rhs) {\n        return Value(mul + rhs.mul,\
    \ add + rhs.add);\n    }\n    Value operator+(const Tag &tag) {\n        return\
    \ Value(tag.a * mul + tag.b * add, add);\n    }\n    friend ostream& operator<<(ostream&\
    \ os, const Value &v) {\n        os << v.mul;\n        return os;\n    }\n   \
    \ friend istream& operator>>(istream& is, Value &v) {\n        is >> v.mul;\n\
    \        v.add = 1;\n        return is;\n    }\n};\n\nint main() {\n    ios::sync_with_stdio(0),\
    \ cin.tie(0);\n    int n, q;\n    cin >> n >> q;\n    vector<Value> arr(n);\n\
    \    for (auto &v : arr)\n        cin >> v;\n    SegmentTree<Value, Tag> seg(arr);\n\
    \    while (q--) {\n        int t;\n        cin >> t;\n        if (t == 0) {\n\
    \            int l, r;\n            Tag tag;\n            cin >> l >> r >> tag.a\
    \ >> tag.b;\n            seg.range_transform(l, r, tag);\n        }\n        else\
    \ {\n            int l, r;\n            cin >> l >> r;\n            cout << seg.range_prod(l,\
    \ r) << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n#include \"default_code.hpp\"\n\n#include \"DataStructure/SegmentTree.hpp\"\n\
    \n#include \"Numeric/Modint.hpp\"\n\nusing mint = modint998244353;\n\nstruct Tag\
    \ {\n    mint a, b;\n    Tag(mint _a = 1, mint _b = 0): a(_a), b(_b) {}\n    Tag\
    \ operator+(const Tag &rhs) {\n        return Tag(a * rhs.a, rhs.a * b + rhs.b);\n\
    \    }\n};\n\nstruct Value {\n    mint mul;\n    int add;\n    Value(mint a =\
    \ 0, int b = 1): mul(a), add(b) {}\n    Value operator+(const Value &rhs) {\n\
    \        return Value(mul + rhs.mul, add + rhs.add);\n    }\n    Value operator+(const\
    \ Tag &tag) {\n        return Value(tag.a * mul + tag.b * add, add);\n    }\n\
    \    friend ostream& operator<<(ostream& os, const Value &v) {\n        os <<\
    \ v.mul;\n        return os;\n    }\n    friend istream& operator>>(istream& is,\
    \ Value &v) {\n        is >> v.mul;\n        v.add = 1;\n        return is;\n\
    \    }\n};\n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int\
    \ n, q;\n    cin >> n >> q;\n    vector<Value> arr(n);\n    for (auto &v : arr)\n\
    \        cin >> v;\n    SegmentTree<Value, Tag> seg(arr);\n    while (q--) {\n\
    \        int t;\n        cin >> t;\n        if (t == 0) {\n            int l,\
    \ r;\n            Tag tag;\n            cin >> l >> r >> tag.a >> tag.b;\n   \
    \         seg.range_transform(l, r, tag);\n        }\n        else {\n       \
    \     int l, r;\n            cin >> l >> r;\n            cout << seg.range_prod(l,\
    \ r) << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - DataStructure/SegmentTree.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2026-05-04 15:56:36+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/range_affine_range_sum.test.cpp
- /verify/test/1_library_checker/data_structure/range_affine_range_sum.test.cpp.html
title: test/1_library_checker/data_structure/range_affine_range_sum.test.cpp
---
