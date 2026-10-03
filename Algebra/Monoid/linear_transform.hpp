#pragma once

template<typename T>
struct linear_transform {
    T a, b;
    linear_transform(T _a = 1, T _b = 0) : a(_a), b(_b) {}
    linear_transform operator+(const linear_transform &rhs) const {
        return linear_transform(a * rhs.a, rhs.a * b + rhs.b);
    }
    T eval(T x) {
        return a * x + b;
    }
    friend std::istream& operator>>(std::istream& is, linear_transform &v) {
        is >> v.a >> v.b;
        return is;
    }
};
