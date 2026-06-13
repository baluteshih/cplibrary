---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Numeric/miller_rabin.hpp
    title: Numeric/miller_rabin.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/pollard_rho.hpp
    title: Numeric/pollard_rho.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/factorize
    links:
    - https://judge.yosupo.jp/problem/factorize
  bundledCode: "#line 1 \"test/1_library_checker/number_theory/factorize.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\n#line 2 \"default_code.hpp\"\
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
    \ vals.end());\n}\n#line 3 \"test/1_library_checker/number_theory/factorize.test.cpp\"\
    \n\n#line 2 \"Numeric/pollard_rho.hpp\"\n\n#line 2 \"Numeric/miller_rabin.hpp\"\
    \n\ntemplate<typename T>\nbool _miller_rabin(T a, T n) {\n    if ((a = a % n)\
    \ == 0) return 1;\n    if ((n & 1) ^ 1) return n == 2;\n    static auto mul =\
    \ [&](T x, T y, T mod) {\n        if constexpr (sizeof(T) == 4) return (long long)x\
    \ * y % mod;\n        else return (__int128)x * y % mod;\n    };\n    T t = std::countr_zero(std::make_unsigned_t<T>(n\
    \ - 1)), x = 1;\n    T tmp = (n - 1) >> t;\n    for (; tmp; tmp >>= 1, a = mul(a,\
    \ a, n))\n        if(tmp & 1) x = mul(x, a, n);\n    if (x == 1 || x == n - 1)\
    \ return 1;\n    while (--t)\n        if ((x = mul(x, x, n)) == n - 1) return\
    \ 1;\n    return 0;\n}\n\ntemplate<typename T>\nbool miller_rabin(T n) {\n   \
    \ if (n == 1) return false;\n    static std::vector<T> _base[4] = {{2, 7, 61},\
    \ {2, 13, 23, 1662803}, {2, 3, 5, 7, 11, 13}, {2, 325, 9375, 28178, 450775, 9780504,\
    \ 1795265022}};\n    std::vector<T> base =\n        (n < 4759123141ll) ? _base[0]\
    \ :\n        (n < 1122004669633ll) ? _base[1] :\n        (n < 3474749660383ll)\
    \ ? _base[2] : _base[3];\n    for (T b : base)\n        if (!_miller_rabin(b,\
    \ n))\n            return false;\n    return true;\n}\n#line 4 \"Numeric/pollard_rho.hpp\"\
    \n\n/*\nreturn an unsorted prime list\n*/\ntemplate<typename T>\nstd::vector<T>\
    \ pollard_rho(T n) {\n    static auto mul = [&](T x, T y, T mod) {\n        if\
    \ constexpr (sizeof(T) == 4) return (long long)x * y % mod;\n        else return\
    \ (__int128)x * y % mod;\n    };\n    std::vector<T> res;\n    auto factorize\
    \ = [&](auto self, T cur) -> void {\n        if (cur == 1) return;\n        if\
    \ (miller_rabin(cur)) return res.push_back(cur);\n        if (cur % 2 == 0) {\n\
    \            int cnt = std::countr_zero(std::make_unsigned_t<T>(cur));\n     \
    \       res.resize(res.size() + cnt, 2);\n            return self(self, cur >>\
    \ cnt);\n        }\n        T p = 2, q, i = 1, x = 0, y = 0, t = 0, ct = 87;\n\
    \        #define f(x) ((mul(x, x, cur) + ct) % cur)\n        while (t++ % 64 ||\
    \ std::__gcd(p, cur) == 1) {\n            if (x == y) x = i++, y = f(x);\n   \
    \         q = mul(p, x < y ? y - x : x - y, cur);\n            if (q) p = q;\n\
    \            if (p == cur) ++ct;\n            x = f(x), y = f(f(y));\n       \
    \ }\n        T d = std::__gcd(p, cur);\n        self(self, cur / d);\n       \
    \ self(self, d);\n    };\n    factorize(factorize, n);\n    return res;\n}\n#line\
    \ 5 \"test/1_library_checker/number_theory/factorize.test.cpp\"\n\nint main()\
    \ {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int q;\n    cin >> q;\n   \
    \ while (q--) {\n        ll x;\n        cin >> x;\n        vector<ll> ans = pollard_rho(x);\n\
    \        ranges::sort(ans);\n        cout << SZ(ans);\n        for (ll i : ans)\n\
    \            cout << \" \" << i;\n        cout << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\n#include \"\
    default_code.hpp\"\n\n#include \"Numeric/pollard_rho.hpp\"\n\nint main() {\n \
    \   ios::sync_with_stdio(0), cin.tie(0);\n    int q;\n    cin >> q;\n    while\
    \ (q--) {\n        ll x;\n        cin >> x;\n        vector<ll> ans = pollard_rho(x);\n\
    \        ranges::sort(ans);\n        cout << SZ(ans);\n        for (ll i : ans)\n\
    \            cout << \" \" << i;\n        cout << \"\\n\";\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - Numeric/pollard_rho.hpp
  - Numeric/miller_rabin.hpp
  isVerificationFile: true
  path: test/1_library_checker/number_theory/factorize.test.cpp
  requiredBy: []
  timestamp: '2026-02-28 23:10:21+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/number_theory/factorize.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/number_theory/factorize.test.cpp
- /verify/test/1_library_checker/number_theory/factorize.test.cpp.html
title: test/1_library_checker/number_theory/factorize.test.cpp
---
