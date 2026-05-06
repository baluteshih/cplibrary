#pragma once

template<bool equal = false, typename T, typename Compare = std::less<T>>
std::vector<int> left_better_position(const std::vector<T> &seq, Compare comp = Compare()) {
    int n = seq.size();
    std::vector<int> res(n), stk;
    auto valid = [&](int a, int b) { // b is valid w.r.t. a
        if constexpr (equal) return !comp(seq[a], seq[b]);
        else return comp(seq[b], seq[a]);
    };
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && !valid(i, stk.back())) stk.pop_back();
        if (stk.empty()) res[i] = -1;
        else res[i] = stk.back();
        stk.push_back(i);
    }
    return res;
}

template<bool equal = false, typename T, typename Compare = std::less<T>>
std::vector<int> right_better_position(const std::vector<T> &seq, Compare comp = Compare()) {
    int n = seq.size();
    std::vector<int> res(n), stk;
    auto valid = [&](int a, int b) { // b is valid w.r.t. a
        if constexpr (equal) return !comp(seq[a], seq[b]);
        else return comp(seq[b], seq[a]);
    };
    for (int i = n - 1; i >= 0; --i) {
        while (!stk.empty() && !valid(i, stk.back())) stk.pop_back();
        if (stk.empty()) res[i] = n;
        else res[i] = stk.back();
        stk.push_back(i);
    }
    return res;
}

template<bool left_equal = false, bool right_equal = false, typename T, typename Compare = std::less<T>>
std::pair<std::vector<int>, std::vector<int>> better_position(const std::vector<T> &seq, Compare comp = Compare()) {
    return std::make_pair(left_better_position<left_equal, T, Compare>(seq, comp), right_better_position<right_equal, T, Compare>(seq, comp));
}
