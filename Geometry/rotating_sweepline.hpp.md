---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Geometry/base.hpp
    title: Geometry/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/5_NCOJ/123.test.cpp
    title: test/5_NCOJ/123.test.cpp
  - icon: ':x:'
    path: test/5_NCOJ/929.test.cpp
    title: test/5_NCOJ/929.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Geometry/rotating_sweepline.hpp\"\n\n#line 2 \"Geometry/base.hpp\"\
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
    \ }\n};\n#line 4 \"Geometry/rotating_sweepline.hpp\"\n\n/*\ninit_order(const std::vector<int>\
    \ &ord)\n\nif reverse_convention is true:\nupdate_ans(const std::vector<int> &ord,\
    \ int l, int r): \n    calculate ans related to line(pts[ord[l]], pts[ord[l+1]],\
    \ ..., pts[ord[r]]) with the support of ord\n    ord[l..r] will be reversed after\
    \ the call of update_ans, so if needed, update_ans should reverse the interval\
    \ in their data structure  \nelse:\nupdate_ans(const std::vector<int> &ord, int\
    \ i): \n    calculate ans related to line(pts[ord[i]], pts[ord[i+1]]) with the\
    \ support of ord\n    ord[i], ord[i+1] will be swapped after the call of update_ans,\
    \ so if needed, update_ans should swap the two elements in their data structure\
    \  \n*/\ntemplate<typename Point, bool reverse_convention = true>\nvoid rotating_sweepline(const\
    \ std::vector<Point> &pts, auto init_order, auto update_ans, const Point &init\
    \ = Point(1, 0)) {\n    int n = pts.size();\n    struct Event {\n        Point\
    \ dir; int u, v;\n    };\n    std::vector<Event> e; e.reserve(n * (n - 1));\n\
    \    for (int i = 0; i < n; ++i)\n        for (int j = 0; j < n; ++j)\n      \
    \      if (i != j)\n                e.push_back({pts[j] - pts[i], i, j});\n  \
    \  std::ranges::sort(e.begin(), e.end(), [&](const Event &a, const Event &b) {\n\
    \        return polar(a.dir, b.dir, init);\n    });\n    vector<int> ord(n), pos(n);\n\
    \    std::iota(ord.begin(), ord.end(), 0);\n    std::ranges::sort(ord, [&](int\
    \ a, int b) {\n        auto va = cross(init, pts[a]);\n        auto vb = cross(init,\
    \ pts[b]);\n        if (va != vb) return va < vb;\n        return dot(init, pts[a])\
    \ < dot(init, pts[b]);\n    });\n    for (int i = 0; i < n; i++) pos[ord[i]] =\
    \ i;\n    init_order(ord);\n    for (int i = 0, j = 0; i < int(e.size()); i =\
    \ j) {\n        std::vector<std::pair<int, int>> tmp;\n        for (; j < int(e.size())\
    \ && !polar(e[i].dir, e[j].dir, init); ++j)\n            tmp.emplace_back(e[j].u,\
    \ e[j].v);\n        ranges::sort(tmp, [&](const std::pair<int, int> &x, const\
    \ std::pair<int, int> &y) {\n            return std::make_pair(pos[x.first], pos[x.second])\
    \ < std::make_pair(pos[y.first], pos[y.second]);\n        });\n        for (int\
    \ k = 0; k < int(tmp.size()); ) {\n            int l = pos[tmp[k].first], r =\
    \ pos[tmp[k].second];\n            for (int tk = k; tk < int(tmp.size()) && pos[tmp[tk].first]\
    \ <= r; ++tk)\n                r = std::max(r, pos[tmp[tk].second]);\n       \
    \     if constexpr (reverse_convention) update_ans(ord, l, r);\n            for\
    \ (; k < int(tmp.size()) && pos[tmp[k].first] <= r; ++k) {\n                auto\
    \ [x, y] = tmp[k]; \n                if constexpr (!reverse_convention) update_ans(ord,\
    \ pos[x]);\n                std::tie(ord[pos[x]], ord[pos[y]], pos[x], pos[y])\
    \ = std::make_tuple(ord[pos[y]], ord[pos[x]], pos[y], pos[x]);\n            }\n\
    \        }\n    }\n}\n"
  code: "#pragma once\n\n#include \"Geometry/base.hpp\"\n\n/*\ninit_order(const std::vector<int>\
    \ &ord)\n\nif reverse_convention is true:\nupdate_ans(const std::vector<int> &ord,\
    \ int l, int r): \n    calculate ans related to line(pts[ord[l]], pts[ord[l+1]],\
    \ ..., pts[ord[r]]) with the support of ord\n    ord[l..r] will be reversed after\
    \ the call of update_ans, so if needed, update_ans should reverse the interval\
    \ in their data structure  \nelse:\nupdate_ans(const std::vector<int> &ord, int\
    \ i): \n    calculate ans related to line(pts[ord[i]], pts[ord[i+1]]) with the\
    \ support of ord\n    ord[i], ord[i+1] will be swapped after the call of update_ans,\
    \ so if needed, update_ans should swap the two elements in their data structure\
    \  \n*/\ntemplate<typename Point, bool reverse_convention = true>\nvoid rotating_sweepline(const\
    \ std::vector<Point> &pts, auto init_order, auto update_ans, const Point &init\
    \ = Point(1, 0)) {\n    int n = pts.size();\n    struct Event {\n        Point\
    \ dir; int u, v;\n    };\n    std::vector<Event> e; e.reserve(n * (n - 1));\n\
    \    for (int i = 0; i < n; ++i)\n        for (int j = 0; j < n; ++j)\n      \
    \      if (i != j)\n                e.push_back({pts[j] - pts[i], i, j});\n  \
    \  std::ranges::sort(e.begin(), e.end(), [&](const Event &a, const Event &b) {\n\
    \        return polar(a.dir, b.dir, init);\n    });\n    vector<int> ord(n), pos(n);\n\
    \    std::iota(ord.begin(), ord.end(), 0);\n    std::ranges::sort(ord, [&](int\
    \ a, int b) {\n        auto va = cross(init, pts[a]);\n        auto vb = cross(init,\
    \ pts[b]);\n        if (va != vb) return va < vb;\n        return dot(init, pts[a])\
    \ < dot(init, pts[b]);\n    });\n    for (int i = 0; i < n; i++) pos[ord[i]] =\
    \ i;\n    init_order(ord);\n    for (int i = 0, j = 0; i < int(e.size()); i =\
    \ j) {\n        std::vector<std::pair<int, int>> tmp;\n        for (; j < int(e.size())\
    \ && !polar(e[i].dir, e[j].dir, init); ++j)\n            tmp.emplace_back(e[j].u,\
    \ e[j].v);\n        ranges::sort(tmp, [&](const std::pair<int, int> &x, const\
    \ std::pair<int, int> &y) {\n            return std::make_pair(pos[x.first], pos[x.second])\
    \ < std::make_pair(pos[y.first], pos[y.second]);\n        });\n        for (int\
    \ k = 0; k < int(tmp.size()); ) {\n            int l = pos[tmp[k].first], r =\
    \ pos[tmp[k].second];\n            for (int tk = k; tk < int(tmp.size()) && pos[tmp[tk].first]\
    \ <= r; ++tk)\n                r = std::max(r, pos[tmp[tk].second]);\n       \
    \     if constexpr (reverse_convention) update_ans(ord, l, r);\n            for\
    \ (; k < int(tmp.size()) && pos[tmp[k].first] <= r; ++k) {\n                auto\
    \ [x, y] = tmp[k]; \n                if constexpr (!reverse_convention) update_ans(ord,\
    \ pos[x]);\n                std::tie(ord[pos[x]], ord[pos[y]], pos[x], pos[y])\
    \ = std::make_tuple(ord[pos[y]], ord[pos[x]], pos[y], pos[x]);\n            }\n\
    \        }\n    }\n}\n"
  dependsOn:
  - Geometry/base.hpp
  isVerificationFile: false
  path: Geometry/rotating_sweepline.hpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/5_NCOJ/929.test.cpp
  - test/5_NCOJ/123.test.cpp
documentation_of: Geometry/rotating_sweepline.hpp
layout: document
redirect_from:
- /library/Geometry/rotating_sweepline.hpp
- /library/Geometry/rotating_sweepline.hpp.html
title: Geometry/rotating_sweepline.hpp
---
