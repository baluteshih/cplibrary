---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Sequence/better_position.hpp
    title: Sequence/better_position.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/cartesian_tree
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "#line 1 \"test/1_library_checker/tree/cartesian_tree.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n#line 2 \"\
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
    }\n#line 3 \"test/1_library_checker/tree/cartesian_tree.test.cpp\"\n\n#line 2\
    \ \"Sequence/better_position.hpp\"\n\ntemplate<bool equal = false, typename T,\
    \ typename Compare = std::less<T>>\nstd::vector<int> left_better_position(const\
    \ std::vector<T> &seq, Compare comp = Compare()) {\n    int n = seq.size();\n\
    \    std::vector<int> res(n), stk;\n    auto valid = [&](int a, int b) { // b\
    \ is valid w.r.t. a\n        if constexpr (equal) return !comp(seq[a], seq[b]);\n\
    \        else return comp(seq[b], seq[a]);\n    };\n    for (int i = 0; i < n;\
    \ ++i) {\n        while (!stk.empty() && !valid(i, stk.back())) stk.pop_back();\n\
    \        if (stk.empty()) res[i] = -1;\n        else res[i] = stk.back();\n  \
    \      stk.push_back(i);\n    }\n    return res;\n}\n\ntemplate<bool equal = false,\
    \ typename T, typename Compare = std::less<T>>\nstd::vector<int> right_better_position(const\
    \ std::vector<T> &seq, Compare comp = Compare()) {\n    int n = seq.size();\n\
    \    std::vector<int> res(n), stk;\n    auto valid = [&](int a, int b) { // b\
    \ is valid w.r.t. a\n        if constexpr (equal) return !comp(seq[a], seq[b]);\n\
    \        else return comp(seq[b], seq[a]);\n    };\n    for (int i = n - 1; i\
    \ >= 0; --i) {\n        while (!stk.empty() && !valid(i, stk.back())) stk.pop_back();\n\
    \        if (stk.empty()) res[i] = n;\n        else res[i] = stk.back();\n   \
    \     stk.push_back(i);\n    }\n    return res;\n}\n\ntemplate<bool left_equal\
    \ = false, bool right_equal = false, typename T, typename Compare = std::less<T>>\n\
    std::pair<std::vector<int>, std::vector<int>> better_position(const std::vector<T>\
    \ &seq, Compare comp = Compare()) {\n    return std::make_pair(left_better_position<left_equal,\
    \ T, Compare>(seq, comp), right_better_position<right_equal, T, Compare>(seq,\
    \ comp));\n}\n#line 5 \"test/1_library_checker/tree/cartesian_tree.test.cpp\"\n\
    \nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n;\n    cin\
    \ >> n;\n    vector<int> arr(n);\n    for (int &i : arr)\n        cin >> i;\n\
    \    auto [lft, rgt] = better_position(arr);\n    vector<int> ans(n);\n    for\
    \ (int i = 0; i < n; ++i)\n        if (lft[i] == -1 && rgt[i] == n) ans[i] = i;\n\
    \        else if (lft[i] == -1) ans[i] = rgt[i];\n        else if (rgt[i] == n)\
    \ ans[i] = lft[i];\n        else ans[i] = arr[lft[i]] < arr[rgt[i]] ? rgt[i] :\
    \ lft[i];\n    for (int i = 0; i < n; ++i)\n        cout << ans[i] << \" \\n\"\
    [i + 1 == n];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n#include\
    \ \"default_code.hpp\"\n\n#include \"Sequence/better_position.hpp\"\n\nint main()\
    \ {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n;\n    cin >> n;\n   \
    \ vector<int> arr(n);\n    for (int &i : arr)\n        cin >> i;\n    auto [lft,\
    \ rgt] = better_position(arr);\n    vector<int> ans(n);\n    for (int i = 0; i\
    \ < n; ++i)\n        if (lft[i] == -1 && rgt[i] == n) ans[i] = i;\n        else\
    \ if (lft[i] == -1) ans[i] = rgt[i];\n        else if (rgt[i] == n) ans[i] = lft[i];\n\
    \        else ans[i] = arr[lft[i]] < arr[rgt[i]] ? rgt[i] : lft[i];\n    for (int\
    \ i = 0; i < n; ++i)\n        cout << ans[i] << \" \\n\"[i + 1 == n];\n}\n"
  dependsOn:
  - default_code.hpp
  - Sequence/better_position.hpp
  isVerificationFile: true
  path: test/1_library_checker/tree/cartesian_tree.test.cpp
  requiredBy: []
  timestamp: '2026-05-06 17:34:12+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/tree/cartesian_tree.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/tree/cartesian_tree.test.cpp
- /verify/test/1_library_checker/tree/cartesian_tree.test.cpp.html
title: test/1_library_checker/tree/cartesian_tree.test.cpp
---
