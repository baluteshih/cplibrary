#pragma once

#include "Numeric/prime_work.hpp"

namespace factor_transform {
    enum target { divisor, multiplier };
    enum type { zeta, mobius };
    template<target tar, type tp, typename T>
    void transform(std::vector<T> &arr) {
        int n = arr.size() - 1;
        assert(arr[0] == T(0));
        auto prime_list = prime_work::prime_list(n);
        for (auto p : prime_list)
            if constexpr (int(tar == divisor) ^ int(tp == mobius))
                for (int i = 1; i <= n / p; ++i)
                    if constexpr (tar == divisor) arr[p * i] += arr[i];
                    else arr[i] -= arr[p * i];
            else
                for (int i = n / p; i >= 1; --i)
                    if constexpr (tar == divisor) arr[p * i] -= arr[i];
                    else arr[i] += arr[p * i];
    }
}
