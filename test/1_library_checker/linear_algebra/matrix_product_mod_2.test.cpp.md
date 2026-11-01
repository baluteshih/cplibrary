---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/DynamicBitset.hpp
    title: Dynamic Bitset
  - icon: ':heavy_check_mark:'
    path: Matrix/MatrixF2.hpp
    title: Matrix/MatrixF2.hpp
  - icon: ':question:'
    path: assumption.hpp
    title: assumption.hpp
  - icon: ':heavy_check_mark:'
    path: pragma.hpp
    title: pragma.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/matrix_product_mod_2
    links:
    - https://judge.yosupo.jp/problem/matrix_product_mod_2
  bundledCode: "#line 1 \"test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product_mod_2\"\n#line\
    \ 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 1 \"pragma.hpp\"\n#ifdef __x86_64__\n    #pragma GCC optimize(\"O3,unroll-loops\"\
    )\n    #pragma GCC target(\"avx2,bmi,bmi2,lzcnt,popcnt\")\n#endif\n#line 4 \"\
    test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp\"\n\n#line\
    \ 2 \"Matrix/MatrixF2.hpp\"\n\n#line 2 \"DataStructure/DynamicBitset.hpp\"\n\n\
    #ifdef __x86_64__\n    #include <x86intrin.h>\n#endif\n\nclass DynamicBitset {\n\
    \    int n;\n    std::vector<uint64_t> a;\n    inline static unsigned char add_carry(unsigned\
    \ char c, uint64_t a, uint64_t b, uint64_t& out) {\n    #ifdef __x86_64__\n  \
    \      return _addcarry_u64(c, a, b, (unsigned long long*)&out);\n    #else\n\
    \        uint64_t sum = a + b + c;\n        out = sum;\n        return (sum <\
    \ a) || (c && sum == a);\n    #endif\n    }\n    inline static unsigned char sub_borrow(unsigned\
    \ char b, uint64_t x, uint64_t y, uint64_t& out) {\n    #ifdef __x86_64__\n  \
    \      return _subborrow_u64(b, x, y, (unsigned long long*)&out);\n    #else\n\
    \        uint64_t sub = x - y - b;\n        out = sub;\n        return (x < y)\
    \ || (b && x == y);\n    #endif\n    }\npublic:\n    DynamicBitset(int _n = 0)\
    \ : n(_n), a((n + 63) >> 6, 0) {}\n    DynamicBitset(std::string_view s) : n(s.size()),\
    \ a((n + 63) >> 6, 0) {\n        for (int i = 0; i < n; ++i) \n            if\
    \ (s[n - 1 - i] == '1') a[i >> 6] |= (1ULL << (i & 63));\n    }\n    void clean()\
    \ { if (n & 63) a.back() &= (1ULL << (n & 63)) - 1; }\n    struct reference {\n\
    \        uint64_t& blk; int bit;\n        reference(uint64_t& b, int idx) : blk(b),\
    \ bit(idx) {}\n        reference& operator=(bool v) { \n            v ? (blk |=\
    \ (1ULL << bit)) : (blk &= ~(1ULL << bit)); \n            return *this; \n   \
    \     }\n        reference& operator=(const reference& o) { return *this = bool(o);\
    \ }\n        operator bool() const { return (blk >> bit) & 1; }\n    };\n    reference\
    \ operator[](int i) { return reference(a[i >> 6], i & 63); }\n    bool operator[](int\
    \ i) const { return (a[i >> 6] >> (i & 63)) & 1; }\n\n    void set(int i) { a[i\
    \ >> 6] |= (1ULL << (i & 63)); }\n    void reset(int i) { a[i >> 6] &= ~(1ULL\
    \ << (i & 63)); }\n    void flip(int i) { a[i >> 6] ^= (1ULL << (i & 63)); }\n\
    \    bool test(int i) const { return (*this)[i]; }\n    int size() const { return\
    \ n; }\n    int count() const { \n        int res = 0; \n        for (auto x :\
    \ a) res += std::popcount(x); \n        return res; \n    }\n    int _Find_first()\
    \ const {\n        for (size_t i = 0; i < a.size(); ++i)\n            if (a[i])\
    \ return i * 64 + std::countr_zero(a[i]);\n        return n;\n    }\n    int _Find_last()\
    \ const {\n        for (int i = (int)a.size() - 1; i >= 0; --i)\n            if\
    \ (a[i]) return i * 64 + 63 - std::countl_zero(a[i]);\n        return -1;\n  \
    \  }\n    int _Find_next(int i) const {\n        if (++i >= n) return n;\n   \
    \     int blk = i >> 6, bit = i & 63;\n        uint64_t x = a[blk] & (~0ULL <<\
    \ bit);\n        if (x) return blk * 64 + std::countr_zero(x);\n        for (size_t\
    \ j = blk + 1; j < a.size(); ++j)\n            if (a[j]) return j * 64 + std::countr_zero(a[j]);\n\
    \        return n;\n    }\n    int _Find_prev(int i) const {\n        if (i <=\
    \ 0) return -1;\n        i = std::min(i, n) - 1;\n        int blk = i >> 6, bit\
    \ = i & 63;\n        uint64_t mask = ~0ULL >> (63 - bit);\n        uint64_t x\
    \ = a[blk] & mask;\n        if (x) return blk * 64 + 63 - std::countl_zero(x);\n\
    \        for (int j = blk - 1; j >= 0; --j)\n            if (a[j]) return j *\
    \ 64 + 63 - std::countl_zero(a[j]);\n        return -1;\n    }\n    bool operator==(const\
    \ DynamicBitset&) const = default;\n    std::string to_string() const {\n    \
    \    std::string s(n, '0');\n        for (int i = 0; i < n; ++i) if ((*this)[i])\
    \ s[n - 1 - i] = '1';\n        return s;\n    }\n    void swap(DynamicBitset &o)\
    \ { std::swap(n, o.n), a.swap(o.a); }\n\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const DynamicBitset& b) { return os << b.to_string(); }\n    friend std::istream&\
    \ operator>>(std::istream& is, DynamicBitset& b) {\n        std::string s; if\
    \ (is >> s) b = DynamicBitset(s);\n        return is;\n    }\n    DynamicBitset&\
    \ operator&=(const DynamicBitset& o) { \n        size_t sz = a.size(); uint64_t*\
    \ p = a.data(); const uint64_t* op = o.a.data();\n        for(size_t i = 0; i\
    \ < sz; ++i) p[i] &= op[i]; \n        return *this; \n    }\n    DynamicBitset&\
    \ operator|=(const DynamicBitset& o) { \n        size_t sz = a.size(); uint64_t*\
    \ p = a.data(); const uint64_t* op = o.a.data();\n        for(size_t i = 0; i\
    \ < sz; ++i) p[i] |= op[i]; \n        return *this; \n    }\n    DynamicBitset&\
    \ operator^=(const DynamicBitset& o) { \n        size_t sz = a.size(); uint64_t*\
    \ p = a.data(); const uint64_t* op = o.a.data();\n        for(size_t i = 0; i\
    \ < sz; ++i) p[i] ^= op[i]; \n        return *this; \n    }\n    DynamicBitset&\
    \ operator+=(const DynamicBitset& o) {\n        unsigned char carry = 0;\n   \
    \     size_t sz = a.size(), osz = o.a.size();\n        uint64_t* p = a.data();\
    \ const uint64_t* op = o.a.data();\n        \n        for (size_t i = 0; i < sz;\
    \ ++i) {\n            uint64_t v = (i < osz) ? op[i] : 0;\n            carry =\
    \ add_carry(carry, p[i], v, p[i]);\n        }\n        clean(); return *this;\n\
    \    } \n    DynamicBitset& operator-=(const DynamicBitset& o) {\n        unsigned\
    \ char borrow = 0;\n        size_t sz = a.size(), osz = o.a.size();\n        uint64_t*\
    \ p = a.data(); const uint64_t* op = o.a.data();\n        \n        for (size_t\
    \ i = 0; i < sz; ++i) {\n            uint64_t v = (i < osz) ? op[i] : 0;\n   \
    \         borrow = sub_borrow(borrow, p[i], v, p[i]);\n        }\n        clean();\
    \ return *this;\n    } \n    DynamicBitset& operator<<=(int k) {\n        if (k\
    \ >= n) { memset(a.data(), 0, a.size() * sizeof(uint64_t)); return *this; }\n\
    \        int blocks = k >> 6, bits = k & 63;\n        int sz = (int)a.size();\n\
    \        uint64_t* p = a.data();\n\n        if (bits == 0)\n            for (int\
    \ i = sz - 1; i >= blocks; --i) p[i] = p[i - blocks];\n        else {\n      \
    \      for (int i = sz - 1; i > blocks; --i)\n                p[i] = (p[i - blocks]\
    \ << bits) | (p[i - blocks - 1] >> (64 - bits));\n            p[blocks] = p[0]\
    \ << bits;\n        }\n        memset(p, 0, blocks * sizeof(uint64_t));\n    \
    \    clean(); return *this;\n    } \n    DynamicBitset& operator>>=(int k) {\n\
    \        if (k >= n) { memset(a.data(), 0, a.size() * sizeof(uint64_t)); return\
    \ *this; }\n        int blocks = k >> 6, bits = k & 63;\n        int sz = (int)a.size();\n\
    \        uint64_t* p = a.data();\n        \n        if (bits == 0)\n         \
    \   for (int i = 0; i < sz - blocks; ++i) p[i] = p[i + blocks];\n        else\
    \ {\n            int limit = sz - blocks - 1;\n            for (int i = 0; i <\
    \ limit; ++i)\n                p[i] = (p[i + blocks] >> bits) | (p[i + blocks\
    \ + 1] << (64 - bits));\n            p[limit] = p[sz - 1] >> bits;\n        }\n\
    \        memset(p + (sz - blocks), 0, blocks * sizeof(uint64_t));\n        clean();\
    \ return *this;\n    }\n    DynamicBitset& flip() {\n        size_t sz = a.size();\n\
    \        uint64_t* p = a.data();\n        for (size_t i = 0; i < sz; ++i) p[i]\
    \ = ~p[i];\n        clean();\n        return *this;\n    }\n\n    DynamicBitset\
    \ operator+(const DynamicBitset& o) const { auto res = *this; return res += o;\
    \ }\n    DynamicBitset operator-(const DynamicBitset& o) const { auto res = *this;\
    \ return res -= o; }\n    DynamicBitset operator&(const DynamicBitset& o) const\
    \ { auto res = *this; return res &= o; }\n    DynamicBitset operator|(const DynamicBitset&\
    \ o) const { auto res = *this; return res |= o; }\n    DynamicBitset operator^(const\
    \ DynamicBitset& o) const { auto res = *this; return res ^= o; }\n    DynamicBitset\
    \ operator<<(int k) const { auto res = *this; return res <<= k; }\n    DynamicBitset\
    \ operator>>(int k) const { auto res = *this; return res >>= k; }\n    DynamicBitset\
    \ operator~() const { auto res = *this; return res.flip(); }\n    DynamicBitset\
    \ operator-() const {\n        DynamicBitset res = ~(*this);\n        uint64_t\
    \ carry = 1;\n        for (size_t i = 0; i < res.a.size() && carry; ++i) {\n \
    \           res.a[i] += 1;\n            carry = (res.a[i] == 0);\n        }\n\
    \        res.clean();\n        return res;\n    }\n};\n#line 4 \"Matrix/MatrixF2.hpp\"\
    \n\nclass MatrixF2 : public std::vector<DynamicBitset> {\npublic:\n    int n()\
    \ const { return (int)this->size(); }\n    int m() const { return n() ? (int)(*this)[0].size()\
    \ : 0; }\n    MatrixF2(int _n, int _m): std::vector<DynamicBitset>(_n, DynamicBitset(_m))\
    \ {}\n    MatrixF2(int _n): MatrixF2(_n, _n) {}\n    MatrixF2(const DynamicBitset\
    \ &vec): MatrixF2(1, vec.size()) {\n        (*this)[0] = vec;\n    }\n    MatrixF2\
    \ transpose() const {\n        MatrixF2 res(m(), n());\n        for (int i = 0;\
    \ i < m(); ++i)\n            for (int j = 0; j < n(); ++j)\n                res[i][j]\
    \ = (*this)[j][i];\n        return res;\n    }\n    MatrixF2& operator*=(const\
    \ MatrixF2 &rhs) {\n        assert(m() == rhs.n());\n        MatrixF2 res(n(),\
    \ rhs.m());\n        for (int i = 0; i < n(); ++i)\n            for (int k = (*this)[i]._Find_first();\
    \ k < rhs.n(); k = (*this)[i]._Find_next(k))\n                res[i] ^= rhs[k];\n\
    \        *this = std::move(res);\n        return *this;\n    }\n    MatrixF2&\
    \ operator+=(const MatrixF2 &rhs) {\n        assert(n() == rhs.n());\n       \
    \ assert(m() == rhs.m());\n        for (int i = 0; i < n(); ++i)\n           \
    \ (*this)[i] ^= rhs[i];\n        return *this;\n    }\n    MatrixF2 operator*(const\
    \ MatrixF2 &rhs) const { return MatrixF2(*this) *= rhs; }\n    MatrixF2 operator+(const\
    \ MatrixF2 &rhs) const { return MatrixF2(*this) += rhs; }\n    static MatrixF2\
    \ identity(int n) {\n        MatrixF2 res(n, n);\n        for (int i = 0; i <\
    \ n; ++i) res[i].set(i);\n        return res;\n    }\n    MatrixF2 pow(long long\
    \ k) const {\n        MatrixF2 res(identity(n()));\n        MatrixF2 base(*this);\n\
    \        for (; k; k >>= 1, base = base * base)\n            if (k & 1)\n    \
    \            res = res * base;\n        return res;\n    }\n};\n#line 6 \"test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, m, k;\n    std::cin >> n >> m >> k;\n    MatrixF2 A(n, m), B(m, k);\n   \
    \ for (auto &v : A) {\n        std::string s;\n        std::cin >> s;\n      \
    \  std::ranges::reverse(s);\n        v = DynamicBitset(s);\n    }\n    for (auto\
    \ &v : B) {\n        std::string s;\n        std::cin >> s;\n        std::ranges::reverse(s);\n\
    \        v = DynamicBitset(s);\n    }\n    auto C = A * B;\n    for (auto &v :\
    \ C) {\n        std::string s = v.to_string();\n        std::ranges::reverse(s);\n\
    \        std::cout << s << \"\\n\"; \n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product_mod_2\"\n\
    #include \"assumption.hpp\"\n#include \"pragma.hpp\"\n\n#include \"Matrix/MatrixF2.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, m, k;\n    std::cin >> n >> m >> k;\n    MatrixF2 A(n, m), B(m, k);\n   \
    \ for (auto &v : A) {\n        std::string s;\n        std::cin >> s;\n      \
    \  std::ranges::reverse(s);\n        v = DynamicBitset(s);\n    }\n    for (auto\
    \ &v : B) {\n        std::string s;\n        std::cin >> s;\n        std::ranges::reverse(s);\n\
    \        v = DynamicBitset(s);\n    }\n    auto C = A * B;\n    for (auto &v :\
    \ C) {\n        std::string s = v.to_string();\n        std::ranges::reverse(s);\n\
    \        std::cout << s << \"\\n\"; \n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - pragma.hpp
  - Matrix/MatrixF2.hpp
  - DataStructure/DynamicBitset.hpp
  isVerificationFile: true
  path: test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp
  requiredBy: []
  timestamp: '2026-07-04 18:47:24+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp
- /verify/test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp.html
title: test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp
---
