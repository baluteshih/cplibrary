#pragma once

template<typename T>
struct mul_v {
    T val;
    mul_v(T _val = 1): val(_val) {}
    mul_v operator+(const mul_v &rhs) const {
        return mul_v(val * rhs.val);
    }
    friend std::ostream& operator<<(std::ostream& os, const mul_v &v) {
        os << v.val;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, mul_v &v) {
        is >> v.val;
        return is;
    }
    operator T() const {
        return val;
    }
};
