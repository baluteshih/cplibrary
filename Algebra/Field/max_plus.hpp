#pragma once

template<typename T>
struct max_plus {
    T a;
    max_plus(T _a = -std::numeric_limits<T>::max() / 2): a(std::max(_a, -std::numeric_limits<T>::max() / 2)) {}
    max_plus operator+(const max_plus &rhs) const {
        return max_plus(std::max(a, rhs.a));
    }
    max_plus operator*(const max_plus &rhs) const {
        return max_plus(a + rhs.a);
    }
    auto operator<=>(const max_plus &) const = default;
    friend ostream& operator<<(ostream& os, const max_plus &v) {
        os << v.a;
        return os;
    }
};
