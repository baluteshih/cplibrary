#pragma once

template<typename T>
struct linear_transform_tag {
    T a, b;
    linear_transform_tag(T _a = 1, T _b = 0): a(_a), b(_b) {}
    linear_transform_tag operator+(const linear_transform_tag &rhs) const {
        return linear_transform_tag(a * rhs.a, rhs.a * b + rhs.b);
    }
};
