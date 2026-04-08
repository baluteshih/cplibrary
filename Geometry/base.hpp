#pragma once
    
template <typename T>
using DefaultFloat = std::conditional_t<std::is_floating_point_v<T>, T, double>;

template <typename T>
constexpr T get_default_eps() {
    if constexpr (std::is_same_v<T, float>)
        return T(1e-6);
    else if constexpr (std::is_same_v<T, double>)
        return T(1e-9);
    else if constexpr (std::is_same_v<T, long double>)
        return T(1e-12);
    else
        return T(0); 
}

template <typename T, T eps = get_default_eps<T>()>
struct Geometry {
    static int sign(T x) {
        if constexpr (std::is_floating_point_v<T>) {
            return (x > eps) - (x < -eps); 
        }
        else {
            return (x > 0) - (x < 0);
        }
    }
    static int cmp(T a, T b) {
        return sign(a - b);
    }
};

template<typename T, T eps = get_default_eps<T>(), typename MulT = T>
struct Pt : Geometry<T, eps> {
    using value_type = T;
    using Geometry<MulT, eps>::sign;
    using Geometry<MulT, eps>::cmp;
    static constexpr T eps_val = eps;
    T x = 0, y = 0;
    Pt() : x(0), y(0) {}
    Pt(T x_, T y_) : x(x_), y(y_) {}
    friend istream& operator>>(istream &is, Pt &p) { return is >> p.x >> p.y; }
    friend ostream& operator<<(ostream &os, const Pt &p) { return os << p.x << ' ' << p.y; }
    friend bool operator==(const Pt &a, const Pt &b) { 
        return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0; 
    }
    friend bool operator!=(const Pt &a, const Pt &b) { return !(a == b); }
    Pt operator-() { return Pt(-x, -y); }
    Pt& operator+=(const Pt &a) {
        x += a.x, y += a.y;
        return *this;
    }
    Pt& operator-=(const Pt &a) {
        x -= a.x, y -= a.y;
        return *this;
    }
    Pt& operator*=(T d) {
        x *= d, y *= d;
        return *this;
    }
    Pt& operator/=(T d) {
        x /= d, y /= d;
        return *this;
    }
    friend Pt operator+(const Pt &a, const Pt &b) { return Pt(a) += b; }
    friend Pt operator-(const Pt &a, const Pt &b) { return Pt(a) -= b; }
    friend Pt operator*(const Pt &a, T d) { return Pt(a) *= d; }
    friend Pt operator/(const Pt &a, T d) { return Pt(a) /= d; }
    friend bool operator<(const Pt &a, const Pt &b) {
        int sx = cmp(a.x, b.x);
        return sx != 0 ? sx == -1 : cmp(a.y, b.y) == -1;
    }
    friend bool operator>(const Pt &a, const Pt &b) { return b < a; }
    friend bool operator<=(const Pt &a, const Pt &b) { return !(b < a); }
    friend bool operator>=(const Pt &a, const Pt &b) { return !(a < b); }
    template <typename U, U _eps, typename _MulT>
    Pt(const Pt<U, _eps, _MulT>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
    friend MulT dot(const Pt &a, const Pt &b) {
        return MulT(a.x) * MulT(b.x) + MulT(a.y) * MulT(b.y);
    }
    friend MulT cross(const Pt &a, const Pt &b) {
        return MulT(a.x) * MulT(b.y) - MulT(a.y) * MulT(b.x);
    }
    friend MulT square(const Pt &a) {
        return dot(a, a);
    }
    friend MulT dist2(const Pt &a, const Pt &b) {
        return square(a - b);
    }
    template <typename Ret = DefaultFloat<T>>
    friend Ret length(const Pt &a) {
        return std::sqrt(static_cast<Ret>(square(a))); 
    }
    template <typename Ret = DefaultFloat<T>>
    friend Ret dist(const Pt &a, const Pt &b) {
        return length<Ret>(a - b); 
    }
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend Pt<Ret, _eps, _MulT> normal(const Pt &a) {
        Ret len = length(a);
        return Pt<Ret, _eps, _MulT>(a) / len;
    }
    friend MulT cross(const Pt &p, const Pt &a, const Pt &b) {
        return cross(a - p, b - p);
    }
    // 1 if on a->b's left
    friend int side(const Pt &p, const Pt &a, const Pt &b) {
        return sign(cross(p, a, b));
    }
    friend bool collinear(const Pt &a, const Pt &b, const Pt &c) {
        return side(a, b, c) == 0;
    }
    friend bool up(const Pt &a) { 
        return sign(a.y) > 0 || (sign(a.y) == 0 && sign(a.x) > 0);
    }
    // 3 colinear? please remember to remove (0, 0)
    friend bool polar(const Pt &a, const Pt &b) {
        bool ua = up(a), ub = up(b);
        return ua != ub ? ua : sign(cross(a, b)) == 1;
    }
    friend bool polar(const Pt &a, const Pt &b, const Pt &base) {
        bool ua = sign(cross(base, a)) > 0 || sameDirection(base, a);
        bool ub = sign(cross(base, b)) > 0 || sameDirection(base, b);
        return ua != ub ? ua : sign(cross(a, b)) == 1;
    }
    friend bool parallel(const Pt &a, const Pt &b) {
        return sign(cross(a, b)) == 0;
    }
    friend bool sameDirection(const Pt &a, const Pt &b) {
        return sign(cross(a, b)) == 0 && sign(dot(a, b)) == 1;
    }
    friend Pt rotate90(const Pt &p) {
        return {-p.y, p.x};
    }
    friend Pt rotate270(const Pt &p) {
        return rotate90(-p);
    }
    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>
    friend Pt<Ret, _eps, _MulT> rotate(const Pt &p, Ret ang) {
        return {Ret(p.x) * std::cos(ang) - Ret(p.y) * std::sin(ang), Ret(p.x) * std::sin(ang) + Ret(p.y) * std::cos(ang)};
    }
    template <typename Ret = DefaultFloat<T>>
    friend Ret angle(const Pt &p) {
        return std::atan2(Ret(p.y), Ret(p.x));
    }
    friend bool _betweenAngle(const Pt &o, const Pt &a, const Pt &b, const Pt &p, int strict) {
        return side(o, a, p) >= strict && side(o, p, b) >= strict;
    }
    // whether op located between the counter-clockwise interval of oa and ob 
    friend bool betweenAngle(const Pt &o, const Pt &a, const Pt &b, const Pt &p, int strict) {
        if (side(o, a, b) >= 0) return _betweenAngle(o, a, b, p, strict);
        return !_betweenAngle(o, b, a, p, !strict);
    }
};
