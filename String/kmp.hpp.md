---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"String/kmp.hpp\"\n\nstd::vector<int> build_fail(const auto\
    \ &B) {\n    std::vector<int> fail(B.size() + 1);\n    fail[0] = -1, fail[1] =\
    \ 0;\n    for (int i = 1, j = 0; i < int(B.size()); fail[++i] = ++j)\n       \
    \ while (j != -1 && B[i] != B[j]) j = fail[j];\n    return fail;\n}\n\nstd::vector<int>\
    \ match(const auto &A, const auto &B, std::vector<int> fail = {}) {\n    if (fail.empty())\
    \ fail = build_fail(B);\n    std::vector<int> ans;\n    for (int i = 0, j = 0;\
    \ i < int(A.size()); ++i) {\n        while (j != -1 && A[i] != B[j]) j = fail[j];\n\
    \        if (++j == int(B.size())) ans.push_back(i + 1 - j), j = fail[j];\n  \
    \  }\n    return ans;\n}\n"
  code: "#pragma once\n\nstd::vector<int> build_fail(const auto &B) {\n    std::vector<int>\
    \ fail(B.size() + 1);\n    fail[0] = -1, fail[1] = 0;\n    for (int i = 1, j =\
    \ 0; i < int(B.size()); fail[++i] = ++j)\n        while (j != -1 && B[i] != B[j])\
    \ j = fail[j];\n    return fail;\n}\n\nstd::vector<int> match(const auto &A, const\
    \ auto &B, std::vector<int> fail = {}) {\n    if (fail.empty()) fail = build_fail(B);\n\
    \    std::vector<int> ans;\n    for (int i = 0, j = 0; i < int(A.size()); ++i)\
    \ {\n        while (j != -1 && A[i] != B[j]) j = fail[j];\n        if (++j ==\
    \ int(B.size())) ans.push_back(i + 1 - j), j = fail[j];\n    }\n    return ans;\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: String/kmp.hpp
  requiredBy: []
  timestamp: '2026-05-08 13:17:22+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: String/kmp.hpp
layout: document
redirect_from:
- /library/String/kmp.hpp
- /library/String/kmp.hpp.html
title: String/kmp.hpp
---
