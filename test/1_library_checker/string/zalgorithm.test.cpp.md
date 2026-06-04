---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: String/z_algo.hpp
    title: String/z_algo.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 1 \"test/1_library_checker/string/zalgorithm.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n#line 2 \"default_code.hpp\"\
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
    \ vals.end());\n}\n#line 3 \"test/1_library_checker/string/zalgorithm.test.cpp\"\
    \n\n#line 2 \"String/z_algo.hpp\"\n\nstd::vector<int> make_z(const std::string\
    \ &s) {\n    std::vector<int> z(s.size());\n    int l = 0, r = 0;\n    z[0] =\
    \ s.size();\n    for (int i = 1; i < std::ssize(s); ++i) {\n        z[i] = std::max(0,\
    \ std::min(r - i + 1, z[i - l]));\n        while (i + z[i] < std::ssize(s) &&\
    \ s[i + z[i]] == s[z[i]]) ++z[i];\n        if (i + z[i] - 1 > r) l = i, r = i\
    \ + z[i] - 1;\n    }\n    return z;\n}\n#line 5 \"test/1_library_checker/string/zalgorithm.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    string s;\n  \
    \  cin >> s;\n    auto z = make_z(s);\n    for (int i = 0; i < SZ(s); ++i)\n \
    \       cout << z[i] << \" \\n\"[i + 1 == SZ(s)];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n#include\
    \ \"default_code.hpp\"\n\n#include \"String/z_algo.hpp\"\n\nint main() {\n   \
    \ ios::sync_with_stdio(0), cin.tie(0);\n    string s;\n    cin >> s;\n    auto\
    \ z = make_z(s);\n    for (int i = 0; i < SZ(s); ++i)\n        cout << z[i] <<\
    \ \" \\n\"[i + 1 == SZ(s)];\n}\n"
  dependsOn:
  - default_code.hpp
  - String/z_algo.hpp
  isVerificationFile: true
  path: test/1_library_checker/string/zalgorithm.test.cpp
  requiredBy: []
  timestamp: '2026-02-28 23:10:21+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/string/zalgorithm.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/string/zalgorithm.test.cpp
- /verify/test/1_library_checker/string/zalgorithm.test.cpp.html
title: test/1_library_checker/string/zalgorithm.test.cpp
---
