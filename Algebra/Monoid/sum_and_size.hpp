#pragma once

template<typename T, typename size_type = int>
struct sum_and_size {
    T val;
    size_type sz;
    sum_and_size(T _val = 0, size_type _sz = 0): val(_val), sz(_sz) {}
    sum_and_size operator+(const sum_and_size &rhs) const {
        return sum_and_size(val + rhs.val, sz + rhs.sz);
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
