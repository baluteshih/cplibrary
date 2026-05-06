---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/BIT.hpp
    title: DataStructure/BIT.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/OrderedSet.hpp
    title: DataStructure/OrderedSet.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/ordered_set
    links:
    - https://judge.yosupo.jp/problem/ordered_set
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/ordered_set.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n#line 2 \"\
    default_code.hpp\"\n\n#include <bits/stdc++.h>\nusing namespace std;\ntypedef\
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
    }\n#line 3 \"test/1_library_checker/data_structure/ordered_set.test.cpp\"\n\n\
    #line 2 \"DataStructure/OrderedSet.hpp\"\n\n#line 2 \"DataStructure/BIT.hpp\"\n\
    \ntemplate<class T>\nclass BIT { // 0-base\n    int n;\n    T total_;\n    vector<T>\
    \ bit;\npublic:\n    BIT(int _n): n(_n), total_(), bit(n + 1) {}\n    void initialize(const\
    \ std::vector<T> &arr) {\n        for (int x = 1; x <= n; ++x) {\n           \
    \ bit[x] = arr[x - 1];\n            int y = x - (x & -x);\n            for (int\
    \ i = x - 1; i > y; i -= i & -i)\n                bit[x] = bit[x] + bit[i];\n\
    \        }\n    }\n    void modify(int x, T v) {\n        total_ += v;\n     \
    \   for (++x; x <= n; x += x & -x)\n            bit[x] = bit[x] + v;\n    }\n\
    \    T prefix(int x) {\n        T res = T();\n        for (++x; x; x -= x & -x)\n\
    \            res = res + bit[x];\n        return res;\n    }\n    T suffix(int\
    \ x) requires requires(T x, T y) { x - y; } {\n        return total_ - prefix(x);\n\
    \    }\n    T range(int l, int r) requires requires(T x, T y) { x - y; } { //\
    \ [l, r)\n        if (l >= r) return T();\n        T res = prefix(r - 1) - prefix(l\
    \ - 1);\n        return res;\n    }\n    int kth(int k) { // 0-base query\n  \
    \      assert((n & (n - 1)) == 0);\n        ++k;\n        int res = 0;\n     \
    \   for (int i = n >> 1; i >= 1; i >>= 1) {\n            if (bit[res + i] < k)\n\
    \                k -= bit[res += i];\n        }\n        return res;\n    }\n\
    \    T total() {\n        return total_;\n    }\n};\n#line 4 \"DataStructure/OrderedSet.hpp\"\
    \n\ntemplate<class T>\nclass OrderedSet {\n    vector<T> vals;\n    vector<bool>\
    \ vis;\n    BIT<int> bit;\n    static vector<T> sort_and_unique(vector<T> _vals)\
    \ {\n        ranges::sort(_vals);\n        _vals.erase(ranges::unique(_vals).begin(),\
    \ _vals.end());\n        return _vals;\n    }\n    int idx(int x) {\n        auto\
    \ it = ranges::lower_bound(vals, x);\n        if (it == vals.end() || *it != x)\
    \ return -1;\n        return it - vals.begin();\n    }\n    int safe_idx(int x)\
    \ {\n        int res = idx(x);\n        assert(res != -1);\n        return res;\n\
    \    }\npublic:\n    OrderedSet(vector<T> _vals): vals(sort_and_unique(_vals)),\
    \ vis(vals.size()), bit(bit_ceil(vals.size())) {}\n    bool insert(T x) {\n  \
    \      x = safe_idx(x);\n        if (vis[x]) return false;\n        vis[x] = true;\n\
    \        bit.modify(x, 1);\n        return true;\n    }\n    bool erase(T x) {\n\
    \        x = safe_idx(x);\n        if (!vis[x]) return false;\n        vis[x]\
    \ = false;\n        bit.modify(x, -1);\n        return true;\n    }\n    bool\
    \ exists(T x) {\n        x = idx(x);\n        if (x == -1) return false;\n   \
    \     return vis[x]; \n    }\n    int size() {\n        return bit.total();\n\
    \    }\n    int lt_count(T x) {\n        int idx = ranges::lower_bound(vals, x)\
    \ - vals.begin() - 1;\n        return bit.prefix(idx);\n    }\n    int leq_count(T\
    \ x) {\n        int idx = ranges::upper_bound(vals, x) - vals.begin() - 1;\n \
    \       return bit.prefix(idx);\n    }\n    int order(T x) {\n        return leq_count(x);\n\
    \    }\n    int kth(int k) { // 0-base query, return 0-base index\n        if\
    \ (size() <= k) return -1;\n        int res = bit.kth(k);\n        return res;\n\
    \    }\n    int leq(T x) { // return 0-base index\n        int res = leq_count(x);\n\
    \        return res == 0 ? -1 : kth(res - 1);\n    }\n    int geq(T x) { // return\
    \ 0-base index\n        int res = lt_count(x);\n        return res == size() ?\
    \ -1 : kth(res);\n    }\n    const T& operator[](size_t index) const {\n     \
    \   return vals[index];\n    } \n};\n#line 5 \"test/1_library_checker/data_structure/ordered_set.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n  \
    \  cin >> n >> q;\n    vector<int> arr(n);\n    for (int &i : arr)\n        cin\
    \ >> i;\n    vector<int> vals(arr);\n    vector<pii> qry(q);\n    for (auto &[t,\
    \ x] : qry) {\n        cin >> t >> x;\n        if (t == 0 || t == 1)\n       \
    \     vals.push_back(x);\n    }\n    vals.push_back(0);\n    OrderedSet<int> ord(vals);\n\
    \    for (int i : arr)\n        ord.insert(i);\n    for (auto &[t, x] : qry) {\n\
    \        if (t == 0) ord.insert(x);\n        else if (t == 1) ord.erase(x);\n\
    \        else if (t == 2) {\n            int res = ord.kth(x - 1);\n         \
    \   if (res != -1) res = ord[res]; \n            cout << res << \"\\n\";\n   \
    \     }\n        else if (t == 3)\n            cout << ord.leq_count(x) << \"\\\
    n\";\n        else if (t == 4) {\n            int res = ord.leq(x);\n        \
    \    if (res != -1) res = ord[res]; \n            cout << res << \"\\n\";\n  \
    \      }\n        else {\n            int res = ord.geq(x);\n            if (res\
    \ != -1) res = ord[res]; \n            cout << res << \"\\n\";\n        }\n  \
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n#include\
    \ \"default_code.hpp\"\n\n#include \"DataStructure/OrderedSet.hpp\"\n\nint main()\
    \ {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n    cin >> n >>\
    \ q;\n    vector<int> arr(n);\n    for (int &i : arr)\n        cin >> i;\n   \
    \ vector<int> vals(arr);\n    vector<pii> qry(q);\n    for (auto &[t, x] : qry)\
    \ {\n        cin >> t >> x;\n        if (t == 0 || t == 1)\n            vals.push_back(x);\n\
    \    }\n    vals.push_back(0);\n    OrderedSet<int> ord(vals);\n    for (int i\
    \ : arr)\n        ord.insert(i);\n    for (auto &[t, x] : qry) {\n        if (t\
    \ == 0) ord.insert(x);\n        else if (t == 1) ord.erase(x);\n        else if\
    \ (t == 2) {\n            int res = ord.kth(x - 1);\n            if (res != -1)\
    \ res = ord[res]; \n            cout << res << \"\\n\";\n        }\n        else\
    \ if (t == 3)\n            cout << ord.leq_count(x) << \"\\n\";\n        else\
    \ if (t == 4) {\n            int res = ord.leq(x);\n            if (res != -1)\
    \ res = ord[res]; \n            cout << res << \"\\n\";\n        }\n        else\
    \ {\n            int res = ord.geq(x);\n            if (res != -1) res = ord[res];\
    \ \n            cout << res << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - DataStructure/OrderedSet.hpp
  - DataStructure/BIT.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/ordered_set.test.cpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/ordered_set.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/ordered_set.test.cpp
- /verify/test/1_library_checker/data_structure/ordered_set.test.cpp.html
title: test/1_library_checker/data_structure/ordered_set.test.cpp
---
