---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/BIT.hpp
    title: DataStructure/BIT.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/PointInAngle.hpp
    title: Geometry/PointInAngle.hpp
  - icon: ':question:'
    path: Geometry/base.hpp
    title: Geometry/base.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/count_points_in_triangle
    links:
    - https://judge.yosupo.jp/problem/count_points_in_triangle
  bundledCode: "#line 1 \"test/1_library_checker/geometry/count_points_in_triangle.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/count_points_in_triangle\"\
    \n#line 2 \"default_code.hpp\"\n\n#include <bits/stdc++.h>\nusing namespace std;\n\
    typedef long long ll;\ntypedef pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n\
    #define X first\n#define Y second\n#define SZ(a) ((int)a.size())\n#define ALL(v)\
    \ v.begin(), v.end()\ntemplate<class A, class B>\nostream& operator<<(ostream&\
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
    }\n#line 3 \"test/1_library_checker/geometry/count_points_in_triangle.test.cpp\"\
    \n\n#line 2 \"Geometry/PointInAngle.hpp\"\n\n#line 2 \"Geometry/base.hpp\"\n \
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
    \ }\n};\n#line 2 \"DataStructure/BIT.hpp\"\n\ntemplate<class T>\nclass BIT { //\
    \ 0-base\n    int n;\n    T total_;\n    vector<T> bit;\npublic:\n    BIT(int\
    \ _n): n(_n), total_(), bit(n + 1) {}\n    void initialize(const std::vector<T>\
    \ &arr) {\n        for (int x = 1; x <= n; ++x) {\n            bit[x] = arr[x\
    \ - 1];\n            int y = x - (x & -x);\n            for (int i = x - 1; i\
    \ > y; i -= i & -i)\n                bit[x] = bit[x] + bit[i];\n        }\n  \
    \  }\n    void modify(int x, T v) {\n        total_ += v;\n        for (++x; x\
    \ <= n; x += x & -x)\n            bit[x] = bit[x] + v;\n    }\n    T prefix(int\
    \ x) {\n        T res = T();\n        for (++x; x; x -= x & -x)\n            res\
    \ = res + bit[x];\n        return res;\n    }\n    T suffix(int x) requires requires(T\
    \ x, T y) { x - y; } {\n        return total_ - prefix(x);\n    }\n    T range(int\
    \ l, int r) requires requires(T x, T y) { x - y; } { // [l, r)\n        if (l\
    \ >= r) return T();\n        T res = prefix(r - 1) - prefix(l - 1);\n        return\
    \ res;\n    }\n    int kth(int k) { // 0-base query\n        assert((n & (n -\
    \ 1)) == 0);\n        ++k;\n        int res = 0;\n        for (int i = n >> 1;\
    \ i >= 1; i >>= 1) {\n            if (bit[res + i] < k)\n                k -=\
    \ bit[res += i];\n        }\n        return res;\n    }\n    T total() {\n   \
    \     return total_;\n    }\n};\n#line 5 \"Geometry/PointInAngle.hpp\"\n\n// cnt[i][j]\
    \ = weight sum of points k s.t. strictly above ij, and i < k < j\n// cnt2[i][j]\
    \ = weight sum of points k s.t. strictly in ij\n// preprocess space: O(n^2), time:\
    \ O(n(n+m)log(n+m)), query time: O(1)\ntemplate<typename T, typename Point>\n\
    struct PointInAngle {\n    std::vector<int> pl;\n    std::vector<Point> pts;\n\
    \    std::vector<std::vector<T>> cnt, cnt2;\n    std::vector<T> cnt3;\n    PointInAngle(const\
    \ std::vector<Point> &_pts, const std::vector<T> weight, const std::vector<Point>\
    \ &extra = {}, const std::vector<T> extra_weight = {}) : pl(_pts.size()), pts(_pts)\
    \ {\n        assert(_pts.size() == weight.size());\n        assert(extra.size()\
    \ == extra_weight.size());\n        pts.insert(pts.end(), extra.begin(), extra.end());\n\
    \        std::ranges::sort(pts), pts.erase(std::ranges::unique(pts).begin(), pts.end());\n\
    \        int n = pts.size();\n        cnt.resize(n, std::vector<T>(n));\n    \
    \    cnt2.resize(n, std::vector<T>(n));\n        cnt3.resize(n);\n        for\
    \ (int i = 0; i < int(_pts.size()); ++i) {\n            pl[i] = std::ranges::lower_bound(pts,\
    \ _pts[i]) - pts.begin();\n            cnt3[pl[i]] = cnt3[pl[i]] + weight[i];\n\
    \        }\n        for (int i = 0; i < int(extra.size()); ++i) {\n          \
    \  int idx = std::ranges::lower_bound(pts, extra[i]) - pts.begin();\n        \
    \    cnt3[idx] = cnt3[idx] + extra_weight[i];\n        }\n        for (int i =\
    \ 0; i + 1 < n; ++i) {\n            std::vector<int> cur(n - i - 1);\n       \
    \     std::iota(cur.begin(), cur.end(), i + 1);\n            std::ranges::sort(cur,\
    \ [&](int a, int b) {\n                Point lft = pts[a] - pts[i];\n        \
    \        Point rgt = pts[b] - pts[i];\n                if (sameDirection(lft,\
    \ rgt)) return a < b;\n                return polar(lft, rgt);\n            });\n\
    \            BIT<T> bit(n);\n            for (int j = 0, k = 0, op = 0; j < int(cur.size());\
    \ j = k) {\n                while (k < int(cur.size()) && sameDirection(pts[cur[j]]\
    \ - pts[i], pts[cur[k]] - pts[i]))\n                    bit.modify(cur[k], T()\
    \ - cnt3[cur[k]]), ++k;\n                while (op < j + int(cur.size()) && (op\
    \ < k || side(pts[i], pts[cur[j]], pts[cur[op % int(cur.size())]]) > 0))\n   \
    \                 bit.modify(cur[op % int(cur.size())], cnt3[cur[op % int(cur.size())]]),\
    \ ++op;\n                T sum = T();\n                for (int p = j; p < k;\
    \ ++p) {\n                    cnt[i][cur[p]] = bit.prefix(cur[p] - 1);\n     \
    \               cnt2[i][cur[p]] = sum;\n                    sum = sum + cnt3[cur[p]];\n\
    \                }\n            }\n        }\n    }\n    // calculate weight sum\
    \ of points strictly inside triangle i, j, k\n    T calc_tri(int x, int y, int\
    \ z) {\n        std::tie(x, y, z) = std::make_tuple(pl[x], pl[y], pl[z]);\n  \
    \      if (x > y) std::swap(x, y);\n        if (y > z) std::swap(y, z);\n    \
    \    if (x > y) std::swap(x, y);\n        if (x == y || y == z) return T();\n\
    \        int tmp = side(pts[x], pts[y], pts[z]);\n        if (tmp == 0) return\
    \ T();\n        if (tmp < 0) return cnt[x][z] - cnt[x][y] - cnt[y][z] - cnt2[x][y]\
    \ - cnt2[y][z] - cnt3[y];\n        return cnt[x][y] + cnt[y][z] - cnt[x][z] -\
    \ cnt2[x][z];\n    }\n};\n#line 5 \"test/1_library_checker/geometry/count_points_in_triangle.test.cpp\"\
    \n\nusing Point = Pt<ll>;\n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n\
    \    int n, m, q;\n    cin >> n;\n    vector<Point> arr(n);\n    for (auto &p\
    \ : arr)\n        cin >> p;\n    cin >> m;\n    vector<Point> extra(m);\n    for\
    \ (auto &p : extra)\n        cin >> p;\n    PointInAngle<int, Point> ds(arr, vector<int>(n,\
    \ 0), extra, vector<int>(m, 1));\n    cin >> q;\n    while (q--) {\n        int\
    \ x, y, z;\n        cin >> x >> y >> z;\n        cout << ds.calc_tri(x, y, z)\
    \ << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/count_points_in_triangle\"\
    \n#include \"default_code.hpp\"\n\n#include \"Geometry/PointInAngle.hpp\"\n\n\
    using Point = Pt<ll>;\n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n\
    \    int n, m, q;\n    cin >> n;\n    vector<Point> arr(n);\n    for (auto &p\
    \ : arr)\n        cin >> p;\n    cin >> m;\n    vector<Point> extra(m);\n    for\
    \ (auto &p : extra)\n        cin >> p;\n    PointInAngle<int, Point> ds(arr, vector<int>(n,\
    \ 0), extra, vector<int>(m, 1));\n    cin >> q;\n    while (q--) {\n        int\
    \ x, y, z;\n        cin >> x >> y >> z;\n        cout << ds.calc_tri(x, y, z)\
    \ << \"\\n\";\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - Geometry/PointInAngle.hpp
  - Geometry/base.hpp
  - DataStructure/BIT.hpp
  isVerificationFile: true
  path: test/1_library_checker/geometry/count_points_in_triangle.test.cpp
  requiredBy: []
  timestamp: '2026-05-07 16:20:41+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/geometry/count_points_in_triangle.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/geometry/count_points_in_triangle.test.cpp
- /verify/test/1_library_checker/geometry/count_points_in_triangle.test.cpp.html
title: test/1_library_checker/geometry/count_points_in_triangle.test.cpp
---
