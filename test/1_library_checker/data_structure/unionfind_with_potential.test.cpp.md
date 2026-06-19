---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/DisjointSet.hpp
    title: Disjoint Set Union (DSU)
  - icon: ':heavy_check_mark:'
    path: DataStructure/PotentialDisjointSet.hpp
    title: Potential Disjoint Set
  - icon: ':question:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind_with_potential
    links:
    - https://judge.yosupo.jp/problem/unionfind_with_potential
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/unionfind_with_potential.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind_with_potential\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/data_structure/unionfind_with_potential.test.cpp\"\
    \n\n#line 2 \"DataStructure/PotentialDisjointSet.hpp\"\n\n#line 2 \"DataStructure/DisjointSet.hpp\"\
    \n\ntemplate<typename T = void, bool undo_tag = false>\nclass DisjointSet {\n\
    protected:\n    static constexpr bool hasT = !std::is_same_v<T, void>;\n    int\
    \ n;\n    std::vector<int> boss, sz;\n    struct Empty {};\n    [[no_unique_address]]\
    \ std::conditional_t<hasT, std::vector<T>, Empty> data;\n    [[no_unique_address]]\
    \ std::conditional_t<undo_tag, std::vector<std::pair<int*, int>>, Empty> cache;\n\
    \    [[no_unique_address]] std::conditional_t<undo_tag && hasT, std::vector<std::pair<T*,\
    \ T>>, Empty> data_cache;\npublic:\n    DisjointSet(int n_): n(n_), boss(n), sz(n,\
    \ 1) {\n        std::iota(boss.begin(), boss.end(), 0);\n        if constexpr\
    \ (hasT) data.resize(n);\n    }\n    DisjointSet(const std::vector<T> &data_)\
    \ requires (hasT) : n(data_.size()), boss(n), sz(n, 1), data(data_) {\n      \
    \  std::iota(boss.begin(), boss.end(), 0);\n    }\n    virtual int leader(int\
    \ u) {\n        if (boss[u] == u) return u;\n        if constexpr (undo_tag) return\
    \ leader(boss[u]);\n        else return boss[u] = leader(boss[u]);\n    }\n  \
    \  int size(int u) {\n        return sz[leader(u)];\n    }\n    bool same(int\
    \ u, int v) {\n        return leader(u) == leader(v);\n    }\n    bool merge(int\
    \ u, int v, bool force = false) {\n        u = leader(u), v = leader(v);\n   \
    \     if (u == v) return false;\n        if (sz[u] < sz[v] && !force) std::swap(u,\
    \ v);\n        if constexpr (undo_tag) {\n            cache.emplace_back(&boss[v],\
    \ boss[v]); \n            cache.emplace_back(&sz[u], sz[v]); \n            if\
    \ constexpr (hasT)\n                data_cache.emplace_back(&data[u], data[u]);\n\
    \        }\n        boss[v] = u;\n        sz[u] += sz[v];\n        if constexpr\
    \ (hasT) {\n            data[u] = data[u] + data[v]; \n        }\n        return\
    \ true;\n    }\n    size_t version() requires (undo_tag && !hasT) {\n        return\
    \ cache.size();\n    }\n    std::pair<size_t, size_t> version() requires (undo_tag\
    \ && hasT) {\n        return std::make_pair(cache.size(), data_cache.size());\n\
    \    }\n    void undo(auto req_version) requires (undo_tag) {\n        while (version()\
    \ != req_version) {\n            if constexpr (!hasT) {\n                *cache.back().first\
    \ = cache.back().second;\n                cache.pop_back();\n            }\n \
    \           else {\n                if (cache.size() > req_version.first) {\n\
    \                    *cache.back().first = cache.back().second;\n            \
    \        cache.pop_back();\n                }\n                else {\n      \
    \              *data_cache.back().first = data_cache.back().second;\n        \
    \            data_cache.pop_back();\n                }\n            }\n      \
    \  }\n    }\n    auto& getdata(int u) requires (hasT) {\n        return data[leader(u)];\n\
    \    }\n    void data_transform(int u, auto func) requires (hasT) {\n        auto\
    \ &cur = getdata(u);\n        if constexpr (undo_tag)\n            data_cache.emplace_back(&cur,\
    \ cur);\n        func(cur);\n    }\n    std::vector<std::vector<int>> groups()\
    \ {\n        std::vector<std::vector<int>> result(n);\n        for (int i = 0;\
    \ i < n; ++i)\n            result[leader(i)].push_back(i);\n        result.erase(remove_if(result.begin(),\
    \ result.end(), [](auto &g) { return g.empty(); }), result.end());\n        return\
    \ result;\n    }\n};\n#line 4 \"DataStructure/PotentialDisjointSet.hpp\"\n\ntemplate<typename\
    \ P, typename T = void>\nclass PotentialDisjointSet : public DisjointSet<T> {\n\
    \    using Super = DisjointSet<T>;\n    std::vector<P> potential;\npublic:\n \
    \   PotentialDisjointSet(int n_): Super(n_), potential(this->n) {}\n    PotentialDisjointSet(const\
    \ std::vector<T> &data_) requires (Super::hasT) : Super(data_), potential(this->n)\
    \ {}\n    int leader(int u) override {\n        if (this->boss[u] == u) return\
    \ u;\n        int org = this->boss[u];\n        int res = leader(org);\n     \
    \   this->boss[u] = res;\n        potential[u] = potential[u] + potential[org];\n\
    \        return res;\n    }\n    // p[u] - p[v] = pot\n    bool merge(int u, int\
    \ v, P pot, bool force = false) {\n        int ru = leader(u);\n        int rv\
    \ = leader(v);\n        if (ru == rv) return false;\n        if (this->sz[ru]\
    \ < this->sz[rv] && !force) { \n            std::swap(ru, rv);\n            std::swap(u,\
    \ v);\n            pot = P() - pot;\n        }\n        this->boss[rv] = ru;\n\
    \        this->sz[ru] += this->sz[rv];\n        if constexpr (Super::hasT) {\n\
    \            this->data[ru] = this->data[ru] + this->data[rv]; \n        }\n \
    \       potential[rv] = P() - potential[v] - pot + potential[u]; \n        return\
    \ true;\n    }\n    // return p[u] - p[v]\n    P diff(int u, int v) {\n      \
    \  assert(this->same(u, v));\n        return potential[u] - potential[v];\n  \
    \  }\n};\n#line 5 \"test/1_library_checker/data_structure/unionfind_with_potential.test.cpp\"\
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
    #line 7 \"test/1_library_checker/data_structure/unionfind_with_potential.test.cpp\"\
    \n\nusing mint = modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int n, q;\n    std::cin >> n >> q;\n    PotentialDisjointSet<mint>\
    \ djs(n);\n    while (q--) {\n        int t, u, v;\n        std::cin >> t >> u\
    \ >> v;\n        if (t == 0) {\n            bool succ = true;\n            mint\
    \ x;\n            std::cin >> x;\n            if (djs.same(u, v)) succ = (djs.diff(u,\
    \ v) == x);\n            else djs.merge(u, v, x);\n            std::cout << succ\
    \ << \"\\n\";\n        }\n        else {\n            if (djs.same(u, v)) std::cout\
    \ << djs.diff(u, v) << \"\\n\";\n            else std::cout << \"-1\\n\";\n  \
    \      }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind_with_potential\"\
    \n#include \"assumption.hpp\"\n\n#include \"DataStructure/PotentialDisjointSet.hpp\"\
    \n\n#include \"Numeric/Modint.hpp\"\n\nusing mint = modint998244353;\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    PotentialDisjointSet<mint> djs(n);\n    while (q--) {\n    \
    \    int t, u, v;\n        std::cin >> t >> u >> v;\n        if (t == 0) {\n \
    \           bool succ = true;\n            mint x;\n            std::cin >> x;\n\
    \            if (djs.same(u, v)) succ = (djs.diff(u, v) == x);\n            else\
    \ djs.merge(u, v, x);\n            std::cout << succ << \"\\n\";\n        }\n\
    \        else {\n            if (djs.same(u, v)) std::cout << djs.diff(u, v) <<\
    \ \"\\n\";\n            else std::cout << \"-1\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - DataStructure/PotentialDisjointSet.hpp
  - DataStructure/DisjointSet.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/unionfind_with_potential.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 18:28:09+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/unionfind_with_potential.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/unionfind_with_potential.test.cpp
- /verify/test/1_library_checker/data_structure/unionfind_with_potential.test.cpp.html
title: test/1_library_checker/data_structure/unionfind_with_potential.test.cpp
---
