---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Numeric/pi_count.hpp
    title: Numeric/pi_count.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/counting_primes
    links:
    - https://judge.yosupo.jp/problem/counting_primes
  bundledCode: "#line 1 \"test/1_library_checker/number_theory/counting_primes.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/counting_primes\"\n#line 2\
    \ \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3\
    \ \"test/1_library_checker/number_theory/counting_primes.test.cpp\"\n\n#line 2\
    \ \"Numeric/pi_count.hpp\"\n\nlong long pi_count(long long n) { // n ~ 10^13 =>\
    \ < 2s\n    if (n <= 1) return 0;\n    int v = std::sqrt(n), s = (v + 1) / 2,\
    \ pc = 0;\n    std::vector<int> smalls(v + 1), skip(v + 1), roughs(s);\n    std::vector<long\
    \ long> larges(s);\n    for (int i = 2; i <= v; ++i) smalls[i] = (i + 1) / 2;\n\
    \    for (int i = 0; i < s; ++i) {\n        roughs[i] = 2 * i + 1;\n        larges[i]\
    \ = (n / (2 * i + 1) + 1) / 2;\n    }\n    for (int p = 3; p <= v; ++p) {\n  \
    \      if (smalls[p] > smalls[p - 1]) {\n            int q = p * p;\n        \
    \    ++pc;\n            if (1LL * q * q > n) break;\n            skip[p] = 1;\n\
    \            for (int i = q; i <= v; i += 2 * p) skip[i] = 1;\n            int\
    \ ns = 0;\n            for (int k = 0; k < s; ++k) {\n                int i =\
    \ roughs[k];\n                if (skip[i]) continue;\n                long long\
    \ d = 1LL * i * p;\n                larges[ns] = larges[k] - (d <= v ? larges[smalls[d]\
    \ - pc] : smalls[n / d]) + pc;\n                roughs[ns++] = i;\n          \
    \  }\n            s = ns;\n            for (int j = v / p; j >= p; --j) {\n  \
    \              int c = smalls[j] - pc, e = std::min(j * p + p, v + 1);\n     \
    \           for (int i = j * p; i < e; ++i) smalls[i] -= c;\n            }\n \
    \       }\n    }\n    for (int k = 1; k < s; ++k) {\n        const long long m\
    \ = n / roughs[k];\n        long long t = larges[k] - (pc + k - 1);\n        for\
    \ (int l = 1; l < k; ++l) {\n            int p = roughs[l];\n            if (1LL\
    \ * p * p > m) break;\n            t -= smalls[m / p] - (pc + l - 1);\n      \
    \  }\n        larges[0] -= t;\n    }\n    return larges[0];\n}\n#line 5 \"test/1_library_checker/number_theory/counting_primes.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    long\
    \ long n;\n    std::cin >> n;\n    std::cout << pi_count(n) << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/counting_primes\"\n#include\
    \ \"assumption.hpp\"\n\n#include \"Numeric/pi_count.hpp\"\n\nint main() {\n  \
    \  std::ios::sync_with_stdio(0), std::cin.tie(0);\n    long long n;\n    std::cin\
    \ >> n;\n    std::cout << pi_count(n) << \"\\n\";\n}\n"
  dependsOn:
  - assumption.hpp
  - Numeric/pi_count.hpp
  isVerificationFile: true
  path: test/1_library_checker/number_theory/counting_primes.test.cpp
  requiredBy: []
  timestamp: '2026-06-29 21:15:04+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/number_theory/counting_primes.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/number_theory/counting_primes.test.cpp
- /verify/test/1_library_checker/number_theory/counting_primes.test.cpp.html
title: test/1_library_checker/number_theory/counting_primes.test.cpp
---
