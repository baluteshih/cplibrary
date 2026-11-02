#pragma once

#include "Convolution/bitwise_transform.hpp"

namespace bitwise_transform {
    // Online Bitwise Transform (subset: i = 0 -> 2^lg - 1, superset: i = 2^lg - 1 -> 0)
    template<target tar = subset, type tp = zeta, typename T = long long>
    struct online_transform {
        static_assert(tar != popcount, "Online transform does not support popcount (FWT).");
        int lg, n, p;
        std::vector<T> arr;

        online_transform(int lg_) : lg(lg_), n(1 << lg_), p(tar == subset ? 0 : n - 1), arr(n, T{}) {}

        // assume a[i] = ai, return transform(a)[i]. does not advance pointer p.
        T assume(int i, T ai = T{}) const {
            assert(p == i);
            T sum{};
            if constexpr (tar == subset)
                for (unsigned int m = i; m > 0; m &= m - 1)
                    sum += arr[i ^ (m & -m)];
            else
                for (unsigned int m = (n - 1) ^ i; m > 0; m &= m - 1)
                    sum += arr[i ^ (m & -m)];
            if constexpr (tp == zeta) return ai + sum;
            else return ai - sum;
        }

        // set a[i] = ai, advance pointer p, and return transform(a)[i].
        T set(int i, T ai) {
            assert(p == i);
            T res = assume(i, ai);
            if constexpr (tar == subset) {
                arr[p++] = (tp == zeta ? ai : res);
                for (int len = 1; (i & len) != 0; len <<= 1)
                    for (int j = p - len; j < p; ++j)
                        arr[j] += arr[j - len];
            } else {
                arr[p--] = (tp == zeta ? ai : res);
                for (int len = 1; (~i & len) != 0 && (p + 1 + (len << 1) <= n); len <<= 1)
                    for (int j = p + 1; j < p + 1 + len; ++j)
                        arr[j] += arr[j + len];
            }
            return res;
        }
    };
}
