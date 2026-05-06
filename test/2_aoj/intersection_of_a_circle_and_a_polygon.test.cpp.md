---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Geometry/base.hpp
    title: Geometry/base.hpp
  - icon: ':question:'
    path: Geometry/circle.hpp
    title: Geometry/circle.hpp
  - icon: ':question:'
    path: Geometry/line.hpp
    title: Geometry/line.hpp
  - icon: ':question:'
    path: Geometry/polygon.hpp
    title: Geometry/polygon.hpp
  - icon: ':question:'
    path: default_code.hpp
    title: default_code.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    ERROR: '0.00001'
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H
  bundledCode: "#line 1 \"test/2_aoj/intersection_of_a_circle_and_a_polygon.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H\"\
    \n#define ERROR 0.00001\n#line 2 \"default_code.hpp\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\ntypedef long long ll;\ntypedef pair<int, int> pii;\ntypedef\
    \ pair<ll, ll> pll;\n#define X first\n#define Y second\n#define SZ(a) ((int)a.size())\n\
    #define ALL(v) v.begin(), v.end()\ntemplate<class A, class B>\nostream& operator<<(ostream&\
    \ os, const pair<A, B> &a) {\n    os << \"(\" << a.first << \", \" << a.second\
    \ << \")\";\n    return os;\n}\ntemplate <typename T>\nconcept PrintableContainer\
    \ = requires(T& a) {\n    a.begin();\n    a.end();\n} && !std::same_as<std::remove_cvref_t<T>,\
    \ std::string> &&\n     !std::same_as<std::remove_cvref_t<T>, std::string_view>\
    \ &&\n     !std::is_convertible_v<T, const char*>;\ntemplate <PrintableContainer\
    \ T>\nstd::ostream& operator<<(std::ostream& os, const T& a) {\n    os << \"[\
    \ \";\n    bool first = true;\n    for (const auto& item : a) {\n        if (!first)\
    \ os << \", \";\n        os << item;\n        first = false;\n    }\n    return\
    \ os << \" ]\";\n}\n#ifdef bbq\n#include <experimental/iterator>\n#define safe\
    \ cerr<<__PRETTY_FUNCTION__<<\" line \"<<__LINE__<<\" safe\\n\"\n#define sepline\
    \ sepline_() \n#define debug(a...) debug_(#a, a)\n#define orange(a...) orange_(#a,\
    \ a)\nvoid debug_(auto s, auto ...a) {\n    cerr << \"\\e[1;32m(\" << s << \"\
    ) = (\";\n    int f = 0;\n    (..., (cerr << (f++ ? \", \" : \"\") << a));\n \
    \   cerr << \")\\e[0m\\n\";\n}\nvoid orange_(auto s, auto L, auto R) {\n    cerr\
    \ << \"\\e[1;33m[ \" << s << \" ] = [ \";\n    using namespace experimental;\n\
    \    copy(L, R, make_ostream_joiner(cerr, \", \"));\n    cerr << \" ]\\e[0m\\\
    n\";\n}\nvoid sepline_(int length = 50) {\n    cerr << \"\\e[1;35m\";\n    cerr\
    \ << string(length, '=');\n    cerr << \"\\e[0m\\n\";\n}\n#else\n#define safe\
    \ ((void)0)\n#define sepline safe\n#define debug(...) safe\n#define orange(...)\
    \ safe\n#endif\n\nvoid chmax(auto &x, auto val) {\n    x = max(x, val);\n}\n\n\
    void chmin(auto &x, auto val) {\n    x = min(x, val);\n}\n\nvector<int> count_array(const\
    \ auto &container, int sz = -1) {\n    if (sz == -1) sz = *ranges::max_element(container)\
    \ + 1;\n    vector<int> res(sz);\n    for (auto x : container) ++res[x];\n   \
    \ return res;\n}\n\ntemplate<class T>\nvoid discretization(vector<T> &vals) {\n\
    \    ranges::sort(vals);\n    vals.erase(ranges::unique(vals).begin(), vals.end());\n\
    }\n#line 4 \"test/2_aoj/intersection_of_a_circle_and_a_polygon.test.cpp\"\n\n\
    #line 2 \"Geometry/circle.hpp\"\n\n#line 2 \"Geometry/base.hpp\"\n    \ntemplate\
    \ <typename T>\nusing DefaultFloat = std::conditional_t<std::is_floating_point_v<T>,\
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
    };\n#line 6 \"Geometry/circle.hpp\"\n\ntemplate<typename T, T eps = get_default_eps<T>(),\
    \ typename MulT = T>\nstruct Circle : Geometry<T, eps> {\n    using value_type\
    \ = T;\n    using Point = Pt<T, eps, MulT>;\n    using Line = Ln<T, eps, MulT>;\n\
    \    using polygon = Polygon<T, eps, MulT>;\n    using Geometry<MulT, eps>::sign;\n\
    \    using Geometry<MulT, eps>::cmp;\n    static constexpr T eps_val = eps;\n\
    \    Point o;\n    T r;\n    Circle(Point _o = {}, T _r = 0) : o(_o), r(_r) {}\n\
    \    template <typename U, U _eps, typename _MulT>\n    Circle(const Circle<U,\
    \ _eps, _MulT>& other) : o(other.o), r(other.r) {}\n    // actually counts number\
    \ of tangent lines\n    friend int typeOfCircles(const Circle &c1, const Circle\
    \ &c2) {\n        auto [o1, r1] = c1;\n        auto [o2, r2] = c2;\n        MulT\
    \ d2 = dist2(o1, o2);\n        int cmpsum = cmp(d2, MulT(r1 + r2) * MulT(r1 +\
    \ r2));\n        if (cmpsum == 1) { return 4; }\n        if (cmpsum == 0) { return\
    \ 3; }\n        int cmpdiff = cmp(d2, MulT(r1 - r2) * MulT(r1 - r2));\n      \
    \  if (cmpdiff == 1) { return 2; }\n        if (cmpdiff == 0) { return 1; }\n\
    \        return 0;\n    }\n    // -1: in, 0: on, 1: out\n    friend bool pointToCircle(const\
    \ Point &p, const Circle &c) {\n        MulT x = square(p - c.o), d = x - MulT(c.r)\
    \ * MulT(c.r);\n        return cmp(dist2(c.o, p), MulT(c.r) * MulT(c.r));\n  \
    \  }\n    // aligned l.a -> l.b;\n    template <typename Ret = DefaultFloat<T>,\
    \ Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT\
    \ = Ret>\n    friend std::vector<Pt<Ret, _eps, _MulT>> circleLineIntersection(const\
    \ Circle &c, const Line &l) {\n        auto casto = Pt<Ret, _eps, _MulT>(c.o);\n\
    \        auto p = projection<Ret, _eps, _MulT>(c.o, l);\n        _MulT h = c.r\
    \ * c.r - square(p - casto);\n        if (sign(h) < 0) { return {}; }\n      \
    \  auto q = normal<Ret, _eps, _MulT>(direction(l)) * std::sqrt(h);\n        return\
    \ {p - q, p + q};\n    }\n    bool segCircleIntersect(const Line &l, const Circle\
    \ &cc) {\n        if (l[0] == l[1]) return pointToCircle(l[0], cc) == 0;\n   \
    \     Point dp = direction(l);\n        MulT a = square(dp);\n        MulT b =\
    \ 2 * dot(dp, l[0] - cc.o);\n        MulT c = square(cc.o) + square(l[0]) - 2\
    \ * dot(cc.o, l[0]) - MulT(cc.r) * MulT(cc.r);\n        MulT res = b * b - 4 *\
    \ a * c;\n        return sign(res) >= 0;\n    }\n    // circles shouldn't be identical\n\
    \    // one intersection dupliacted, aligned c1 counterclockwise\n    template\
    \ <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(),\
    \ typename _MulT = Ret>\n    friend std::vector<Pt<Ret, _eps, _MulT>> circleIntersection(const\
    \ Circle &c1, const Circle &c2) {\n        int type = typeOfCircles(c1, c2);\n\
    \        if (type == 0 || type == 4) { return {}; }\n        auto [o1, r1] = c1;\n\
    \        auto [o2, r2] = c2;\n        Ret d = std::clamp(dist(o1, o2), std::abs(Ret(r1\
    \ - r2)), Ret(r1 + r2));\n        Ret y = (r1 * r1 + d * d - r2 * r2) / (2 * d);\n\
    \        Ret x = std::sqrt(_MulT(r1) * _MulT(r1) - _MulT(y) * _MulT(y));\n   \
    \     auto dir = normal<Ret, _eps, _MulT>(o2 - o1);\n        auto q1 = Pt<Ret,\
    \ _eps, _MulT>(o1) + dir * y;\n        auto q2 = rotate90(dir) * x;\n        return\
    \ {q1 - q2, q1 + q2};\n    }\n    // counterclockwise, on circle -> no tangent\n\
    \    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret>\
    \ ? eps : get_default_eps<Ret>(), typename _MulT = Ret>\n    friend std::vector<Pt<Ret,\
    \ _eps, _MulT>> pointCircleTangent(const Point &p, const Circle &c) {\n      \
    \  MulT x = square(p - c.o), d = x - MulT(c.r) * MulT(c.r);\n        if (sign(d)\
    \ <= 0) { return {}; }\n        auto q1 = Pt<Ret, _eps, _MulT>(c.o) + Pt<Ret,\
    \ _eps, _MulT>(p - c.o) * (Ret(c.r) * Ret(c.r) / Ret(x));\n        auto q2 = Pt<Ret,\
    \ _eps, _MulT>(rotate90(p - c.o)) * (Ret(c.r) * std::sqrt(Ret(d)) / Ret(x));\n\
    \        return {q1 - q2, q1 + q2};\n    }\n    // one-point tangent lines are\
    \ not returned\n    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T,\
    \ Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>\n    friend std::vector<Ln<Ret,\
    \ _eps, _MulT>> externalTangent(const Circle &c1, const Circle &c2) {\n      \
    \  auto [o1, r1] = Circle<Ret, _eps, _MulT>(c1);\n        auto [o2, r2] = Circle<Ret,\
    \ _eps, _MulT>(c2);\n        std::vector<Ln<Ret, _eps, _MulT>> res;\n        if\
    \ (cmp(c1.r, c2.r) == 0) {\n            auto dr = rotate90(normal(o2 - o1)) *\
    \ r1;\n            res.emplace_back(o1 + dr, o2 + dr);\n            res.emplace_back(o1\
    \ - dr, o2 - dr);\n        }\n        else {\n            auto p = (o2 * r1 -\
    \ o1 * r2) / (r1 - r2);\n            auto ps = pointCircleTangent(p, Circle<Ret,\
    \ _eps, _MulT>(c1)), qs = pointCircleTangent(p, Circle<Ret, _eps, _MulT>(c2));\n\
    \            for (int i = 0; i < int(std::min(ps.size(), qs.size())); ++i) \n\
    \                res.emplace_back(ps[i], qs[i]);\n        }\n        return res;\n\
    \    }\n    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T,\
    \ Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>\n    friend std::vector<Ln<Ret,\
    \ _eps, _MulT>> internalTangent(const Circle &c1, const Circle &c2) {\n      \
    \  auto [o1, r1] = Circle<Ret, _eps, _MulT>(c1);\n        auto [o2, r2] = Circle<Ret,\
    \ _eps, _MulT>(c2);\n        vector<Ln<Ret, _eps, _MulT>> res;\n        auto p\
    \ = (o1 * r2 + o2 * r1) / (r1 + r2);\n        auto ps = pointCircleTangent(p,\
    \ Circle<Ret, _eps, _MulT>(c1)), qs = pointCircleTangent(p, Circle<Ret, _eps,\
    \ _MulT>(c2));\n        for (int i = 0; i < int(std::min(ps.size(), qs.size()));\
    \ i++)\n            res.emplace_back(ps[i], qs[i]);\n        return res;\n   \
    \ }\n    // OAB and circle directed area\n    template <typename Ret = DefaultFloat<T>,\
    \ Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT\
    \ = Ret>\n    static Ret triangleCircleIntersectionArea(const Point &p1, const\
    \ Point &p2, Ret r) {\n        using FPt = Pt<Ret, _eps, _MulT>;\n        auto\
    \ angle = [&](const FPt &_p1, const FPt &_p2) { \n            return std::atan2(cross(_p1,\
    \ _p2), dot(_p1, _p2));\n        };\n        FPt _p1 = p1, _p2 = p2;\n       \
    \ auto v = circleLineIntersection(Circle(FPt(), r), Ln(_p1, _p2));\n        if\
    \ (v.empty()) { return r * r * angle(_p1, _p2) / 2; }\n        bool b1 = FPt::cmp(square(_p1),\
    \ r * r) == 1;\n        bool b2 = FPt::cmp(square(_p2), r * r) == 1;\n       \
    \ if (b1 && b2) {\n            if (FPt::sign(dot(_p1 - v[0], _p2 - v[0])) <= 0\
    \ && FPt::sign(dot(_p1 - v[0], _p2 - v[0])) <= 0)\n                return r *\
    \ r * (angle(_p1, v[0]) + angle(v[1], _p2)) / 2 + cross(v[0], v[1]) / 2;\n   \
    \         return r * r * angle(_p1, _p2) / 2;\n        }\n        if (b1) return\
    \ (r * r * angle(_p1, v[0]) + cross(v[0], _p2)) / 2;\n        if (b2) return (cross(_p1,\
    \ v[1]) + r * r * angle(v[1], _p2)) / 2;\n        return cross(_p1, _p2) / 2;\n\
    \    }\n    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T,\
    \ Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>\n    friend Ret polyCircleIntersectionArea(const\
    \ polygon &a, Circle c) {\n        int n = a.size();\n        Ret ans = 0;\n \
    \       for (int i = 0; i < n; i++)\n            ans += triangleCircleIntersectionArea<Ret,\
    \ _eps, _MulT>(a[i], a[(i + 1) % n], c.r);\n        return ans;\n    }\n    template\
    \ <typename Ret = DefaultFloat<T>>\n    friend Ret circleIntersectionArea(Circle\
    \ a, Circle b) {\n        int tp = typeOfCircles(a, b);\n        if (tp >= 3)\
    \ return 0;\n        if (tp <= 1) {\n            Ret r = std::min(a.r, b.r);\n\
    \            return r * r * std::numbers::pi_v<Ret>;\n        }\n        Ret res\
    \ = 0, d = dist<Ret>(a.o, b.o);\n        for (int i = 0; i < 2; ++i) {\n     \
    \       Ret alpha = std::acos((b.r * b.r + d * d - a.r * a.r) / (2 * Ret(b.r)\
    \ * d));\n            Ret s = alpha * Ret(b.r) * Ret(b.r);\n            Ret t\
    \ = Ret(b.r) * Ret(b.r) * std::sin(alpha) * std::cos(alpha);\n            res\
    \ += s - t;\n            std::swap(a, b);\n        }\n        return res;\n  \
    \  }\n};\n#line 6 \"test/2_aoj/intersection_of_a_circle_and_a_polygon.test.cpp\"\
    \n\nusing cir = Circle<int>;\nusing polygon = Polygon<int>;\n\nint main() {\n\
    \    ios::sync_with_stdio(0), cin.tie(0);\n    cir c;\n    int n;\n    cin >>\
    \ n >> c.r;\n    polygon poly(n);\n    for (auto &p : poly)\n        cin >> p;\n\
    \    cout << fixed << setprecision(10) << polyCircleIntersectionArea(poly, c)\
    \ << \"\\n\";\n}\n\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H\"\
    \n#define ERROR 0.00001\n#include \"default_code.hpp\"\n\n#include \"Geometry/circle.hpp\"\
    \n\nusing cir = Circle<int>;\nusing polygon = Polygon<int>;\n\nint main() {\n\
    \    ios::sync_with_stdio(0), cin.tie(0);\n    cir c;\n    int n;\n    cin >>\
    \ n >> c.r;\n    polygon poly(n);\n    for (auto &p : poly)\n        cin >> p;\n\
    \    cout << fixed << setprecision(10) << polyCircleIntersectionArea(poly, c)\
    \ << \"\\n\";\n}\n\n"
  dependsOn:
  - default_code.hpp
  - Geometry/circle.hpp
  - Geometry/base.hpp
  - Geometry/line.hpp
  - Geometry/polygon.hpp
  isVerificationFile: true
  path: test/2_aoj/intersection_of_a_circle_and_a_polygon.test.cpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/2_aoj/intersection_of_a_circle_and_a_polygon.test.cpp
layout: document
redirect_from:
- /verify/test/2_aoj/intersection_of_a_circle_and_a_polygon.test.cpp
- /verify/test/2_aoj/intersection_of_a_circle_and_a_polygon.test.cpp.html
title: test/2_aoj/intersection_of_a_circle_and_a_polygon.test.cpp
---
