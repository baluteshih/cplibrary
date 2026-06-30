#pragma once

#include "Algebra/Field/concept.hpp"

template<typename T, class Allocator = std::allocator<T>>
requires isField<T>
class Vector : public std::vector<T, Allocator> {
    int n() const { return (int)this->size(); }
public:
    Vector(int _n): std::vector<T, Allocator>(_n) {}
    Vector& operator*=(const T &v) {
        for (int i = 0; i < n(); ++i)
            (*this)[i] = (*this)[i] * v;
        return *this;
    }
    Vector& operator/=(const T &v) {
        for (int i = 0; i < n(); ++i)
            (*this)[i] = (*this)[i] / v;
        return *this;
    }
    Vector& operator+=(const Vector &rhs) {
        assert(n() == rhs.n());
        for (int i = 0; i < n(); ++i)
            (*this)[i] = (*this)[i] + rhs[i];
        return *this;
    }
    Vector& operator-=(const Vector &rhs) {
        assert(n() == rhs.n());
        for (int i = 0; i < n(); ++i)
            (*this)[i] = (*this)[i] - rhs[i];
        return *this;
    }
    T operator*(const Vector &rhs) const {
        assert(n() == rhs.n());
        T res = T();
        for (int i = 0; i < n(); ++i)
            res = res + (*this)[i] * rhs[i];
        return res;
    }
    Vector& operator|=(Vector const& rhs) {
        this->insert(this->end(), rhs.begin(), rhs.end());
        return *this;
    }
    Vector operator*(const T &v) const { return Vector(*this) *= v; }
    Vector operator/(const T &v) const { return Vector(*this) /= v; }
    Vector operator+(const Vector &rhs) const { return Vector(*this) += rhs; }
    Vector operator-(const Vector &rhs) const { return Vector(*this) -= rhs; }
    Vector operator|(Vector const& rhs) const { return Vector(*this) |= rhs; }
    int find_pivot() {
        int pivot = 0;
        while (pivot < n() && (*this)[pivot] == T(0)) ++pivot;
        return pivot;
    }
};
