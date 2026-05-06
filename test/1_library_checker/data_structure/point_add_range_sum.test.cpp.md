---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/SegmentTree.hpp
    title: DataStructure/SegmentTree.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/point_add_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n#line\
    \ 2 \"default_code.hpp\"\n\n#include <bits/stdc++.h>\nusing namespace std;\ntypedef\
    \ long long ll;\ntypedef pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n#define\
    \ X first\n#define Y second\n#define SZ(a) ((int)a.size())\n#define ALL(v) v.begin(),\
    \ v.end()\ntemplate<class A, class B>\nostream& operator<<(ostream& os, const\
    \ pair<A, B> &a) {\n    os << \"(\" << a.first << \", \" << a.second << \")\"\
    ;\n    return os;\n}\ntemplate <typename T>\nconcept PrintableContainer = requires(T&\
    \ a) {\n    a.begin();\n    a.end();\n} && !std::same_as<std::remove_cvref_t<T>,\
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
    }\n#line 3 \"test/1_library_checker/data_structure/point_add_range_sum.test.cpp\"\
    \n\n#line 2 \"DataStructure/SegmentTree.hpp\"\n\ntemplate<typename Value = int,\
    \ typename Tag = void, bool pushdown = true>\nclass SegmentTree {\n    static\
    \ constexpr bool hasTag = !std::is_same_v<Tag, void>;\n    static_assert(pushdown\
    \ || hasTag, \"Lazy tag must exist when pushdown is false\");\n    int n;\n  \
    \  vector<Value> seg;\n    struct Empty {};\n    [[no_unique_address]] std::conditional_t<hasTag,\
    \ std::vector<Tag>, Empty> lazy;\n    Value get_val(int rt) {\n        if constexpr\
    \ (pushdown) return seg[rt];\n        else return seg[rt] + lazy[rt];\n    }\n\
    \    void up(int rt) {\n        seg[rt] = get_val(rt << 1) + get_val(rt << 1 |\
    \ 1);\n    }\n    void give_tag(int rt, auto tag) requires (hasTag) {\n      \
    \  if constexpr (pushdown) seg[rt] = seg[rt] + tag;\n        lazy[rt] = lazy[rt]\
    \ + tag;\n    }\n    void down(int rt) requires (hasTag && pushdown) {\n     \
    \   give_tag(rt << 1, lazy[rt]);\n        give_tag(rt << 1 | 1, lazy[rt]);\n \
    \       lazy[rt] = Tag();\n    }\n    void initialize(int l, int r, int rt, const\
    \ vector<Value> &data) {\n        if (r - l == 1) \n            return seg[rt]\
    \ = data[l], void();\n        int mid = (l + r) >> 1;\n        initialize(l, mid,\
    \ rt << 1, data);\n        initialize(mid, r, rt << 1 | 1, data);\n        up(rt);\n\
    \    }\n    Value range_prod(int L, int R, int l, int r, int rt) {\n        if\
    \ (L <= l && R >= r)\n            return get_val(rt);\n        if constexpr (hasTag\
    \ && pushdown) down(rt);\n        int mid = (l + r) >> 1;\n        if constexpr\
    \ (pushdown) {\n            if (R <= mid) return range_prod(L, R, l, mid, rt <<\
    \ 1);\n            if (L >= mid) return range_prod(L, R, mid, r, rt << 1 | 1);\n\
    \            return range_prod(L, R, l, mid, rt << 1) + range_prod(L, R, mid,\
    \ r, rt << 1 | 1); \n        }\n        else {\n            if (R <= mid) return\
    \ range_prod(L, R, l, mid, rt << 1) + lazy[rt];\n            if (L >= mid) return\
    \ range_prod(L, R, mid, r, rt << 1 | 1) + lazy[rt];\n            return range_prod(L,\
    \ R, l, mid, rt << 1) + range_prod(L, R, mid, r, rt << 1 | 1) + lazy[rt];\n  \
    \      }\n    }\n    void modify(int x, int l, int r, int rt, const Value &v)\
    \ {\n        if (r - l == 1)\n            return seg[rt] = v, void();\n      \
    \  if constexpr (hasTag && pushdown) down(rt);\n        int mid = (l + r) >> 1;\n\
    \        if constexpr (pushdown) {\n            if (x < mid) modify(x, l, mid,\
    \ rt << 1, v);\n            else modify(x, mid, r, rt << 1 | 1, v);\n        }\n\
    \        else {\n            if (x < mid) modify(x, l, mid, rt << 1, v - lazy[rt]);\n\
    \            else modify(x, mid, r, rt << 1 | 1, v - lazy[rt]);\n        }\n \
    \       up(rt);\n    }\n    void transform(int x, int l, int r, int rt, const\
    \ auto &func) {\n        if (r - l == 1)\n            return func(seg[rt]), void();\n\
    \        if constexpr (hasTag && pushdown) down(rt);\n        int mid = (l + r)\
    \ >> 1;\n        if (x < mid) transform(x, l, mid, rt << 1, func);\n        else\
    \ transform(x, mid, r, rt << 1 | 1, func);\n        up(rt);\n    }\n    void range_transform(int\
    \ L, int R, int l, int r, int rt, const auto &tag) requires (hasTag) {\n     \
    \   if (L <= l && R >= r)\n            return give_tag(rt, tag);\n        if constexpr\
    \ (pushdown) down(rt);\n        int mid = (l + r) >> 1;\n        if (L < mid)\
    \ range_transform(L, R, l, mid, rt << 1, tag);\n        if (R > mid) range_transform(L,\
    \ R, mid, r, rt << 1 | 1, tag);\n        up(rt);\n    }\n    void range_transform_beats(int\
    \ L, int R, int l, int r, int rt, const auto &tag, const auto &tag_condition,\
    \ auto... tag_sum) requires (hasTag) {\n        if (L <= l && R >= r && tag_condition([&]{\
    \ if constexpr(pushdown) return seg[rt]; else return get_val(rt) + (..., tag_sum);\
    \ }()))\n            return give_tag(rt, tag);\n        assert(r - l > 1);\n \
    \       if constexpr (pushdown) down(rt);\n        else ((tag_sum = tag_sum +\
    \ lazy[rt]), ...);\n        int mid = (l + r) >> 1;\n        if (L < mid) range_transform_beats(L,\
    \ R, l, mid, rt << 1, tag, tag_condition, tag_sum...);\n        if (R > mid) range_transform_beats(L,\
    \ R, mid, r, rt << 1 | 1, tag, tag_condition, tag_sum...);\n        up(rt);\n\
    \    }\n    int range_left_search(int L, int R, int l, int r, int rt, const auto\
    \ &condition, auto... tag_sum) {\n        if (r - l == 1) {\n            if (!condition([&]{\
    \ if constexpr(pushdown) return seg[rt]; else return get_val(rt) + (..., tag_sum);\
    \ }()))\n                return R;\n            return l;\n        }\n       \
    \ int mid = (l + r) >> 1;\n        if constexpr (hasTag && pushdown) down(rt);\n\
    \        if constexpr (!pushdown) ((tag_sum = tag_sum + lazy[rt]), ...);\n   \
    \     if (L <= l && R >= r) {\n            if (condition([&]{ if constexpr(pushdown)\
    \ return seg[rt << 1]; else return get_val(rt << 1) + (..., tag_sum); }()))\n\
    \                return range_left_search(L, R, l, mid, rt << 1, condition, tag_sum...);\n\
    \            return range_left_search(L, R, mid, r, rt << 1 | 1, condition, tag_sum...);\n\
    \        }\n        int left = R;\n        if (L < mid) left = range_left_search(L,\
    \ R, l, mid, rt << 1, condition, tag_sum...);\n        if (left == R) {\n    \
    \        if (R > mid) return range_left_search(L, R, mid, r, rt << 1 | 1, condition,\
    \ tag_sum...);\n            return R;\n        }\n        return left;\n    }\n\
    \    int range_right_search(int L, int R, int l, int r, int rt, const auto &condition,\
    \ auto... tag_sum) {\n        if (r - l == 1) {\n            if (!condition([&]{\
    \ if constexpr(pushdown) return seg[rt]; else return get_val(rt) + (..., tag_sum);\
    \ }()))\n                return L - 1;\n            return l;\n        }\n   \
    \     int mid = (l + r) >> 1;\n        if constexpr (hasTag && pushdown) down(rt);\n\
    \        if constexpr (!pushdown) ((tag_sum = tag_sum + lazy[rt]), ...);\n   \
    \     if (L <= l && R >= r) {\n            if (condition([&]{ if constexpr(pushdown)\
    \ return seg[rt << 1 | 1]; else return get_val(rt << 1 | 1) + (..., tag_sum);\
    \ }()))\n                return range_right_search(L, R, mid, r, rt << 1 | 1,\
    \ condition, tag_sum...);\n            return range_right_search(L, R, l, mid,\
    \ rt << 1, condition, tag_sum...);\n        }\n        int right = L - 1;\n  \
    \      if (R > mid) right = range_right_search(L, R, mid, r, rt << 1 | 1, condition,\
    \ tag_sum...);\n        if (right == L - 1) {\n            if (L < mid) return\
    \ range_right_search(L, R, l, mid, rt << 1, condition, tag_sum...);\n        \
    \    return L - 1;\n        }\n        return right;\n    }\n    Value get(int\
    \ x, int l, int r, int rt) {\n        [[no_unique_address]] std::conditional_t<!pushdown,\
    \ Tag, Empty> tag;\n        while (r - l > 1) {\n            if constexpr (hasTag\
    \ && pushdown) down(rt);\n            if constexpr (!pushdown) tag = tag + lazy[rt];\n\
    \            int mid = (l + r) >> 1;\n            if (x < mid) r = mid, rt = rt\
    \ << 1;\n            else l = mid, rt = rt << 1 | 1;\n        }\n        if constexpr\
    \ (pushdown) return seg[rt];\n        else return get_val(rt) + tag;\n    }\n\
    \    void printnode(int l, int r, int rt) {\n        std::cerr << \"[\" << l <<\
    \ \", \" << r << \"): \";\n        if constexpr (hasTag) std::cerr << \"val =\
    \ \" << seg[rt] << \", tag = \" << lazy[rt];\n        else std::cerr << seg[rt];\n\
    \        std::cerr << \"\\n\";\n    }\n    void printinfo(int L, int R, int l,\
    \ int r, int rt) {\n        printnode(l, r, rt);\n        if (L <= l && R >= r)\n\
    \            return;\n        int mid = (l + r) >> 1;\n        if (L < mid) printinfo(L,\
    \ R, l, mid, rt << 1);\n        if (R > mid) printinfo(L, R, mid, r, rt << 1 |\
    \ 1);\n    }\n    void printall(int l, int r, int rt) {\n        printnode(l,\
    \ r, rt);\n        if (r - l == 1) return;\n        int mid = (l + r) >> 1;\n\
    \        printall(l, mid, rt << 1);\n        printall(mid, r, rt << 1 | 1);\n\
    \    }\n    public:\n    SegmentTree(const vector<Value> &data): n(data.size()),\
    \ seg(n << 2) { \n        if constexpr (hasTag) lazy.resize(n << 2); \n      \
    \  initialize(0, n, 1, data);\n    }\n    SegmentTree(int size): SegmentTree(vector<Value>(size))\
    \ {}\n    Value get(int x) {\n        assert(0 <= x && x < n);\n        return\
    \ get(x, 0, n, 1);\n    }\n    Value range_prod(int l, int r) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        if (l == r) return Value();\n\
    \        return range_prod(l, r, 0, n, 1);\n    }\n    void modify(int x, const\
    \ Value &v) {\n        assert(0 <= x && x < n);\n        modify(x, 0, n, 1, v);\n\
    \    }\n    void transform(int x, const auto &func) {\n        assert(0 <= x &&\
    \ x < n);\n        transform(x, 0, n, 1, func);\n    }\n    void range_transform(int\
    \ l, int r, const auto &tag) requires (hasTag) {\n        assert(0 <= l && r <=\
    \ n);\n        assert(l <= r);\n        if (l < r)\n            range_transform(l,\
    \ r, 0, n, 1, tag);\n    }\n    void range_transform_beats(int l, int r, const\
    \ auto &tag, const auto &tag_condition) requires (hasTag) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        if (l < r)\n            range_transform_beats(l,\
    \ r, 0, n, 1, tag, tag_condition);\n    }\n    /*\n       For the given element\
    \ range [l, r)\n       Perform segment tree binary search within the range with\
    \ left half first \n     */\n    int range_left_search(const auto &condition,\
    \ int l = -1, int r = -1) {\n        if (l == -1 && r == -1) l = 0, r = n;\n \
    \       assert(0 <= l && r <= n);\n        assert(l <= r);\n        if (l == r)\
    \ return r;\n        return range_left_search(l, r, 0, n, 1, condition);\n   \
    \ }\n    /*\n       For the given element range (l, r]\n       Perform segment\
    \ tree binary search within the range with right half first \n     */\n    int\
    \ range_right_search(const auto &condition, int l = -1, int r = -1) {\n      \
    \  if (l == -1 && r == -1) l = -1, r = n - 1;\n        ++l, ++r;\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        if (l == r) return l - 1;\n\
    \        return range_right_search(l, r, 0, n, 1, condition);\n    }\n    void\
    \ printinfo(int l, int r) {\n        assert(0 <= l && r <= n);\n        assert(l\
    \ <= r);\n        std::cerr << \"\\e[1;33mInfo [\" << l << \", \" << r << \"):\\\
    n\";\n        if (l < r) \n            printinfo(l, r, 0, n, 1);\n        cerr\
    \ << \"\\e[0m\\n\";\n    }\n    void printall() {\n        std::cerr << \"\\e[1;33mInfo\
    \ all:\\n\";\n        printall(0, n, 1);\n        cerr << \"\\e[0m\\n\";\n   \
    \ }\n};\n#line 5 \"test/1_library_checker/data_structure/point_add_range_sum.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n  \
    \  cin >> n >> q;\n    vector<ll> arr(n);\n    for (auto &v : arr)\n        cin\
    \ >> v;\n    SegmentTree<ll> seg(arr);\n    while (q--) {\n        int t;\n  \
    \      cin >> t;\n        if (t == 0) {\n            int p, x;\n            cin\
    \ >> p >> x;\n            seg.transform(p, [&](ll &a) {\n                a +=\
    \ x;\n            });\n        }\n        else {\n            int l, r;\n    \
    \        cin >> l >> r;\n            cout << seg.range_prod(l, r) << \"\\n\";\n\
    \        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    #include \"default_code.hpp\"\n\n#include \"DataStructure/SegmentTree.hpp\"\n\n\
    int main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n    cin\
    \ >> n >> q;\n    vector<ll> arr(n);\n    for (auto &v : arr)\n        cin >>\
    \ v;\n    SegmentTree<ll> seg(arr);\n    while (q--) {\n        int t;\n     \
    \   cin >> t;\n        if (t == 0) {\n            int p, x;\n            cin >>\
    \ p >> x;\n            seg.transform(p, [&](ll &a) {\n                a += x;\n\
    \            });\n        }\n        else {\n            int l, r;\n         \
    \   cin >> l >> r;\n            cout << seg.range_prod(l, r) << \"\\n\";\n   \
    \     }\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - DataStructure/SegmentTree.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/point_add_range_sum.test.cpp
  requiredBy: []
  timestamp: '2026-05-04 15:56:36+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/point_add_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/point_add_range_sum.test.cpp
- /verify/test/1_library_checker/data_structure/point_add_range_sum.test.cpp.html
title: test/1_library_checker/data_structure/point_add_range_sum.test.cpp
---
