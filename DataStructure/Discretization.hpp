#pragma once

template<typename T>
class Discretization {
    std::vector<T> vals;
    static std::vector<T> sort_and_unique(std::vector<T> _vals) {
        std::ranges::sort(_vals);
        _vals.erase(std::ranges::unique(_vals).begin(), _vals.end());
        return _vals;
    }
public:
    int idx(int x) {
        auto it = ranges::lower_bound(vals, x);
        if (it == vals.end() || *it != x) return -1;
        return it - vals.begin();
    }
    int safe_idx(int x) {
        int res = idx(x);
        assert(res != -1);
        return res;
    }
    Discretization(const std::vector<T> &_vals): vals(sort_and_unique(_vals)) {}
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
};
