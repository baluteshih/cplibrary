---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: String/sais.hpp
    title: String/sais.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/number_of_substrings
    links:
    - https://judge.yosupo.jp/problem/number_of_substrings
  bundledCode: "#line 1 \"test/1_library_checker/string/number_of_substrings.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n#line\
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
    }\n#line 3 \"test/1_library_checker/string/number_of_substrings.test.cpp\"\n\n\
    #line 2 \"String/sais.hpp\"\n\n/*\n0-base\nThe input string should not contain\
    \ 0\nsa[i]: sa[i]-th suffix is the i-th lexicographically smallest suffix.\nhi[i]:\
    \ LCP of suffix sa[i] and suffix sa[i - 1].\nra[i]: the rank of the i-th suffix\n\
    */\nstruct Suffix {\n    int n; std::vector<int> sa, hi, ra;\n    Suffix(const\
    \ auto &_s, int _n) : n(_n), hi(n), ra(n) {\n        for (const auto &c : _s)\
    \ assert(c != 0);\n        std::vector<int> s(_s.begin(), _s.end());\n       \
    \ s.push_back(0);\n        sa = sais(s); sa.erase(sa.begin());\n        for (int\
    \ i = 0; i < n; ++i) ra[sa[i]] = i;\n        for (int i = 0, h = 0; i < n; ++i)\
    \ {\n            if (!ra[i]) { h = 0; continue; }\n            for (int j = sa[ra[i]\
    \ - 1]; std::max(i, j) + h < n && s[i + h] == s[j + h];) ++h;\n            hi[ra[i]]\
    \ = h ? h-- : 0;\n        }\n    }\n    Suffix(const auto &_s) : Suffix(_s, (int)_s.size())\
    \ {}\n    static auto sais(const auto &s) {\n        const int n = SZ(s), z =\
    \ std::ranges::max(s) + 1;\n        if (n == 1) return std::vector{0};\n     \
    \   std::vector<int> c(z); for (int x : s) ++c[x];\n        std::partial_sum(c.begin(),\
    \ c.end(), c.begin());\n        std::vector<int> sa(n);\n        auto I = std::views::iota(0,\
    \ n);\n        std::vector<bool> t(n, true);\n        for (int i = n - 2; i >=\
    \ 0; --i)\n            t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);\n\
    \        auto is_lms = std::views::filter([&t](int x) { \n            return x\
    \ && t[x] && !t[x - 1];\n        });\n        auto induce = [&] {\n          \
    \  for (auto x = c; int y : sa)\n                if (y--) if (!t[y]) sa[x[s[y]\
    \ - 1]++] = y;\n            for (auto x = c; int y : sa | std::views::reverse)\n\
    \                if (y--) if (t[y]) sa[--x[s[y]]] = y;\n        };\n        std::vector<int>\
    \ lms, q(n);\n        lms.reserve(n);\n        for (auto x = c; int i : I | is_lms)\n\
    \            q[i] = lms.size(), lms.push_back(sa[--x[s[i]]] = i);\n        induce();\n\
    \        std::vector<int> ns(lms.size());\n        for (int j = -1, nz = 0; int\
    \ i : sa | is_lms) {\n            if (j >= 0) {\n                int len = min({n\
    \ - i, n - j, lms[q[i] + 1] - i});\n                ns[q[i]] = nz += std::lexicographical_compare(std::begin(s)\
    \ + j, std::begin(s) + j + len, std::begin(s) + i, std::begin(s) + i + len);\n\
    \            }\n            j = i;\n        }\n        std::ranges::fill(sa, 0);\n\
    \        auto nsa = sais(ns);\n        for (auto x = c; int y : nsa | std::views::reverse)\n\
    \            y = lms[y], sa[--x[s[y]]] = y;\n        return induce(), sa;\n  \
    \  }\n};\n#line 5 \"test/1_library_checker/string/number_of_substrings.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    string s;\n  \
    \  cin >> s;\n    auto suffix = Suffix(s);\n    ll ans = 0;\n    for (int i =\
    \ 0; i < SZ(s); ++i) {\n        ans += i + 1;\n        if (i) ans -= suffix.hi[i];\n\
    \    }\n    cout << ans << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\
    #include \"default_code.hpp\"\n\n#include \"String/sais.hpp\"\n\nint main() {\n\
    \    ios::sync_with_stdio(0), cin.tie(0);\n    string s;\n    cin >> s;\n    auto\
    \ suffix = Suffix(s);\n    ll ans = 0;\n    for (int i = 0; i < SZ(s); ++i) {\n\
    \        ans += i + 1;\n        if (i) ans -= suffix.hi[i];\n    }\n    cout <<\
    \ ans << \"\\n\";\n}\n"
  dependsOn:
  - default_code.hpp
  - String/sais.hpp
  isVerificationFile: true
  path: test/1_library_checker/string/number_of_substrings.test.cpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/string/number_of_substrings.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/string/number_of_substrings.test.cpp
- /verify/test/1_library_checker/string/number_of_substrings.test.cpp.html
title: test/1_library_checker/string/number_of_substrings.test.cpp
---
