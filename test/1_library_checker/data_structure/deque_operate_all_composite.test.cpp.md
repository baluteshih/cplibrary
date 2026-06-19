---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/SwagDeque.hpp
    title: SWAG Deque
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
    PROBLEM: https://judge.yosupo.jp/problem/deque_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/deque_operate_all_composite
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/deque_operate_all_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/deque_operate_all_composite\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/data_structure/deque_operate_all_composite.test.cpp\"\
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
    #line 2 \"DataStructure/SwagDeque.hpp\"\n\ntemplate<typename T>\nclass SwagDeque\
    \ {\n    int sz;\n    std::vector<T> data_l, data_r, cum_l, cum_r;\n    void rebuild()\
    \ {\n        std::vector<T> X;\n        std::ranges::reverse(data_l);\n      \
    \  X.insert(X.end(), data_l.begin(), data_l.end());\n        X.insert(X.end(),\
    \ data_r.begin(), data_r.end());\n        clear();\n        int m = X.size() /\
    \ 2;\n        for (int i = m - 1; i >= 0; --i) push_front(X[i]);\n        for\
    \ (int i = m; i < int(X.size()); ++i) push_back(X[i]);\n    }\npublic:\n    SwagDeque()\
    \ : sz(0), cum_l(1, T()), cum_r(1, T()) {}\n    int size() { return sz; }\n  \
    \  void push_back(T x) {\n        ++sz;\n        data_r.push_back(x);\n      \
    \  cum_r.push_back(cum_r.back() + x);\n    }\n    void push_front(T x) {\n   \
    \     ++sz;\n        data_l.push_back(x);\n        cum_l.push_back(x + cum_l.back());\n\
    \    }\n    void clear() {\n        sz = 0;\n        data_l.clear(), data_r.clear();\n\
    \        std::vector<T>(1, T()).swap(cum_l);\n        std::vector<T>(1, T()).swap(cum_r);\n\
    \    }\n    void pop_front() {\n        if (sz == 1) return clear();\n       \
    \ if (data_l.empty()) rebuild();\n        --sz;\n        data_l.pop_back();\n\
    \        cum_l.pop_back();\n    }\n    void pop_back() {\n        if (sz == 1)\
    \ return clear();\n        if (data_r.empty()) rebuild();\n        --sz;\n   \
    \     data_r.pop_back();\n        cum_r.pop_back();\n    }\n    T front() {\n\
    \        if (!data_l.empty()) return data_l.back();\n        return data_r[0];\n\
    \    }\n    T lprod() { return cum_l.back(); }\n    T rprod() { return cum_r.back();\
    \ }\n    T prod() { return lprod() + rprod(); }\n};\n#line 6 \"test/1_library_checker/data_structure/deque_operate_all_composite.test.cpp\"\
    \n\nusing mint = modint998244353;\n\nstruct Value {\n    mint a, b;\n    Value(mint\
    \ _a = 1, mint _b = 0): a(_a), b(_b) {}\n    Value operator+(const Value &rhs)\
    \ {\n        return Value(a * rhs.a, rhs.a * b + rhs.b);\n    }\n    mint get_val(mint\
    \ x) {\n        return a * x + b;\n    }\n};\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int q;\n    std::cin >> q;\n    SwagDeque<Value> dq;\n\
    \    while (q--) {\n        int type;\n        std::cin >> type;\n        if (type\
    \ == 0) {\n            mint a, b;\n            std::cin >> a >> b;\n         \
    \   dq.push_front(Value(a, b));\n        }\n        else if (type == 1) {\n  \
    \          mint a, b;\n            std::cin >> a >> b;\n            dq.push_back(Value(a,\
    \ b));\n        }\n        else if (type == 2) {\n            dq.pop_front();\n\
    \        }\n        else if (type == 3) {\n            dq.pop_back();\n      \
    \  }\n        else {\n            mint x;\n            std::cin >> x;\n      \
    \      std::cout << dq.prod().get_val(x) << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/deque_operate_all_composite\"\
    \n#include \"assumption.hpp\"\n\n#include \"Numeric/Modint.hpp\"\n#include \"\
    DataStructure/SwagDeque.hpp\"\n\nusing mint = modint998244353;\n\nstruct Value\
    \ {\n    mint a, b;\n    Value(mint _a = 1, mint _b = 0): a(_a), b(_b) {}\n  \
    \  Value operator+(const Value &rhs) {\n        return Value(a * rhs.a, rhs.a\
    \ * b + rhs.b);\n    }\n    mint get_val(mint x) {\n        return a * x + b;\n\
    \    }\n};\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int q;\n    std::cin >> q;\n    SwagDeque<Value> dq;\n    while (q--) {\n\
    \        int type;\n        std::cin >> type;\n        if (type == 0) {\n    \
    \        mint a, b;\n            std::cin >> a >> b;\n            dq.push_front(Value(a,\
    \ b));\n        }\n        else if (type == 1) {\n            mint a, b;\n   \
    \         std::cin >> a >> b;\n            dq.push_back(Value(a, b));\n      \
    \  }\n        else if (type == 2) {\n            dq.pop_front();\n        }\n\
    \        else if (type == 3) {\n            dq.pop_back();\n        }\n      \
    \  else {\n            mint x;\n            std::cin >> x;\n            std::cout\
    \ << dq.prod().get_val(x) << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - DataStructure/SwagDeque.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/deque_operate_all_composite.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 14:18:54+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/deque_operate_all_composite.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/deque_operate_all_composite.test.cpp
- /verify/test/1_library_checker/data_structure/deque_operate_all_composite.test.cpp.html
title: test/1_library_checker/data_structure/deque_operate_all_composite.test.cpp
---
