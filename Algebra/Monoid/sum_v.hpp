#pragma once

template<typename T>
struct sum_v {
    T val;
    sum_v(T _val = 0): val(_val) {}
    sum_v operator+(const sum_v &rhs) const {
        return sum_v(val + rhs.val);
    }
    friend std::ostream& operator<<(std::ostream& os, const sum_v &v) {
        os << v.val;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, sum_v &v) {
        is >> v.val;
        return is;
    }
    operator T() const {
        return val;
    }
};
