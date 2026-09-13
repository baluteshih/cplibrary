#pragma once

template<typename T>
class Discretization : public std::vector<T> {
public:
    using std::vector<T>::vector;
    virtual void build() {
        std::ranges::sort(*this);
        auto [first, last] = std::ranges::unique(*this);
        this->erase(first, last);
    }
    int idx(T x) {
        auto it = std::ranges::lower_bound(*this, x);
        if (it == this->end() || *it != x) return -1;
        return it - this->begin();
    }
    int safe_idx(T x) {
        int res = idx(x);
        assert(res != -1);
        return res;
    }
    int left_close(T x) {
        return std::ranges::lower_bound(*this, x) - this->begin();
    }
    int left_open(T x) {
        return std::ranges::upper_bound(*this, x) - this->begin() - 1;
    }
    int right_close(T x) {
        return std::ranges::upper_bound(*this, x) - this->begin() - 1;
    }
    int right_open(T x) {
        return std::ranges::lower_bound(*this, x) - this->begin();
    }
};
