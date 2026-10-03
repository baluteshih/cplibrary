#pragma once

template<typename T, typename size_type = int>
struct sum_and_size {
    T val;
    size_type sz;
    sum_and_size(T _val, size_type _sz) : val(_val), sz(_sz) {}
    sum_and_size(T _val) : sum_and_size(_val, 1) {}
    sum_and_size() : sum_and_size(0, 0) {}
    sum_and_size operator+(const sum_and_size &rhs) const {
        return sum_and_size(val + rhs.val, sz + rhs.sz);
    }
    sum_and_size operator-(const sum_and_size &rhs) const {
        return sum_and_size(val - rhs.val, sz - rhs.sz);
    }
    friend std::ostream& operator<<(std::ostream& os, const sum_and_size &v) {
        os << v.val;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, sum_and_size &v) {
        is >> v.val;
        v.sz = 1;
        return is;
    }
};
