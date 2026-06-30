#pragma once

template<typename T>
class Discretization {
    std::vector<T> vals;
    static std::vector<T> sort_and_unique(std::ranges::range auto &&_vals) {
        std::vector<T> res;
        std::ranges::copy(_vals, std::back_inserter(res));
        std::ranges::sort(res);
        auto [first, last] = std::ranges::unique(res);
        res.erase(first, last);
        return res;
    }
public:
    int idx(T x) {
        auto it = std::ranges::lower_bound(vals, x);
        if (it == vals.end() || *it != x) return -1;
        return it - vals.begin();
    }
    int safe_idx(T x) {
        int res = idx(x);
        assert(res != -1);
        return res;
    }
    Discretization(std::ranges::range auto &&_vals) : vals(sort_and_unique(std::forward<decltype(_vals)>(_vals))) {}
    int left_close(T x) {
        return std::ranges::lower_bound(vals, x) - vals.begin();
    }
    int left_open(T x) {
        return std::ranges::upper_bound(vals, x) - vals.begin() - 1;
    }
    int right_close(T x) {
        return std::ranges::upper_bound(vals, x) - vals.begin() - 1;
    }
    int right_open(T x) {
        return std::ranges::lower_bound(vals, x) - vals.begin();
    }
    const T& operator[](size_t index) const {
        return vals[index];
    }
    int size() {
        return vals.size();
    }
};

template <std::ranges::range R>
Discretization(R&&) -> Discretization<std::ranges::range_value_t<R>>;
