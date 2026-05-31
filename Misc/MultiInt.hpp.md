---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: String/RollingHash.hpp
    title: String/RollingHash.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/string/longest_common_substring.test.cpp
    title: test/1_library_checker/string/longest_common_substring.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Misc/MultiInt.hpp\"\n\ntemplate <typename... Ints>\nstruct\
    \ MultiInt {\n    std::tuple<Ints...> v;\n    MultiInt() = default;\n    template\
    \ <typename T> requires std::is_integral_v<T>\n    MultiInt(T x) : v{ Ints(x)...\
    \ } {}\n    MultiInt(Ints... args) : v{args...} {}\n    MultiInt(std::tuple<Ints...>\
    \ t) : v(t) {}\n    MultiInt& operator+=(const MultiInt& o) {\n        [&]<std::size_t...\
    \ I>(std::index_sequence<I...>) {\n            ((std::get<I>(v) += std::get<I>(o.v)),\
    \ ...);\n        }(std::index_sequence_for<Ints...>{});\n        return *this;\n\
    \    }\n    MultiInt& operator-=(const MultiInt& o) {\n        [&]<std::size_t...\
    \ I>(std::index_sequence<I...>) {\n            ((std::get<I>(v) -= std::get<I>(o.v)),\
    \ ...);\n        }(std::index_sequence_for<Ints...>{});\n        return *this;\n\
    \    }\n    MultiInt& operator*=(const MultiInt& o) {\n        [&]<std::size_t...\
    \ I>(std::index_sequence<I...>) {\n            ((std::get<I>(v) *= std::get<I>(o.v)),\
    \ ...);\n        }(std::index_sequence_for<Ints...>{});\n        return *this;\n\
    \    }\n    MultiInt& operator/=(const MultiInt& o) {\n        [&]<std::size_t...\
    \ I>(std::index_sequence<I...>) {\n            ((std::get<I>(v) /= std::get<I>(o.v)),\
    \ ...);\n        }(std::index_sequence_for<Ints...>{});\n        return *this;\n\
    \    }\n    MultiInt operator+(const MultiInt& o) const { auto res = *this; return\
    \ res += o; }\n    MultiInt operator-(const MultiInt& o) const { auto res = *this;\
    \ return res -= o; }\n    MultiInt operator*(const MultiInt& o) const { auto res\
    \ = *this; return res *= o; }\n    MultiInt operator/(const MultiInt& o) const\
    \ { auto res = *this; return res /= o; }\n    bool operator==(const MultiInt&\
    \ o) const requires requires { v == o.v; } {\n        return v == o.v;\n    }\n\
    \    std::strong_ordering operator<=>(const MultiInt& o) const requires requires\
    \ { v <=> o.v; } {\n        return v <=> o.v;\n    }\n    friend ostream& operator<<(ostream&\
    \ os, const MultiInt& obj) {\n        std::apply([&os](const auto&... args) {\n\
    \            bool first = true;\n            ((os << (first ? \"\" : \" \") <<\
    \ args, first = false), ...);\n        }, obj.v);\n        return os;\n    }\n\
    };\n"
  code: "#pragma once\n\ntemplate <typename... Ints>\nstruct MultiInt {\n    std::tuple<Ints...>\
    \ v;\n    MultiInt() = default;\n    template <typename T> requires std::is_integral_v<T>\n\
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
    \ return os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Misc/MultiInt.hpp
  requiredBy:
  - String/RollingHash.hpp
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/string/longest_common_substring.test.cpp
documentation_of: Misc/MultiInt.hpp
layout: document
redirect_from:
- /library/Misc/MultiInt.hpp
- /library/Misc/MultiInt.hpp.html
title: Misc/MultiInt.hpp
---
