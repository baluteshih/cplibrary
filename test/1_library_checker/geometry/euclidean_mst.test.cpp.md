---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/IterableOf.hpp
    title: Algebra/IterableOf.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/concept.hpp
    title: Algebra/Monoid/concept.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/DisjointSet.hpp
    title: Disjoint Set Union (DSU)
  - icon: ':heavy_check_mark:'
    path: Geometry/DelaunayTriangulation.hpp
    title: Geometry/DelaunayTriangulation.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/base.hpp
    title: Geometry/base.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/centers.hpp
    title: Geometry/centers.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/line.hpp
    title: Geometry/line.hpp
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/minimum_spanning_tree.hpp
    title: Graph/minimum_spanning_tree.hpp
  - icon: ':heavy_check_mark:'
    path: Sequence/same_position.hpp
    title: Sequence/same_position.hpp
  - icon: ':question:'
    path: assumption.hpp
    title: assumption.hpp
  - icon: ':heavy_check_mark:'
    path: default_code.hpp
    title: default_code.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/euclidean_mst
    links:
    - https://judge.yosupo.jp/problem/euclidean_mst
  bundledCode: "#line 1 \"test/1_library_checker/geometry/euclidean_mst.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/euclidean_mst\"\n#line 2 \"\
    assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 2 \"default_code.hpp\"\
    \n\n#line 4 \"default_code.hpp\"\nusing namespace std;\ntypedef long long ll;\n\
    typedef pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n#define X first\n#define\
    \ Y second\n#define SZ(a) ((int)a.size())\n#define ALL(v) v.begin(), v.end()\n\
    template <typename T>\nconcept PrintableContainer = requires(T& a) {\n    a.begin();\n\
    \    a.end();\n} && !std::convertible_to<std::remove_cvref_t<T>, std::string_view>;\
    \ \ntemplate<class A, class B>\nostream& operator<<(ostream& os, const pair<A,\
    \ B> &a);\ntemplate <PrintableContainer T>\nstd::ostream& operator<<(std::ostream&\
    \ os, const T& a);\ntemplate<class A, class B>\nostream& operator<<(ostream& os,\
    \ const pair<A, B> &a) {\n    os << \"(\" << a.first << \", \" << a.second <<\
    \ \")\";\n    return os;\n}\ntemplate <PrintableContainer T>\nstd::ostream& operator<<(std::ostream&\
    \ os, const T& a) {\n    os << \"[ \";\n    bool first = true;\n    for (const\
    \ auto& item : a) {\n        if (!first) os << \", \";\n        os << item;\n\
    \        first = false;\n    }\n    return os << \" ]\";\n}\n#ifdef bbq\n#include\
    \ <experimental/iterator>\n#define safe cerr<<__PRETTY_FUNCTION__<<\" line \"\
    <<__LINE__<<\" safe\\n\"\n#define sepline sepline_() \n#define debug(a...) debug_(#a,\
    \ a)\n#define orange(a...) orange_(#a, a)\nvoid debug_(auto s, auto ...a) {\n\
    \    cerr << \"\\e[1;32m(\" << s << \") = (\";\n    int f = 0;\n    (..., (cerr\
    \ << (f++ ? \", \" : \"\") << a));\n    cerr << \")\\e[0m\\n\";\n}\nvoid orange_(auto\
    \ s, auto L, auto R) {\n    cerr << \"\\e[1;33m[ \" << s << \" ] = [ \";\n   \
    \ using namespace experimental;\n    copy(L, R, make_ostream_joiner(cerr, \",\
    \ \"));\n    cerr << \" ]\\e[0m\\n\";\n}\nvoid sepline_(int length = 50) {\n \
    \   cerr << \"\\e[1;35m\";\n    cerr << string(length, '=');\n    cerr << \"\\\
    e[0m\\n\";\n}\n#else\n#define safe ((void)0)\n#define sepline safe\n#define debug(...)\
    \ safe\n#define orange(...) safe\n#endif\nvoid chmax(auto &x, auto val) { x =\
    \ max(x, val); }\nvoid chmin(auto &x, auto val) { x = min(x, val); }\nauto floor_div(auto\
    \ a, auto b) { return a / b - (a % b && (a < 0) ^ (b < 0)); }\nauto ceil_div(auto\
    \ a, auto b) { return a / b + (a % b && (a < 0) ^ (b > 0)); }\nstring bitstring(auto\
    \ x, int width = -1) {\n    string res;\n    while (x) res.push_back((x & 1) +\
    \ '0'), x >>= 1;\n    if (res.empty()) res = \"0\";\n    if (width != -1) res.resize(width,\
    \ '0');\n    ranges::reverse(res);\n    return res;\n}\nvector<int> count_array(const\
    \ auto &container, int sz = -1) {\n    if (sz == -1) sz = *ranges::max_element(container)\
    \ + 1;\n    vector<int> res(sz);\n    for (auto x : container) ++res[x];\n   \
    \ return res;\n}\n#line 4 \"test/1_library_checker/geometry/euclidean_mst.test.cpp\"\
    \n\n#line 2 \"Geometry/DelaunayTriangulation.hpp\"\n\n#line 2 \"Geometry/base.hpp\"\
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
    \    friend std::istream& operator>>(std::istream &is, Pt &p) { return is >> p.x\
    \ >> p.y; }\n    friend std::ostream& operator<<(std::ostream &os, const Pt &p)\
    \ { return os << p.x << ' ' << p.y; }\n    friend bool operator==(const Pt &a,\
    \ const Pt &b) { \n        return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0; \n\
    \    }\n    friend bool operator!=(const Pt &a, const Pt &b) { return !(a == b);\
    \ }\n    Pt operator-() { return Pt(-x, -y); }\n    Pt& operator+=(const Pt &a)\
    \ {\n        x += a.x, y += a.y;\n        return *this;\n    }\n    Pt& operator-=(const\
    \ Pt &a) {\n        x -= a.x, y -= a.y;\n        return *this;\n    }\n    Pt&\
    \ operator*=(T d) {\n        x *= d, y *= d;\n        return *this;\n    }\n \
    \   Pt& operator/=(T d) {\n        x /= d, y /= d;\n        return *this;\n  \
    \  }\n    friend Pt operator+(const Pt &a, const Pt &b) { return Pt(a) += b; }\n\
    \    friend Pt operator-(const Pt &a, const Pt &b) { return Pt(a) -= b; }\n  \
    \  friend Pt operator*(const Pt &a, T d) { return Pt(a) *= d; }\n    friend Pt\
    \ operator/(const Pt &a, T d) { return Pt(a) /= d; }\n    friend bool operator<(const\
    \ Pt &a, const Pt &b) {\n        int sx = cmp(a.x, b.x);\n        return sx !=\
    \ 0 ? sx == -1 : cmp(a.y, b.y) == -1;\n    }\n    friend bool operator>(const\
    \ Pt &a, const Pt &b) { return b < a; }\n    friend bool operator<=(const Pt &a,\
    \ const Pt &b) { return !(b < a); }\n    friend bool operator>=(const Pt &a, const\
    \ Pt &b) { return !(a < b); }\n    template <typename U, U _eps, typename _MulT>\n\
    \    Pt(const Pt<U, _eps, _MulT>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))\
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
    \ }\n};\n#line 2 \"Geometry/centers.hpp\"\n\n#line 2 \"Geometry/line.hpp\"\n\n\
    #line 4 \"Geometry/line.hpp\"\n\ntemplate<typename T, T eps = get_default_eps<T>(),\
    \ typename MulT = T>\nstruct Ln : Geometry<T, eps> {\n    using value_type = T;\n\
    \    using Point = Pt<T, eps, MulT>;\n    std::array<Point, 2> l;\n    using Geometry<MulT,\
    \ eps>::sign;\n    using Geometry<MulT, eps>::cmp;\n    static constexpr T eps_val\
    \ = eps;\n    Ln() {}\n    Ln(const Point &a, const Point &b) : l{a, b} {}\n \
    \   friend std::istream& operator>>(std::istream &is, Ln &p) { return is >> p.l[0]\
    \ >> p.l[1]; }\n    friend std::ostream& operator<<(std::ostream &os, const Ln\
    \ &p) { return os << p.l[0] << ' ' << p.l[1]; }\n    template <typename U, U _eps,\
    \ typename _MulT>\n    Ln(const Ln<U, _eps, _MulT>& other) : l{other.l[0], other.l[1]}\
    \ {}\n    friend int side(const Point &p, const Ln &l) { \n        return side(p,\
    \ l[0], l[1]);\n    }\n    Point& operator[](int index) {\n        return l[index];\n\
    \    }\n    const Point& operator[](int index) const {\n        return l[index];\n\
    \    }\n    friend Point direction(const Ln &l) {\n        return l[1] - l[0];\n\
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
    \  using type = Ln<T, eps, MulT>;\n};\n#line 5 \"Geometry/centers.hpp\"\n\n//\
    \ radius: (a + b + c) * r / 2 = A or pointToLineDist\ntemplate<typename Point,\
    \ typename T = DefaultFloat<typename Point::value_type>, T eps = std::is_same_v<typename\
    \ Point::value_type, T> ? Point::eps_val : get_default_eps<T>(), typename MulT\
    \ = T>\nPt<T, eps, MulT> incenter(const Point &a, const Point &b, const Point\
    \ &c) {\n    T la = length(b - c), lb = length(c - a), lc = length(a - b);\n \
    \   return (Pt<T, eps, MulT>(a) * la + Pt<T, eps, MulT>(b) * lb + Pt<T, eps, MulT>(c)\
    \ * lc) / (la + lb + lc);\n}\n\ntemplate<typename Point, typename T = DefaultFloat<typename\
    \ Point::value_type>, T eps = std::is_same_v<typename Point::value_type, T> ?\
    \ Point::eps_val : get_default_eps<T>(), typename MulT = T>\nPt<T, eps, MulT>\
    \ circumcenter(const Point &a, const Point &b, const Point &c) {\n    Pt<T, eps,\
    \ MulT> ba = b - a, ca = c - a;\n    T db = square(ba), dc = square(ca), d = 2\
    \ * cross(ba, ca);\n    return Pt<T, eps, MulT>(a) - Pt<T, eps, MulT>(ba.y * dc\
    \ - ca.y * db, ca.x * db - ba.x * dc) / d;\n}\n\ntemplate<typename Point, typename\
    \ T = DefaultFloat<typename Point::value_type>, T eps = std::is_same_v<typename\
    \ Point::value_type, T> ? Point::eps_val : get_default_eps<T>(), typename MulT\
    \ = T>\nPt<T, eps, MulT> orthocenter(const Point &a, const Point &b, const Point\
    \ &c) {\n    Ln<T, eps, MulT> u(c, Pt<T, eps, MulT>(c.x - a.y + b.y, c.y + a.x\
    \ - b.x));\n    Ln<T, eps, MulT> v(b, Pt<T, eps, MulT>(b.x - a.y + c.y, b.y +\
    \ a.x - c.x));\n    return lineIntersection(u, v);\n}\n\n// -1: in, 0: on, 1:\
    \ out, C^4\ntemplate<typename Point, typename MulT = typename Point::value_type,\
    \ MulT eps = std::is_same_v<typename Point::value_type, MulT> ? Point::eps_val\
    \ : get_default_eps<MulT>()>\nint pointInCircumCircle(const Point &a, const Point\
    \ &b, const Point &c, const Point &q) {\n    MulT det = 0;\n    det += MulT(square(a)\
    \ - square(q)) * MulT(cross(b - q, c - q));\n    det += MulT(square(b) - square(q))\
    \ * MulT(cross(c - q, a - q));\n    det += MulT(square(c) - square(q)) * MulT(cross(a\
    \ - q, b - q));\n    return Geometry<MulT, eps>::sign(det);\n}\n#line 5 \"Geometry/DelaunayTriangulation.hpp\"\
    \n\ntemplate <typename Point, typename MulT = typename Point::value_type, MulT\
    \ eps = std::is_same_v<typename Point::value_type, MulT> ? Point::eps_val : get_default_eps<MulT>()>\n\
    struct DelaunayTriangulation {\n    using T = typename Point::value_type;\n  \
    \  struct Edge {\n        int orig, dest;\n        int nxt, prev;\n    };\n  \
    \  std::vector<Point> pts;\n    std::vector<Edge> edg;\n    std::vector<int> oidx;\n\
    \    int make_edge(int u, int v) {\n        int e1 = edg.size(); edg.push_back({u,\
    \ v, e1, e1});\n        int e2 = edg.size(); edg.push_back({v, u, e2, e2});\n\
    \        return e1;\n    }\n    void splice(int a, int b) {\n        int a_nxt\
    \ = edg[a].nxt, b_nxt = edg[b].nxt;\n        edg[a].nxt = b_nxt; edg[b_nxt].prev\
    \ = a;\n        edg[b].nxt = a_nxt; edg[a_nxt].prev = b;\n    }\n    int sym(int\
    \ e)   const { return e ^ 1; }\n    int orig(int e)  const { return edg[e].orig;\
    \ }\n    int dest(int e)  const { return edg[e].dest; }\n    int onxt(int e) \
    \ const { return edg[e].nxt; }\n    int oprev(int e) const { return edg[e].prev;\
    \ }\n    int lnext(int e) const { return oprev(sym(e)); }\n    int rprev(int e)\
    \ const { return onxt(sym(e)); }\n    int connect(int a, int b) {\n        int\
    \ e = make_edge(dest(a), orig(b));\n        splice(e, lnext(a));\n        splice(sym(e),\
    \ b);\n        return e;\n    }\n    void delete_edge(int e) {\n        splice(e,\
    \ oprev(e));\n        splice(sym(e), oprev(sym(e)));\n        edg[e].orig = -1;\n\
    \        edg[sym(e)].orig = -1;\n    }\n    bool ccw(int a, int b, int c) const\
    \ {\n        return side(pts[a], pts[b], pts[c]) == 1;\n    }\n    bool in_circle(int\
    \ a, int b, int c, int p) const {\n        return pointInCircumCircle<Point, MulT,\
    \ eps>(pts[a], pts[b], pts[c], pts[p]) == 1; \n    }\n    bool right_of(int x,\
    \ int e) const { return ccw(x, dest(e), orig(e)); }\n    bool left_of(int x, int\
    \ e)  const { return ccw(x, orig(e), dest(e)); }\n    std::pair<int, int> solve(int\
    \ l, int r) {\n        if (l + 1 == r) {\n            int a = make_edge(l, r);\n\
    \            return {a, sym(a)};\n        }\n        if (l + 2 == r) {\n     \
    \       int a = make_edge(l, l + 1);\n            int b = make_edge(l + 1, r);\n\
    \            splice(sym(a), b);\n            if (ccw(l, l + 1, r)) {\n       \
    \         connect(b, a);\n                return {a, sym(b)};\n            }\n\
    \            else if (ccw(l, r, l + 1)) {\n                int c = connect(b,\
    \ a);\n                return {sym(c), c};\n            }\n            else return\
    \ {a, sym(b)};\n        }\n        int mid = l + (r - l) / 2;\n        auto [ldo,\
    \ ldi] = solve(l, mid);\n        auto [rdi, rdo] = solve(mid + 1, r);\n      \
    \  while (true) {\n            if (left_of(orig(rdi), ldi)) ldi = lnext(ldi);\n\
    \            else if (right_of(orig(ldi), rdi)) rdi = rprev(rdi);\n          \
    \  else break;\n        }\n        int basel = connect(sym(rdi), ldi);\n     \
    \   if (orig(ldi) == orig(ldo)) ldo = sym(basel);\n        if (orig(rdi) == orig(rdo))\
    \ rdo = basel;\n        while (true) {\n            int lcand = rprev(basel);\n\
    \            bool lvalid = right_of(dest(lcand), basel);\n            if (lvalid)\
    \ {\n                while (right_of(dest(onxt(lcand)), basel) && in_circle(dest(basel),\
    \ orig(basel), dest(lcand), dest(onxt(lcand)))) {\n                    int t =\
    \ onxt(lcand);\n                    delete_edge(lcand);\n                    lcand\
    \ = t;\n                }\n            }\n            int rcand = oprev(basel);\n\
    \            bool rvalid = right_of(dest(rcand), basel);\n            if (rvalid)\
    \ {\n                while (right_of(dest(oprev(rcand)), basel) && in_circle(dest(basel),\
    \ orig(basel), dest(rcand), dest(oprev(rcand)))) {\n                    int t\
    \ = oprev(rcand);\n                    delete_edge(rcand);\n                 \
    \   rcand = t;\n                }\n            }\n            if (!lvalid && !rvalid)\
    \ break;\n            if (!lvalid || (rvalid && in_circle(dest(lcand), orig(lcand),\
    \ orig(basel), dest(rcand))))\n                basel = connect(rcand, sym(basel));\n\
    \            else\n                basel = connect(sym(basel), sym(lcand));\n\
    \        }\n        return {ldo, rdo};\n    }\n    DelaunayTriangulation(std::vector<Point>\
    \ input_pts) {\n        oidx.resize(input_pts.size());\n        std::iota(oidx.begin(),\
    \ oidx.end(), 0);\n        std::sort(oidx.begin(), oidx.end(), [&](int a, int\
    \ b) {\n            if (input_pts[a] != input_pts[b]) return input_pts[a] < input_pts[b];\n\
    \            return a < b;\n        });\n        pts.resize(std::ranges::unique(oidx,\
    \ [&](int a, int b) {\n            return input_pts[a] == input_pts[b]; \n   \
    \     }).begin() - oidx.begin());\n        for (int i = 0; i < int(pts.size());\
    \ ++i) pts[i] = input_pts[oidx[i]];\n        edg.clear();\n        edg.reserve(pts.size()\
    \ * 12);\n        if (pts.size() >= 2) solve(0, pts.size() - 1);\n    }\n    std::vector<std::pair<int,\
    \ int>> get_edges() {\n        std::vector<std::pair<int, int>> res;\n       \
    \ for (int i = 0; i < int(edg.size()); i += 2)\n            if (edg[i].orig !=\
    \ -1)\n                res.emplace_back(oidx[orig(i)], oidx[dest(i)]);\n     \
    \   return res;\n    }\n};\n#line 2 \"Graph/minimum_spanning_tree.hpp\"\n\n#line\
    \ 2 \"Graph/base.hpp\"\n\ntemplate<typename W>\nstruct edge_data {\n    int from,\
    \ to;\n    W weight;\n    edge_data() = default;\n    edge_data(int u, int v,\
    \ const W &w) : from(u), to(v), weight(w) {}\n};\ntemplate<>\nstruct edge_data<void>\
    \ { \n    int from, to; \n    edge_data() = default;\n    edge_data(int u, int\
    \ v) : from(u), to(v) {}\n};\n\ntemplate<bool directed = true, typename Edge =\
    \ void, typename Vertex = void>\nclass Graph {\npublic:\n    static constexpr\
    \ bool is_directed = directed;\n    static constexpr bool hasEdgeWeight = !std::is_same_v<Edge,\
    \ void>;\n    static constexpr bool hasVertexWeight = !std::is_same_v<Vertex,\
    \ void>;\n    static constexpr bool hasEdgeWeightReverse = requires(Edge v) {\
    \ v.reverse(); };\n    using edge_value_type = Edge;\n    using vertex_value_type\
    \ = Vertex;\n    struct Empty {};\n    struct edge_v : public edge_data<Edge>\
    \ {\n        using edge_data<Edge>::edge_data;\n        template <typename OtherEdge>\n\
    \        edge_v(const OtherEdge &other) requires(hasEdgeWeight && requires(OtherEdge\
    \ o) { o.weight; })\n            : edge_data<Edge>(other.from, other.to, other.weight)\
    \ {}\n        template <typename OtherEdge>\n        edge_v(const OtherEdge &other)\
    \ requires(!hasEdgeWeight || !requires(OtherEdge o) { o.weight; })\n         \
    \   : edge_data<Edge>(other.from, other.to) {}\n        edge_v reversed() const\
    \ {\n            edge_v res(*this);\n            std::swap(res.from, res.to);\n\
    \            if constexpr (hasEdgeWeightReverse) res.weight.reverse();\n     \
    \       return res;\n        }\n        friend std::ostream& operator<<(std::ostream&\
    \ os, const edge_v &v) {\n            os << \"(\" << v.from << \"->\" << v.to;\n\
    \            if constexpr (hasEdgeWeight) os << \", \" << v.weight;\n        \
    \    os << \")\";\n            return os;\n        }\n    };\n    std::vector<std::vector<std::pair<int,\
    \ int>>> G;\n    std::vector<edge_v> edges;\n    [[no_unique_address]] std::conditional_t<hasVertexWeight,\
    \ std::vector<Vertex>, Empty> weight;\n    Graph(int _n) : G(_n) {\n        if\
    \ constexpr (hasVertexWeight) weight.resize(_n);\n    }\n    int n() const { return\
    \ G.size(); }\n    int m() const { return edges.size(); }\n    int opposite(int\
    \ u, int eid) const { return edges[eid].from ^ edges[eid].to ^ u; }\n    auto&\
    \ edge(int idx) {\n        return edges[idx]; \n    }\n    auto &vertex(int idx)\
    \ requires (hasVertexWeight) {\n        return weight[idx];\n    }\n    const\
    \ auto& edge(int idx) const {\n        return edges[idx]; \n    }\n    const auto\
    \ &vertex(int idx) const requires (hasVertexWeight) {\n        return weight[idx];\n\
    \    }\n    auto &vertex_weight() requires (hasVertexWeight) {\n        return\
    \ weight;\n    }\n    const auto &vertex_weight() const requires (hasVertexWeight)\
    \ {\n        return weight;\n    }\n    void set_vertex_weight(const auto &vec)\
    \ {\n        for (int i = 0; i < n(); ++i)\n            weight[i] = vec[i];\n\
    \    }\n    void add_edge(int u, int v, const auto &w) requires (hasEdgeWeight)\
    \ {\n        G[u].emplace_back(v, edges.size());\n        if constexpr (!directed)\
    \ G[v].emplace_back(u, edges.size());\n        edges.emplace_back(u, v, w);\n\
    \    }\n    void add_edge(int u, int v) requires (!hasEdgeWeight) {\n        G[u].emplace_back(v,\
    \ edges.size());\n        if constexpr (!directed) G[v].emplace_back(u, edges.size());\n\
    \        edges.emplace_back(u, v);\n    }\n    void add_edge(const edge_v &e)\
    \ {\n        G[e.from].emplace_back(e.to, edges.size());\n        if constexpr\
    \ (!directed) G[e.to].emplace_back(e.from, edges.size());\n        edges.emplace_back(e);\n\
    \    }\n    void pop_edge() {\n        G[edges.back().from].pop_back();\n    \
    \    if constexpr (!directed) G[edges.back().to].pop_back();\n        edges.pop_back();\n\
    \    }\n    std::vector<int> in_degree() const {\n        std::vector<int> res(n());\n\
    \        for (auto &e : edges) {\n            if constexpr (!is_directed) ++res[e.from];\n\
    \            ++res[e.to];\n        }\n        return res;\n    }\n    virtual\
    \ std::vector<int> out_degree() const {\n        std::vector<int> res(n());\n\
    \        for (auto &e : edges) {\n            if constexpr (!is_directed) ++res[e.to];\n\
    \            ++res[e.from];\n        }\n        return res;\n    }\n    std::vector<std::pair<int,\
    \ int>>& operator[](int idx) {\n        return G[idx];\n    }\n    const std::vector<std::pair<int,\
    \ int>>& operator[](int idx) const {\n        return G[idx];\n    }\n    Graph\
    \ reversed() const {\n        Graph res(n());\n        for (auto &e : edges)\n\
    \            res.add_edge(e.reversed());\n        if constexpr (hasVertexWeight)\
    \ res.set_vertex_weight(weight);\n        return res;\n    }\n    std::pair<std::vector<int>,\
    \ std::vector<int>> cycle() const {\n        std::vector<int> vis(this->n());\n\
    \        std::vector<int> res_v, res_e;\n        int cyc_end = -1;\n        auto\
    \ dfs = [&](auto self, int u, int f) -> int {\n            vis[u] = 1;\n     \
    \       for (auto [v, eid] : G[u]) {\n                if (eid == f || vis[v] ==\
    \ 2) continue;\n                if (vis[v] == 1) {\n                    res_v.push_back(u);\n\
    \                    res_e.push_back(eid);\n                    cyc_end = v;\n\
    \                    return 1;\n                }\n                int rt = self(self,\
    \ v, eid);\n                if (rt) {\n                    if (rt == 1) { \n \
    \                       res_e.push_back(eid);\n                        res_v.push_back(u);\n\
    \                    }\n                    if (cyc_end == u) rt = 2;\n      \
    \              return rt;\n                }\n            }\n            vis[u]\
    \ = 2;\n            return 0;\n        };\n        for (int i = 0; i < this->n();\
    \ ++i)\n            if (!vis[i] && dfs(dfs, i, -1))\n                break;\n\
    \        std::ranges::reverse(res_v);\n        std::ranges::reverse(res_e);\n\
    \        return std::make_pair(res_v, res_e);\n    }\n    Graph<true, Edge, Vertex>\
    \ oriented(const std::vector<int> &rk) const requires (!directed) {\n        Graph<true,\
    \ Edge, Vertex> res(this->n());\n        for (auto &e : edges)\n            if\
    \ (rk[e.from] < rk[e.to])\n                res.add_edge(e);\n            else\n\
    \                res.add_edge(e.reversed());\n        return res;\n    }\n   \
    \ Graph induced(const std::vector<int> &subset) const {\n        std::vector<int>\
    \ idx(n(), -1);\n        for (int cnt = 0; int i : subset) idx[i] = cnt++;\n \
    \       Graph res(subset.size());\n        for (auto e : edges) {\n          \
    \  e.from = idx[e.from], e.to = idx[e.to];\n            if (e.to == -1 || e.from\
    \ == -1) continue;\n            res.add_edge(e);\n        }\n        return res;\n\
    \    }\n    std::vector<int> reachable(int s) const {\n        std::vector<int>\
    \ res, vis(n());\n        auto dfs = [&](auto self, int u) -> void {\n       \
    \     vis[u] = 1;\n            for (auto [v, eid] : G[u])\n                if\
    \ (!vis[v])\n                    self(self, v);\n            res.push_back(u);\n\
    \        };\n        dfs(dfs, s);\n        return res;\n    }\n};\n\ntemplate<typename\
    \ Edge = void, typename Vertex = void>\nclass UndirectedGraph : public Graph<false,\
    \ Edge, Vertex> {\npublic:\n    using Graph<false, Edge, Vertex>::Graph;\n   \
    \ std::vector<std::vector<int>> components() {\n        std::vector<std::vector<int>>\
    \ res;\n        std::vector<bool> vis(this->n());\n        auto dfs = [&](auto\
    \ self, int u) -> void {\n            vis[u] = true;\n            res.back().push_back(u);\n\
    \            for (auto [v, eid] : this->G[u])\n                if (!vis[v])\n\
    \                    self(self, v);\n        };\n        for (int i = 0; i < this->n();\
    \ ++i) {\n            if (vis[i]) continue;\n            res.emplace_back();\n\
    \            dfs(dfs, i);\n        }\n        return res;\n    }\n    bool is_connected()\
    \ {\n        return components().size() == 1;\n    }\n};\n#line 2 \"DataStructure/DisjointSet.hpp\"\
    \n\n#line 2 \"Algebra/Monoid/concept.hpp\"\n\n#line 2 \"Algebra/ValidOperation.hpp\"\
    \n\ntemplate <typename A, typename B>\nconcept Addable = !std::is_void_v<A> &&\
    \ !std::is_void_v<B> && requires(A a, B b) { a + b; };\n\ntemplate <typename A,\
    \ typename B>\nconcept Subtractable = !std::is_void_v<A> && !std::is_void_v<B>\
    \ && requires(A a, B b) { a - b; };\n\ntemplate <typename A, typename B>\nconcept\
    \ Multiplicable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a * b; };\n#line 4 \"Algebra/Monoid/concept.hpp\"\n\ntemplate<typename\
    \ T>\nconcept isMonoid = Addable<T, T> && std::default_initializable<T>;\n\ntemplate<typename\
    \ T>\nconcept isCommutativeMonoid = isMonoid<T>;\n#line 4 \"DataStructure/DisjointSet.hpp\"\
    \n\ntemplate<typename T = void, bool undo_tag = false>\nclass DisjointSet {\n\
    protected:\n    static constexpr bool hasT = isCommutativeMonoid<T>;\n    int\
    \ n;\n    std::vector<int> boss, sz;\n    struct Empty {};\n    [[no_unique_address]]\
    \ std::conditional_t<hasT, std::vector<T>, Empty> data;\n    [[no_unique_address]]\
    \ std::conditional_t<undo_tag, std::vector<std::pair<int*, int>>, Empty> cache;\n\
    \    [[no_unique_address]] std::conditional_t<undo_tag && hasT, std::vector<std::pair<T*,\
    \ T>>, Empty> data_cache;\npublic:\n    DisjointSet(int n_): n(n_), boss(n), sz(n,\
    \ 1) {\n        std::iota(boss.begin(), boss.end(), 0);\n        if constexpr\
    \ (hasT) data.resize(n);\n    }\n    DisjointSet(const std::ranges::range auto\
    \ &data_) requires (hasT) : n(data_.size()), boss(n), sz(n, 1), data(data_) {\n\
    \        std::iota(boss.begin(), boss.end(), 0);\n    }\n    virtual int leader(int\
    \ u) {\n        if (boss[u] == u) return u;\n        if constexpr (undo_tag) return\
    \ leader(boss[u]);\n        else return boss[u] = leader(boss[u]);\n    }\n  \
    \  int size(int u) {\n        return sz[leader(u)];\n    }\n    bool same(int\
    \ u, int v) {\n        return leader(u) == leader(v);\n    }\n    bool merge(int\
    \ u, int v, bool force = false) {\n        u = leader(u), v = leader(v);\n   \
    \     if (u == v) return false;\n        if (sz[u] < sz[v] && !force) std::swap(u,\
    \ v);\n        if constexpr (undo_tag) {\n            cache.emplace_back(&boss[v],\
    \ boss[v]); \n            cache.emplace_back(&sz[u], sz[v]); \n            if\
    \ constexpr (hasT)\n                data_cache.emplace_back(&data[u], data[u]);\n\
    \        }\n        boss[v] = u;\n        sz[u] += sz[v];\n        if constexpr\
    \ (hasT) {\n            data[u] = data[u] + data[v]; \n        }\n        return\
    \ true;\n    }\n    size_t version() requires (undo_tag && !hasT) {\n        return\
    \ cache.size();\n    }\n    std::pair<size_t, size_t> version() requires (undo_tag\
    \ && hasT) {\n        return std::make_pair(cache.size(), data_cache.size());\n\
    \    }\n    void undo(auto req_version) requires (undo_tag) {\n        while (version()\
    \ != req_version) {\n            if constexpr (!hasT) {\n                *cache.back().first\
    \ = cache.back().second;\n                cache.pop_back();\n            }\n \
    \           else {\n                if (cache.size() > req_version.first) {\n\
    \                    *cache.back().first = cache.back().second;\n            \
    \        cache.pop_back();\n                }\n                else {\n      \
    \              *data_cache.back().first = data_cache.back().second;\n        \
    \            data_cache.pop_back();\n                }\n            }\n      \
    \  }\n    }\n    auto& getdata(int u) requires (hasT) {\n        return data[leader(u)];\n\
    \    }\n    void data_transform(int u, auto func) requires (hasT) {\n        auto\
    \ &cur = getdata(u);\n        if constexpr (undo_tag)\n            data_cache.emplace_back(&cur,\
    \ cur);\n        func(cur);\n    }\n    std::vector<std::vector<int>> groups()\
    \ {\n        std::vector<std::vector<int>> result(n);\n        for (int i = 0;\
    \ i < n; ++i)\n            result[leader(i)].push_back(i);\n        result.erase(remove_if(result.begin(),\
    \ result.end(), [](auto &g) { return g.empty(); }), result.end());\n        return\
    \ result;\n    }\n};\n#line 5 \"Graph/minimum_spanning_tree.hpp\"\n\ntemplate<typename\
    \ Edge = int, typename Vertex = void>\nstd::vector<int> minimum_spanning_tree(const\
    \ UndirectedGraph<Edge, Vertex> &graph) {\n    std::vector<int> idx(graph.m());\n\
    \    std::iota(idx.begin(), idx.end(), 0);\n    std::ranges::sort(idx.begin(),\
    \ idx.end(), [&](int a, int b) {\n        return graph.edge(a).weight < graph.edge(b).weight;\
    \ \n    });\n    DisjointSet dsu(graph.n());\n    std::vector<int> res;\n    for\
    \ (int i : idx)\n        if (dsu.merge(graph.edge(i).from, graph.edge(i).to))\n\
    \            res.push_back(i);\n    return res;\n}\n#line 2 \"Sequence/same_position.hpp\"\
    \n\n#line 2 \"Algebra/IterableOf.hpp\"\n\ntemplate <typename C, typename T>\n\
    concept IterableOf = std::ranges::range<C> && std::same_as<std::ranges::range_value_t<C>,\
    \ T>;\n#line 4 \"Sequence/same_position.hpp\"\n\ntemplate<bool indexable_range\
    \ = false, std::ranges::range C>\nstd::vector<int> previous_same_position(const\
    \ C &arr) {\n    std::conditional_t<indexable_range, std::vector<int>, std::map<std::ranges::range_value_t<C>,\
    \ int>> prv;\n    if constexpr (indexable_range) prv.resize(*std::ranges::max_element(arr)\
    \ + 1);\n    std::vector<int> res(arr.size());\n    for (int i = 0; const auto\
    \ &v : arr)\n        res[i] = prv[v] - 1, prv[v] = ++i;\n    return res;\n}\n\n\
    template<bool indexable_range = false, std::ranges::range C>\nstd::vector<int>\
    \ next_same_position(const C &arr) {\n    std::vector<int> res = previous_same_position(arr\
    \ | std::views::reverse);\n    std::ranges::reverse(res);\n    for (int &i : res)\
    \ i = int(arr.size()) - i - 1;\n    return res;\n}\n#line 8 \"test/1_library_checker/geometry/euclidean_mst.test.cpp\"\
    \n\nusing Point = Pt<int>;\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int n;\n    std::cin >> n;\n    std::vector<Point> vec(n);\n\
    \    for (auto &p : vec)\n        std::cin >> p;\n    auto res = DelaunayTriangulation<Point,\
    \ long long>(vec);\n    auto edges = res.get_edges();\n    UndirectedGraph<int>\
    \ G(n);\n    for (auto [u, v] : edges)\n        G.add_edge(u, v, dist2(vec[u],\
    \ vec[v]));\n    auto prev = previous_same_position(vec);\n    for (int i = 0;\
    \ i < n; ++i)\n        if (prev[i] != -1)\n            G.add_edge(i, prev[i],\
    \ 0);\n    auto ans = minimum_spanning_tree(G);\n    for (int e : ans)\n     \
    \   std::cout << G.edge(e).from << \" \" << G.edge(e).to << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/euclidean_mst\"\n#include\
    \ \"assumption.hpp\"\n#include \"default_code.hpp\"\n\n#include \"Geometry/DelaunayTriangulation.hpp\"\
    \n#include \"Graph/minimum_spanning_tree.hpp\"\n#include \"Sequence/same_position.hpp\"\
    \n\nusing Point = Pt<int>;\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int n;\n    std::cin >> n;\n    std::vector<Point> vec(n);\n\
    \    for (auto &p : vec)\n        std::cin >> p;\n    auto res = DelaunayTriangulation<Point,\
    \ long long>(vec);\n    auto edges = res.get_edges();\n    UndirectedGraph<int>\
    \ G(n);\n    for (auto [u, v] : edges)\n        G.add_edge(u, v, dist2(vec[u],\
    \ vec[v]));\n    auto prev = previous_same_position(vec);\n    for (int i = 0;\
    \ i < n; ++i)\n        if (prev[i] != -1)\n            G.add_edge(i, prev[i],\
    \ 0);\n    auto ans = minimum_spanning_tree(G);\n    for (int e : ans)\n     \
    \   std::cout << G.edge(e).from << \" \" << G.edge(e).to << \"\\n\";\n}\n"
  dependsOn:
  - assumption.hpp
  - default_code.hpp
  - Geometry/DelaunayTriangulation.hpp
  - Geometry/base.hpp
  - Geometry/centers.hpp
  - Geometry/line.hpp
  - Graph/minimum_spanning_tree.hpp
  - Graph/base.hpp
  - DataStructure/DisjointSet.hpp
  - Algebra/Monoid/concept.hpp
  - Algebra/ValidOperation.hpp
  - Sequence/same_position.hpp
  - Algebra/IterableOf.hpp
  isVerificationFile: true
  path: test/1_library_checker/geometry/euclidean_mst.test.cpp
  requiredBy: []
  timestamp: '2026-09-25 00:52:55+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/geometry/euclidean_mst.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/geometry/euclidean_mst.test.cpp
- /verify/test/1_library_checker/geometry/euclidean_mst.test.cpp.html
title: test/1_library_checker/geometry/euclidean_mst.test.cpp
---
