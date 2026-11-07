#pragma once

std::vector<int> build_fail(const auto &B) {
    std::vector<int> fail(B.size() + 1);
    fail[0] = -1;
    if (B.empty()) return fail;
    fail[1] = 0;
    for (int i = 1, j = 0; i < int(B.size()); fail[++i] = ++j)
        while (j != -1 && B[i] != B[j]) j = fail[j];
    return fail;
}

std::vector<int> match(const auto &A, const auto &B, std::vector<int> fail = {}) {
    if (B.empty()) {
        std::vector<int> ans(A.size() + 1);
        std::iota(ans.begin(), ans.end(), 0);
        return ans;
    }
    if (fail.empty()) fail = build_fail(B);
    std::vector<int> ans;
    for (int i = 0, j = 0; i < int(A.size()); ++i) {
        while (j != -1 && A[i] != B[j]) j = fail[j];
        if (++j == int(B.size())) ans.push_back(i + 1 - j), j = fail[j];
    }
    return ans;
}
