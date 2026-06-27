#pragma once

// return non-sorted differences
template<typename T>
std::vector<T> maximum_non_adjacent_elements(const std::vector<T> &arr) {
    std::vector<T> diff, stk;
    for (auto &v : arr) {
        stk.push_back(v);
        while (int(stk.size()) >= 2) {
            T l = T(), m = stk.end()[-2], r = stk.end()[-1];
            if (int(stk.size()) >= 3) l = stk.end()[-3];
            if ((int(stk.size()) == 2 || l <= m) && m >= r) {
                diff.push_back(m);
                stk.pop_back(), stk.pop_back();
                if (!stk.empty()) stk.back() = l + r - m;
            }
            else break;
        }
    }
    for (int i = int(stk.size()) - 1; i >= 0; i -= 2) diff.push_back(stk[i]);
    return diff;
}
