#pragma once

namespace prime_work {
    int limit = 2;
    std::vector<int> min_factor({0, 0, 2}); // min_factor[i] := min prime factor of i, min_factor[0] = min_factor[1] = 0
    std::vector<int> list({2}); // prime list
    void ensure_upper_bound(int n) {
        if (limit < n) {
            limit = n;
            std::vector<int>(n + 1, 0).swap(min_factor);
            std::vector<int>().swap(list);
            for (int i = 2; i <= n; ++i) {
                if (min_factor[i] == 0) {
                    min_factor[i] = i;
                    list.push_back(i);
                }
                for (int j : list) {
                    if (i * j > n) break;
                    min_factor[i * j] = j;
                    if (i % j == 0) break;
                }
            }
        }
    }
    std::vector<int> prime_list(int n) {
        ensure_upper_bound(n);
        return std::vector<int>(list.begin(), std::ranges::upper_bound(list, n));
    }
};
