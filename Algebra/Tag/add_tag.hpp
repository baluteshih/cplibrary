#pragma once

template<typename T>
struct add_tag {
    T a;
    add_tag(T _a = 0): a(_a) {}
    add_tag operator+(const add_tag &rhs) const {
        return add_tag(a + rhs.a);
    }
    add_tag operator-() const {
        return add_tag(-a);
    }
};
