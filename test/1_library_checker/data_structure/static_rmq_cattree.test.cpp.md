---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/CatTree.hpp
    title: DataStructure/CatTree.hpp
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
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/static_rmq_cattree.test.cpp\"\
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
    \ vals.end());\n}\n#line 3 \"test/1_library_checker/data_structure/static_rmq_cattree.test.cpp\"\
    \n\n#line 2 \"DataStructure/CatTree.hpp\"\n\ntemplate<typename Value = int>\n\
    class CatTree {\n    int n;\n    std::vector<int> mid;\n    std::vector<std::vector<Value>>\
    \ lft, rgt;\n    void initialize(int l, int r, int rt, const vector<Value> &data)\
    \ {\n        if (r - l == 1) {\n            lft[rt].push_back(data[l]);\n    \
    \        return;\n        }\n        mid[rt] = (l + r) >> 1;\n        lft[rt].resize(mid[rt]\
    \ - l);\n        rgt[rt].resize(r - mid[rt]);\n        for (int i = mid[rt] -\
    \ 1; i >= l; --i) {\n            lft[rt][mid[rt] - i - 1] = i < std::ssize(data)\
    \ ? data[i] : Value();\n            if (mid[rt] - i - 1 > 0)\n               \
    \ lft[rt][mid[rt] - i - 1] = lft[rt][mid[rt] - i - 1] + lft[rt][mid[rt] - i -\
    \ 2];\n        }\n        for (int i = mid[rt]; i < r; ++i) {\n            rgt[rt][i\
    \ - mid[rt]] = i < std::ssize(data) ? data[i] : Value();\n            if (i -\
    \ mid[rt] > 0)\n                rgt[rt][i - mid[rt]] = rgt[rt][i - mid[rt] - 1]\
    \ + rgt[rt][i - mid[rt]];\n        }\n        initialize(l, mid[rt], rt << 1,\
    \ data);\n        initialize(mid[rt], r, rt << 1 | 1, data);\n    }\n    static\
    \ int ceilpow2(int sz) {\n        int m = 1;\n        while (m < sz) m <<= 1;\n\
    \        return m;\n    }\npublic:\n    CatTree(const std::vector<Value> &data):\
    \ n(ceilpow2(data.size())), mid(n), lft(n << 1), rgt(n) { \n        initialize(0,\
    \ n, 1, data);\n    }\n    CatTree(int size): CatTree(std::vector<Value>(size))\
    \ {}\n    Value range_prod(int l, int r) {\n        assert(0 <= l && r <= n);\n\
    \        assert(l <= r);\n        if (l == r) return Value();\n        --r;\n\
    \        l += n, r += n;\n        if (l == r) return lft[l][0];\n        int lca\
    \ = l >> (std::__lg(l ^ r) + 1);\n        l -= n, r -= n;\n        return lft[lca][mid[lca]\
    \ - l - 1] + rgt[lca][r - mid[lca]];\n    }\n};\n#line 5 \"test/1_library_checker/data_structure/static_rmq_cattree.test.cpp\"\
    \n\nstruct Value {\n    int val;\n    Value(int _v = 2e9): val(_v) {}\n    Value\
    \ operator+(const Value &a) const {\n        return Value(min(val, a.val));\n\
    \    }\n    friend ostream& operator<<(ostream& os, const Value &v) {\n      \
    \  os << v.val;\n        return os;\n    }\n    friend istream& operator>>(istream&\
    \ is, Value &v) {\n        is >> v.val;\n        return is;\n    }\n};\n\nint\
    \ main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n    cin >>\
    \ n >> q;\n    vector<Value> arr(n);\n    for (auto &v : arr)\n        cin >>\
    \ v;\n    CatTree<Value> seg(arr);\n    while (q--) {\n        int l, r;\n   \
    \     cin >> l >> r;\n        cout << seg.range_prod(l, r) << \"\\n\";\n    }\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#include \"\
    default_code.hpp\"\n\n#include \"DataStructure/CatTree.hpp\"\n\nstruct Value {\n\
    \    int val;\n    Value(int _v = 2e9): val(_v) {}\n    Value operator+(const\
    \ Value &a) const {\n        return Value(min(val, a.val));\n    }\n    friend\
    \ ostream& operator<<(ostream& os, const Value &v) {\n        os << v.val;\n \
    \       return os;\n    }\n    friend istream& operator>>(istream& is, Value &v)\
    \ {\n        is >> v.val;\n        return is;\n    }\n};\n\nint main() {\n   \
    \ ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n    cin >> n >> q;\n  \
    \  vector<Value> arr(n);\n    for (auto &v : arr)\n        cin >> v;\n    CatTree<Value>\
    \ seg(arr);\n    while (q--) {\n        int l, r;\n        cin >> l >> r;\n  \
    \      cout << seg.range_prod(l, r) << \"\\n\";\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - DataStructure/CatTree.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
  requiredBy: []
  timestamp: '2026-03-18 20:28:14+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
- /verify/test/1_library_checker/data_structure/static_rmq_cattree.test.cpp.html
title: test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
---
