---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/ZkwSegmentTree.hpp
    title: DataStructure/ZkwSegmentTree.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/static_rmq_zkw.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#line 2 \"default_code.hpp\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\ntypedef long long ll;\ntypedef\
    \ pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n#define X first\n#define Y second\n\
    #define SZ(a) ((int)a.size())\n#define ALL(v) v.begin(), v.end()\ntemplate<class\
    \ A, class B>\nostream& operator<<(ostream& os, const pair<A, B> &a) {\n    os\
    \ << \"(\" << a.first << \", \" << a.second << \")\";\n    return os;\n}\ntemplate\
    \ <typename T>\nconcept PrintableContainer = requires(T& a) {\n    a.begin();\n\
    \    a.end();\n} && !std::same_as<std::remove_cvref_t<T>, std::string> &&\n  \
    \   !std::same_as<std::remove_cvref_t<T>, std::string_view> &&\n     !std::is_convertible_v<T,\
    \ const char*>;\ntemplate <PrintableContainer T>\nstd::ostream& operator<<(std::ostream&\
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
    \ safe\n#define orange(...) safe\n#endif\n\nvoid chmax(auto &x, auto val) {\n\
    \    x = max(x, val);\n}\n\nvoid chmin(auto &x, auto val) {\n    x = min(x, val);\n\
    }\n\nvector<int> count_array(const auto &container, int sz = -1) {\n    if (sz\
    \ == -1) sz = *ranges::max_element(container) + 1;\n    vector<int> res(sz);\n\
    \    for (auto x : container) ++res[x];\n    return res;\n}\n\ntemplate<class\
    \ T>\nvoid discretization(vector<T> &vals) {\n    ranges::sort(vals);\n    vals.erase(ranges::unique(vals).begin(),\
    \ vals.end());\n}\n#line 3 \"test/1_library_checker/data_structure/static_rmq_zkw.test.cpp\"\
    \n\n#line 2 \"DataStructure/ZkwSegmentTree.hpp\"\n\ntemplate<typename Value =\
    \ int, typename Tag = void, bool pushdown = true>\nclass ZkwSegmentTree {\n  \
    \  static constexpr bool hasTag = !std::is_same_v<Tag, void>;\n    static_assert(pushdown\
    \ || hasTag, \"Lazy tag must exist when pushdown is false\");\n    int n;\n  \
    \  vector<Value> seg;\n    struct Empty {};\n    [[no_unique_address]] std::conditional_t<hasTag,\
    \ std::vector<Tag>, Empty> lazy;\n    Value get_val(int rt) {\n        if constexpr\
    \ (pushdown) return seg[rt];\n        else return seg[rt] + lazy[rt];\n    }\n\
    \    void give_tag(int rt, auto tag) requires (hasTag) {\n        if constexpr\
    \ (pushdown) seg[rt] = seg[rt] + tag;\n        lazy[rt] = lazy[rt] + tag;\n  \
    \  }\n    void down(int p) requires (hasTag && pushdown) {\n        p += n;\n\
    \        for (int h = std::__lg(n); h > 0; h--) {\n            int i = p >> h;\n\
    \            give_tag(i << 1, lazy[i]); \n            give_tag(i << 1 | 1, lazy[i]);\n\
    \            lazy[i] = Tag();\n        }\n    }\n    void up(int p) {\n      \
    \  if constexpr (pushdown) {\n            seg[p] = seg[p << 1] + seg[p << 1 |\
    \ 1];\n            if constexpr (hasTag) seg[p] = seg[p] + lazy[p];\n        }\n\
    \        else seg[p] = get_val(p << 1) + get_val(p << 1 | 1);\n    }\n    void\
    \ pull(int l, int r) requires (hasTag) {\n        l += n, r += n - 1;\n      \
    \  for (l >>= 1, r >>= 1; l != r; l >>= 1, r >>= 1)\n            up(l), up(r);\n\
    \        for (; l >= 1; l >>= 1)\n            up(l);\n    }\n    auto tag_prod(int\
    \ p) requires (!pushdown) {\n        Tag res = Tag();\n        for (p += n; p\
    \ >= 1; p >>= 1)\n            res = res + lazy[p];\n        return res;\n    }\n\
    \    void printnode(int rt) {\n        int l = rt, r = rt;\n        while (l <\
    \ n) l <<= 1;\n        while (r < n) r = r << 1 | 1;\n        l -= n, r -= n -\
    \ 1;\n        std::cerr << rt<< \" [\" << l << \", \" << r << \"): \";\n     \
    \   if constexpr (hasTag) std::cerr << \"val = \" << seg[rt] << \", tag = \" <<\
    \ lazy[rt];\n        else std::cerr << seg[rt];\n        std::cerr << \"\\n\"\
    ;\n    }\n    static int ceilpow2(int sz) {\n        int m = 1;\n        while\
    \ (m < sz) m <<= 1;\n        return m;\n    }\npublic:\n    ZkwSegmentTree(const\
    \ vector<Value> &data): n(ceilpow2(data.size())), seg(n << 1) { \n        if constexpr\
    \ (hasTag) lazy.resize(n << 1); \n        for (int i = 0; i < int(data.size());\
    \ ++i) seg[i + n] = data[i];\n        for (int i = n - 1; i > 0; --i) up(i);\n\
    \    }\n    ZkwSegmentTree(int size): ZkwSegmentTree(vector<Value>(size)) {}\n\
    \    Value get(int x) {\n        assert(0 <= x && x < n);\n        if constexpr\
    \ (hasTag) {\n            if constexpr (pushdown) down(x);\n            else return\
    \ seg[x + n] + tag_prod(x); \n        }\n        return seg[x + n];\n    }\n \
    \   Value range_prod(int l, int r) {\n        assert(0 <= l && r <= n);\n    \
    \    assert(l <= r);\n        if (l == r) return Value();\n        if constexpr\
    \ (hasTag && pushdown)\n            down(l), down(r - 1);\n        Value resl\
    \ = Value(), resr = Value();\n        int tl = l + n, tr = r + n - 1;\n      \
    \  bool l_valid = false, r_valid = false;\n        for (l += n, r += n; l < r;\
    \ l >>= 1, r >>= 1) {\n            if (l & 1) resl = resl + get_val(l++), l_valid\
    \ = true;\n            if (r & 1) resr = get_val(--r) + resr, r_valid = true;\n\
    \            if constexpr (!pushdown) {\n                tl >>= 1, tr >>= 1;\n\
    \                if (l_valid) resl = resl + lazy[tl];\n                if (r_valid)\
    \ resr = resr + lazy[tr];\n            }\n        }\n        if constexpr (!pushdown)\
    \ {\n            for (tl >>= 1, tr >>= 1; tl >= 1; tl >>= 1, tr >>= 1) {\n   \
    \             if (l_valid) resl = resl + lazy[tl];\n                if (r_valid)\
    \ resr = resr + lazy[tr];\n            }\n        }\n        return resl + resr;\n\
    \    }\n    void modify(int x, Value v) {\n        assert(0 <= x && x < n);\n\
    \        if constexpr (hasTag) {\n            if constexpr (pushdown) down(x);\n\
    \            else v = v - tag_prod(x); \n        }\n        for (seg[x += n] =\
    \ v; x > 1; up(x >>= 1));\n    }\n    void transform(int x, const auto &func)\
    \ {\n        assert(0 <= x && x < n);\n        if constexpr (hasTag && pushdown)\n\
    \            down(x);\n        for (func(seg[x += n]); x > 1; up(x >>= 1));\n\
    \    }\n    void range_transform(int l, int r, const auto &tag) requires (hasTag)\
    \ {\n        assert(0 <= l && r <= n);\n        assert(l <= r);\n        if (l\
    \ < r) {\n            if constexpr (hasTag && pushdown)\n                down(l),\
    \ down(r - 1);\n            int tl = l, tr = r;\n            for (l += n, r +=\
    \ n; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) give_tag(l++, tag);\n\
    \                if (r & 1) give_tag(--r, tag);\n            }\n            pull(tl,\
    \ tr);\n        }\n    }\n    void printinfo(int l, int r) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        std::cerr << \"\\e[1;33mInfo\
    \ [\" << l << \", \" << r << \"):\\n\";\n        if (l < r) {\n            for\
    \ (l += n, r += n; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) printnode(l++);\n\
    \                if (r & 1) printnode(--r);\n            }\n        }\n      \
    \  cerr << \"\\e[0m\\n\";\n    }\n    void printall() {\n        std::cerr <<\
    \ \"\\e[1;33mInfo all:\\n\";\n        for (int i = 1; i < n + n; ++i)\n      \
    \      printnode(i);\n        cerr << \"\\e[0m\\n\";\n    }\n};\n#line 5 \"test/1_library_checker/data_structure/static_rmq_zkw.test.cpp\"\
    \n\nstruct Value {\n    int val;\n    Value(int _v = 1e9): val(_v) {}\n    Value\
    \ operator+(const Value &rhs) {\n        return Value(min(val, rhs.val));\n  \
    \  }\n    friend ostream& operator<<(ostream& os, const Value &v) {\n        os\
    \ << v.val;\n        return os;\n    }\n    friend istream& operator>>(istream&\
    \ is, Value &v) {\n        is >> v.val;\n        return is;\n    }\n};\n\nint\
    \ main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n    cin >>\
    \ n >> q;\n    vector<Value> arr(n);\n    for (auto &v : arr)\n        cin >>\
    \ v;\n    ZkwSegmentTree<Value> seg(arr);\n    while (q--) {\n        int l, r;\n\
    \        cin >> l >> r;\n        cout << seg.range_prod(l, r) << \"\\n\";\n  \
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#include \"\
    default_code.hpp\"\n\n#include \"DataStructure/ZkwSegmentTree.hpp\"\n\nstruct\
    \ Value {\n    int val;\n    Value(int _v = 1e9): val(_v) {}\n    Value operator+(const\
    \ Value &rhs) {\n        return Value(min(val, rhs.val));\n    }\n    friend ostream&\
    \ operator<<(ostream& os, const Value &v) {\n        os << v.val;\n        return\
    \ os;\n    }\n    friend istream& operator>>(istream& is, Value &v) {\n      \
    \  is >> v.val;\n        return is;\n    }\n};\n\nint main() {\n    ios::sync_with_stdio(0),\
    \ cin.tie(0);\n    int n, q;\n    cin >> n >> q;\n    vector<Value> arr(n);\n\
    \    for (auto &v : arr)\n        cin >> v;\n    ZkwSegmentTree<Value> seg(arr);\n\
    \    while (q--) {\n        int l, r;\n        cin >> l >> r;\n        cout <<\
    \ seg.range_prod(l, r) << \"\\n\";\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - DataStructure/ZkwSegmentTree.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/static_rmq_zkw.test.cpp
  requiredBy: []
  timestamp: '2026-05-04 20:54:41+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/static_rmq_zkw.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/static_rmq_zkw.test.cpp
- /verify/test/1_library_checker/data_structure/static_rmq_zkw.test.cpp.html
title: test/1_library_checker/data_structure/static_rmq_zkw.test.cpp
---
