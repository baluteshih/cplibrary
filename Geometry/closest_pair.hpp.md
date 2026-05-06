---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Geometry/base.hpp
    title: Geometry/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/geometry/closest_pair.test.cpp
    title: test/1_library_checker/geometry/closest_pair.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Geometry/closest_pair.hpp\"\n\n#line 2 \"Geometry/base.hpp\"\
    \n    \ntemplate <typename T>\nusing DefaultFloat = std::conditional_t<std::is_floating_point_v<T>,\
    \ T, double>;\n\ntemplate <typename T>\nconstexpr T get_default_eps() {\n    if\
    \ constexpr (std::is_same_v<T, float>)\n        return T(1e-6);\n    else if constexpr\
    \ (std::is_same_v<T, double>)\n        return T(1e-9);\n    else if constexpr\
    \ (std::is_same_v<T, long double>)\n        return T(1e-12);\n    else\n     \
    \   return T(0); \n}\n\ntemplate <typename T, T eps = get_default_eps<T>()>\n\
    struct Geometry {\n    static int sign(T x) {\n        if constexpr (std::is_floating_point_v<T>)\
    \ {\n            return (x > eps) - (x < -eps); \n        }\n        else {\n\
    \            return (x > 0) - (x < 0);\n        }\n    }\n    static int cmp(T\
    \ a, T b) {\n        return sign(a - b);\n    }\n};\n\ntemplate<typename T, T\
    \ eps = get_default_eps<T>(), typename MulT = T>\nstruct Pt : Geometry<T, eps>\
    \ {\n    using value_type = T;\n    using Geometry<MulT, eps>::sign;\n    using\
    \ Geometry<MulT, eps>::cmp;\n    static constexpr T eps_val = eps;\n    T x =\
    \ 0, y = 0;\n    Pt() : x(0), y(0) {}\n    Pt(T x_, T y_) : x(x_), y(y_) {}\n\
    \    friend istream& operator>>(istream &is, Pt &p) { return is >> p.x >> p.y;\
    \ }\n    friend ostream& operator<<(ostream &os, const Pt &p) { return os << p.x\
    \ << ' ' << p.y; }\n    friend bool operator==(const Pt &a, const Pt &b) { \n\
    \        return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0; \n    }\n    friend\
    \ bool operator!=(const Pt &a, const Pt &b) { return !(a == b); }\n    Pt operator-()\
    \ { return Pt(-x, -y); }\n    Pt& operator+=(const Pt &a) {\n        x += a.x,\
    \ y += a.y;\n        return *this;\n    }\n    Pt& operator-=(const Pt &a) {\n\
    \        x -= a.x, y -= a.y;\n        return *this;\n    }\n    Pt& operator*=(T\
    \ d) {\n        x *= d, y *= d;\n        return *this;\n    }\n    Pt& operator/=(T\
    \ d) {\n        x /= d, y /= d;\n        return *this;\n    }\n    friend Pt operator+(const\
    \ Pt &a, const Pt &b) { return Pt(a) += b; }\n    friend Pt operator-(const Pt\
    \ &a, const Pt &b) { return Pt(a) -= b; }\n    friend Pt operator*(const Pt &a,\
    \ T d) { return Pt(a) *= d; }\n    friend Pt operator/(const Pt &a, T d) { return\
    \ Pt(a) /= d; }\n    friend bool operator<(const Pt &a, const Pt &b) {\n     \
    \   int sx = cmp(a.x, b.x);\n        return sx != 0 ? sx == -1 : cmp(a.y, b.y)\
    \ == -1;\n    }\n    friend bool operator>(const Pt &a, const Pt &b) { return\
    \ b < a; }\n    friend bool operator<=(const Pt &a, const Pt &b) { return !(b\
    \ < a); }\n    friend bool operator>=(const Pt &a, const Pt &b) { return !(a <\
    \ b); }\n    template <typename U, U _eps, typename _MulT>\n    Pt(const Pt<U,\
    \ _eps, _MulT>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))\
    \ {}\n    friend MulT dot(const Pt &a, const Pt &b) {\n        return MulT(a.x)\
    \ * MulT(b.x) + MulT(a.y) * MulT(b.y);\n    }\n    friend MulT cross(const Pt\
    \ &a, const Pt &b) {\n        return MulT(a.x) * MulT(b.y) - MulT(a.y) * MulT(b.x);\n\
    \    }\n    friend MulT square(const Pt &a) {\n        return dot(a, a);\n   \
    \ }\n    friend MulT dist2(const Pt &a, const Pt &b) {\n        return square(a\
    \ - b);\n    }\n    template <typename Ret = DefaultFloat<T>>\n    friend Ret\
    \ length(const Pt &a) {\n        return std::sqrt(static_cast<Ret>(square(a)));\
    \ \n    }\n    template <typename Ret = DefaultFloat<T>>\n    friend Ret dist(const\
    \ Pt &a, const Pt &b) {\n        return length<Ret>(a - b); \n    }\n    template\
    \ <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(),\
    \ typename _MulT = Ret>\n    friend Pt<Ret, _eps, _MulT> normal(const Pt &a) {\n\
    \        Ret len = length(a);\n        return Pt<Ret, _eps, _MulT>(a) / len;\n\
    \    }\n    friend MulT cross(const Pt &p, const Pt &a, const Pt &b) {\n     \
    \   return cross(a - p, b - p);\n    }\n    // 1 if on a->b's left\n    friend\
    \ int side(const Pt &p, const Pt &a, const Pt &b) {\n        return sign(cross(p,\
    \ a, b));\n    }\n    friend bool collinear(const Pt &a, const Pt &b, const Pt\
    \ &c) {\n        return side(a, b, c) == 0;\n    }\n    friend bool up(const Pt\
    \ &a) { \n        return sign(a.y) > 0 || (sign(a.y) == 0 && sign(a.x) > 0);\n\
    \    }\n    // 3 colinear? please remember to remove (0, 0)\n    friend bool polar(const\
    \ Pt &a, const Pt &b) {\n        bool ua = up(a), ub = up(b);\n        return\
    \ ua != ub ? ua : sign(cross(a, b)) == 1;\n    }\n    friend bool polar(const\
    \ Pt &a, const Pt &b, const Pt &base) {\n        bool ua = sign(cross(base, a))\
    \ > 0 || sameDirection(base, a);\n        bool ub = sign(cross(base, b)) > 0 ||\
    \ sameDirection(base, b);\n        return ua != ub ? ua : sign(cross(a, b)) ==\
    \ 1;\n    }\n    friend bool parallel(const Pt &a, const Pt &b) {\n        return\
    \ sign(cross(a, b)) == 0;\n    }\n    friend bool sameDirection(const Pt &a, const\
    \ Pt &b) {\n        return sign(cross(a, b)) == 0 && sign(dot(a, b)) == 1;\n \
    \   }\n    friend Pt rotate90(const Pt &p) {\n        return {-p.y, p.x};\n  \
    \  }\n    friend Pt rotate270(const Pt &p) {\n        return rotate90(-p);\n \
    \   }\n    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T,\
    \ Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>\n    friend Pt<Ret,\
    \ _eps, _MulT> rotate(const Pt &p, Ret ang) {\n        return {Ret(p.x) * std::cos(ang)\
    \ - Ret(p.y) * std::sin(ang), Ret(p.x) * std::sin(ang) + Ret(p.y) * std::cos(ang)};\n\
    \    }\n    template <typename Ret = DefaultFloat<T>>\n    friend Ret angle(const\
    \ Pt &p) {\n        return std::atan2(Ret(p.y), Ret(p.x));\n    }\n    friend\
    \ bool _betweenAngle(const Pt &o, const Pt &a, const Pt &b, const Pt &p, int strict)\
    \ {\n        return side(o, a, p) >= strict && side(o, p, b) >= strict;\n    }\n\
    \    // whether op located between the counter-clockwise interval of oa and ob\
    \ \n    friend bool betweenAngle(const Pt &o, const Pt &a, const Pt &b, const\
    \ Pt &p, int strict) {\n        if (side(o, a, b) >= 0) return _betweenAngle(o,\
    \ a, b, p, strict);\n        return !_betweenAngle(o, b, a, p, !strict);\n   \
    \ }\n};\n#line 4 \"Geometry/closest_pair.hpp\"\n\ntemplate<typename T, T eps =\
    \ get_default_eps<T>(), typename MulT = T>\nstd::pair<int, int> closest_pair(const\
    \ std::vector<Pt<T, eps, MulT>> &dots) {\n    int n = dots.size();\n    assert(n\
    \ >= 2);\n    std::vector<int> idx(n);\n    std::iota(idx.begin(), idx.end(),\
    \ 0);\n    std::ranges::sort(idx, [&](int a, int b) {\n        return dots[a]\
    \ < dots[b]; \n    });\n    MulT min_d2 = std::numeric_limits<MulT>::max();\n\
    \    std::pair<int, int> best = std::make_pair(-1, -1);\n    auto sq = [](T x)\
    \ { return MulT(x) * MulT(x); };\n    auto update = [&](int i, int j) {\n    \
    \    MulT cur = dist2(dots[i], dots[j]);\n        if (min_d2 > cur) {\n      \
    \      best = std::make_pair(i, j);\n            min_d2 = cur;\n        }\n  \
    \  };\n    auto cmp_y = [&dots](int a, int b) {\n        return dots[a].y < dots[b].y;\
    \  \n    };\n    std::multiset<int, decltype(cmp_y)> st(cmp_y);\n    std::vector<typename\
    \ std::multiset<int, decltype(cmp_y)>::iterator> its(n);\n    for (int i = 0,\
    \ lft = 0; i < n; ++i) {\n        int u = idx[i];\n        while (lft < i && sq(dots[u].x\
    \ - dots[idx[lft]].x) >= min_d2)\n            st.erase(its[lft++]);\n        auto\
    \ it = st.lower_bound(u);\n        for (auto t = it; t != st.begin();) {\n   \
    \         if (sq(dots[u].y - dots[*(--t)].y) >= min_d2) break;\n            update(*t,\
    \ u);\n        }\n        for (auto t = it; t != st.end(); ++t) {\n          \
    \  if (sq(dots[u].y - dots[*t].y) >= min_d2) break;\n            update(*t, u);\n\
    \        }\n        its[i] = st.insert(it, u);\n    }\n    return best;\n}\n"
  code: "#pragma once\n\n#include \"Geometry/base.hpp\"\n\ntemplate<typename T, T\
    \ eps = get_default_eps<T>(), typename MulT = T>\nstd::pair<int, int> closest_pair(const\
    \ std::vector<Pt<T, eps, MulT>> &dots) {\n    int n = dots.size();\n    assert(n\
    \ >= 2);\n    std::vector<int> idx(n);\n    std::iota(idx.begin(), idx.end(),\
    \ 0);\n    std::ranges::sort(idx, [&](int a, int b) {\n        return dots[a]\
    \ < dots[b]; \n    });\n    MulT min_d2 = std::numeric_limits<MulT>::max();\n\
    \    std::pair<int, int> best = std::make_pair(-1, -1);\n    auto sq = [](T x)\
    \ { return MulT(x) * MulT(x); };\n    auto update = [&](int i, int j) {\n    \
    \    MulT cur = dist2(dots[i], dots[j]);\n        if (min_d2 > cur) {\n      \
    \      best = std::make_pair(i, j);\n            min_d2 = cur;\n        }\n  \
    \  };\n    auto cmp_y = [&dots](int a, int b) {\n        return dots[a].y < dots[b].y;\
    \  \n    };\n    std::multiset<int, decltype(cmp_y)> st(cmp_y);\n    std::vector<typename\
    \ std::multiset<int, decltype(cmp_y)>::iterator> its(n);\n    for (int i = 0,\
    \ lft = 0; i < n; ++i) {\n        int u = idx[i];\n        while (lft < i && sq(dots[u].x\
    \ - dots[idx[lft]].x) >= min_d2)\n            st.erase(its[lft++]);\n        auto\
    \ it = st.lower_bound(u);\n        for (auto t = it; t != st.begin();) {\n   \
    \         if (sq(dots[u].y - dots[*(--t)].y) >= min_d2) break;\n            update(*t,\
    \ u);\n        }\n        for (auto t = it; t != st.end(); ++t) {\n          \
    \  if (sq(dots[u].y - dots[*t].y) >= min_d2) break;\n            update(*t, u);\n\
    \        }\n        its[i] = st.insert(it, u);\n    }\n    return best;\n}\n"
  dependsOn:
  - Geometry/base.hpp
  isVerificationFile: false
  path: Geometry/closest_pair.hpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/geometry/closest_pair.test.cpp
documentation_of: Geometry/closest_pair.hpp
layout: document
redirect_from:
- /library/Geometry/closest_pair.hpp
- /library/Geometry/closest_pair.hpp.html
title: Geometry/closest_pair.hpp
---
