#pragma once

template<typename T, T inf = std::numeric_limits<T>::max()>
struct min_v {
    T val;
    min_v(T _val = inf): val(_val) {}
    min_v operator+(const min_v &rhs) const {
        return min_v(std::min(val, rhs.val));
    }
    friend std::ostream& operator<<(std::ostream& os, const min_v &v) {
        os << v.val;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, min_v &v) {
        is >> v.val;
        return is;
    }
};
