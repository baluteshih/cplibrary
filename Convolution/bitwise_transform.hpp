#pragma once

namespace bitwise_transform {
    // popcount: res[j] = sum_i (-1)^{popcount(i & j)}arr[i], ignore type
    enum target { subset, superset, popcount };
    enum type { zeta, mobius };
    template<target tar, type tp = zeta, typename T = long long>
    void transform(std::vector<T> &arr) {
        int n = arr.size();  
        assert((n & (n - 1)) == 0);
        for (int L = 2; L <= n; L <<= 1)
            for (int i = 0; i < n; i += L)
                for (int j = i; j < i + (L >> 1); ++j) {
                    if constexpr (tar == subset) {
                        if constexpr (tp == zeta) arr[j + (L >> 1)] += arr[j];
                        else arr[j + (L >> 1)] -= arr[j];
                    }
                    else if constexpr (tar == superset) {
                        if constexpr (tp == zeta) arr[j] += arr[j + (L >> 1)];
                        else arr[j] -= arr[j + (L >> 1)];
                    }
                    else std::tie(arr[j], arr[j + (L >> 1)]) = std::make_pair(arr[j] + arr[j + (L >> 1)], arr[j] - arr[j + (L >> 1)]);
                }
    }
    template<typename T>
    std::vector<std::vector<T>> ranked_zeta(const std::vector<T> &arr) {
        int n = arr.size(), lg = std::__lg(n);
        assert((n & (n - 1)) == 0);
        std::vector<std::vector<T>> res(lg + 1, std::vector<T>(n));
        for (int i = 0; i < n; ++i)
            res[std::popcount(static_cast<unsigned int>(i))][i] = arr[i];
        for (int i = 0; i <= lg; ++i)
            transform<subset, zeta>(res[i]);
        return res;
    }
    template<typename T>
    std::vector<T> ranked_mobius(std::vector<std::vector<T>> arr) {
        int n = arr[0].size(), lg = arr.size() - 1;
        assert((n & (n - 1)) == 0);
        std::vector<T> res(n);
        for (int i = 0; i <= lg; ++i)
            transform<subset, mobius>(arr[i]);
        for (int i = 0; i < n; ++i)
            res[i] = arr[std::popcount(static_cast<unsigned int>(i))][i];
        return res;
    }
}
