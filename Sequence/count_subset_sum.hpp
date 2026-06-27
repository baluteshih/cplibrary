#pragma once

#include "Enumerate/subset_enumerate.hpp"

// [lft, rgt)
template<typename T>
long long count_subset_sum(const std::vector<T> &arr, T lft, T rgt) {
    int n = arr.size();
    if (n == 0) return lft <= 0 && 0 < rgt;
    if (n == 1) return (lft <= 0 && 0 < rgt) + (lft <= arr[0] && arr[0] < rgt);
    auto lset = subset_enumerate(std::vector<T>(arr.begin(), arr.begin() + n / 2));
    auto rset = subset_enumerate(std::vector<T>(arr.begin() + n / 2, arr.end()));
    std::ranges::sort(lset, std::greater<T>()), std::ranges::sort(rset);
    auto count = [&](T gap) -> long long {
        long long res = 0;
        for (int i = 0; auto &v : lset) {
            while (i < int(rset.size()) && v + rset[i] < gap) ++i;
            res += i;
        }
        return res;
    };
    long long res = 0;
    if (lset[0] + rset.back() >= rgt) res += count(rgt);
    else res += (long long)lset.size() * (long long)rset.size();
    if (lset.back() + rset[0] < lft) res -= count(lft);
    return res;
}

// [lft, rgt)
template<typename T>
std::vector<long long> count_subset_sum_with_count(const std::vector<T> &arr, T lft, T rgt) {
    int n = arr.size();
    if (n == 0) return {lft <= 0 && 0 < rgt};
    if (n == 1) return {(lft <= 0 && 0 < rgt), (lft <= arr[0] && arr[0] < rgt)};
    struct Val {
        T v;
        int cnt;
        Val(T _v, int _cnt = 1) : v(_v), cnt(_cnt) {}
        Val() : Val(0, 0) {} 
        Val operator+(const Val &rhs) const { return Val(v + rhs.v, cnt + rhs.cnt); }
        auto operator<=>(const Val&) const = default;
    };
    auto lset = subset_enumerate(std::vector<Val>(arr.begin(), arr.begin() + n / 2));
    auto rset = subset_enumerate(std::vector<Val>(arr.begin() + n / 2, arr.end()));
    std::ranges::sort(lset, std::greater<Val>()), std::ranges::sort(rset);
    auto count = [&](T gap) -> std::vector<long long> {
        std::vector<long long> res(n + 1), cur(n + 1);
        for (int i = 0; auto &v : lset) {
            while (i < int(rset.size()) && v.v + rset[i].v < gap) ++cur[rset[i++].cnt];
            for (int j = 0; j <= n; ++j) res[v.cnt + j] += cur[j];
        }
        return res;
    };
    std::vector<long long> res(n + 1);
    if (lset[0] + rset.back() >= rgt) res = count(rgt); 
    else {
        std::vector<long long> lcnt(n + 1), rcnt(n + 1);
        for (auto &v : lset) ++lcnt[v.cnt];
        for (auto &v : rset) ++rcnt[v.cnt];
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                res[i + j] += lcnt[i] * rcnt[j];
    }
    if (lset.back() + rset[0] < lft) {
        auto minus = count(lft);
        for (int i = 0; i <= n; ++i) res[i] -= minus[i];
    }
    return res;
}
