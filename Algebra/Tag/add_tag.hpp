#pragma once

template<typename T>
struct add_tag {
    T a;
    add_tag(T _a = 0): a(_a) {}
    add_tag& operator+=(const add_tag &rhs) {
        a += rhs.a;
        return *this;
    }
    add_tag operator-() const {
        return add_tag(-a);
    }
    friend std::ostream& operator<<(std::ostream& os, const add_tag &v) {
        os << v.a;
        return os;
    }
};
