---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Geometry/base.hpp
    title: Geometry/base.hpp
  - icon: ':question:'
    path: Geometry/line.hpp
    title: Geometry/line.hpp
  - icon: ':question:'
    path: Geometry/polygon.hpp
    title: Geometry/polygon.hpp
  - icon: ':question:'
    path: Misc/cyc_bitonic_search.hpp
    title: Misc/cyc_bitonic_search.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Geometry/furthest_pair.hpp
    title: Geometry/furthest_pair.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/outerTangentBetweenConvex.hpp
    title: Geometry/outerTangentBetweenConvex.hpp
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
    path: test/2_aoj/convex_cut.test.cpp
    title: test/2_aoj/convex_cut.test.cpp
  - icon: ':x:'
    path: test/3_qoj/2162.test.cpp
    title: test/3_qoj/2162.test.cpp
  - icon: ':x:'
    path: test/4_codeforces/101242J.test.cpp
    title: test/4_codeforces/101242J.test.cpp
  - icon: ':x:'
    path: test/4_codeforces/104114B.test.cpp
    title: test/4_codeforces/104114B.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Geometry/convex.hpp\"\n\n#line 2 \"Geometry/base.hpp\"\n\
    \    \ntemplate <typename T>\nusing DefaultFloat = std::conditional_t<std::is_floating_point_v<T>,\
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
    \ }\n};\n#line 2 \"Geometry/line.hpp\"\n\n#line 4 \"Geometry/line.hpp\"\n\ntemplate<typename\
    \ T, T eps = get_default_eps<T>(), typename MulT = T>\nstruct Ln : Geometry<T,\
    \ eps> {\n    using value_type = T;\n    using Point = Pt<T, eps, MulT>;\n   \
    \ std::array<Point, 2> l;\n    using Geometry<MulT, eps>::sign;\n    using Geometry<MulT,\
    \ eps>::cmp;\n    static constexpr T eps_val = eps;\n    Ln() {}\n    Ln(const\
    \ Point &a, const Point &b) : l{a, b} {}\n    friend istream& operator>>(istream\
    \ &is, Ln &p) { return is >> p.l[0] >> p.l[1]; }\n    friend ostream& operator<<(ostream\
    \ &os, const Ln &p) { return os << p.l[0] << ' ' << p.l[1]; }\n    template <typename\
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
    \  using type = Ln<T, eps, MulT>;\n};\n#line 2 \"Geometry/polygon.hpp\"\n\n#line\
    \ 5 \"Geometry/polygon.hpp\"\n\ntemplate<typename T, T eps = get_default_eps<T>(),\
    \ typename MulT = T>\nclass Polygon : public std::vector<Pt<T, eps, MulT>>, public\
    \ Geometry<MulT, eps> {\npublic:\n    using Point = Pt<T, eps, MulT>;\n    using\
    \ Line = Ln<T, eps, MulT>;\n    using std::vector<Pt<T, eps, MulT>>::vector;\n\
    \    using Geometry<MulT, eps>::sign;\n    using Geometry<MulT, eps>::cmp;\n \
    \   Polygon(const std::vector<Point> &vec) : Polygon(vec.begin(), vec.end()) {}\
    \ \n    template <typename U, U _eps, typename _MulT>\n    Polygon(const Polygon<U,\
    \ _eps, _MulT>& other) : Polygon(other.begin(), other.end()) {}\n    Point& at(int\
    \ index) {\n        index %= this->size();\n        if (index < 0) index += this->size();\n\
    \        return (*this)[index];\n    }\n    const Point& at(int index) const {\n\
    \        index %= this->size();\n        if (index < 0) index += this->size();\n\
    \        return (*this)[index];\n    }\n    Line edge(int index) const {\n   \
    \     return Ln(at(index), at(index + 1));\n    }\n    // return twice of the\
    \ true direct area\n    MulT area() {\n        MulT res = 0;\n        int n =\
    \ this->size();\n        for (int i = 0; i < n; ++i)\n            res += cross((*this)[i],\
    \ (*this)[(i + 1) % n]);\n        return res;\n    }\n    int polygon_dir() {\n\
    \        return sign(area());\n    }\n    friend bool pointInPoly(const Point\
    \ &p, const Polygon &a, bool strict = false) {\n        int n = a.size(), res\
    \ = 0;\n        for (int i = 0; i < n; i++) {\n            Point u = a[i], v =\
    \ a[(i + 1) % n];\n            if (pointOnSeg(p, Ln(u, v))) { return !strict;\
    \ }\n            if (cmp(u.y, v.y) <= 0) { std::swap(u, v); }\n            if\
    \ (cmp(p.y, u.y) > 0 || cmp(p.y, v.y) <= 0) { continue; }\n            res ^=\
    \ sign(cross(p, u, v)) > 0;\n        }\n        return res;\n    }\n    friend\
    \ bool pointStrictlyInPoly(const Point &p, const Polygon &a) {\n        return\
    \ pointInPoly(p, a, true);\n    }\n    template <typename Ret = DefaultFloat<T>>\n\
    \    friend Ret polyUnionArea(const std::vector<Polygon> &poly) {\n        auto\
    \ rat = [&](const Point &a, const Point &b) {\n            return sign(b.x) ?\
    \ Ret(a.x) / Ret(b.x) : Ret(a.y) / Ret(b.y);\n        };\n        Ret res = 0;\n\
    \        for (auto &p : poly)\n            for (int a = 0; a < int(p.size());\
    \ ++a) {\n                Point A = p[a], B = p[(a + 1) % int(p.size())];\n  \
    \              std::vector<std::pair<Ret, int>> segs;\n                segs.emplace_back(Ret(0),\
    \ 0);\n                segs.emplace_back(Ret(1), 0);\n                for (auto\
    \ &q : poly) {\n                    if (&p == &q) continue;\n                \
    \    for (int b = 0; b < int(q.size()); ++b) {\n                        Point\
    \ C = q[b], D = q[(b + 1) % int(q.size())];\n                        int sc =\
    \ side(A, B, C), sd = side(A, B, D);\n                        if (sc != sd &&\
    \ std::min(sc, sd) < 0) {\n                            Ret sa = cross(D - C, A\
    \ - C), sb = cross(D - C, B - C);\n                            segs.emplace_back(sa\
    \ / (sa - sb), Geometry<int>::sign(sc - sd));\n                        }\n   \
    \                     if (!sc && !sd && &q < &p && sign(dot(B - A, D - C)) > 0)\
    \ {\n                            segs.emplace_back(rat(C - A, B - A), 1);\n  \
    \                          segs.emplace_back(rat(D - A, B - A), -1);\n       \
    \                 }\n                    }\n                }\n              \
    \  std::ranges::sort(segs);\n                for (auto &s : segs) s.first = std::clamp(s.first,\
    \ Ret(0), Ret(1));\n                Ret sum = 0;\n                int cnt = segs[0].second;\n\
    \                for (int j = 1; j < int(segs.size()); ++j) {\n              \
    \      if (!cnt) sum += segs[j].first - segs[j - 1].first;\n                 \
    \   cnt += segs[j].second;\n                }\n                res += Ret(cross(A,\
    \ B)) * sum;\n            }\n        return res / 2;\n    }\n};\n\ntemplate <typename\
    \ PointType>\nstruct PolygonType;\n\ntemplate <typename T, T eps, typename MulT>\n\
    struct PolygonType<Pt<T, eps, MulT>> {\n    using type = Polygon<T, eps, MulT>;\n\
    };\n#line 2 \"Misc/cyc_bitonic_search.hpp\"\n\n/* \n   bool pred(int a, int b);\n\
    \   a is better than b\n   f(0) ~ f(n - 1) is a cyclic-shift bitonic-function\n\
    \   return idx s.t. pred(x, idx) is false forall x\n*/\nint cyc_bitonic_search(int\
    \ n, auto pred) {\n    if (n == 1) return 0;\n    int l = 0, r = n; bool rv =\
    \ pred(1, 0);\n    while (r - l > 1) {\n        int m = (l + r) / 2;\n       \
    \ if (pred(0, m) ? rv: pred(m, (m + 1) % n)) r = m;\n        else l = m;\n   \
    \ }\n    return pred(l, r % n) ? l : r % n;\n}\n\n/* \n   bool pred(int o, int\
    \ a, int b);\n   a is better than b\n   f(o, 0) ~ f(o, n - 1) is a cyclic-shift\
    \ bitonic-function\n   return idx[o] s.t. pred(o, x, idx[o]) is false forall x\n\
    \   idx should be non-decreasing, and idx[o] != o\n*/\nstd::vector<int> rotating_calipers(int\
    \ n, auto pred) {\n    assert(n >= 2);\n    std::vector<int> res(n, 1);\n    for\
    \ (int i = 2; i < n; ++i)\n        if (pred(0, i, res[0]))\n            res[0]\
    \ = i;\n    for (int i = 1; i < n; ++i) {\n        res[i] = res[i - 1];\n    \
    \    while ((res[i] + 1) % n != i && pred(i, (res[i] + 1) % n, res[i] % n))\n\
    \            ++res[i];\n        res[i] %= n;\n    }\n    return res;\n}\n#line\
    \ 7 \"Geometry/convex.hpp\"\n\ntemplate <typename Point>\nPolygonType<Point>::type\
    \ convexHull(std::vector<Point> dots, bool sort_and_unique = true) {\n    if (sort_and_unique)\
    \ {\n        std::ranges::sort(dots);\n        dots.erase(ranges::unique(dots).begin(),\
    \ dots.end());\n    }\n    int n = dots.size();\n    if (n <= 1) { return dots;\
    \ }\n    std::vector<Point> res(2 * n);\n    int j = 0;\n    for (int i = 0; i\
    \ < n; res[j++] = dots[i++]) {\n        while (j >= 2 && side(res[j - 2], res[j\
    \ - 1], dots[i]) <= 0) { j--; }\n    }\n    for (int i = n - 2, k = j; i >= 0;\
    \ res[j++] = dots[i--]) {\n        while (j > k && side(res[j - 2], res[j - 1],\
    \ dots[i]) <= 0) { j--; }\n    }\n    res.resize(j - 1);\n    return res;\n}\n\
    \ntemplate <typename Point>\nstd::pair<typename PolygonType<Point>::type, typename\
    \ PolygonType<Point>::type> convexHullParts(std::vector<Point> dots, bool sort_and_unique\
    \ = true) {\n    if (sort_and_unique) {\n        std::ranges::sort(dots);\n  \
    \      dots.erase(ranges::unique(dots).begin(), dots.end());\n    }\n    int n\
    \ = dots.size();\n    if (n <= 1) { return std::make_pair(dots, dots); }\n   \
    \ std::vector<Point> res(2 * n);\n    int j = 0;\n    for (int i = 0; i < n; res[j++]\
    \ = dots[i++]) {\n        while (j >= 2 && side(res[j - 2], res[j - 1], dots[i])\
    \ <= 0) { j--; }\n    }\n    int k = j;\n    for (int i = n - 2; i >= 0; res[j++]\
    \ = dots[i--]) {\n        while (j > k && side(res[j - 2], res[j - 1], dots[i])\
    \ <= 0) { j--; }\n    }\n    std::vector<Point> lower(res.begin(), res.begin()\
    \ + k);\n    std::vector<Point> upper(res.begin() + k - 1, res.begin() + j);\n\
    \    std::ranges::reverse(upper);\n    return std::make_pair(lower, upper);\n\
    }\n\n// warning : if all point on same line will return {1, 2, 3, 2}\ntemplate\
    \ <typename Point>\nPolygonType<Point>::type convexHullNonstrict(std::vector<Point>\
    \ dots, bool sort_and_unique = true) {\n    if (sort_and_unique) {\n        std::ranges::sort(dots);\n\
    \        dots.erase(ranges::unique(dots).begin(), dots.end());\n    }\n    int\
    \ n = dots.size();\n    if (n <= 1) { return dots; }\n    std::vector<Point> res(2\
    \ * n);\n    int j = 0;\n    for (int i = 0; i < n; res[j++] = dots[i++]) {\n\
    \        while (j >= 2 && side(res[j - 2], res[j - 1], dots[i]) < 0) { j--; }\n\
    \    }\n    for (int i = n - 2, k = j; i >= 0; res[j++] = dots[i--]) {\n     \
    \   while (j > k && side(res[j - 2], res[j - 1], dots[i]) < 0) { j--; }\n    }\n\
    \    res.resize(j - 1);\n    return res;\n}\n\n// a and b are nonempty, need reorder\n\
    template <typename polygon>\npolygon convexMinkowski(polygon a, polygon b) {\n\
    \    a = convexHull(a), b = convexHull(b);\n    int n = a.size(), m = b.size();\n\
    \    if (n != 1) { std::swap(n, m), std::swap(a, b); }\n    if (n == 1) {\n  \
    \      for (auto &p : b) { p = p + a[0]; }\n        return b;\n    }\n    a.push_back(a[0]),\
    \ a.push_back(a[1]);\n    b.push_back(b[0]), b.push_back(b[1]);\n    polygon c;\n\
    \    for (int i = 0, j = 0; i < n || j < m; ) {\n        c.push_back(a[i] + b[j]);\n\
    \        int s = sign(cross(a[i + 1] - a[i], b[j + 1] - b[j]));\n        if (i\
    \ < n && s >= 0) { i++; }\n        if (j < m && s <= 0) { j++; }\n    }\n    return\
    \ c;\n}\n\n// 1: in, 0: on, -1: out\ntemplate <typename Point>\nint pointInConvex(const\
    \ Point &p, const typename PolygonType<Point>::type &a) {\n    int n = a.size();\n\
    \    if (n < 3) { return pointOnSeg(p, Ln(a[0], a.back())) ? 0 : -1; }\n    if\
    \ (side(p, a[1], a[0]) >= 0) {\n        return pointOnSeg(p, Ln(a[1], a[0])) ?\
    \ 0 : -1;\n    }\n    if (side(p, a[0], a.back()) >= 0) {\n        return pointOnSeg(p,\
    \ Ln(a[0], a.back())) ? 0 : -1;\n    }\n    int l = 1, r = n - 2;\n    while (l\
    \ < r) {\n        int m = (l + r + 1) >> 1;\n        if (side(p, a[0], a[m]) >=\
    \ 0) l = m;\n        else r = m - 1;\n    }\n    return side(p, a[l], a[l + 1]);\n\
    }\n\n/* The point should be strictly out of hull\n   return arbitrary point on\
    \ the tangent line */\ntemplate <typename Point>\nstd::pair<int, int> tangentLineToConvex(const\
    \ Point &p, const typename PolygonType<Point>::type &a) {\n    auto gao = [&](int\
    \ s) {\n        return cyc_bitonic_search(a.size(), \n        [&](int x, int y)\
    \ { return side(p, a[x], a[y]) == s; });\n    };\n    return std::make_pair(gao(1),\
    \ gao(-1));\n}\n\ntemplate <typename Point>\nint tangentDirection(const Point\
    \ &dir, const typename PolygonType<Point>::type &C) {\n  return cyc_bitonic_search(SZ(C),\
    \ [&](int a, int b) {\n    return Point::cmp(cross(dir, C[a]), cross(dir, C[b]))\
    \ > 0;\n  });\n}\n\ntemplate<typename T, T eps = get_default_eps<T>(), typename\
    \ MulT = T>\nstd::pair<int, int> lineIntersectConvex(const Ln<T, eps, MulT> &ln,\
    \ const Polygon<T, eps, MulT> &C) {\n    auto cmpL = [&](int i) {\n        return\
    \ Ln<T, eps, MulT>::sign(cross(C[i] - ln[0], direction(ln)));\n    };\n    int\
    \ A = tangentDirection(-direction(ln), C);\n    int B = tangentDirection(direction(ln),\
    \ C);\n    int n = SZ(C);\n    if (cmpL(A) < 0 || cmpL(B) > 0)\n        return\
    \ std::make_pair(-1, -1); // no collision\n    auto gao = [&](int l, int r) {\n\
    \        for (int t = l; (l + 1) % n != r; ) {\n            int m = ((l + r +\
    \ (l < r ? 0 : n)) / 2) % n;\n            (cmpL(m) == cmpL(t) ? l : r) = m;\n\
    \        }\n        return (l + !cmpL(r)) % n;\n    };\n    std::pair<int, int>\
    \ res = std::make_pair(gao(B, A), gao(A, B)); // (i, j)\n    if (res.first ==\
    \ res.second) // touching the corner i\n        return std::make_pair(res.first,\
    \ -1);\n    if (!cmpL(res.first) && !cmpL(res.second)) // along side i, i+1\n\
    \        switch ((res.first - res.second + n + 1) % n) {\n            case 0:\
    \ return std::make_pair(res.first, res.first);\n            case 2: return std::make_pair(res.second,\
    \ res.second);\n        }\n    /* crossing sides (i, i+1) and (j, j+1)\n     \
    \  crossing corner i is treated as side (i, i+1)\n       returned in the same\
    \ order as the line hits the convex */\n    return res;\n} // convex cut: (r,\
    \ l]\n"
  code: "#pragma once\n\n#include \"Geometry/base.hpp\"\n#include \"Geometry/line.hpp\"\
    \n#include \"Geometry/polygon.hpp\"\n#include \"Misc/cyc_bitonic_search.hpp\"\n\
    \ntemplate <typename Point>\nPolygonType<Point>::type convexHull(std::vector<Point>\
    \ dots, bool sort_and_unique = true) {\n    if (sort_and_unique) {\n        std::ranges::sort(dots);\n\
    \        dots.erase(ranges::unique(dots).begin(), dots.end());\n    }\n    int\
    \ n = dots.size();\n    if (n <= 1) { return dots; }\n    std::vector<Point> res(2\
    \ * n);\n    int j = 0;\n    for (int i = 0; i < n; res[j++] = dots[i++]) {\n\
    \        while (j >= 2 && side(res[j - 2], res[j - 1], dots[i]) <= 0) { j--; }\n\
    \    }\n    for (int i = n - 2, k = j; i >= 0; res[j++] = dots[i--]) {\n     \
    \   while (j > k && side(res[j - 2], res[j - 1], dots[i]) <= 0) { j--; }\n   \
    \ }\n    res.resize(j - 1);\n    return res;\n}\n\ntemplate <typename Point>\n\
    std::pair<typename PolygonType<Point>::type, typename PolygonType<Point>::type>\
    \ convexHullParts(std::vector<Point> dots, bool sort_and_unique = true) {\n  \
    \  if (sort_and_unique) {\n        std::ranges::sort(dots);\n        dots.erase(ranges::unique(dots).begin(),\
    \ dots.end());\n    }\n    int n = dots.size();\n    if (n <= 1) { return std::make_pair(dots,\
    \ dots); }\n    std::vector<Point> res(2 * n);\n    int j = 0;\n    for (int i\
    \ = 0; i < n; res[j++] = dots[i++]) {\n        while (j >= 2 && side(res[j - 2],\
    \ res[j - 1], dots[i]) <= 0) { j--; }\n    }\n    int k = j;\n    for (int i =\
    \ n - 2; i >= 0; res[j++] = dots[i--]) {\n        while (j > k && side(res[j -\
    \ 2], res[j - 1], dots[i]) <= 0) { j--; }\n    }\n    std::vector<Point> lower(res.begin(),\
    \ res.begin() + k);\n    std::vector<Point> upper(res.begin() + k - 1, res.begin()\
    \ + j);\n    std::ranges::reverse(upper);\n    return std::make_pair(lower, upper);\n\
    }\n\n// warning : if all point on same line will return {1, 2, 3, 2}\ntemplate\
    \ <typename Point>\nPolygonType<Point>::type convexHullNonstrict(std::vector<Point>\
    \ dots, bool sort_and_unique = true) {\n    if (sort_and_unique) {\n        std::ranges::sort(dots);\n\
    \        dots.erase(ranges::unique(dots).begin(), dots.end());\n    }\n    int\
    \ n = dots.size();\n    if (n <= 1) { return dots; }\n    std::vector<Point> res(2\
    \ * n);\n    int j = 0;\n    for (int i = 0; i < n; res[j++] = dots[i++]) {\n\
    \        while (j >= 2 && side(res[j - 2], res[j - 1], dots[i]) < 0) { j--; }\n\
    \    }\n    for (int i = n - 2, k = j; i >= 0; res[j++] = dots[i--]) {\n     \
    \   while (j > k && side(res[j - 2], res[j - 1], dots[i]) < 0) { j--; }\n    }\n\
    \    res.resize(j - 1);\n    return res;\n}\n\n// a and b are nonempty, need reorder\n\
    template <typename polygon>\npolygon convexMinkowski(polygon a, polygon b) {\n\
    \    a = convexHull(a), b = convexHull(b);\n    int n = a.size(), m = b.size();\n\
    \    if (n != 1) { std::swap(n, m), std::swap(a, b); }\n    if (n == 1) {\n  \
    \      for (auto &p : b) { p = p + a[0]; }\n        return b;\n    }\n    a.push_back(a[0]),\
    \ a.push_back(a[1]);\n    b.push_back(b[0]), b.push_back(b[1]);\n    polygon c;\n\
    \    for (int i = 0, j = 0; i < n || j < m; ) {\n        c.push_back(a[i] + b[j]);\n\
    \        int s = sign(cross(a[i + 1] - a[i], b[j + 1] - b[j]));\n        if (i\
    \ < n && s >= 0) { i++; }\n        if (j < m && s <= 0) { j++; }\n    }\n    return\
    \ c;\n}\n\n// 1: in, 0: on, -1: out\ntemplate <typename Point>\nint pointInConvex(const\
    \ Point &p, const typename PolygonType<Point>::type &a) {\n    int n = a.size();\n\
    \    if (n < 3) { return pointOnSeg(p, Ln(a[0], a.back())) ? 0 : -1; }\n    if\
    \ (side(p, a[1], a[0]) >= 0) {\n        return pointOnSeg(p, Ln(a[1], a[0])) ?\
    \ 0 : -1;\n    }\n    if (side(p, a[0], a.back()) >= 0) {\n        return pointOnSeg(p,\
    \ Ln(a[0], a.back())) ? 0 : -1;\n    }\n    int l = 1, r = n - 2;\n    while (l\
    \ < r) {\n        int m = (l + r + 1) >> 1;\n        if (side(p, a[0], a[m]) >=\
    \ 0) l = m;\n        else r = m - 1;\n    }\n    return side(p, a[l], a[l + 1]);\n\
    }\n\n/* The point should be strictly out of hull\n   return arbitrary point on\
    \ the tangent line */\ntemplate <typename Point>\nstd::pair<int, int> tangentLineToConvex(const\
    \ Point &p, const typename PolygonType<Point>::type &a) {\n    auto gao = [&](int\
    \ s) {\n        return cyc_bitonic_search(a.size(), \n        [&](int x, int y)\
    \ { return side(p, a[x], a[y]) == s; });\n    };\n    return std::make_pair(gao(1),\
    \ gao(-1));\n}\n\ntemplate <typename Point>\nint tangentDirection(const Point\
    \ &dir, const typename PolygonType<Point>::type &C) {\n  return cyc_bitonic_search(SZ(C),\
    \ [&](int a, int b) {\n    return Point::cmp(cross(dir, C[a]), cross(dir, C[b]))\
    \ > 0;\n  });\n}\n\ntemplate<typename T, T eps = get_default_eps<T>(), typename\
    \ MulT = T>\nstd::pair<int, int> lineIntersectConvex(const Ln<T, eps, MulT> &ln,\
    \ const Polygon<T, eps, MulT> &C) {\n    auto cmpL = [&](int i) {\n        return\
    \ Ln<T, eps, MulT>::sign(cross(C[i] - ln[0], direction(ln)));\n    };\n    int\
    \ A = tangentDirection(-direction(ln), C);\n    int B = tangentDirection(direction(ln),\
    \ C);\n    int n = SZ(C);\n    if (cmpL(A) < 0 || cmpL(B) > 0)\n        return\
    \ std::make_pair(-1, -1); // no collision\n    auto gao = [&](int l, int r) {\n\
    \        for (int t = l; (l + 1) % n != r; ) {\n            int m = ((l + r +\
    \ (l < r ? 0 : n)) / 2) % n;\n            (cmpL(m) == cmpL(t) ? l : r) = m;\n\
    \        }\n        return (l + !cmpL(r)) % n;\n    };\n    std::pair<int, int>\
    \ res = std::make_pair(gao(B, A), gao(A, B)); // (i, j)\n    if (res.first ==\
    \ res.second) // touching the corner i\n        return std::make_pair(res.first,\
    \ -1);\n    if (!cmpL(res.first) && !cmpL(res.second)) // along side i, i+1\n\
    \        switch ((res.first - res.second + n + 1) % n) {\n            case 0:\
    \ return std::make_pair(res.first, res.first);\n            case 2: return std::make_pair(res.second,\
    \ res.second);\n        }\n    /* crossing sides (i, i+1) and (j, j+1)\n     \
    \  crossing corner i is treated as side (i, i+1)\n       returned in the same\
    \ order as the line hits the convex */\n    return res;\n} // convex cut: (r,\
    \ l]\n"
  dependsOn:
  - Geometry/base.hpp
  - Geometry/line.hpp
  - Geometry/polygon.hpp
  - Misc/cyc_bitonic_search.hpp
  isVerificationFile: false
  path: Geometry/convex.hpp
  requiredBy:
  - Geometry/furthest_pair.hpp
  - Geometry/outerTangentBetweenConvex.hpp
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/3_qoj/2162.test.cpp
  - test/4_codeforces/104114B.test.cpp
  - test/4_codeforces/101242J.test.cpp
  - test/0_custom/outerTangentBetweenConvex.test.cpp
  - test/1_library_checker/geometry/static_convex_hull.test.cpp
  - test/1_library_checker/geometry/furthest_pair.test.cpp
  - test/2_aoj/convex_cut.test.cpp
documentation_of: Geometry/convex.hpp
layout: document
redirect_from:
- /library/Geometry/convex.hpp
- /library/Geometry/convex.hpp.html
title: Geometry/convex.hpp
---
