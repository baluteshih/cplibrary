#pragma once

template<typename T>
std::vector<T> subset_enumerate(const std::vector<T> &arr) {
    std::vector<T> res;
    T cur = T();
    auto dfs = [&](auto self, int u) -> void {
        if (u == int(arr.size())) return res.push_back(cur);
        T tmp = cur;
        cur = cur + arr[u];
        self(self, u + 1);
        cur = tmp;
        self(self, u + 1);
    };
    dfs(dfs, 0);
    return res;
}
