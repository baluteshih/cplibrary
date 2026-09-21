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
  bundledCode: "#line 2 \"Sequence/maximum_non_adjacent_elements.hpp\"\n\n// return\
    \ non-sorted differences\ntemplate<typename T>\nstd::vector<T> maximum_non_adjacent_elements(const\
    \ std::vector<T> &arr) {\n    std::vector<T> diff, stk;\n    for (auto &v : arr)\
    \ {\n        stk.push_back(v);\n        while (int(stk.size()) >= 2) {\n     \
    \       T l = T(), m = stk.end()[-2], r = stk.end()[-1];\n            if (int(stk.size())\
    \ >= 3) l = stk.end()[-3];\n            if ((int(stk.size()) == 2 || l <= m) &&\
    \ m >= r) {\n                diff.push_back(m);\n                stk.pop_back(),\
    \ stk.pop_back();\n                if (!stk.empty()) stk.back() = l + r - m;\n\
    \            }\n            else break;\n        }\n    }\n    for (int i = int(stk.size())\
    \ - 1; i >= 0; i -= 2) diff.push_back(stk[i]);\n    return diff;\n}\n"
  code: "#pragma once\n\n// return non-sorted differences\ntemplate<typename T>\n\
    std::vector<T> maximum_non_adjacent_elements(const std::vector<T> &arr) {\n  \
    \  std::vector<T> diff, stk;\n    for (auto &v : arr) {\n        stk.push_back(v);\n\
    \        while (int(stk.size()) >= 2) {\n            T l = T(), m = stk.end()[-2],\
    \ r = stk.end()[-1];\n            if (int(stk.size()) >= 3) l = stk.end()[-3];\n\
    \            if ((int(stk.size()) == 2 || l <= m) && m >= r) {\n             \
    \   diff.push_back(m);\n                stk.pop_back(), stk.pop_back();\n    \
    \            if (!stk.empty()) stk.back() = l + r - m;\n            }\n      \
    \      else break;\n        }\n    }\n    for (int i = int(stk.size()) - 1; i\
    \ >= 0; i -= 2) diff.push_back(stk[i]);\n    return diff;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Sequence/maximum_non_adjacent_elements.hpp
  requiredBy: []
  timestamp: '2026-06-28 02:52:11+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Sequence/maximum_non_adjacent_elements.hpp
layout: document
redirect_from:
- /library/Sequence/maximum_non_adjacent_elements.hpp
- /library/Sequence/maximum_non_adjacent_elements.hpp.html
title: Sequence/maximum_non_adjacent_elements.hpp
---
