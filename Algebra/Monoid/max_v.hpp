#pragma once

template<typename T, T inf = std::numeric_limits<T>::max()>
struct max_v {
    T val;
    max_v(T _val = -inf): val(_val) {}
    max_v operator+(const max_v &rhs) const {
        return max_v(std::max(val, rhs.val));
    }
    friend std::ostream& operator<<(std::ostream& os, const max_v &v) {
        os << v.val;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, max_v &v) {
        is >> v.val;
        return is;
    }
};
