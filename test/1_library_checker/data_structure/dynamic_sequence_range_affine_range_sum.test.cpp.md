---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/size_value.hpp
    title: Algebra/size_value.hpp
  - icon: ':question:'
    path: DataStructure/DefaultAllocator.hpp
    title: Default Allocator
  - icon: ':question:'
    path: DataStructure/Treap.hpp
    title: Treap
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
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp\"\
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
    #line 2 \"DataStructure/Treap.hpp\"\n\n#line 2 \"DataStructure/DefaultAllocator.hpp\"\
    \n\ntemplate<typename T>\nstruct DefaultAllocator {\n    template<typename...\
    \ Args>\n    static T* allocate(Args&&... args) { \n        return new T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) { delete p; }\n};\n#line 2 \"Algebra/size_value.hpp\"\
    \n\nstruct size_v {\n    int sz;\n    size_v(int sz_ = 0): sz(sz_) {}\n    size_v\
    \ operator+(const size_v &rhs) const {\n        return size_v(sz + rhs.sz);\n\
    \    }\n    int size() const {\n        return sz; \n    }\n    friend std::ostream&\
    \ operator<<(std::ostream& os, const size_v &v) {\n        os << v.sz;\n     \
    \   return os;\n    }\n};\n#line 5 \"DataStructure/Treap.hpp\"\n\n#ifndef RNGSEED\n\
    \    #define RNGSEED 880301\n#endif\n\ntemplate<typename Key = void, \n      \
    \   typename Value = size_v,\n         typename Tag = void, \n         bool Rev\
    \ = false,\n         template<typename> class Allocator = DefaultAllocator,\n\
    \         bool persistent = false\n>\nclass Treap {\n    static constexpr bool\
    \ hasKey = !std::is_same_v<Key, void>;\n    static constexpr bool hasValue = !std::is_same_v<Value,\
    \ void>;\n    static constexpr bool hasTag = !std::is_same_v<Tag, void>;\n   \
    \ static constexpr bool usePri = !persistent;\n    static constexpr bool hasSize\
    \ = requires(Value v) { v.size(); };\n    static constexpr bool hasValueReverse\
    \ = requires(Value v) { v.reverse(); };\n    struct Empty {};\n    template <bool\
    \ Condition, typename T>\n    static auto get_default() {\n        if constexpr\
    \ (Condition) return T();\n        else return Empty{};\n    }\n    template <bool\
    \ Condition>\n    static auto get_pri() {\n        if constexpr (Condition) return\
    \ rng();\n        else return Empty{};\n    }\n    static_assert(hasKey || hasValue);\n\
    \    static_assert(!hasTag || hasValue);\n    static inline std::mt19937 rng{RNGSEED};\n\
    \    struct node {\n        node *l = nullptr, *r = nullptr;\n        [[no_unique_address]]\
    \ std::conditional_t<!persistent, node*, Empty> f = get_default<!persistent, node*>();\n\
    \        [[no_unique_address]] std::conditional_t<hasKey, Key, Empty> key = get_default<hasKey,\
    \ Key>();\n        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty>\
    \ org = get_default<hasValue, Value>();\n        [[no_unique_address]] std::conditional_t<hasValue,\
    \ Value, Empty> val = get_default<hasValue, Value>();\n        [[no_unique_address]]\
    \ std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag, Tag>();\n\
    \        [[no_unique_address]] std::conditional_t<Rev, int, Empty> rev = get_default<Rev,\
    \ int>();\n        [[no_unique_address]] std::conditional_t<usePri, unsigned,\
    \ Empty> pri = get_pri<usePri>();\n        void up() {\n            if constexpr\
    \ (hasValue) {\n                val = org;\n                if (l) val = l->val\
    \ + org;\n                if (r) val = val + r->val;\n            }\n        \
    \    if constexpr (!persistent) {\n                f = nullptr;\n            \
    \    if (l) l->f = this;\n                if (r) r->f = this;\n            }\n\
    \        }\n        void give_tag(const auto &tag) requires (hasTag) {\n     \
    \       org = org + tag; \n            val = val + tag;\n            lazy = lazy\
    \ + tag;\n        }\n        void reverse() requires (Rev) {\n            rev\
    \ ^= 1;\n            if constexpr (hasValueReverse) {\n                org.reverse();\n\
    \                val.reverse();\n            }\n            std::swap(l, r);\n\
    \        }\n        void down() requires (hasTag || Rev) {\n            bool need_rev\
    \ = false;\n            if constexpr (Rev) need_rev = rev;\n            bool need_tag\
    \ = false;\n            if constexpr (hasTag) { \n                if constexpr\
    \ (std::equality_comparable<Tag>) need_tag = (lazy != Tag());\n              \
    \  else need_tag = true;\n            }\n            if (!need_rev && !need_tag)\
    \ return;\n            if (l) {\n                if constexpr (persistent) l =\
    \ NodeAlloc::allocate(*l);\n                if constexpr (hasTag) if (need_tag)\
    \ l->give_tag(lazy);\n                if constexpr (Rev) if (need_rev) l->reverse();\n\
    \            }\n            if (r) {\n                if constexpr (persistent)\
    \ r = NodeAlloc::allocate(*r);\n                if constexpr (hasTag) if (need_tag)\
    \ r->give_tag(lazy);\n                if constexpr (Rev) if (need_rev) r->reverse();\n\
    \            }\n            if constexpr (hasTag) lazy = Tag();\n            if\
    \ constexpr (Rev) rev = 0;\n        }\n        node() = default;\n        node(const\
    \ auto &v) requires (!hasKey || !hasValue) {\n            if constexpr (hasKey)\
    \ key = Key(v);\n            else org = val = Value(v);\n        }\n        node(const\
    \ auto &k, const auto &v) requires (hasKey && hasValue) : key(k), org(v), val(v)\
    \ {\n        }\n        friend std::ostream& operator<<(std::ostream& os, const\
    \ node &v) {\n            if constexpr (hasKey && hasValue) os << \"{key = \"\
    \ << v.key << \", org = \" << v.org << \"}\";\n            else if constexpr (hasKey)\
    \ os << v.key;\n            else os << v.org;\n            return os;\n      \
    \  }\n        void debuginfo() const {\n            std::cerr << \"\\e[1;33minfo:\
    \ \";\n            auto printnode = [&](std::string name, node* ptr) {\n     \
    \           std::cerr << name << \": \";\n                if (ptr) std::cerr <<\
    \ *ptr;\n                else std::cerr << \"null\";\n            };\n       \
    \     printnode(\"l\", l), std::cerr << \", \";\n            printnode(\"r\",\
    \ r), std::cerr << \", \";\n            if constexpr (!persistent) printnode(\"\
    f\", f);\n            std::cerr << \"\\e[0m\\n\";\n        }\n    };\n    using\
    \ NodeAlloc = Allocator<node>;\n    node *root = nullptr;\n    static void split(node\
    \ *source, node *&left, node *&right, const auto &condition) {\n        if (!source)\
    \ return left = right = nullptr, void();\n        if constexpr (persistent) source\
    \ = NodeAlloc::allocate(*source); \n        if constexpr (hasTag || Rev) source->down();\n\
    \        if (condition(source)) {\n            left = source;\n            split(source->r,\
    \ left->r, right, condition);\n            left->up();\n        }\n        else\
    \ {\n            right = source;\n            split(source->l, left, right->l,\
    \ condition);\n            right->up();\n        }\n    }\n    static void split_value(node\
    \ *source, node *&left, node *&right, const auto &left_product, const auto &condition)\
    \ requires (hasValue) {\n        if (!source) return left = right = nullptr, void();\n\
    \        if constexpr (persistent) source = NodeAlloc::allocate(*source); \n \
    \       if constexpr (hasTag || Rev) source->down();\n        Value current =\
    \ left_product + get_val(source->l) + source->org;\n        if (condition(current))\
    \ {\n            left = source;\n            split_value(source->r, left->r, right,\
    \ current, condition);\n            left->up();\n        }\n        else {\n \
    \           right = source;\n            split_value(source->l, left, right->l,\
    \ left_product, condition);\n            right->up();\n        }\n    }\n    static\
    \ Value prefix_product(node *source, const auto &condition) requires (hasValue)\
    \ {\n        if (!source) return Value();\n        if constexpr (hasTag || Rev)\
    \ source->down();\n        if (condition(source))\n            return get_val(source->l)\
    \ + source->org + prefix_product(source->r, condition);\n        return prefix_product(source->l,\
    \ condition);\n    }\n    static Value prefix_product_cond(node *source, const\
    \ auto &left_product, const auto &condition) requires (hasValue) {\n        if\
    \ (!source) return left_product;\n        if constexpr (hasTag || Rev) source->down();\n\
    \        Value current = left_product + get_val(source->l) + source->org;\n  \
    \      if (condition(current))\n            return prefix_product_cond(source->r,\
    \ current, condition);\n        return prefix_product_cond(source->l, left_product,\
    \ condition);\n    }\n    static node *merge(node *left, node *right) {\n    \
    \    if (!left || !right) return left ? left : right;\n        bool useleft =\
    \ true;\n        if constexpr (usePri)\n            useleft = left->pri < right->pri;\n\
    \        else\n            useleft = rng() % (get_size(left) + get_size(right))\
    \ < size_t(get_size(left));\n        if (useleft) {\n            if constexpr\
    \ (persistent) left = NodeAlloc::allocate(*left); \n            if constexpr (hasTag\
    \ || Rev) left->down();\n            left->r = merge(left->r, right);\n      \
    \      left->up();\n            return left;\n        }\n        if constexpr\
    \ (persistent) right = NodeAlloc::allocate(*right);\n        if constexpr (hasTag\
    \ || Rev) right->down();\n        right->l = merge(left, right->l);\n        right->up();\n\
    \        return right;\n    }\n    static Key get_key(node *a) requires (hasKey)\
    \ {\n        return get_key(a, Key());\n    }\n    static Key get_key(node *a,\
    \ auto Default) requires (hasKey) {\n        return a ? a->key : Default;\n  \
    \  }\n    static Value get_org(node *a) requires (hasValue) {\n        return\
    \ a ? a->org : Value();\n    }\n    static Value get_org(node *a, auto Default)\
    \ requires (hasValue) {\n        return a ? a->org : Default;\n    }\n    static\
    \ Value get_val(node *a) requires (hasValue) {\n        return a ? a->val : Value();\n\
    \    }\n    static Value get_val(node *a, Value Default) requires (hasValue) {\n\
    \        return a ? a->val : Default;\n    }\n    static int get_size(node *a)\
    \ requires (hasSize) { \n        return a ? a->val.size() : 0;\n    }\n    static\
    \ void free(node *&ptr) requires (!persistent) {\n        if (ptr == nullptr)\
    \ return;\n        free(ptr->l);\n        free(ptr->r);\n        NodeAlloc::deallocate(ptr);\n\
    \        ptr = nullptr;\n    }\n    static node* find_min(node *start) {\n   \
    \     if (!start) return nullptr;\n        node *res = start;\n        while (true)\
    \ {\n            if constexpr (hasTag || Rev) res->down();\n            if (res->l)\
    \ res = res->l;\n            else break;\n        }\n        return res;\n   \
    \ }\n    node* find_min() const {\n        return find_min(root);\n    }\n   \
    \ static node* find_max(node *start) {\n        if (!start) return nullptr;\n\
    \        node *res = start;\n        while (true) {\n            if constexpr\
    \ (hasTag || Rev) res->down();\n            if (res->r) res = res->r;\n      \
    \      else break;\n        }\n        return res;\n    }\n    node* find_max()\
    \ const {\n        return find_max(root);\n    }\n    static void access(node\
    \ *ptr) requires (!persistent) {\n        assert(ptr != nullptr);\n        if\
    \ (ptr->f != nullptr)\n            access(ptr->f);\n        if constexpr (hasTag\
    \ || Rev) ptr->down();\n    }\n    static node* find_next(node *ptr) requires\
    \ (!persistent) {\n        assert(ptr != nullptr);\n        access(ptr);\n   \
    \     if (ptr->r != nullptr)\n            return find_min(ptr->r);\n        while\
    \ (ptr->f != nullptr && ptr->f->r == ptr)\n            ptr = ptr->f;\n       \
    \ if (ptr->f == nullptr) return nullptr;\n        return ptr->f;\n    }\n    static\
    \ node* find_prev(node *ptr) requires (!persistent) {\n        assert(ptr != nullptr);\n\
    \        access(ptr);\n        if (ptr->l != nullptr)\n            return find_max(ptr->l);\n\
    \        while (ptr->f != nullptr && ptr->f->l == ptr)\n            ptr = ptr->f;\n\
    \        assert(ptr->f != nullptr);\n        return ptr->f;\n    }\n    node *find(const\
    \ auto &condition) {\n        node *cur = root, *res = nullptr;\n        while\
    \ (cur != nullptr) {\n            if constexpr (hasTag || Rev) cur->down();\n\
    \            if (condition(cur))\n                cur = cur->r;\n            else\
    \ {\n                res = cur;\n                cur = cur->l;\n            }\n\
    \        }\n        return res;\n    }\n    node *find_value(const auto &condition)\
    \ {\n        node *cur = root, *res = nullptr;\n        Value left_product = Value();\n\
    \        while (cur != nullptr) {\n            if constexpr (hasTag || Rev) cur->down();\n\
    \            Value current = left_product + get_val(cur->l) + cur->org; \n   \
    \         if (condition(current)) {\n                cur = cur->r;\n         \
    \       left_product = current;\n            }\n            else {\n         \
    \       res = cur;\n                cur = cur->l;\n            }\n        }\n\
    \        return res;\n    }\npublic:\n    Treap() = default;\n    Treap(node *root_)\
    \ : root(root_) {}\n    Treap(const auto &v) requires (!hasKey || !hasValue) :\
    \ root(NodeAlloc::allocate(v)) {}\n    Treap(const auto &k, const auto &v) requires\
    \ (hasKey && hasValue) : root(NodeAlloc::allocate(k, v)) {}\n    void destruct()\
    \ requires (!persistent) {\n        free(root);\n    }\n    void reverse() requires\
    \ (Rev) {\n        if (root) {\n            if constexpr (persistent) root = NodeAlloc::allocate(*root);\n\
    \            root->reverse();\n        }\n    }\n    void transform(const auto\
    \ &tag) requires (hasTag) {\n        if (root) {\n            if constexpr (persistent)\
    \ root = NodeAlloc::allocate(*root);\n            root->give_tag(tag);\n     \
    \   }\n    }\n    Treap& left_merge(auto&& left) requires std::same_as<std::decay_t<decltype(left)>,\
    \ Treap> {\n        root = merge(left.root, root);\n        left.root = nullptr;\n\
    \        return *this;\n    }\n    Treap& right_merge(auto&& right) requires std::same_as<std::decay_t<decltype(right)>,\
    \ Treap> {\n        root = merge(root, right.root);\n        right.root = nullptr;\n\
    \        return *this;\n    }\n    static Treap merge(auto&& left, auto&& right)\
    \ \n        requires (std::same_as<std::decay_t<decltype(left)>, Treap> &&\n \
    \                 std::same_as<std::decay_t<decltype(right)>, Treap>) {\n    \
    \    Treap res(left.merge(right));\n        left.root = nullptr;\n        return\
    \ res;\n    }\n    void swap(Treap &rhs) {\n        std::swap(root, rhs.root);\n\
    \    }\n    bool empty() {\n        return root == nullptr;\n    }\n    int size()\
    \ requires (hasSize) {\n        return get_size(root);\n    }\n    void push_back(const\
    \ auto &v) {\n        right_merge(Treap(v));\n    }\n    void push_back(const\
    \ auto &k, const auto &v) requires (hasKey && hasValue) {\n        right_merge(Treap(k,\
    \ v));\n    }\n    void push_front(const auto &v) {\n        left_merge(Treap(v));\
    \ \n    }\n    void push_front(const auto &k, const auto &v) requires (hasKey\
    \ && hasValue) {\n        left_merge(Treap(k, v)); \n    }\n    struct Iterator\
    \ {\n        using iterator_category = std::bidirectional_iterator_tag;\n    \
    \    using difference_type   = std::ptrdiff_t;\n        using reference      \
    \   = const node&;\n        using value_type        = node;\n        using pointer\
    \           = node*; \n        Iterator(node* ptr, const Treap *tree) : m_ptr(ptr),\
    \ m_tree(tree) {}\n        reference operator*() const { return *m_ptr; }\n  \
    \      auto operator->() const { return m_ptr; }\n        Iterator& operator++()\
    \ requires (!persistent) {\n            m_ptr = find_next(m_ptr);\n          \
    \  return *this;\n        }\n        Iterator operator++(int) requires (!persistent)\
    \ {\n            Iterator tmp = *this;\n            ++(*this);\n            return\
    \ tmp;\n        }\n        Iterator& operator--() requires (!persistent) {\n \
    \           if (m_ptr == nullptr) m_ptr = m_tree->find_max();\n            else\
    \ m_ptr = find_prev(m_ptr);\n            return *this;\n        }\n        Iterator\
    \ operator--(int) requires (!persistent) {\n            Iterator tmp = *this;\n\
    \            --(*this);\n            return tmp;\n        }\n        friend bool\
    \ operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr;\
    \ };\n        friend bool operator!= (const Iterator& a, const Iterator& b) {\
    \ return a.m_ptr != b.m_ptr; };\n        void access_ptr() requires (!persistent)\
    \ {\n            access(m_ptr);\n        }\n    private:\n        node* m_ptr;\n\
    \        const Treap* m_tree;\n    };\n    Iterator begin() const { return Iterator(find_min(),\
    \ this); }\n    Iterator end() const { return Iterator(nullptr, this); }\n   \
    \ Iterator rbegin() const { return Iterator(find_max(), this); }\n    Iterator\
    \ bound_condition(const auto &condition) {\n        return Iterator(find(condition),\
    \ this);\n    }\n    Iterator bound_condition_value(const auto &condition) requires\
    \ (hasValue) {\n        return Iterator(find_value(condition), this);\n    }\n\
    \    template<typename K, typename Comp = std::less<Key>>\n    Iterator lower_bound(const\
    \ K &k, const Comp &cmp = Comp()) requires (hasKey) {\n        return Iterator(find([&k,\
    \ &cmp](node *src) { \n            return cmp(src->key, k);\n        }), this);\n\
    \    }\n    template<typename K, typename Comp = std::less<Key>>\n    Iterator\
    \ upper_bound(const K &k, const Comp &cmp = Comp()) requires (hasKey) {\n    \
    \    return Iterator(find([&k, &cmp](node *src) { \n            return !cmp(k,\
    \ src->key);\n        }), this);\n    }\n    template<typename V, typename Comp\
    \ = std::less<Value>>\n    Iterator lower_bound_value(const V &v, const Comp &cmp\
    \ = Comp()) requires (hasValue) {\n        return Iterator(find_value([&v, &cmp](const\
    \ Value &src) { \n            return cmp(src, v);\n        }), this);\n    }\n\
    \    template<typename V, typename Comp = std::less<Value>>\n    Iterator upper_bound_value(const\
    \ V &v, const Comp &cmp = Comp()) requires (hasValue) {\n        return Iterator(find_value([&v,\
    \ &cmp](const Value &src) { \n            return !cmp(v, src);\n        }), this);\n\
    \    }\n    template<bool try_access = true>\n    void erase(Iterator it) requires\
    \ (!persistent) {\n        if constexpr (try_access)\n            access(it);\n\
    \        node *target = it.operator->();\n        node *parent = target->f;\n\
    \        node *&point_to = !parent ? root : parent->l == target ? parent->l :\
    \ parent->r;\n        point_to = merge(target->l, target->r);\n        while (parent)\
    \ {\n            node *grand = parent->f;\n            parent->up();\n       \
    \     parent = grand;\n        }\n        NodeAlloc::deallocate(target);\n   \
    \ }\n    Treap split_key(const auto &condition) {\n        node *left;\n     \
    \   split(root, left, root, condition);\n        return Treap(left);\n    }\n\
    \    template<typename K, typename Comp = std::less<Key>>\n    Treap split_key_lt(const\
    \ K &k, const Comp &cmp = Comp()) requires (hasKey) {\n        return split_key([&k,\
    \ &cmp](node *src) {\n            return cmp(src->key, k); \n        });\n   \
    \ }\n    template<typename K, typename Comp = std::less<Key>>\n    Treap split_key_leq(const\
    \ K &k, const Comp &cmp = Comp()) requires (hasKey) {\n        return split_key([&k,\
    \ &cmp](node *src) {\n            return !cmp(k, src->key); \n        });\n  \
    \  }\n    Treap split_value(const auto &condition) requires (hasValue) {\n   \
    \     node *left;\n        split_value(root, left, root, Value(), condition);\n\
    \        return Treap(left);\n    }\n    Treap split_size(const int &k) requires\
    \ (hasSize) {\n        return split_value([&k](const Value &src) {\n         \
    \   return src.size() <= k;  \n        });\n    }\n    Key get_key() requires\
    \ (hasKey) {\n        return get_key(root);\n    }\n    Value product() requires\
    \ (hasValue) {\n        return get_val(root);\n    }\n    template<typename K,\
    \ typename Comp = std::less<Key>>\n    Value prefix_product_key_lt(const K &k,\
    \ const Comp &cmp = Comp()) requires (hasKey && hasValue) {\n        return prefix_product(root,\
    \ [&k, &cmp](node *src) {\n            return cmp(src->key, k);\n        });\n\
    \    }\n    template<typename K, typename Comp = std::less<Key>>\n    Value prefix_product_key_leq(const\
    \ K &k, const Comp &cmp = Comp()) requires (hasKey && hasValue) {\n        return\
    \ prefix_product(root, [&k, &cmp](node *src) {\n            return !cmp(k, src->key);\n\
    \        });\n    }\n    Value prefix_product_cond(const auto &condition) requires\
    \ (hasValue) {\n        return prefix_product_cond(root, Value(), condition);\n\
    \    }\n    std::array<Treap, 2> split_range(int l, int r) requires (hasSize)\
    \ {\n        assert(l <= r);\n        Treap left = split_size(l);\n        Treap\
    \ right = split_size(r - l);\n        swap(right);\n        return {left, right};\n\
    \    }\n    Value range_prod(int l, int r) requires (hasValue && hasSize) {\n\
    \        auto [left, right] = split_range(l, r);\n        Value res = product();\n\
    \        this->left_merge(left).right_merge(right);\n        return res;\n   \
    \ }\n    void range_transform(int l, int r, const auto &tag) requires (hasTag\
    \ && hasSize) {\n        auto [left, right] = split_range(l, r);\n        if (!empty())\
    \ transform(tag);\n        this->left_merge(left).right_merge(right);\n    }\n\
    \    void range_reverse(int l, int r) requires (Rev && hasSize) {\n        auto\
    \ [left, right] = split_range(l, r);\n        if (!empty()) reverse();\n     \
    \   this->left_merge(left).right_merge(right);\n    }\n    Iterator kth(int k)\
    \ requires (hasSize) {\n        return Iterator(find_value([&k](const Value &v)\
    \ {\n            return v.size() <= k;\n        }), this);\n    }\n};\n#line 6\
    \ \"test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \n\nusing mint = modint998244353;\n\nstruct Tag {\n    mint a, b;\n    Tag(mint\
    \ _a = 1, mint _b = 0): a(_a), b(_b) {}\n    Tag operator+(const Tag &rhs) {\n\
    \        return Tag(a * rhs.a, rhs.a * b + rhs.b);\n    }\n};\n\nstruct Value\
    \ {\n    mint val;\n    int sz;\n    Value(mint a = 0, int b = 0): val(a), sz(b)\
    \ {}\n    Value operator+(const Value &rhs) const {\n        return Value(val\
    \ + rhs.val, sz + rhs.sz);\n    }\n    Value operator+(const Tag &tag) const {\n\
    \        return Value(tag.a * val + tag.b * sz, sz);\n    }\n    int size() const\
    \ {\n        return sz; \n    }\n    static Value get(int l, int r) {\n      \
    \  return Value(0, r - l);\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const Value &v) {\n        os << v.val;\n        return os;\n    }\n   \
    \ friend std::istream& operator>>(std::istream& is, Value &v) {\n        is >>\
    \ v.val;\n        v.sz = 1;\n        return is;\n    }\n};\n\nusing treap = Treap<void,\
    \ Value, Tag, true>;\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    treap tree;\n    for (int i = 0;\
    \ i < n; ++i) {\n        Value v;\n        std::cin >> v;\n        tree.push_back(v);\n\
    \    }\n    while (q--) {\n        int t;\n        std::cin >> t;\n        if\
    \ (t == 0) {\n            int i;\n            Value v;\n            std::cin >>\
    \ i >> v;\n            auto lft = tree.split_size(i);\n            tree.left_merge(treap(v)).left_merge(lft);\n\
    \        }\n        else if (t == 1) {\n            int i;\n            std::cin\
    \ >> i;\n            tree.erase<false>(tree.kth(i));\n        }\n        else\
    \ if (t == 2) {\n            int l, r;\n            std::cin >> l >> r;\n    \
    \        tree.range_reverse(l, r);\n        }\n        else if (t == 3) {\n  \
    \          int l, r;\n            Tag tag;\n            std::cin >> l >> r >>\
    \ tag.a >> tag.b;\n            tree.range_transform(l, r, tag);\n        }\n \
    \       else {\n            int l, r;\n            std::cin >> l >> r;\n     \
    \       std::cout << tree.range_prod(l, r) << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n#include \"assumption.hpp\"\n\n#include \"Numeric/Modint.hpp\"\n#include \"\
    DataStructure/Treap.hpp\"\n\nusing mint = modint998244353;\n\nstruct Tag {\n \
    \   mint a, b;\n    Tag(mint _a = 1, mint _b = 0): a(_a), b(_b) {}\n    Tag operator+(const\
    \ Tag &rhs) {\n        return Tag(a * rhs.a, rhs.a * b + rhs.b);\n    }\n};\n\n\
    struct Value {\n    mint val;\n    int sz;\n    Value(mint a = 0, int b = 0):\
    \ val(a), sz(b) {}\n    Value operator+(const Value &rhs) const {\n        return\
    \ Value(val + rhs.val, sz + rhs.sz);\n    }\n    Value operator+(const Tag &tag)\
    \ const {\n        return Value(tag.a * val + tag.b * sz, sz);\n    }\n    int\
    \ size() const {\n        return sz; \n    }\n    static Value get(int l, int\
    \ r) {\n        return Value(0, r - l);\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const Value &v) {\n        os << v.val;\n        return os;\n    }\n   \
    \ friend std::istream& operator>>(std::istream& is, Value &v) {\n        is >>\
    \ v.val;\n        v.sz = 1;\n        return is;\n    }\n};\n\nusing treap = Treap<void,\
    \ Value, Tag, true>;\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    treap tree;\n    for (int i = 0;\
    \ i < n; ++i) {\n        Value v;\n        std::cin >> v;\n        tree.push_back(v);\n\
    \    }\n    while (q--) {\n        int t;\n        std::cin >> t;\n        if\
    \ (t == 0) {\n            int i;\n            Value v;\n            std::cin >>\
    \ i >> v;\n            auto lft = tree.split_size(i);\n            tree.left_merge(treap(v)).left_merge(lft);\n\
    \        }\n        else if (t == 1) {\n            int i;\n            std::cin\
    \ >> i;\n            tree.erase<false>(tree.kth(i));\n        }\n        else\
    \ if (t == 2) {\n            int l, r;\n            std::cin >> l >> r;\n    \
    \        tree.range_reverse(l, r);\n        }\n        else if (t == 3) {\n  \
    \          int l, r;\n            Tag tag;\n            std::cin >> l >> r >>\
    \ tag.a >> tag.b;\n            tree.range_transform(l, r, tag);\n        }\n \
    \       else {\n            int l, r;\n            std::cin >> l >> r;\n     \
    \       std::cout << tree.range_prod(l, r) << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - DataStructure/Treap.hpp
  - DataStructure/DefaultAllocator.hpp
  - Algebra/size_value.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 14:18:54+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp
- /verify/test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp.html
title: test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp
---
