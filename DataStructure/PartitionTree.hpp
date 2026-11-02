#pragma once

#include "Algebra/ValidOperation.hpp"

template <typename T = int, typename Value = void>
class PartitionTree {
private:
    static constexpr bool hasValue = !std::is_void_v<Value>;
    struct Empty {};
    using ValueType = std::conditional_t<hasValue, Value, Empty>;
    static_assert(!hasValue || (Addable<Value, Value> && Subtractable<Value, Value>));
    int n, max_depth;
    std::vector<T> sorted;
    std::vector<std::vector<T>> val;
    std::vector<std::vector<int>> to_l;
    [[no_unique_address]] std::conditional_t<hasValue, std::vector<std::vector<ValueType>>, Empty> sum_l{};
    void build(int d, int l, int r) {
        if (r - l <= 1) return;
        int mid = l + (r - l) / 2;
        T median = sorted[mid];
        int same = mid - l;
        for (int i = l; i < r; ++i)
            if (val[d][i] < median)
                --same;
        int lpos = l, rpos = mid;
        for (int i = l; i < r; ++i) {
            to_l[d][i] = (i == l ? 0 : to_l[d][i - 1]);
            if constexpr (hasValue) sum_l[d][i] = (i == l ? ValueType{} : sum_l[d][i - 1]);
            bool go_left = false;
            if (val[d][i] < median) go_left = true;
            else if (val[d][i] == median && same > 0) go_left = true, --same;
            if (go_left) {
                val[d + 1][lpos++] = val[d][i];
                to_l[d][i]++;
                if constexpr (hasValue) sum_l[d][i] = sum_l[d][i] + val[d][i];
            }
            else val[d + 1][rpos++] = val[d][i];
        }
        build(d + 1, l, mid);
        build(d + 1, mid, r);
    }
    T query_kth(int d, int l, int r, int ql, int qr, int k) const {
        if (r - l <= 1) return val[d][l];
        int mid = l + (r - l) / 2;
        int cnt_prev = (ql == l ? 0 : to_l[d][ql - 1]);
        int cnt_in = to_l[d][qr - 1] - cnt_prev;
        if (k <= cnt_in) {
            int next_l = l + cnt_prev;
            int next_r = l + cnt_prev + cnt_in;
            return query_kth(d + 1, l, mid, next_l, next_r, k);
        }
        else {
            int next_l = mid + (ql - l - cnt_prev);
            int next_r = mid + (qr - l - cnt_prev - cnt_in);
            return query_kth(d + 1, mid, r, next_l, next_r, k - cnt_in);
        }
    }
    ValueType query_sum(int d, int l, int r, int ql, int qr, int k) const requires (hasValue) {
        if (k == 0) return ValueType{};
        if (r - l <= 1) return val[d][l];
        int mid = l + (r - l) / 2;
        int cnt_prev = (ql == l ? 0 : to_l[d][ql - 1]);
        int cnt_in = to_l[d][qr - 1] - cnt_prev;
        if (k <= cnt_in) {
            int next_l = l + cnt_prev;
            int next_r = l + cnt_prev + cnt_in;
            return query_sum(d + 1, l, mid, next_l, next_r, k);
        }
        else {
            ValueType sum_in = ValueType{};
            if constexpr (hasValue) sum_in = sum_l[d][qr - 1] - (ql == l ? ValueType{} : sum_l[d][ql - 1]);
            int next_l = mid + (ql - l - cnt_prev);
            int next_r = mid + (qr - l - cnt_prev - cnt_in);
            return sum_in + query_sum(d + 1, mid, r, next_l, next_r, k - cnt_in);
        }
    }
public:
    PartitionTree() : n(0), max_depth(0) {}
    PartitionTree(const std::vector<T>& a) {
        n = a.size();
        if (n == 0) return;
        max_depth = std::__lg(n) + 2;
        sorted = a;
        std::sort(sorted.begin(), sorted.end());
        val.assign(max_depth, std::vector<T>(n));
        to_l.assign(max_depth, std::vector<int>(n, 0));
        if constexpr (hasValue) sum_l.assign(max_depth, std::vector<ValueType>(n, 0));
        val[0] = a;
        build(0, 0, n);
    }
    T kth_smallest(int ql, int qr, int k) const {
        assert(ql >= 0 && qr <= n && ql < qr);
        assert(k >= 1 && k <= qr - ql);
        return query_kth(0, 0, n, ql, qr, k);
    }
    T kth_largest(int ql, int qr, int k) const {
        int total = qr - ql;
        return kth_smallest(ql, qr, total - k + 1);
    }
    ValueType sum_k_smallest(int ql, int qr, int k) const requires (hasValue) {
        assert(ql >= 0 && qr <= n && ql <= qr);
        if (k <= 0 || ql == qr) return ValueType{};
        k = std::min(k, qr - ql);
        return query_sum(0, 0, n, ql, qr, k);
    }
    ValueType sum_k_largest(int ql, int qr, int k) const requires (hasValue) {
        assert(ql >= 0 && qr <= n && ql <= qr);
        if (k <= 0 || ql == qr) return ValueType{};
        k = std::min(k, qr - ql);
        int total = qr - ql;
        ValueType total_sum = sum_k_smallest(ql, qr, total);
        if (k == total) return total_sum;
        return total_sum - sum_k_smallest(ql, qr, total - k);
    }
};
