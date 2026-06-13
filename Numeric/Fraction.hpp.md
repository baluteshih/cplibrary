---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/Fraction.hpp\"\n\nnamespace FracFmt {\n    inline\
    \ const char* sep = \"/\";\n    inline bool omit_one = true;\n}\n\ntemplate<typename\
    \ T, bool use_gcd = false>\nstruct Fraction {\n    T n, d;\n    \n    void simplify()\
    \ {\n        if constexpr (use_gcd) {\n            T t = std::gcd(n, d);\n   \
    \         n /= t, d /= t;\n        }\n        if (d < T(0)) n = -n, d = -d;\n\
    \    }\n    \n    Fraction(const T &_n = 0, const T &_d = 1): n(_n), d(_d) {\n\
    \        simplify();\n    }\n    \n    Fraction operator+() const { return *this;\
    \ }\n    Fraction operator-() const { return Fraction(-n, d); }\n    \n    Fraction&\
    \ operator+=(const Fraction &b) {\n        std::tie(n, d) = std::make_pair(n *\
    \ b.d + b.n * d, d * b.d);\n        simplify();\n        return *this; \n    }\n\
    \    Fraction& operator-=(const Fraction &b) {\n        std::tie(n, d) = std::make_pair(n\
    \ * b.d - b.n * d, d * b.d);\n        simplify();\n        return *this;\n   \
    \ }\n    Fraction& operator*=(const Fraction &b) {\n        std::tie(n, d) = std::make_pair(n\
    \ * b.n, d * b.d);\n        simplify();\n        return *this;\n    }\n    Fraction&\
    \ operator/=(const Fraction &b) {\n        std::tie(n, d) = std::make_pair(n *\
    \ b.d, d * b.n);\n        simplify();\n        return *this;\n    }\n    Fraction\
    \ simplified() const {\n        T t = std::gcd(n, d);\n        return Fraction(n\
    \ / t, d / t);\n    }\n    \n    friend Fraction operator+(const Fraction &lhs,\
    \ const Fraction &rhs) { \n        return Fraction(lhs) += rhs; \n    }\n    friend\
    \ Fraction operator-(const Fraction &lhs, const Fraction &rhs) { \n        return\
    \ Fraction(lhs) -= rhs; \n    }\n    friend Fraction operator*(const Fraction\
    \ &lhs, const Fraction &rhs) { \n        return Fraction(lhs) *= rhs; \n    }\n\
    \    friend Fraction operator/(const Fraction &lhs, const Fraction &rhs) { \n\
    \        return Fraction(lhs) /= rhs; \n    }\n    \n    friend bool operator==(const\
    \ Fraction &lhs, const Fraction &rhs) {\n        if constexpr (use_gcd) return\
    \ lhs.n == rhs.n && lhs.d == rhs.d;\n        else return lhs.n * rhs.d == rhs.n\
    \ * lhs.d;\n    }\n    friend bool operator!=(const Fraction &lhs, const Fraction\
    \ &rhs) {\n        return !(lhs == rhs);\n    }\n    friend std::strong_ordering\
    \ operator<=>(const Fraction &lhs, const Fraction &rhs) {\n        return lhs.n\
    \ * rhs.d <=> rhs.n * lhs.d;\n    }\n    \n    T val() const { return n / d; }\n\
    \    T floor() const { return n / d - (n % d && n < 0); }\n    T ceil() const\
    \ { return n / d + (n % d && n >= 0); }\n    \n    friend std::ostream& operator<<(std::ostream&\
    \ os, const Fraction &v) {\n        os << v.n;\n        if (!FracFmt::omit_one\
    \ || v.d != T(1))\n            os << FracFmt::sep << v.d;\n        return os;\n\
    \    }\n};\n"
  code: "#pragma once\n\nnamespace FracFmt {\n    inline const char* sep = \"/\";\n\
    \    inline bool omit_one = true;\n}\n\ntemplate<typename T, bool use_gcd = false>\n\
    struct Fraction {\n    T n, d;\n    \n    void simplify() {\n        if constexpr\
    \ (use_gcd) {\n            T t = std::gcd(n, d);\n            n /= t, d /= t;\n\
    \        }\n        if (d < T(0)) n = -n, d = -d;\n    }\n    \n    Fraction(const\
    \ T &_n = 0, const T &_d = 1): n(_n), d(_d) {\n        simplify();\n    }\n  \
    \  \n    Fraction operator+() const { return *this; }\n    Fraction operator-()\
    \ const { return Fraction(-n, d); }\n    \n    Fraction& operator+=(const Fraction\
    \ &b) {\n        std::tie(n, d) = std::make_pair(n * b.d + b.n * d, d * b.d);\n\
    \        simplify();\n        return *this; \n    }\n    Fraction& operator-=(const\
    \ Fraction &b) {\n        std::tie(n, d) = std::make_pair(n * b.d - b.n * d, d\
    \ * b.d);\n        simplify();\n        return *this;\n    }\n    Fraction& operator*=(const\
    \ Fraction &b) {\n        std::tie(n, d) = std::make_pair(n * b.n, d * b.d);\n\
    \        simplify();\n        return *this;\n    }\n    Fraction& operator/=(const\
    \ Fraction &b) {\n        std::tie(n, d) = std::make_pair(n * b.d, d * b.n);\n\
    \        simplify();\n        return *this;\n    }\n    Fraction simplified()\
    \ const {\n        T t = std::gcd(n, d);\n        return Fraction(n / t, d / t);\n\
    \    }\n    \n    friend Fraction operator+(const Fraction &lhs, const Fraction\
    \ &rhs) { \n        return Fraction(lhs) += rhs; \n    }\n    friend Fraction\
    \ operator-(const Fraction &lhs, const Fraction &rhs) { \n        return Fraction(lhs)\
    \ -= rhs; \n    }\n    friend Fraction operator*(const Fraction &lhs, const Fraction\
    \ &rhs) { \n        return Fraction(lhs) *= rhs; \n    }\n    friend Fraction\
    \ operator/(const Fraction &lhs, const Fraction &rhs) { \n        return Fraction(lhs)\
    \ /= rhs; \n    }\n    \n    friend bool operator==(const Fraction &lhs, const\
    \ Fraction &rhs) {\n        if constexpr (use_gcd) return lhs.n == rhs.n && lhs.d\
    \ == rhs.d;\n        else return lhs.n * rhs.d == rhs.n * lhs.d;\n    }\n    friend\
    \ bool operator!=(const Fraction &lhs, const Fraction &rhs) {\n        return\
    \ !(lhs == rhs);\n    }\n    friend std::strong_ordering operator<=>(const Fraction\
    \ &lhs, const Fraction &rhs) {\n        return lhs.n * rhs.d <=> rhs.n * lhs.d;\n\
    \    }\n    \n    T val() const { return n / d; }\n    T floor() const { return\
    \ n / d - (n % d && n < 0); }\n    T ceil() const { return n / d + (n % d && n\
    \ >= 0); }\n    \n    friend std::ostream& operator<<(std::ostream& os, const\
    \ Fraction &v) {\n        os << v.n;\n        if (!FracFmt::omit_one || v.d !=\
    \ T(1))\n            os << FracFmt::sep << v.d;\n        return os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/Fraction.hpp
  requiredBy: []
  timestamp: '2026-06-04 20:52:48+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Numeric/Fraction.hpp
layout: document
redirect_from:
- /library/Numeric/Fraction.hpp
- /library/Numeric/Fraction.hpp.html
title: Numeric/Fraction.hpp
---
