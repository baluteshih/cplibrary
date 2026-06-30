#pragma once

template<typename T>
struct min_plus {
    T a;
    min_plus(T _a = std::numeric_limits<T>::max() / 2): a(std::min(_a, std::numeric_limits<T>::max() / 2)) {}
    min_plus operator+(const min_plus &rhs) const {
        return min_plus(std::min(a, rhs.a));
    }
    min_plus operator*(const min_plus &rhs) const {
        return min_plus(a + rhs.a);
    }
    auto operator<=>(const min_plus &) const = default;
    friend ostream& operator<<(ostream& os, const min_plus &v) {
        os << v.a;
        return os;
    }
};
