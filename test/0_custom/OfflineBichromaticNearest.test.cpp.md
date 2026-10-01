---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/ZkwSegmentTree.hpp
    title: Zkw Segment Tree
  - icon: ':heavy_check_mark:'
    path: Geometry/OfflineBichromaticNearest.hpp
    title: Geometry/OfflineBichromaticNearest.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/base.hpp
    title: Geometry/base.hpp
  - icon: ':heavy_check_mark:'
    path: Misc/i256.hpp
    title: Misc/i256.hpp
  - icon: ':question:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"test/0_custom/OfflineBichromaticNearest.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n#line 2 \"assumption.hpp\"\
    \n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3 \"test/0_custom/OfflineBichromaticNearest.test.cpp\"\
    \n\n#line 2 \"Geometry/OfflineBichromaticNearest.hpp\"\n\n#line 2 \"Geometry/base.hpp\"\
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
    \ }\n};\n#line 2 \"DataStructure/ZkwSegmentTree.hpp\"\n\ntemplate<typename Value\
    \ = int, typename Tag = void, bool pushdown = true>\nclass ZkwSegmentTree {\n\
    \    static constexpr bool hasTag = !std::is_same_v<Tag, void>;\n    static_assert(pushdown\
    \ || hasTag, \"Lazy tag must exist when pushdown is false\");\n    int n, sz,\
    \ lg;\n    std::vector<Value> seg;\n    struct Empty {};\n    [[no_unique_address]]\
    \ std::conditional_t<hasTag, std::vector<Tag>, Empty> lazy;\n    using SearchTag\
    \ = std::conditional_t<!pushdown, Tag, Empty>;\n\n    decltype(auto) get_val(int\
    \ rt) {\n        if constexpr (pushdown) return static_cast<const Value&>(seg[rt]);\n\
    \        else return seg[rt] + lazy[rt];\n    }\n    decltype(auto) search_val(int\
    \ rt, const SearchTag &tag) {\n        if constexpr (pushdown) return static_cast<const\
    \ Value&>(seg[rt]);\n        else return get_val(rt) + tag;\n    }\n    void give_tag(int\
    \ rt, const auto &tag) requires (hasTag) {\n        if constexpr (pushdown) seg[rt]\
    \ = seg[rt] + tag;\n        lazy[rt] = lazy[rt] + tag;\n    }\n    void push(int\
    \ rt) requires (hasTag && pushdown) {\n        give_tag(rt << 1, lazy[rt]);\n\
    \        give_tag(rt << 1 | 1, lazy[rt]);\n        lazy[rt] = Tag();\n    }\n\
    \    void down(int p) requires (hasTag && pushdown) {\n        p += n;\n     \
    \   for (int h = lg; h > 0; --h)\n            push(p >> h);\n    }\n    void down(int\
    \ l, int r) requires (hasTag && pushdown) {\n        l += n, r += n;\n       \
    \ for (int h = lg; h > 0; --h) {\n            int a = l >> h, b = r >> h;\n  \
    \          push(a);\n            if (a != b) push(b);\n        }\n    }\n    void\
    \ up(int p) {\n        if constexpr (pushdown) {\n            seg[p] = seg[p <<\
    \ 1] + seg[p << 1 | 1];\n            if constexpr (hasTag) seg[p] = seg[p] + lazy[p];\n\
    \        }\n        else seg[p] = get_val(p << 1) + get_val(p << 1 | 1);\n   \
    \ }\n    void pull(int l, int r) requires (hasTag) {\n        l += n, r += n -\
    \ 1;\n        for (l >>= 1, r >>= 1; l != r; l >>= 1, r >>= 1)\n            up(l),\
    \ up(r);\n        for (; l >= 1; l >>= 1)\n            up(l);\n    }\n    auto\
    \ tag_prod(int p) requires (!pushdown) {\n        Tag res = Tag();\n        for\
    \ (p += n; p >= 1; p >>= 1)\n            res = res + lazy[p];\n        return\
    \ res;\n    }\n\n    int descend_left(int rt, const auto &condition) requires\
    \ (pushdown) {\n        while (rt < n) {\n            if constexpr (hasTag) push(rt);\n\
    \            rt <<= 1;\n            if (!condition(seg[rt])) ++rt;\n        }\n\
    \        return rt - n;\n    }\n    int descend_right(int rt, const auto &condition)\
    \ requires (pushdown) {\n        while (rt < n) {\n            if constexpr (hasTag)\
    \ push(rt);\n            rt = rt << 1 | 1;\n            if (!condition(seg[rt]))\
    \ --rt;\n        }\n        return rt - n;\n    }\n    int range_left_search_iter(int\
    \ L, int R, const auto &condition) requires (pushdown) {\n        if constexpr\
    \ (hasTag) down(L, R - 1);\n        int right[32], rn = 0;\n        for (L +=\
    \ n, R += n; L < R; L >>= 1, R >>= 1) {\n            if (L & 1) {\n          \
    \      if (condition(seg[L])) return descend_left(L, condition);\n           \
    \     ++L;\n            }\n            if (R & 1) right[rn++] = --R;\n       \
    \ }\n        while (rn--)\n            if (condition(seg[right[rn]]))\n      \
    \          return descend_left(right[rn], condition);\n        return -1;\n  \
    \  }\n    int range_right_search_iter(int L, int R, const auto &condition) requires\
    \ (pushdown) {\n        if constexpr (hasTag) down(L, R - 1);\n        int left[32],\
    \ ln = 0;\n        for (L += n, R += n; L < R; L >>= 1, R >>= 1) {\n         \
    \   if (L & 1) left[ln++] = L++;\n            if (R & 1) {\n                --R;\n\
    \                if (condition(seg[R])) return descend_right(R, condition);\n\
    \            }\n        }\n        while (ln--)\n            if (condition(seg[left[ln]]))\n\
    \                return descend_right(left[ln], condition);\n        return -1;\n\
    \    }\n    int range_left_search_rec(int L, int R, int l, int r, int rt, const\
    \ auto &condition, SearchTag tag) requires (!pushdown) {\n        if (R <= l ||\
    \ r <= L) return R;\n        if (L <= l && r <= R && !condition(search_val(rt,\
    \ tag))) return R;\n        if (r - l == 1) return l;\n        tag = tag + lazy[rt];\n\
    \        int mid = (l + r) >> 1;\n        int res = range_left_search_rec(L, R,\
    \ l, mid, rt << 1, condition, tag);\n        if (res != R) return res;\n     \
    \   return range_left_search_rec(L, R, mid, r, rt << 1 | 1, condition, tag);\n\
    \    }\n    int range_right_search_rec(int L, int R, int l, int r, int rt, const\
    \ auto &condition, SearchTag tag) requires (!pushdown) {\n        if (R <= l ||\
    \ r <= L) return L - 1;\n        if (L <= l && r <= R && !condition(search_val(rt,\
    \ tag))) return L - 1;\n        if (r - l == 1) return l;\n        tag = tag +\
    \ lazy[rt];\n        int mid = (l + r) >> 1;\n        int res = range_right_search_rec(L,\
    \ R, mid, r, rt << 1 | 1, condition, tag);\n        if (res != L - 1) return res;\n\
    \        return range_right_search_rec(L, R, l, mid, rt << 1, condition, tag);\n\
    \    }\n    void printnode(int rt) {\n        int l = rt, r = rt;\n        while\
    \ (l < n) l <<= 1;\n        while (r < n) r = r << 1 | 1;\n        l -= n, r -=\
    \ n - 1;\n        std::cerr << rt << \" [\" << l << \", \" << r << \"): \";\n\
    \        if constexpr (hasTag) std::cerr << \"val = \" << seg[rt] << \", tag =\
    \ \" << lazy[rt];\n        else std::cerr << seg[rt];\n        std::cerr << \"\
    \\n\";\n    }\npublic:\n    ZkwSegmentTree(const std::vector<Value> &data):\n\
    \        n(std::bit_ceil(data.size())), sz(data.size()), lg(std::__lg(n)), seg(n\
    \ << 1) {\n        if constexpr (hasTag) lazy.resize(n << 1);\n        std::copy(data.begin(),\
    \ data.end(), seg.begin() + n);\n        for (int i = n - 1; i > 0; --i) up(i);\n\
    \    }\n    ZkwSegmentTree(int size):\n        n(std::bit_ceil((unsigned int)size)),\
    \ sz(size), lg(std::__lg(n)), seg(n << 1) {\n        if constexpr (hasTag) lazy.resize(n\
    \ << 1);\n    }\n    Value get(int x) {\n        assert(0 <= x && x < sz);\n \
    \       if constexpr (hasTag) {\n            if constexpr (pushdown) down(x);\n\
    \            else return seg[x + n] + tag_prod(x);\n        }\n        return\
    \ seg[x + n];\n    }\n    Value all_prod() {\n        return get_val(1);\n   \
    \ }\n    Value range_prod(int l, int r) {\n        assert(0 <= l && r <= sz);\n\
    \        assert(l <= r);\n        if (l == r) return Value();\n        if constexpr\
    \ (hasTag && pushdown)\n            down(l, r - 1);\n        Value resl = Value(),\
    \ resr = Value();\n        int tl = l + n, tr = r + n - 1;\n        bool l_valid\
    \ = false, r_valid = false;\n        for (l += n, r += n; l < r; l >>= 1, r >>=\
    \ 1) {\n            if (l & 1) resl = resl + get_val(l++), l_valid = true;\n \
    \           if (r & 1) resr = get_val(--r) + resr, r_valid = true;\n         \
    \   if constexpr (!pushdown) {\n                tl >>= 1, tr >>= 1;\n        \
    \        if (l_valid) resl = resl + lazy[tl];\n                if (r_valid) resr\
    \ = resr + lazy[tr];\n            }\n        }\n        if constexpr (!pushdown)\
    \ {\n            for (tl >>= 1, tr >>= 1; tl >= 1; tl >>= 1, tr >>= 1) {\n   \
    \             if (l_valid) resl = resl + lazy[tl];\n                if (r_valid)\
    \ resr = resr + lazy[tr];\n            }\n        }\n        return resl + resr;\n\
    \    }\n    void modify(int x, Value v) {\n        assert(0 <= x && x < sz);\n\
    \        if constexpr (hasTag) {\n            if constexpr (pushdown) down(x);\n\
    \            else v = v - tag_prod(x);\n        }\n        for (seg[x += n] =\
    \ std::move(v); x > 1; up(x >>= 1));\n    }\n    void transform(int x, const auto\
    \ &func) {\n        assert(0 <= x && x < sz);\n        if constexpr (hasTag &&\
    \ pushdown)\n            down(x);\n        for (func(seg[x += n]); x > 1; up(x\
    \ >>= 1));\n    }\n    void range_transform(int l, int r, const auto &tag) requires\
    \ (hasTag) {\n        assert(0 <= l && r <= sz);\n        assert(l <= r);\n  \
    \      if (l < r) {\n            if constexpr (pushdown)\n                down(l,\
    \ r - 1);\n            int tl = l, tr = r;\n            for (l += n, r += n; l\
    \ < r; l >>= 1, r >>= 1) {\n                if (l & 1) give_tag(l++, tag);\n \
    \               if (r & 1) give_tag(--r, tag);\n            }\n            pull(tl,\
    \ tr);\n        }\n    }\n    int range_left_search(const auto &condition, int\
    \ l = -1, int r = -1) {\n        if (l == -1 && r == -1) l = 0, r = sz;\n    \
    \    assert(0 <= l && r <= sz);\n        assert(l <= r);\n        if (l == r)\
    \ return r;\n        if constexpr (pushdown) {\n            int res = range_left_search_iter(l,\
    \ r, condition);\n            return res == -1 ? r : res;\n        }\n       \
    \ else return range_left_search_rec(l, r, 0, n, 1, condition, SearchTag());\n\
    \    }\n    int range_right_search(const auto &condition, int l = -1, int r =\
    \ -1) {\n        if (l == -1 && r == -1) l = -1, r = sz - 1;\n        ++l, ++r;\n\
    \        assert(0 <= l && r <= sz);\n        assert(l <= r);\n        if (l ==\
    \ r) return l - 1;\n        if constexpr (pushdown) {\n            int res = range_right_search_iter(l,\
    \ r, condition);\n            return res == -1 ? l - 1 : res;\n        }\n   \
    \     else return range_right_search_rec(l, r, 0, n, 1, condition, SearchTag());\n\
    \    }\n    int descend(const auto &go_left) {\n        int rt = 1;\n        SearchTag\
    \ tag = SearchTag();\n        while (rt < n) {\n            if constexpr (hasTag\
    \ && pushdown) push(rt);\n            if constexpr (!pushdown) tag = tag + lazy[rt];\n\
    \            int lc = rt << 1, rc = lc | 1;\n            rt = go_left(search_val(lc,\
    \ tag), search_val(rc, tag)) ? lc : rc;\n        }\n        return rt - n;\n \
    \   }\n    void printinfo(int l, int r) {\n        assert(0 <= l && r <= sz);\n\
    \        assert(l <= r);\n        std::cerr << \"\\e[1;33mInfo [\" << l << \"\
    , \" << r << \"):\\n\";\n        if (l < r) {\n            for (l += n, r += n;\
    \ l < r; l >>= 1, r >>= 1) {\n                if (l & 1) printnode(l++);\n   \
    \             if (r & 1) printnode(--r);\n            }\n        }\n        std::cerr\
    \ << \"\\e[0m\\n\";\n    }\n    void printall() {\n        std::cerr << \"\\e[1;33mInfo\
    \ all:\\n\";\n        for (int i = 1; i < n + n; ++i)\n            printnode(i);\n\
    \        std::cerr << \"\\e[0m\\n\";\n    }\n};\n#line 5 \"Geometry/OfflineBichromaticNearest.hpp\"\
    \n\ntemplate<typename Dist, bool maintain_count>\nstruct BichromaticNearestResult;\n\
    \ntemplate<typename Dist>\nstruct BichromaticNearestResult<Dist, false> {\n  \
    \  int id = -1;\n    Dist dist2{};\n};\n\ntemplate<typename Dist>\nstruct BichromaticNearestResult<Dist,\
    \ true> {\n    int id = -1;\n    Dist dist2{};\n    int count = 0;\n};\n\ntemplate<\n\
    \    typename Point, // |x|, |y| <= C\n    bool maintain_count = false,\n    typename\
    \ MulT = typename Point::value_type, // 8C^2\n    typename EventT = MulT, // 8C^3\n\
    \    typename EventMulT = EventT, // 128C^5\n    MulT eps = std::is_same_v<typename\
    \ Point::value_type, MulT> ? MulT(Point::eps_val) : get_default_eps<MulT>(),\n\
    \    EventT event_eps = std::is_same_v<MulT, EventT> ? EventT(eps) : get_default_eps<EventT>()\n\
    >\nstruct OfflineBichromaticNearest {\n    using Result = BichromaticNearestResult<MulT,\
    \ maintain_count>;\n\n    struct Empty {};\n    struct CountData { int count =\
    \ 1; };\n    using MaybeCount = std::conditional_t<maintain_count, CountData,\
    \ Empty>;\n    struct BaseSite {\n        Point p;\n        int original_id;\n\
    \        [[no_unique_address]] MaybeCount data;\n    };\n    struct Site {\n \
    \       MulT x, y;\n        int id, yr;\n        [[no_unique_address]] MaybeCount\
    \ data;\n    };\n    struct Query {\n        MulT x, y;\n        int id;\n   \
    \ };\n    struct Event {\n        EventT num, den;\n        int u, v, w;\n   \
    \ };\n    struct EventGreater {\n        bool operator()(const Event &a, const\
    \ Event &b) const {\n            if constexpr (std::is_floating_point_v<EventT>)\
    \ {\n                EventT x = a.num / a.den, y = b.num / b.den;\n          \
    \      if (x != y) return x > y;\n            }\n            else {\n        \
    \        EventMulT x = EventMulT(a.num) * EventMulT(b.den);\n                EventMulT\
    \ y = EventMulT(b.num) * EventMulT(a.den);\n                if (x != y) return\
    \ x > y;\n            }\n            return std::tie(a.v, a.u, a.w) > std::tie(b.v,\
    \ b.u, b.w);\n        }\n    };\n    struct ActiveNoCount {\n        int first\
    \ = -1, last = -1;\n        friend ActiveNoCount operator+(const ActiveNoCount\
    \ &a, const ActiveNoCount &b) {\n            return {a.first != -1 ? a.first :\
    \ b.first, b.last != -1 ? b.last : a.last};\n        }\n    };\n    struct ActiveCount\
    \ {\n        int first = -1, last = -1;\n        int count = 0;\n        friend\
    \ ActiveCount operator+(const ActiveCount &a, const ActiveCount &b) {\n      \
    \      return {a.first != -1 ? a.first : b.first, b.last != -1 ? b.last : a.last,\
    \ a.count + b.count};\n        }\n    };\n\n    using ActiveInfo = std::conditional_t<maintain_count,\
    \ ActiveCount, ActiveNoCount>;\n\n    std::vector<BaseSite> base;\n\n    explicit\
    \ OfflineBichromaticNearest(const std::vector<Point> &blue) {\n        std::vector<int>\
    \ ord(blue.size());\n        std::iota(ord.begin(), ord.end(), 0);\n        std::ranges::sort(ord,\
    \ [&](int a, int b) {\n            if (blue[a].x != blue[b].x) return blue[a].x\
    \ < blue[b].x;\n            if (blue[a].y != blue[b].y) return blue[a].y < blue[b].y;\n\
    \            return a < b;\n        });\n        for (int id : ord) {\n      \
    \      if (base.empty() || base.back().p.x != blue[id].x || base.back().p.y !=\
    \ blue[id].y)\n                base.push_back({blue[id], id, {}});\n         \
    \   else if constexpr (maintain_count)\n                ++base.back().data.count;\n\
    \        }\n    }\n    static MulT sqdist(MulT ax, MulT ay, MulT bx, MulT by)\
    \ {\n        MulT dx = ax - bx, dy = ay - by;\n        return dx * dx + dy * dy;\n\
    \    }\n    static MulT sqdist(const Query &q, const Site &p) {\n        return\
    \ sqdist(q.x, q.y, p.x, p.y);\n    }\n    static MulT orient(const Site &a, const\
    \ Site &b, const Site &c) {\n        MulT x1 = b.x - a.x, y1 = b.y - a.y;\n  \
    \      MulT x2 = c.x - a.x, y2 = c.y - a.y;\n        return x1 * y2 - y1 * x2;\n\
    \    }\n    static MulT norm2(const Site &p) {\n        return p.x * p.x + p.y\
    \ * p.y;\n    }\n    static int multiplicity(const Site &p) {\n        if constexpr\
    \ (maintain_count) return p.data.count;\n        else return 1;\n    }\n    static\
    \ ActiveInfo active_leaf(int v, int count) {\n        if constexpr (maintain_count)\
    \ return {v, v, count};\n        else return {v, v};\n    }\n    static Event\
    \ make_event(const Site &a, const Site &b, const Site &c) {\n        MulT sa =\
    \ norm2(a), sb = norm2(b), sc = norm2(c);\n        EventT num = EventT(sb - sa)\
    \ * EventT(c.y - a.y) - EventT(sc - sa) * EventT(b.y - a.y);\n        EventT den\
    \ = EventT(2) * EventT(orient(a, b, c));\n        if (den < EventT(0)) num = -num,\
    \ den = -den;\n        return {num, den, a.id, b.id, c.id};\n    }\n    static\
    \ bool event_before_x(const Event &e, MulT x, bool inclusive) {\n        if constexpr\
    \ (std::is_floating_point_v<EventT>) {\n            int c = Geometry<EventT, event_eps>::cmp(e.num\
    \ / e.den, EventT(x));\n            return inclusive ? c <= 0 : c < 0;\n     \
    \   }\n        else {\n            EventMulT lhs = EventMulT(e.num);\n       \
    \     EventMulT rhs = EventMulT(x) * EventMulT(e.den);\n            return inclusive\
    \ ? lhs <= rhs : lhs < rhs;\n        }\n    }\n\n    // inclusive_site_x = true\
    \  => site.x <= query.x\n    // inclusive_site_x = false => site.x <  query.x\n\
    \    std::vector<Result> sweep(const std::vector<Point> &red, int sx, bool inclusive_site_x)\
    \ const {\n        int n = int(base.size()), qn = int(red.size());\n\n       \
    \ std::vector<Site> p(n);\n        for (int i = 0; i < n; ++i) {\n           \
    \ p[i].x = MulT(sx) * MulT(base[i].p.x);\n            p[i].y = MulT(base[i].p.y);\n\
    \            p[i].id = i;\n            p[i].yr = -1;\n            if constexpr\
    \ (maintain_count) p[i].data.count = base[i].data.count;\n        }\n\n      \
    \  std::vector<int> yo(n);\n        std::iota(yo.begin(), yo.end(), 0);\n    \
    \    std::ranges::sort(yo, [&](int a, int b) {\n            if (p[a].y != p[b].y)\
    \ return p[a].y < p[b].y;\n            return a < b;\n        });\n        int\
    \ yn = 0;\n        for (int i = 0; i < n; ++i) {\n            if (i == 0 || p[yo[i]].y\
    \ != p[yo[i - 1]].y) ++yn;\n            p[yo[i]].yr = yn - 1;\n        }\n\n \
    \       std::vector<Query> q(qn);\n        for (int i = 0; i < qn; ++i)\n    \
    \        q[i] = {MulT(sx) * MulT(red[i].x), MulT(red[i].y), i};\n\n        std::vector<int>\
    \ po(n), qo(qn);\n        std::iota(po.begin(), po.end(), 0);\n        std::iota(qo.begin(),\
    \ qo.end(), 0);\n        std::ranges::sort(po, [&](int a, int b) {\n         \
    \   if (p[a].x != p[b].x) return p[a].x < p[b].x;\n            if (p[a].y != p[b].y)\
    \ return p[a].y < p[b].y;\n            return a < b;\n        });\n        std::ranges::sort(qo,\
    \ [&](int a, int b) {\n            if (q[a].x != q[b].x) return q[a].x < q[b].x;\n\
    \            return a < b;\n        });\n\n        ZkwSegmentTree<ActiveInfo>\
    \ tr(yn);\n        std::priority_queue<Event, std::vector<Event>, EventGreater>\
    \ pq;\n\n        auto has = [](const ActiveInfo &x) { return x.first != -1; };\n\
    \        auto at = [&](int r) { return tr.get(r).first; };\n        auto active\
    \ = [&](int v) { return v >= 0 && at(p[v].yr) == v; };\n        auto prev = [&](int\
    \ r) {\n            if (r == 0) return -1;\n            int x = tr.range_right_search(has,\
    \ -1, r - 1);\n            return x == -1 ? -1 : at(x);\n        };\n        auto\
    \ next = [&](int r) {\n            int x = tr.range_left_search(has, r + 1, yn);\n\
    \            return x == yn ? -1 : at(x);\n        };\n        auto neigh = [&](int\
    \ v) { return std::pair(prev(p[v].yr), next(p[v].yr)); };\n        auto schedule\
    \ = [&](int v) {\n            if (!active(v)) return;\n            auto [u, w]\
    \ = neigh(v);\n            if (u != -1 && w != -1 && Geometry<MulT, eps>::sign(orient(p[u],\
    \ p[v], p[w])) < 0)\n                pq.push(make_event(p[u], p[v], p[w]));\n\
    \        };\n        auto valid = [&](const Event &e) {\n            if (!active(e.u)\
    \ || !active(e.v) || !active(e.w)) return false;\n            auto [u, w] = neigh(e.v);\n\
    \            return u == e.u && w == e.w;\n        };\n        auto erase = [&](int\
    \ v) {\n            auto [u, w] = neigh(v);\n            tr.modify(p[v].yr, ActiveInfo());\n\
    \            schedule(u), schedule(w);\n        };\n        auto process = [&](MulT\
    \ x, bool inclusive) {\n            while (!pq.empty() && event_before_x(pq.top(),\
    \ x, inclusive)) {\n                Event e = pq.top();\n                pq.pop();\n\
    \                if (valid(e)) erase(e.v);\n            }\n        };\n      \
    \  auto insert = [&](int v) {\n            int r = p[v].yr;\n            int u\
    \ = prev(r), w = next(r);\n            tr.modify(r, active_leaf(v, multiplicity(p[v])));\n\
    \            schedule(u), schedule(v), schedule(w);\n        };\n\n        auto\
    \ nearest = [&](const Query &x) -> Result {\n            if (!has(tr.all_prod()))\
    \ return {};\n\n            int r = tr.descend([&](const ActiveInfo &a, const\
    \ ActiveInfo &b) {\n                if (!has(a)) return false;\n             \
    \   if (!has(b)) return true;\n                return Geometry<MulT, eps>::cmp(sqdist(x,\
    \ p[a.last]), sqdist(x, p[b.first])) <= 0;\n            });\n\n            int\
    \ v = at(r);\n            MulT d = sqdist(x, p[v]);\n            if constexpr\
    \ (!maintain_count) return {base[p[v].id].original_id, d};\n            else {\n\
    \                auto left_tied = [&](const ActiveInfo &a) {\n               \
    \     return has(a) && Geometry<MulT, eps>::cmp(sqdist(x, p[a.last]), d) == 0;\n\
    \                };\n                auto right_tied = [&](const ActiveInfo &a)\
    \ {\n                    return has(a) && Geometry<MulT, eps>::cmp(sqdist(x, p[a.first]),\
    \ d) == 0;\n                };\n                int l = tr.range_left_search(left_tied,\
    \ 0, r + 1);\n                int rr = tr.range_right_search(right_tied, r - 1,\
    \ yn - 1);\n                int count = tr.range_prod(l, rr + 1).count;\n    \
    \            return {base[p[v].id].original_id, d, count};\n            }\n  \
    \      };\n\n        std::vector<Result> ans(qn);\n        int i = 0, j = 0;\n\
    \        auto insert_at = [&](MulT x) {\n            while (i < n && p[po[i]].x\
    \ == x) insert(po[i++]);\n        };\n        auto query_at = [&](MulT x) {\n\
    \            while (j < qn && q[qo[j]].x == x) {\n                ans[q[qo[j]].id]\
    \ = nearest(q[qo[j]]);\n                ++j;\n            }\n        };\n\n  \
    \      while (i < n || j < qn) {\n            MulT x;\n            if (i == n)\
    \ x = q[qo[j]].x;\n            else if (j == qn) x = p[po[i]].x;\n           \
    \ else x = std::min(p[po[i]].x, q[qo[j]].x);\n\n            process(x, false);\n\
    \n            if constexpr (maintain_count) {\n                if (inclusive_site_x)\n\
    \                    insert_at(x), process(x, false), query_at(x);\n         \
    \       else\n                    query_at(x), insert_at(x), process(x, false);\n\
    \                process(x, true);\n            }\n            else {\n      \
    \          if (inclusive_site_x)\n                    insert_at(x), process(x,\
    \ true), query_at(x);\n                else\n                    query_at(x),\
    \ insert_at(x), process(x, true);\n            }\n        }\n        return ans;\n\
    \    }\n\n    std::vector<Result> query(const std::vector<Point> &red) const {\n\
    \        std::vector<Result> ans(red.size());\n        if (base.empty()) return\
    \ ans;\n        auto l = sweep(red, +1, true);\n        auto r = sweep(red, -1,\
    \ !maintain_count);\n        for (int i = 0; i < int(red.size()); ++i) {\n   \
    \         if (l[i].id == -1) {\n                ans[i] = r[i];\n             \
    \   continue;\n            }\n            if (r[i].id == -1) {\n             \
    \   ans[i] = l[i];\n                continue;\n            }\n            int\
    \ c = Geometry<MulT, eps>::cmp(l[i].dist2, r[i].dist2);\n            if (c < 0)\
    \ ans[i] = l[i];\n            else if (c > 0) ans[i] = r[i];\n            else\
    \ if constexpr (maintain_count)\n                ans[i] = {l[i].id, l[i].dist2,\
    \ l[i].count + r[i].count};\n            else\n                ans[i] = l[i];\n\
    \        }\n        return ans;\n    }\n};\n#line 2 \"Misc/i256.hpp\"\n\nstruct\
    \ i256 {\n    using u64 = std::uint64_t;\n    using u128 = unsigned __int128;\n\
    \    using s128 = __int128_t;\n\n    std::array<u64, 4> a{};\n\n    constexpr\
    \ i256() = default;\n\n    template <class T>\n    requires (std::is_integral_v<T>\
    \ && sizeof(T) <= 8)\n    constexpr i256(T x) {\n        if constexpr (std::is_signed_v<T>)\
    \ {\n            s128 y = static_cast<s128>(x);\n            u128 z = static_cast<u128>(y);\n\
    \            a[0] = static_cast<u64>(z);\n            a[1] = static_cast<u64>(z\
    \ >> 64);\n            a[2] = a[3] = (y < 0 ? ~u64(0) : u64(0));\n        } else\
    \ {\n            u128 z = static_cast<u128>(x);\n            a[0] = static_cast<u64>(z);\n\
    \            a[1] = static_cast<u64>(z >> 64);\n            a[2] = a[3] = 0;\n\
    \        }\n    }\n\n    constexpr i256(s128 x) {\n        u128 z = static_cast<u128>(x);\n\
    \        a[0] = static_cast<u64>(z);\n        a[1] = static_cast<u64>(z >> 64);\n\
    \        a[2] = a[3] = (x < 0 ? ~u64(0) : u64(0));\n    }\n\n    constexpr i256(u128\
    \ x) {\n        a[0] = static_cast<u64>(x);\n        a[1] = static_cast<u64>(x\
    \ >> 64);\n        a[2] = a[3] = 0;\n    }\n\n    constexpr bool negative() const\
    \ {\n        return a[3] >> 63;\n    }\n\n    static constexpr u128 abs128(s128\
    \ x) {\n        u128 u = static_cast<u128>(x);\n        return x < 0 ? (~u + 1)\
    \ : u;\n    }\n\n    // Fast exact signed 128 x 128 -> signed 256.\n    static\
    \ constexpr i256 mul128(s128 x, s128 y) {\n        u128 ux = abs128(x), uy = abs128(y);\n\
    \        u64 x0 = static_cast<u64>(ux), x1 = static_cast<u64>(ux >> 64);\n   \
    \     u64 y0 = static_cast<u64>(uy), y1 = static_cast<u64>(uy >> 64);\n\n    \
    \    i256 r;\n        // Base-2^64 schoolbook multiplication, only 2 x 2 limbs.\n\
    \        r.a = {};\n        u64 xs[2] = {x0, x1}, ys[2] = {y0, y1};\n        for\
    \ (int i = 0; i < 2; ++i) {\n            u64 c = 0;\n            for (int j =\
    \ 0; j < 2; ++j) {\n                u128 cur = u128(xs[i]) * ys[j] + r.a[i + j]\
    \ + c;\n                r.a[i + j] = static_cast<u64>(cur);\n                c\
    \ = static_cast<u64>(cur >> 64);\n            }\n            int k = i + 2;\n\
    \            while (c && k < 4) {\n                u128 cur = u128(r.a[k]) + c;\n\
    \                r.a[k] = static_cast<u64>(cur);\n                c = static_cast<u64>(cur\
    \ >> 64);\n                ++k;\n            }\n        }\n        if ((x < 0)\
    \ != (y < 0)) r = -r;\n        return r;\n    }\n\n    friend constexpr bool operator==(const\
    \ i256&, const i256&) = default;\n\n    friend constexpr bool operator<(const\
    \ i256& x, const i256& y) {\n        bool sx = x.negative(), sy = y.negative();\n\
    \        if (sx != sy) return sx;\n        for (int i = 3; i >= 0; --i)\n    \
    \        if (x.a[i] != y.a[i])\n                return x.a[i] < y.a[i];\n    \
    \    return false;\n    }\n\n    friend constexpr bool operator!=(const i256&\
    \ x, const i256& y) { return !(x == y); }\n    friend constexpr bool operator>(const\
    \ i256& x, const i256& y) { return y < x; }\n    friend constexpr bool operator<=(const\
    \ i256& x, const i256& y) { return !(y < x); }\n    friend constexpr bool operator>=(const\
    \ i256& x, const i256& y) { return !(x < y); }\n\n    constexpr i256 operator-()\
    \ const {\n        i256 r;\n        for (int i = 0; i < 4; ++i) r.a[i] = ~a[i];\n\
    \        for (int i = 0; i < 4; ++i)\n            if (++r.a[i] != 0) break;\n\
    \        return r;\n    }\n\n    constexpr i256& operator+=(const i256& o) {\n\
    \        u64 carry = 0;\n        for (int i = 0; i < 4; ++i) {\n            u128\
    \ cur = u128(a[i]) + o.a[i] + carry;\n            a[i] = static_cast<u64>(cur);\n\
    \            carry = static_cast<u64>(cur >> 64);\n        }\n        return *this;\n\
    \    }\n\n    constexpr i256& operator-=(const i256& o) {\n        return *this\
    \ += -o;\n    }\n\n    constexpr i256& operator*=(const i256& o) {\n        std::array<u64,\
    \ 4> r{};\n        for (int i = 0; i < 4; ++i) {\n            u64 carry = 0;\n\
    \            for (int j = 0; i + j < 4; ++j) {\n                u128 cur = u128(a[i])\
    \ * o.a[j] + r[i + j] + carry;\n                r[i + j] = static_cast<u64>(cur);\n\
    \                carry = static_cast<u64>(cur >> 64);\n            }\n       \
    \ }\n        a = r;\n        return *this;\n    }\n\n    friend constexpr i256\
    \ operator+(i256 x, const i256& y) { return x += y; }\n    friend constexpr i256\
    \ operator-(i256 x, const i256& y) { return x -= y; }\n    friend constexpr i256\
    \ operator*(i256 x, const i256& y) { return x *= y; }\n};\n#line 6 \"test/0_custom/OfflineBichromaticNearest.test.cpp\"\
    \n\nusing Point = Pt<long long>;\n\nPoint gen_point(int MAXC) {\n    static std::mt19937\
    \ rng(880301);\n    Point res;\n    res.x = int(rng() % (2 * MAXC + 1)) - MAXC;\
    \ \n    res.y = int(rng() % (2 * MAXC + 1)) - MAXC; \n    return res;\n}\n\nvoid\
    \ test() {\n    std::vector<int> sz{1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 5, 10, 100,\
    \ 1000, 2000};\n    std::vector<int> maxc{10, 1000, 1'000'000'000};\n    for (int\
    \ MAXC : maxc)\n        for (int n : sz) {\n            std::vector<Point> arr(n);\n\
    \            for (auto &p : arr) p = gen_point(MAXC);\n            OfflineBichromaticNearest<Point,\
    \ true, long long, __int128, i256> solver(arr);\n            for (int m : sz)\
    \ {\n                std::vector<Point> qry(m);\n                for (auto &p\
    \ : qry) p = gen_point(MAXC);\n                std::vector<std::pair<long long,\
    \ int>> ans(m, std::make_pair(9ll * MAXC * MAXC, 0));\n                for (int\
    \ i = 0; i < m; ++i)\n                    for (auto &p : arr) {\n            \
    \            if (dist2(p, qry[i]) < ans[i].first)\n                          \
    \  ans[i] = std::make_pair(dist2(p, qry[i]), 1);\n                        else\
    \ if (dist2(p, qry[i]) == ans[i].first)\n                            ++ans[i].second;\n\
    \                    }\n                auto res = solver.query(qry);\n      \
    \          for (int i = 0; i < m; ++i) {\n                    assert(res[i].dist2\
    \ == ans[i].first);\n                    assert(res[i].count == ans[i].second);\n\
    \                }\n            }\n        }\n}\n\nint main() {\n    test();\n\
    \    int a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << \"\\n\";\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n#include \"assumption.hpp\"\
    \n\n#include \"Geometry/OfflineBichromaticNearest.hpp\"\n#include \"Misc/i256.hpp\"\
    \n\nusing Point = Pt<long long>;\n\nPoint gen_point(int MAXC) {\n    static std::mt19937\
    \ rng(880301);\n    Point res;\n    res.x = int(rng() % (2 * MAXC + 1)) - MAXC;\
    \ \n    res.y = int(rng() % (2 * MAXC + 1)) - MAXC; \n    return res;\n}\n\nvoid\
    \ test() {\n    std::vector<int> sz{1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 5, 10, 100,\
    \ 1000, 2000};\n    std::vector<int> maxc{10, 1000, 1'000'000'000};\n    for (int\
    \ MAXC : maxc)\n        for (int n : sz) {\n            std::vector<Point> arr(n);\n\
    \            for (auto &p : arr) p = gen_point(MAXC);\n            OfflineBichromaticNearest<Point,\
    \ true, long long, __int128, i256> solver(arr);\n            for (int m : sz)\
    \ {\n                std::vector<Point> qry(m);\n                for (auto &p\
    \ : qry) p = gen_point(MAXC);\n                std::vector<std::pair<long long,\
    \ int>> ans(m, std::make_pair(9ll * MAXC * MAXC, 0));\n                for (int\
    \ i = 0; i < m; ++i)\n                    for (auto &p : arr) {\n            \
    \            if (dist2(p, qry[i]) < ans[i].first)\n                          \
    \  ans[i] = std::make_pair(dist2(p, qry[i]), 1);\n                        else\
    \ if (dist2(p, qry[i]) == ans[i].first)\n                            ++ans[i].second;\n\
    \                    }\n                auto res = solver.query(qry);\n      \
    \          for (int i = 0; i < m; ++i) {\n                    assert(res[i].dist2\
    \ == ans[i].first);\n                    assert(res[i].count == ans[i].second);\n\
    \                }\n            }\n        }\n}\n\nint main() {\n    test();\n\
    \    int a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << \"\\n\";\n\
    }\n"
  dependsOn:
  - assumption.hpp
  - Geometry/OfflineBichromaticNearest.hpp
  - Geometry/base.hpp
  - DataStructure/ZkwSegmentTree.hpp
  - Misc/i256.hpp
  isVerificationFile: true
  path: test/0_custom/OfflineBichromaticNearest.test.cpp
  requiredBy: []
  timestamp: '2026-10-01 14:29:05+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/0_custom/OfflineBichromaticNearest.test.cpp
layout: document
redirect_from:
- /verify/test/0_custom/OfflineBichromaticNearest.test.cpp
- /verify/test/0_custom/OfflineBichromaticNearest.test.cpp.html
title: test/0_custom/OfflineBichromaticNearest.test.cpp
---
