---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Geometry/base.hpp
    title: Geometry/base.hpp
  _extendedRequiredBy:
  - icon: ':question:'
    path: Geometry/centers.hpp
    title: Geometry/centers.hpp
  - icon: ':question:'
    path: Geometry/circle.hpp
    title: Geometry/circle.hpp
  - icon: ':x:'
    path: Geometry/circle_cover.hpp
    title: Geometry/circle_cover.hpp
  - icon: ':question:'
    path: Geometry/convex.hpp
    title: Geometry/convex.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/furthest_pair.hpp
    title: Geometry/furthest_pair.hpp
  - icon: ':x:'
    path: Geometry/half_plane_intersection.hpp
    title: Geometry/half_plane_intersection.hpp
  - icon: ':question:'
    path: Geometry/minimum_enclosing_circle.hpp
    title: Geometry/minimum_enclosing_circle.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/outerTangentBetweenConvex.hpp
    title: Geometry/outerTangentBetweenConvex.hpp
  - icon: ':question:'
    path: Geometry/polygon.hpp
    title: Geometry/polygon.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/0_custom/outerTangentBetweenConvex.test.cpp
    title: test/0_custom/outerTangentBetweenConvex.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/geometry/furthest_pair.test.cpp
    title: test/1_library_checker/geometry/furthest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/geometry/static_convex_hull.test.cpp
    title: test/1_library_checker/geometry/static_convex_hull.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/area.test.cpp
    title: test/2_aoj/area.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/area_of_intersection_between_two_circles.test.cpp
    title: test/2_aoj/area_of_intersection_between_two_circles.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/circumscribed_circle_of_a_triangle.test.cpp
    title: test/2_aoj/circumscribed_circle_of_a_triangle.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/common_tangent.test.cpp
    title: test/2_aoj/common_tangent.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/convex_cut.test.cpp
    title: test/2_aoj/convex_cut.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/counter-clockwise.test.cpp
    title: test/2_aoj/counter-clockwise.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/cross_point.test.cpp
    title: test/2_aoj/cross_point.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/cross_points_of_a_circle_and_a_line.test.cpp
    title: test/2_aoj/cross_points_of_a_circle_and_a_line.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/cross_points_of_circles.test.cpp
    title: test/2_aoj/cross_points_of_circles.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/distance.test.cpp
    title: test/2_aoj/distance.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/incircle_of_a_triangle.test.cpp
    title: test/2_aoj/incircle_of_a_triangle.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/intersection.test.cpp
    title: test/2_aoj/intersection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/intersection_of_a_circle_and_a_polygon.test.cpp
    title: test/2_aoj/intersection_of_a_circle_and_a_polygon.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/minimum_enclosing_circle.test.cpp
    title: test/2_aoj/minimum_enclosing_circle.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/parallel-orthogonal.test.cpp
    title: test/2_aoj/parallel-orthogonal.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/polygon-point_containment.test.cpp
    title: test/2_aoj/polygon-point_containment.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/projection.test.cpp
    title: test/2_aoj/projection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/reflection.test.cpp
    title: test/2_aoj/reflection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/tangent_to_a_circle.test.cpp
    title: test/2_aoj/tangent_to_a_circle.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/type_of_circle.test.cpp
    title: test/2_aoj/type_of_circle.test.cpp
  - icon: ':x:'
    path: test/3_qoj/2162.test.cpp
    title: test/3_qoj/2162.test.cpp
  - icon: ':x:'
    path: test/3_qoj/6445.test.cpp
    title: test/3_qoj/6445.test.cpp
  - icon: ':x:'
    path: test/4_codeforces/101242J.test.cpp
    title: test/4_codeforces/101242J.test.cpp
  - icon: ':x:'
    path: test/4_codeforces/101673A.test.cpp
    title: test/4_codeforces/101673A.test.cpp
  - icon: ':x:'
    path: test/4_codeforces/104114B.test.cpp
    title: test/4_codeforces/104114B.test.cpp
  - icon: ':x:'
    path: test/6_TIOJ/1503.test.cpp
    title: test/6_TIOJ/1503.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Geometry/line.hpp\"\n\n#line 2 \"Geometry/base.hpp\"\n \
    \   \ntemplate <typename T>\nusing DefaultFloat = std::conditional_t<std::is_floating_point_v<T>,\
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
    \ }\n};\n#line 4 \"Geometry/line.hpp\"\n\ntemplate<typename T, T eps = get_default_eps<T>(),\
    \ typename MulT = T>\nstruct Ln : Geometry<T, eps> {\n    using value_type = T;\n\
    \    using Point = Pt<T, eps, MulT>;\n    std::array<Point, 2> l;\n    using Geometry<MulT,\
    \ eps>::sign;\n    using Geometry<MulT, eps>::cmp;\n    static constexpr T eps_val\
    \ = eps;\n    Ln() {}\n    Ln(const Point &a, const Point &b) : l{a, b} {}\n \
    \   friend istream& operator>>(istream &is, Ln &p) { return is >> p.l[0] >> p.l[1];\
    \ }\n    friend ostream& operator<<(ostream &os, const Ln &p) { return os << p.l[0]\
    \ << ' ' << p.l[1]; }\n    template <typename U, U _eps, typename _MulT>\n   \
    \ Ln(const Ln<U, _eps, _MulT>& other) : l{other.l[0], other.l[1]} {}\n    friend\
    \ int side(const Point &p, const Ln &l) { \n        return side(p, l[0], l[1]);\n\
    \    }\n    Point& operator[](int index) {\n        return l[index];\n    }\n\
    \    const Point& operator[](int index) const {\n        return l[index];\n  \
    \  }\n    friend Point direction(const Ln &l) {\n        return l[1] - l[0];\n\
    \    }\n    friend bool parallel(const Ln &l1, const Ln &l2) {\n        return\
    \ parallel(direction(l1), direction(l2));\n    }\n    friend bool sameDirection(const\
    \ Ln &l1, const Ln &l2) {\n        return sameDirection(direction(l1), direction(l2));\n\
    \    }\n    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T,\
    \ Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>\n    friend Pt<Ret,\
    \ _eps, _MulT> projection(const Point &p, const Ln &l) {\n        auto d = direction(l);\n\
    \        return Pt<Ret, _eps, _MulT>(l[0]) + Pt<Ret, _eps, _MulT>(d) * (Ret(dot(p\
    \ - l[0], d)) / Ret(square(d)));\n    }\n    template <typename Ret = DefaultFloat<T>,\
    \ Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT\
    \ = Ret>\n    friend Pt<Ret, _eps, _MulT> reflection(const Point &p, const Ln\
    \ &l) {\n        return projection<Ret, _eps, _MulT>(p, l) * Ret(2) - Pt<Ret,\
    \ _eps, _MulT>(p);\n    }\n    template <typename Ret = DefaultFloat<T>>\n   \
    \ friend Ret pointToLineDist(const Point &p, const Ln &l) {\n        if (l[0]\
    \ == l[1]) { return dist<Ret>(p, l[0]); }\n        return std::abs(cross(l[0]\
    \ - l[1], l[0] - p)) / length<Ret>(direction(l));\n    }\n    // better use integers\
    \ if you don't need exact coordinate\n    // l <= r is not explicitly required\n\
    \    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret>\
    \ ? eps : get_default_eps<Ret>(), typename _MulT = Ret>\n    friend Pt<Ret, _eps,\
    \ _MulT> lineIntersection(const Ln &l1, const Ln &l2) {\n        return Pt<Ret,\
    \ _eps, _MulT>(l1[0]) - Pt<Ret, _eps, _MulT>(direction(l1)) * (Ret(cross(direction(l2),\
    \ l1[0] - l2[0])) / Ret(cross(direction(l2), direction(l1))));\n    }\n    template\
    \ <typename U>\n    static bool between(U m, U l, U r) {\n        return cmp(l,\
    \ m) == 0 || cmp(m, r) == 0 || (l < m) != (r < m);\n    }\n    friend bool pointOnSeg(const\
    \ Point &p, const Ln &l) {\n        return side(p, l) == 0 && between(p.x, l[0].x,\
    \ l[1].x) && between(p.y, l[0].y, l[1].y);\n    }\n    friend bool pointStrictlyOnSeg(const\
    \ Point &p, const Ln &l) {\n        return side(p, l) == 0 && sign(dot(p - l[0],\
    \ direction(l))) * sign(dot(p - l[1], direction(l))) < 0;\n    }\n    template\
    \ <typename U>\n    static bool overlap(U l1, U r1, U l2, U r2) {\n        if\
    \ (l1 > r1) { std::swap(l1, r1); }\n        if (l2 > r2) { std::swap(l2, r2);\
    \ }\n        return cmp(r1, l2) != -1 && cmp(r2, l1) != -1;\n    }\n    friend\
    \ bool segIntersect(const Ln &l1, const Ln &l2) {\n        auto [p1, p2] = l1.l;\n\
    \        auto [q1, q2] = l2.l;\n        return overlap(p1.x, p2.x, q1.x, q2.x)\
    \ && overlap(p1.y, p2.y, q1.y, q2.y) &&\n                side(p1, l2) * side(p2,\
    \ l2) <= 0 &&\n                side(q1, l1) * side(q2, l1) <= 0;\n    }\n    //\
    \ parallel intersecting is false\n    friend bool segStrictlyIntersect(const Ln\
    \ &l1, const Ln &l2) {\n        auto [p1, p2] = l1.l;\n        auto [q1, q2] =\
    \ l2.l;\n        return side(p1, l2) * side(p2, l2) < 0 &&\n               side(q1,\
    \ l1) * side(q2, l1) < 0;\n    }\n    // parallel or intersect at source doesn't\
    \ count\n    friend bool rayIntersect(const Ln &l1, const Ln &l2) {\n        int\
    \ x = sign(cross(l1[1] - l1[0], l2[1] - l2[0]));\n        return x == 0 ? false\
    \ : side(l1[0], l2) == x && side(l2[0], l1) == -x;\n    } \n    template <typename\
    \ Ret = DefaultFloat<T>>\n    friend Ret pointToSegDist(const Point &p, const\
    \ Ln &l) {\n        auto d = direction(l);\n        if (sign(dot(p - l[0], d))\
    \ >= 0 && sign(dot(p - l[1], d)) <= 0)\n            return pointToLineDist<Ret>(p,\
    \ l);\n        return std::min(dist<Ret>(p, l[0]), dist<Ret>(p, l[1]));\n    }\n\
    \    template <typename Ret = DefaultFloat<T>>\n    friend Ret segDist(const Ln\
    \ &l1, const Ln &l2) {\n        if (segIntersect(l1, l2)) { return Ret(0); }\n\
    \        return std::min({pointToSegDist<Ret>(l1[0], l2), pointToSegDist<Ret>(l1[1],\
    \ l2),\n                pointToSegDist<Ret>(l2[0], l1), pointToSegDist<Ret>(l2[1],\
    \ l1)});\n    }\n};\n\ntemplate <typename PointType>\nstruct LineType;\n\ntemplate\
    \ <typename T, T eps, typename MulT>\nstruct LineType<Pt<T, eps, MulT>> {\n  \
    \  using type = Ln<T, eps, MulT>;\n};\n"
  code: "#pragma once\n\n#include \"Geometry/base.hpp\"\n\ntemplate<typename T, T\
    \ eps = get_default_eps<T>(), typename MulT = T>\nstruct Ln : Geometry<T, eps>\
    \ {\n    using value_type = T;\n    using Point = Pt<T, eps, MulT>;\n    std::array<Point,\
    \ 2> l;\n    using Geometry<MulT, eps>::sign;\n    using Geometry<MulT, eps>::cmp;\n\
    \    static constexpr T eps_val = eps;\n    Ln() {}\n    Ln(const Point &a, const\
    \ Point &b) : l{a, b} {}\n    friend istream& operator>>(istream &is, Ln &p) {\
    \ return is >> p.l[0] >> p.l[1]; }\n    friend ostream& operator<<(ostream &os,\
    \ const Ln &p) { return os << p.l[0] << ' ' << p.l[1]; }\n    template <typename\
    \ U, U _eps, typename _MulT>\n    Ln(const Ln<U, _eps, _MulT>& other) : l{other.l[0],\
    \ other.l[1]} {}\n    friend int side(const Point &p, const Ln &l) { \n      \
    \  return side(p, l[0], l[1]);\n    }\n    Point& operator[](int index) {\n  \
    \      return l[index];\n    }\n    const Point& operator[](int index) const {\n\
    \        return l[index];\n    }\n    friend Point direction(const Ln &l) {\n\
    \        return l[1] - l[0];\n    }\n    friend bool parallel(const Ln &l1, const\
    \ Ln &l2) {\n        return parallel(direction(l1), direction(l2));\n    }\n \
    \   friend bool sameDirection(const Ln &l1, const Ln &l2) {\n        return sameDirection(direction(l1),\
    \ direction(l2));\n    }\n    template <typename Ret = DefaultFloat<T>, Ret _eps\
    \ = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>\n\
    \    friend Pt<Ret, _eps, _MulT> projection(const Point &p, const Ln &l) {\n \
    \       auto d = direction(l);\n        return Pt<Ret, _eps, _MulT>(l[0]) + Pt<Ret,\
    \ _eps, _MulT>(d) * (Ret(dot(p - l[0], d)) / Ret(square(d)));\n    }\n    template\
    \ <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(),\
    \ typename _MulT = Ret>\n    friend Pt<Ret, _eps, _MulT> reflection(const Point\
    \ &p, const Ln &l) {\n        return projection<Ret, _eps, _MulT>(p, l) * Ret(2)\
    \ - Pt<Ret, _eps, _MulT>(p);\n    }\n    template <typename Ret = DefaultFloat<T>>\n\
    \    friend Ret pointToLineDist(const Point &p, const Ln &l) {\n        if (l[0]\
    \ == l[1]) { return dist<Ret>(p, l[0]); }\n        return std::abs(cross(l[0]\
    \ - l[1], l[0] - p)) / length<Ret>(direction(l));\n    }\n    // better use integers\
    \ if you don't need exact coordinate\n    // l <= r is not explicitly required\n\
    \    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret>\
    \ ? eps : get_default_eps<Ret>(), typename _MulT = Ret>\n    friend Pt<Ret, _eps,\
    \ _MulT> lineIntersection(const Ln &l1, const Ln &l2) {\n        return Pt<Ret,\
    \ _eps, _MulT>(l1[0]) - Pt<Ret, _eps, _MulT>(direction(l1)) * (Ret(cross(direction(l2),\
    \ l1[0] - l2[0])) / Ret(cross(direction(l2), direction(l1))));\n    }\n    template\
    \ <typename U>\n    static bool between(U m, U l, U r) {\n        return cmp(l,\
    \ m) == 0 || cmp(m, r) == 0 || (l < m) != (r < m);\n    }\n    friend bool pointOnSeg(const\
    \ Point &p, const Ln &l) {\n        return side(p, l) == 0 && between(p.x, l[0].x,\
    \ l[1].x) && between(p.y, l[0].y, l[1].y);\n    }\n    friend bool pointStrictlyOnSeg(const\
    \ Point &p, const Ln &l) {\n        return side(p, l) == 0 && sign(dot(p - l[0],\
    \ direction(l))) * sign(dot(p - l[1], direction(l))) < 0;\n    }\n    template\
    \ <typename U>\n    static bool overlap(U l1, U r1, U l2, U r2) {\n        if\
    \ (l1 > r1) { std::swap(l1, r1); }\n        if (l2 > r2) { std::swap(l2, r2);\
    \ }\n        return cmp(r1, l2) != -1 && cmp(r2, l1) != -1;\n    }\n    friend\
    \ bool segIntersect(const Ln &l1, const Ln &l2) {\n        auto [p1, p2] = l1.l;\n\
    \        auto [q1, q2] = l2.l;\n        return overlap(p1.x, p2.x, q1.x, q2.x)\
    \ && overlap(p1.y, p2.y, q1.y, q2.y) &&\n                side(p1, l2) * side(p2,\
    \ l2) <= 0 &&\n                side(q1, l1) * side(q2, l1) <= 0;\n    }\n    //\
    \ parallel intersecting is false\n    friend bool segStrictlyIntersect(const Ln\
    \ &l1, const Ln &l2) {\n        auto [p1, p2] = l1.l;\n        auto [q1, q2] =\
    \ l2.l;\n        return side(p1, l2) * side(p2, l2) < 0 &&\n               side(q1,\
    \ l1) * side(q2, l1) < 0;\n    }\n    // parallel or intersect at source doesn't\
    \ count\n    friend bool rayIntersect(const Ln &l1, const Ln &l2) {\n        int\
    \ x = sign(cross(l1[1] - l1[0], l2[1] - l2[0]));\n        return x == 0 ? false\
    \ : side(l1[0], l2) == x && side(l2[0], l1) == -x;\n    } \n    template <typename\
    \ Ret = DefaultFloat<T>>\n    friend Ret pointToSegDist(const Point &p, const\
    \ Ln &l) {\n        auto d = direction(l);\n        if (sign(dot(p - l[0], d))\
    \ >= 0 && sign(dot(p - l[1], d)) <= 0)\n            return pointToLineDist<Ret>(p,\
    \ l);\n        return std::min(dist<Ret>(p, l[0]), dist<Ret>(p, l[1]));\n    }\n\
    \    template <typename Ret = DefaultFloat<T>>\n    friend Ret segDist(const Ln\
    \ &l1, const Ln &l2) {\n        if (segIntersect(l1, l2)) { return Ret(0); }\n\
    \        return std::min({pointToSegDist<Ret>(l1[0], l2), pointToSegDist<Ret>(l1[1],\
    \ l2),\n                pointToSegDist<Ret>(l2[0], l1), pointToSegDist<Ret>(l2[1],\
    \ l1)});\n    }\n};\n\ntemplate <typename PointType>\nstruct LineType;\n\ntemplate\
    \ <typename T, T eps, typename MulT>\nstruct LineType<Pt<T, eps, MulT>> {\n  \
    \  using type = Ln<T, eps, MulT>;\n};\n"
  dependsOn:
  - Geometry/base.hpp
  isVerificationFile: false
  path: Geometry/line.hpp
  requiredBy:
  - Geometry/half_plane_intersection.hpp
  - Geometry/outerTangentBetweenConvex.hpp
  - Geometry/circle.hpp
  - Geometry/polygon.hpp
  - Geometry/convex.hpp
  - Geometry/minimum_enclosing_circle.hpp
  - Geometry/centers.hpp
  - Geometry/furthest_pair.hpp
  - Geometry/circle_cover.hpp
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/0_custom/outerTangentBetweenConvex.test.cpp
  - test/4_codeforces/101242J.test.cpp
  - test/4_codeforces/104114B.test.cpp
  - test/4_codeforces/101673A.test.cpp
  - test/3_qoj/2162.test.cpp
  - test/3_qoj/6445.test.cpp
  - test/2_aoj/area.test.cpp
  - test/2_aoj/type_of_circle.test.cpp
  - test/2_aoj/cross_points_of_circles.test.cpp
  - test/2_aoj/counter-clockwise.test.cpp
  - test/2_aoj/incircle_of_a_triangle.test.cpp
  - test/2_aoj/tangent_to_a_circle.test.cpp
  - test/2_aoj/circumscribed_circle_of_a_triangle.test.cpp
  - test/2_aoj/intersection.test.cpp
  - test/2_aoj/projection.test.cpp
  - test/2_aoj/intersection_of_a_circle_and_a_polygon.test.cpp
  - test/2_aoj/cross_points_of_a_circle_and_a_line.test.cpp
  - test/2_aoj/polygon-point_containment.test.cpp
  - test/2_aoj/common_tangent.test.cpp
  - test/2_aoj/minimum_enclosing_circle.test.cpp
  - test/2_aoj/reflection.test.cpp
  - test/2_aoj/cross_point.test.cpp
  - test/2_aoj/parallel-orthogonal.test.cpp
  - test/2_aoj/convex_cut.test.cpp
  - test/2_aoj/area_of_intersection_between_two_circles.test.cpp
  - test/2_aoj/distance.test.cpp
  - test/1_library_checker/geometry/static_convex_hull.test.cpp
  - test/1_library_checker/geometry/furthest_pair.test.cpp
  - test/6_TIOJ/1503.test.cpp
documentation_of: Geometry/line.hpp
layout: document
redirect_from:
- /library/Geometry/line.hpp
- /library/Geometry/line.hpp.html
title: Geometry/line.hpp
---
