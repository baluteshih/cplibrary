---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/number_theory/counting_primes.test.cpp
    title: test/1_library_checker/number_theory/counting_primes.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/pi_count.hpp\"\n\nlong long pi_count(long long n)\
    \ { // n ~ 10^13 => < 2s\n    if (n <= 1) return 0;\n    int v = std::sqrt(n),\
    \ s = (v + 1) / 2, pc = 0;\n    std::vector<int> smalls(v + 1), skip(v + 1), roughs(s);\n\
    \    std::vector<long long> larges(s);\n    for (int i = 2; i <= v; ++i) smalls[i]\
    \ = (i + 1) / 2;\n    for (int i = 0; i < s; ++i) {\n        roughs[i] = 2 * i\
    \ + 1;\n        larges[i] = (n / (2 * i + 1) + 1) / 2;\n    }\n    for (int p\
    \ = 3; p <= v; ++p) {\n        if (smalls[p] > smalls[p - 1]) {\n            int\
    \ q = p * p;\n            ++pc;\n            if (1LL * q * q > n) break;\n   \
    \         skip[p] = 1;\n            for (int i = q; i <= v; i += 2 * p) skip[i]\
    \ = 1;\n            int ns = 0;\n            for (int k = 0; k < s; ++k) {\n \
    \               int i = roughs[k];\n                if (skip[i]) continue;\n \
    \               long long d = 1LL * i * p;\n                larges[ns] = larges[k]\
    \ - (d <= v ? larges[smalls[d] - pc] : smalls[n / d]) + pc;\n                roughs[ns++]\
    \ = i;\n            }\n            s = ns;\n            for (int j = v / p; j\
    \ >= p; --j) {\n                int c = smalls[j] - pc, e = std::min(j * p + p,\
    \ v + 1);\n                for (int i = j * p; i < e; ++i) smalls[i] -= c;\n \
    \           }\n        }\n    }\n    for (int k = 1; k < s; ++k) {\n        const\
    \ long long m = n / roughs[k];\n        long long t = larges[k] - (pc + k - 1);\n\
    \        for (int l = 1; l < k; ++l) {\n            int p = roughs[l];\n     \
    \       if (1LL * p * p > m) break;\n            t -= smalls[m / p] - (pc + l\
    \ - 1);\n        }\n        larges[0] -= t;\n    }\n    return larges[0];\n}\n"
  code: "#pragma once\n\nlong long pi_count(long long n) { // n ~ 10^13 => < 2s\n\
    \    if (n <= 1) return 0;\n    int v = std::sqrt(n), s = (v + 1) / 2, pc = 0;\n\
    \    std::vector<int> smalls(v + 1), skip(v + 1), roughs(s);\n    std::vector<long\
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
    \  }\n        larges[0] -= t;\n    }\n    return larges[0];\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/pi_count.hpp
  requiredBy: []
  timestamp: '2026-06-29 21:15:04+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/number_theory/counting_primes.test.cpp
documentation_of: Numeric/pi_count.hpp
layout: document
redirect_from:
- /library/Numeric/pi_count.hpp
- /library/Numeric/pi_count.hpp.html
title: Numeric/pi_count.hpp
---
