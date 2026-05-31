---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Misc/MultiInt.hpp
    title: Misc/MultiInt.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/string/longest_common_substring.test.cpp
    title: test/1_library_checker/string/longest_common_substring.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"String/RollingHash.hpp\"\n\n#line 2 \"Misc/MultiInt.hpp\"\
    \n\ntemplate <typename... Ints>\nstruct MultiInt {\n    std::tuple<Ints...> v;\n\
    \    MultiInt() = default;\n    template <typename T> requires std::is_integral_v<T>\n\
    \    MultiInt(T x) : v{ Ints(x)... } {}\n    MultiInt(Ints... args) : v{args...}\
    \ {}\n    MultiInt(std::tuple<Ints...> t) : v(t) {}\n    MultiInt& operator+=(const\
    \ MultiInt& o) {\n        [&]<std::size_t... I>(std::index_sequence<I...>) {\n\
    \            ((std::get<I>(v) += std::get<I>(o.v)), ...);\n        }(std::index_sequence_for<Ints...>{});\n\
    \        return *this;\n    }\n    MultiInt& operator-=(const MultiInt& o) {\n\
    \        [&]<std::size_t... I>(std::index_sequence<I...>) {\n            ((std::get<I>(v)\
    \ -= std::get<I>(o.v)), ...);\n        }(std::index_sequence_for<Ints...>{});\n\
    \        return *this;\n    }\n    MultiInt& operator*=(const MultiInt& o) {\n\
    \        [&]<std::size_t... I>(std::index_sequence<I...>) {\n            ((std::get<I>(v)\
    \ *= std::get<I>(o.v)), ...);\n        }(std::index_sequence_for<Ints...>{});\n\
    \        return *this;\n    }\n    MultiInt& operator/=(const MultiInt& o) {\n\
    \        [&]<std::size_t... I>(std::index_sequence<I...>) {\n            ((std::get<I>(v)\
    \ /= std::get<I>(o.v)), ...);\n        }(std::index_sequence_for<Ints...>{});\n\
    \        return *this;\n    }\n    MultiInt operator+(const MultiInt& o) const\
    \ { auto res = *this; return res += o; }\n    MultiInt operator-(const MultiInt&\
    \ o) const { auto res = *this; return res -= o; }\n    MultiInt operator*(const\
    \ MultiInt& o) const { auto res = *this; return res *= o; }\n    MultiInt operator/(const\
    \ MultiInt& o) const { auto res = *this; return res /= o; }\n    bool operator==(const\
    \ MultiInt& o) const requires requires { v == o.v; } {\n        return v == o.v;\n\
    \    }\n    std::strong_ordering operator<=>(const MultiInt& o) const requires\
    \ requires { v <=> o.v; } {\n        return v <=> o.v;\n    }\n    friend ostream&\
    \ operator<<(ostream& os, const MultiInt& obj) {\n        std::apply([&os](const\
    \ auto&... args) {\n            bool first = true;\n            ((os << (first\
    \ ? \"\" : \" \") << args, first = false), ...);\n        }, obj.v);\n       \
    \ return os;\n    }\n};\n#line 4 \"String/RollingHash.hpp\"\n\ntemplate <int base,\
    \ typename... Ints>\nstruct RollingHash {\n    using Val = MultiInt<Ints...>;\n\
    \    int sz = 0;\n    Val val;\n    inline static std::vector<Val> p_pow, p_ipow;\n\
    \    static void initialize() {\n        p_pow = std::vector<Val>{Val(1), Val(base)};\n\
    \        p_ipow = std::vector<Val>{Val(1), Val(1) / Val(base)};\n    }\n    static\
    \ void extend(int sz) {\n        if (p_pow.empty()) initialize();\n        int\
    \ cur = p_pow.size();\n        if (sz <= cur) return;\n        p_pow.resize(sz),\
    \ p_ipow.resize(sz);\n        if (cur < sz) {\n            for (int i = cur; i\
    \ < sz; ++i) {\n                p_pow[i] = p_pow[i - 1] * p_pow[1];\n        \
    \        p_ipow[i] = p_ipow[i - 1] * p_ipow[1]; \n            }\n        }\n \
    \   }\n    static Val get_pow(int idx) {\n        if (idx >= int(p_pow.size()))\
    \ extend(idx + 1);\n        return p_pow[idx];\n    }\n    static Val get_ipow(int\
    \ idx) {\n        if (idx >= int(p_ipow.size())) extend(idx + 1);\n        return\
    \ p_ipow[idx];\n    }\n    RollingHash() = default; \n    template <typename T>\
    \ \n    RollingHash(int _sz, T x) : sz(_sz), val(x) {}\n    RollingHash(int _sz,\
    \ Ints... args) : sz(_sz), val(args...) {}\n    RollingHash& operator+=(const\
    \ RollingHash &rhs) {\n        val += rhs.val * get_pow(sz);\n        sz += rhs.sz;\n\
    \        return *this; \n    }\n    RollingHash& operator*=(const int &v) {\n\
    \        if (v > 0) val *= get_pow(v);\n        else if (v < 0) val *= get_ipow(-v);\n\
    \        return *this;\n    }\n    RollingHash& operator-=(const RollingHash &rhs)\
    \ {\n        val -= rhs.val;\n        sz -= rhs.sz;\n        return *this; \n\
    \    }\n    RollingHash operator+(const RollingHash& o) const { auto res = *this;\
    \ return res += o; }\n    RollingHash operator-(const RollingHash& o) const {\
    \ auto res = *this; return res -= o; }\n    RollingHash operator*(const int& o)\
    \ const { auto res = *this; return res *= o; }\n    bool operator==(const RollingHash\
    \ &rhs) const {\n        return sz == rhs.sz && val == rhs.val;\n    }\n    std::strong_ordering\
    \ operator<=>(const RollingHash &rhs) const {\n        if (sz != rhs.sz) return\
    \ sz <=> rhs.sz;\n        return val <=> rhs.val;\n    }\n    static std::vector<RollingHash>\
    \ prefixHash(const auto &a) {\n        std::vector<RollingHash> res(a.size());\n\
    \        extend(a.size());\n        for (int i = 0; i < int(a.size()); ++i) {\n\
    \            res[i] = RollingHash(1, Val(a[i]));\n            if (i) res[i] =\
    \ res[i - 1] + res[i];\n        }\n        return res;\n    }\n    static RollingHash\
    \ rangeHash(const std::vector<RollingHash> &prefix_sum, int l, int r) {\n    \
    \    if (l > r) return RollingHash();\n        if (l == 0) return prefix_sum[r\
    \ - 1];\n        return (prefix_sum[r - 1] - prefix_sum[l - 1]) * (-l);\n    }\n\
    \    friend ostream& operator<<(ostream& os, const RollingHash& v) {\n       \
    \ os << v.sz << \" | \" << v.val; \n        return os;\n    }\n};\n"
  code: "#pragma once\n\n#include \"Misc/MultiInt.hpp\"\n\ntemplate <int base, typename...\
    \ Ints>\nstruct RollingHash {\n    using Val = MultiInt<Ints...>;\n    int sz\
    \ = 0;\n    Val val;\n    inline static std::vector<Val> p_pow, p_ipow;\n    static\
    \ void initialize() {\n        p_pow = std::vector<Val>{Val(1), Val(base)};\n\
    \        p_ipow = std::vector<Val>{Val(1), Val(1) / Val(base)};\n    }\n    static\
    \ void extend(int sz) {\n        if (p_pow.empty()) initialize();\n        int\
    \ cur = p_pow.size();\n        if (sz <= cur) return;\n        p_pow.resize(sz),\
    \ p_ipow.resize(sz);\n        if (cur < sz) {\n            for (int i = cur; i\
    \ < sz; ++i) {\n                p_pow[i] = p_pow[i - 1] * p_pow[1];\n        \
    \        p_ipow[i] = p_ipow[i - 1] * p_ipow[1]; \n            }\n        }\n \
    \   }\n    static Val get_pow(int idx) {\n        if (idx >= int(p_pow.size()))\
    \ extend(idx + 1);\n        return p_pow[idx];\n    }\n    static Val get_ipow(int\
    \ idx) {\n        if (idx >= int(p_ipow.size())) extend(idx + 1);\n        return\
    \ p_ipow[idx];\n    }\n    RollingHash() = default; \n    template <typename T>\
    \ \n    RollingHash(int _sz, T x) : sz(_sz), val(x) {}\n    RollingHash(int _sz,\
    \ Ints... args) : sz(_sz), val(args...) {}\n    RollingHash& operator+=(const\
    \ RollingHash &rhs) {\n        val += rhs.val * get_pow(sz);\n        sz += rhs.sz;\n\
    \        return *this; \n    }\n    RollingHash& operator*=(const int &v) {\n\
    \        if (v > 0) val *= get_pow(v);\n        else if (v < 0) val *= get_ipow(-v);\n\
    \        return *this;\n    }\n    RollingHash& operator-=(const RollingHash &rhs)\
    \ {\n        val -= rhs.val;\n        sz -= rhs.sz;\n        return *this; \n\
    \    }\n    RollingHash operator+(const RollingHash& o) const { auto res = *this;\
    \ return res += o; }\n    RollingHash operator-(const RollingHash& o) const {\
    \ auto res = *this; return res -= o; }\n    RollingHash operator*(const int& o)\
    \ const { auto res = *this; return res *= o; }\n    bool operator==(const RollingHash\
    \ &rhs) const {\n        return sz == rhs.sz && val == rhs.val;\n    }\n    std::strong_ordering\
    \ operator<=>(const RollingHash &rhs) const {\n        if (sz != rhs.sz) return\
    \ sz <=> rhs.sz;\n        return val <=> rhs.val;\n    }\n    static std::vector<RollingHash>\
    \ prefixHash(const auto &a) {\n        std::vector<RollingHash> res(a.size());\n\
    \        extend(a.size());\n        for (int i = 0; i < int(a.size()); ++i) {\n\
    \            res[i] = RollingHash(1, Val(a[i]));\n            if (i) res[i] =\
    \ res[i - 1] + res[i];\n        }\n        return res;\n    }\n    static RollingHash\
    \ rangeHash(const std::vector<RollingHash> &prefix_sum, int l, int r) {\n    \
    \    if (l > r) return RollingHash();\n        if (l == 0) return prefix_sum[r\
    \ - 1];\n        return (prefix_sum[r - 1] - prefix_sum[l - 1]) * (-l);\n    }\n\
    \    friend ostream& operator<<(ostream& os, const RollingHash& v) {\n       \
    \ os << v.sz << \" | \" << v.val; \n        return os;\n    }\n};\n"
  dependsOn:
  - Misc/MultiInt.hpp
  isVerificationFile: false
  path: String/RollingHash.hpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/string/longest_common_substring.test.cpp
documentation_of: String/RollingHash.hpp
layout: document
redirect_from:
- /library/String/RollingHash.hpp
- /library/String/RollingHash.hpp.html
title: String/RollingHash.hpp
---
