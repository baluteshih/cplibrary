---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Matrix/MatrixF2.hpp
    title: Matrix/MatrixF2.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp
    title: test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/DynamicBitset.hpp\"\n\n#ifdef __x86_64__\n\
    \    #include <x86intrin.h>\n#endif\n\nclass DynamicBitset {\n    int n;\n   \
    \ std::vector<uint64_t> a;\n    inline static unsigned char add_carry(unsigned\
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
    \        res.clean();\n        return res;\n    }\n};\n"
  code: "#pragma once\n\n#ifdef __x86_64__\n    #include <x86intrin.h>\n#endif\n\n\
    class DynamicBitset {\n    int n;\n    std::vector<uint64_t> a;\n    inline static\
    \ unsigned char add_carry(unsigned char c, uint64_t a, uint64_t b, uint64_t& out)\
    \ {\n    #ifdef __x86_64__\n        return _addcarry_u64(c, a, b, (unsigned long\
    \ long*)&out);\n    #else\n        uint64_t sum = a + b + c;\n        out = sum;\n\
    \        return (sum < a) || (c && sum == a);\n    #endif\n    }\n    inline static\
    \ unsigned char sub_borrow(unsigned char b, uint64_t x, uint64_t y, uint64_t&\
    \ out) {\n    #ifdef __x86_64__\n        return _subborrow_u64(b, x, y, (unsigned\
    \ long long*)&out);\n    #else\n        uint64_t sub = x - y - b;\n        out\
    \ = sub;\n        return (x < y) || (b && x == y);\n    #endif\n    }\npublic:\n\
    \    DynamicBitset(int _n = 0) : n(_n), a((n + 63) >> 6, 0) {}\n    DynamicBitset(std::string_view\
    \ s) : n(s.size()), a((n + 63) >> 6, 0) {\n        for (int i = 0; i < n; ++i)\
    \ \n            if (s[n - 1 - i] == '1') a[i >> 6] |= (1ULL << (i & 63));\n  \
    \  }\n    void clean() { if (n & 63) a.back() &= (1ULL << (n & 63)) - 1; }\n \
    \   struct reference {\n        uint64_t& blk; int bit;\n        reference(uint64_t&\
    \ b, int idx) : blk(b), bit(idx) {}\n        reference& operator=(bool v) { \n\
    \            v ? (blk |= (1ULL << bit)) : (blk &= ~(1ULL << bit)); \n        \
    \    return *this; \n        }\n        reference& operator=(const reference&\
    \ o) { return *this = bool(o); }\n        operator bool() const { return (blk\
    \ >> bit) & 1; }\n    };\n    reference operator[](int i) { return reference(a[i\
    \ >> 6], i & 63); }\n    bool operator[](int i) const { return (a[i >> 6] >> (i\
    \ & 63)) & 1; }\n\n    void set(int i) { a[i >> 6] |= (1ULL << (i & 63)); }\n\
    \    void reset(int i) { a[i >> 6] &= ~(1ULL << (i & 63)); }\n    void flip(int\
    \ i) { a[i >> 6] ^= (1ULL << (i & 63)); }\n    bool test(int i) const { return\
    \ (*this)[i]; }\n    int size() const { return n; }\n    int count() const { \n\
    \        int res = 0; \n        for (auto x : a) res += std::popcount(x); \n \
    \       return res; \n    }\n    int _Find_first() const {\n        for (size_t\
    \ i = 0; i < a.size(); ++i)\n            if (a[i]) return i * 64 + std::countr_zero(a[i]);\n\
    \        return n;\n    }\n    int _Find_last() const {\n        for (int i =\
    \ (int)a.size() - 1; i >= 0; --i)\n            if (a[i]) return i * 64 + 63 -\
    \ std::countl_zero(a[i]);\n        return -1;\n    }\n    int _Find_next(int i)\
    \ const {\n        if (++i >= n) return n;\n        int blk = i >> 6, bit = i\
    \ & 63;\n        uint64_t x = a[blk] & (~0ULL << bit);\n        if (x) return\
    \ blk * 64 + std::countr_zero(x);\n        for (size_t j = blk + 1; j < a.size();\
    \ ++j)\n            if (a[j]) return j * 64 + std::countr_zero(a[j]);\n      \
    \  return n;\n    }\n    int _Find_prev(int i) const {\n        if (i <= 0) return\
    \ -1;\n        i = std::min(i, n) - 1;\n        int blk = i >> 6, bit = i & 63;\n\
    \        uint64_t mask = ~0ULL >> (63 - bit);\n        uint64_t x = a[blk] & mask;\n\
    \        if (x) return blk * 64 + 63 - std::countl_zero(x);\n        for (int\
    \ j = blk - 1; j >= 0; --j)\n            if (a[j]) return j * 64 + 63 - std::countl_zero(a[j]);\n\
    \        return -1;\n    }\n    bool operator==(const DynamicBitset&) const =\
    \ default;\n    std::string to_string() const {\n        std::string s(n, '0');\n\
    \        for (int i = 0; i < n; ++i) if ((*this)[i]) s[n - 1 - i] = '1';\n   \
    \     return s;\n    }\n    void swap(DynamicBitset &o) { std::swap(n, o.n), a.swap(o.a);\
    \ }\n\n    friend std::ostream& operator<<(std::ostream& os, const DynamicBitset&\
    \ b) { return os << b.to_string(); }\n    friend std::istream& operator>>(std::istream&\
    \ is, DynamicBitset& b) {\n        std::string s; if (is >> s) b = DynamicBitset(s);\n\
    \        return is;\n    }\n    DynamicBitset& operator&=(const DynamicBitset&\
    \ o) { \n        size_t sz = a.size(); uint64_t* p = a.data(); const uint64_t*\
    \ op = o.a.data();\n        for(size_t i = 0; i < sz; ++i) p[i] &= op[i]; \n \
    \       return *this; \n    }\n    DynamicBitset& operator|=(const DynamicBitset&\
    \ o) { \n        size_t sz = a.size(); uint64_t* p = a.data(); const uint64_t*\
    \ op = o.a.data();\n        for(size_t i = 0; i < sz; ++i) p[i] |= op[i]; \n \
    \       return *this; \n    }\n    DynamicBitset& operator^=(const DynamicBitset&\
    \ o) { \n        size_t sz = a.size(); uint64_t* p = a.data(); const uint64_t*\
    \ op = o.a.data();\n        for(size_t i = 0; i < sz; ++i) p[i] ^= op[i]; \n \
    \       return *this; \n    }\n    DynamicBitset& operator+=(const DynamicBitset&\
    \ o) {\n        unsigned char carry = 0;\n        size_t sz = a.size(), osz =\
    \ o.a.size();\n        uint64_t* p = a.data(); const uint64_t* op = o.a.data();\n\
    \        \n        for (size_t i = 0; i < sz; ++i) {\n            uint64_t v =\
    \ (i < osz) ? op[i] : 0;\n            carry = add_carry(carry, p[i], v, p[i]);\n\
    \        }\n        clean(); return *this;\n    } \n    DynamicBitset& operator-=(const\
    \ DynamicBitset& o) {\n        unsigned char borrow = 0;\n        size_t sz =\
    \ a.size(), osz = o.a.size();\n        uint64_t* p = a.data(); const uint64_t*\
    \ op = o.a.data();\n        \n        for (size_t i = 0; i < sz; ++i) {\n    \
    \        uint64_t v = (i < osz) ? op[i] : 0;\n            borrow = sub_borrow(borrow,\
    \ p[i], v, p[i]);\n        }\n        clean(); return *this;\n    } \n    DynamicBitset&\
    \ operator<<=(int k) {\n        if (k >= n) { memset(a.data(), 0, a.size() * sizeof(uint64_t));\
    \ return *this; }\n        int blocks = k >> 6, bits = k & 63;\n        int sz\
    \ = (int)a.size();\n        uint64_t* p = a.data();\n\n        if (bits == 0)\n\
    \            for (int i = sz - 1; i >= blocks; --i) p[i] = p[i - blocks];\n  \
    \      else {\n            for (int i = sz - 1; i > blocks; --i)\n           \
    \     p[i] = (p[i - blocks] << bits) | (p[i - blocks - 1] >> (64 - bits));\n \
    \           p[blocks] = p[0] << bits;\n        }\n        memset(p, 0, blocks\
    \ * sizeof(uint64_t));\n        clean(); return *this;\n    } \n    DynamicBitset&\
    \ operator>>=(int k) {\n        if (k >= n) { memset(a.data(), 0, a.size() * sizeof(uint64_t));\
    \ return *this; }\n        int blocks = k >> 6, bits = k & 63;\n        int sz\
    \ = (int)a.size();\n        uint64_t* p = a.data();\n        \n        if (bits\
    \ == 0)\n            for (int i = 0; i < sz - blocks; ++i) p[i] = p[i + blocks];\n\
    \        else {\n            int limit = sz - blocks - 1;\n            for (int\
    \ i = 0; i < limit; ++i)\n                p[i] = (p[i + blocks] >> bits) | (p[i\
    \ + blocks + 1] << (64 - bits));\n            p[limit] = p[sz - 1] >> bits;\n\
    \        }\n        memset(p + (sz - blocks), 0, blocks * sizeof(uint64_t));\n\
    \        clean(); return *this;\n    }\n    DynamicBitset& flip() {\n        size_t\
    \ sz = a.size();\n        uint64_t* p = a.data();\n        for (size_t i = 0;\
    \ i < sz; ++i) p[i] = ~p[i];\n        clean();\n        return *this;\n    }\n\
    \n    DynamicBitset operator+(const DynamicBitset& o) const { auto res = *this;\
    \ return res += o; }\n    DynamicBitset operator-(const DynamicBitset& o) const\
    \ { auto res = *this; return res -= o; }\n    DynamicBitset operator&(const DynamicBitset&\
    \ o) const { auto res = *this; return res &= o; }\n    DynamicBitset operator|(const\
    \ DynamicBitset& o) const { auto res = *this; return res |= o; }\n    DynamicBitset\
    \ operator^(const DynamicBitset& o) const { auto res = *this; return res ^= o;\
    \ }\n    DynamicBitset operator<<(int k) const { auto res = *this; return res\
    \ <<= k; }\n    DynamicBitset operator>>(int k) const { auto res = *this; return\
    \ res >>= k; }\n    DynamicBitset operator~() const { auto res = *this; return\
    \ res.flip(); }\n    DynamicBitset operator-() const {\n        DynamicBitset\
    \ res = ~(*this);\n        uint64_t carry = 1;\n        for (size_t i = 0; i <\
    \ res.a.size() && carry; ++i) {\n            res.a[i] += 1;\n            carry\
    \ = (res.a[i] == 0);\n        }\n        res.clean();\n        return res;\n \
    \   }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/DynamicBitset.hpp
  requiredBy:
  - Matrix/MatrixF2.hpp
  timestamp: '2026-07-04 18:47:24+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp
documentation_of: DataStructure/DynamicBitset.hpp
layout: document
title: Dynamic Bitset
---

A dynamically sized bitset that supports bitwise operations, arithmetic operations (addition, subtraction, negation), shifting, and bit searching. It is optimized to perform operations 64 bits at a time using `uint64_t` blocks, and leverages x86 intrinsics for fast addition/subtraction carry propagation.

---

## Constructor (Size)

```cpp
DynamicBitset(int n = 0);
```

* $O(N / 64)$ time

Constructs an empty `DynamicBitset` of size `n` with all bits initialized to `0`.

---

## Constructor (String)

```cpp
DynamicBitset(std::string_view s);
```

* $O(|s|)$ time

Constructs a `DynamicBitset` from a binary string `s` (consisting of `'0'` and `'1'`). The least significant bit (index `0`) corresponds to the last character of the string `s` (i.e. `s.back()`).

---

## clean

```cpp
void clean();
```

* $O(1)$ time

Clears/zeros out the unused/trailing bits in the last `uint64_t` block that lie beyond the bounds of the bitset size `n`. Usually called internally after shift or arithmetic operations.

---

## size

```cpp
int size() const;
```

* $O(1)$ time

Returns the number of bits in the bitset.

---

## count

```cpp
int count() const;
```

* $O(N / 64)$ time

Returns the number of bits that are set to `1`.

---

## test

```cpp
bool test(int i) const;
```

* $O(1)$ time

Returns the value of the bit at index `i`.

---

## set

```cpp
void set(int i);
```

* $O(1)$ time

Sets the bit at index `i` to `1`.

---

## reset

```cpp
void reset(int i);
```

* $O(1)$ time

Sets the bit at index `i` to `0`.

---

## flip

```cpp
void flip(int i);
```

* $O(1)$ time

Flips the value of the bit at index `i`.

---

## operator[]

```cpp
reference operator[](int i);
bool operator[](int i) const;
```

* $O(1)$ time

Accesses the bit at index `i`. The non-const version returns a proxy helper class `reference` which allows modification (e.g. `b[i] = 1`).

---

## _Find_first

```cpp
int _Find_first() const;
```

* $O(N / 64)$ time

Returns the index of the first (lowest) bit set to `1`. If no such bit exists, returns the size of the bitset.

---

## _Find_last

```cpp
int _Find_last() const;
```

* $O(N / 64)$ time

Returns the index of the last (highest) bit set to `1`. If no such bit exists, returns `-1`.

---

## _Find_next

```cpp
int _Find_next(int i) const;
```

* $O(N / 64)$ time

Returns the index of the first set bit after index `i` (greater than `i`). If no such bit exists, returns the size of the bitset.

---

## _Find_prev

```cpp
int _Find_prev(int i) const;
```

* $O(N / 64)$ time

Returns the index of the first set bit before index `i` (less than `i`). If no such bit exists, returns `-1`.

---

## swap

```cpp
void swap(DynamicBitset &o);
```

* $O(1)$ time

Swaps the contents of this bitset with another bitset `o`.

---

## to_string

```cpp
std::string to_string() const;
```

* $O(N)$ time

Returns the binary string representation of the bitset.

---

## Bitwise Operators

```cpp
DynamicBitset operator~() const;
DynamicBitset& flip();

DynamicBitset& operator&=(const DynamicBitset& o);
DynamicBitset& operator|=(const DynamicBitset& o);
DynamicBitset& operator^=(const DynamicBitset& o);

DynamicBitset operator&(const DynamicBitset& o) const;
DynamicBitset operator|(const DynamicBitset& o) const;
DynamicBitset operator^(const DynamicBitset& o) const;
```

* $O(N / 64)$ time

Performs standard bitwise operations (NOT, AND, OR, XOR).
* `flip()` is equivalent to `operator~` but modifies the bitset in-place and returns `*this`.

---

## Shift Operators

```cpp
DynamicBitset& operator<<=(int k);
DynamicBitset& operator>>=(int k);

DynamicBitset operator<<(int k) const;
DynamicBitset operator>>(int k) const;
```

* $O(N / 64)$ time

Performs left and right bit-shifts by `k` positions.

---

## Arithmetic Operators

```cpp
DynamicBitset& operator+=(const DynamicBitset& o);
DynamicBitset& operator-=(const DynamicBitset& o);

DynamicBitset operator+(const DynamicBitset& o) const;
DynamicBitset operator-(const DynamicBitset& o) const;
DynamicBitset operator-() const;
```

* $O(N / 64)$ time

Performs arithmetic addition, subtraction, or negation (two's complement) treating the bitset as a large binary integer.
* Utilizes x86 hardware carry/borrow instructions (`_addcarry_u64` / `_subborrow_u64`) when compiled on `__x86_64__` architecture.

---

## Comparison Operators

```cpp
bool operator==(const DynamicBitset&) const = default;
```

* $O(N / 64)$ time

Checks if two bitsets are equal.

---

## Stream I/O

```cpp
friend std::ostream& operator<<(std::ostream& os, const DynamicBitset& b);
friend std::istream& operator>>(std::istream& is, DynamicBitset& b);
```

Allows direct input/output of the bitset from/to streams using binary strings.
