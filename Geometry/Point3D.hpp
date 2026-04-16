#pragma once
    
#include "Geometry/base.hpp"

template<typename T, T eps = get_default_eps<T>(), typename MulT = T>
struct Pt3 : Geometry<T, eps> {
    using value_type = T;
    using Geometry<MulT, eps>::sign;
    using Geometry<MulT, eps>::cmp;
    static constexpr T eps_val = eps;
    T x = 0, y = 0, z = 0;
    Pt3() : x(0), y(0), z(0) {}
    Pt3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
    friend istream& operator>>(istream &is, Pt3 &p) { return is >> p.x >> p.y >> p.z; }
    friend ostream& operator<<(ostream &os, const Pt3 &p) { return os << p.x << ' ' << p.y << ' ' << p.z; }
    friend bool operator==(const Pt3 &a, const Pt3 &b) {
        return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0 && cmp(a.z, b.z) == 0; 
    }
    friend bool operator!=(const Pt3 &a, const Pt3 &b) { return !(a == b); }
    Pt3 operator-() { return Pt(-x, -y, -z); }
    Pt3& operator+=(const Pt3 &a) {
        x += a.x, y += a.y, z += a.z;
        return *this;
    }
    Pt3& operator-=(const Pt3 &a) {
        x -= a.x, y -= a.y, z -= a.z;
        return *this;
    }
    Pt3& operator*=(T d) {
        x *= d, y *= d, z *= d;
        return *this;
    }
    Pt3& operator/=(T d) {
        x /= d, y /= d, z /= d;
        return *this;
    }
    friend Pt3 operator+(const Pt3 &a, const Pt3 &b) { return Pt3(a) += b; }
    friend Pt3 operator-(const Pt3 &a, const Pt3 &b) { return Pt3(a) -= b; }
    friend Pt3 operator*(const Pt3 &a, T d) { return Pt3(a) *= d; }
    friend Pt3 operator/(const Pt3 &a, T d) { return Pt3(a) /= d; }
    friend bool operator<(const Pt3 &a, const Pt3 &b) {
        int sx = cmp(a.x, b.x);
        if (sx != 0) return sx == -1;
        int sy = cmp(a.y, b.y);
        return sy != 0 ? sy == -1 : cmp(a.z, b.z) == -1;
    }
    friend bool operator>(const Pt3 &a, const Pt3 &b) { return b < a; }
    friend bool operator<=(const Pt3 &a, const Pt3 &b) { return !(b < a); }
    friend bool operator>=(const Pt3 &a, const Pt3 &b) { return !(a < b); }
    template <typename U, U _eps, typename _MulT>
    Pt3(const Pt3<U, _eps, _MulT>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {}
    template <typename U, U _eps, typename _MulT>
    Pt3(const Pt<U, _eps, _MulT>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(square(other))) {}
    friend MulT dot(const Pt3 &a, const Pt3 &b) {
        return MulT(a.x) * MulT(b.x) + MulT(a.y) * MulT(b.y) + MulT(a.z) * MulT(b.z);
    }
    friend Pt3 cross(const Pt3 &a, const Pt3 &b) {
        return Pt3(MulT(a.y) * MulT(b.z) - MulT(a.z) * MulT(b.y), MulT(a.z) * MulT(b.x) - MulT(a.x) * MulT(b.z), MulT(a.x) * MulT(b.y) - MulT(a.y) * MulT(b.x));
    }
    friend MulT square(const Pt3 &a) {
        return dot(a, a);
    }
    friend MulT dist2(const Pt3 &a, const Pt3 &b) {
        return square(a - b);
    }
    template <typename Ret = DefaultFloat<T>>
    friend Ret length(const Pt3 &a) {
        return std::sqrt(static_cast<Ret>(square(a))); 
    }
    template <typename Ret = DefaultFloat<T>>
    friend Ret dist(const Pt3 &a, const Pt3 &b) {
        return length<Ret>(a - b); 
    }
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend Pt3<Ret, _eps, _MulT> normal(const Pt3 &a) {
        Ret len = length(a);
        return Pt3<Ret, _eps, _MulT>(a) / len;
    }
    friend Pt3 cross(const Pt3 &p, const Pt3 &a, const Pt3 &b) {
        return cross(a - p, b - p);
    }
    template <typename Ret = DefaultFloat<T>>
    friend Ret area(const Pt3 &a, const Pt3 &b, const Pt3 &c) {
        return length<Ret>(cross(a, b, c));
    }
    friend MulT volume(const Pt3 &a, const Pt3 &b, const Pt3 &c, const Pt3 &d) {
        return dot(cross(a, b, c), d - a);
    }
    // Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
    template <typename Ret = DefaultFloat<T>>
    friend Ret phi(const Pt3 &p) {
        return std::atan2(Ret(p.y), Ret(p.x));
    }
    // Zenith angle (latitude) to the z-axis in interval [0, pi]
    template <typename Ret = DefaultFloat<T>>
    friend Ret theta(const Pt3 &p) {
        return std::atan2(std::sqrt(Ret(p.x) * Ret(p.x) + Ret(p.y) * Ret(p.y)), Ret(p.z));
    }
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend Pt3 masscenter(const Pt3 &a, const Pt3 &b, const Pt3 &c, const Pt3 &d) {
        return Pt3<Ret, _eps, _MulT>(a + b + c + d) / Ret(4);
    }
    // proj. u to the plane of a, b, and c
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend Pt<Ret, _eps, _MulT> proj(const Pt3 &a, const Pt3 &b, const Pt3 &c, const Pt3 &u) {
        Pt3<Ret, _eps, _MulT> e1 = b - a;
        Pt3<Ret, _eps, _MulT> e2 = c - a;
        e1 = e1 / length<Ret>(e1);
        e2 = e2 - e1 * Ret(dot(e2, e1));
        e2 = e2 / length<Ret>(e2);
        Pt3<Ret, _eps, _MulT> p = u - a;
        return Pt<Ret, _eps, _MulT>(Ret(dot(p, e1)), Ret(dot(p, e2)));
    }
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend Pt3<Ret, _eps, _MulT> rotate_around(const Pt3 &p, Ret angle, const Pt3 &axis) {
        Ret s = std::sin(angle), c = std::cos(angle);
        Pt3<Ret, _eps, _MulT> u = Pt3<Ret, _eps, _MulT>(axis) / length<Ret>(axis);
        return u * Ret(dot(u, p)) * (1 - c) + Pt3<Ret, _eps, _MulT>(p) * c + cross(u, Pt3<Ret, _eps, _MulT>(p)) * s;
    }
};
