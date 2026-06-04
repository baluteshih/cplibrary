#pragma once

namespace FracFmt {
    inline const char* sep = "/";
    inline bool omit_one = true;
}

template<typename T, bool use_gcd = false>
struct Fraction {
    T n, d;
    
    void simplify() {
        if constexpr (use_gcd) {
            T t = std::gcd(n, d);
            n /= t, d /= t;
        }
        if (d < T(0)) n = -n, d = -d;
    }
    
    Fraction(const T &_n = 0, const T &_d = 1): n(_n), d(_d) {
        simplify();
    }
    
    Fraction operator+() const { return *this; }
    Fraction operator-() const { return Fraction(-n, d); }
    
    Fraction& operator+=(const Fraction &b) {
        std::tie(n, d) = std::make_pair(n * b.d + b.n * d, d * b.d);
        simplify();
        return *this; 
    }
    Fraction& operator-=(const Fraction &b) {
        std::tie(n, d) = std::make_pair(n * b.d - b.n * d, d * b.d);
        simplify();
        return *this;
    }
    Fraction& operator*=(const Fraction &b) {
        std::tie(n, d) = std::make_pair(n * b.n, d * b.d);
        simplify();
        return *this;
    }
    Fraction& operator/=(const Fraction &b) {
        std::tie(n, d) = std::make_pair(n * b.d, d * b.n);
        simplify();
        return *this;
    }
    Fraction simplified() const {
        T t = std::gcd(n, d);
        return Fraction(n / t, d / t);
    }
    
    friend Fraction operator+(const Fraction &lhs, const Fraction &rhs) { 
        return Fraction(lhs) += rhs; 
    }
    friend Fraction operator-(const Fraction &lhs, const Fraction &rhs) { 
        return Fraction(lhs) -= rhs; 
    }
    friend Fraction operator*(const Fraction &lhs, const Fraction &rhs) { 
        return Fraction(lhs) *= rhs; 
    }
    friend Fraction operator/(const Fraction &lhs, const Fraction &rhs) { 
        return Fraction(lhs) /= rhs; 
    }
    
    friend bool operator==(const Fraction &lhs, const Fraction &rhs) {
        if constexpr (use_gcd) return lhs.n == rhs.n && lhs.d == rhs.d;
        else return lhs.n * rhs.d == rhs.n * lhs.d;
    }
    friend bool operator!=(const Fraction &lhs, const Fraction &rhs) {
        return !(lhs == rhs);
    }
    friend std::strong_ordering operator<=>(const Fraction &lhs, const Fraction &rhs) {
        return lhs.n * rhs.d <=> rhs.n * lhs.d;
    }
    
    T val() const { return n / d; }
    T floor() const { return n / d - (n % d && n < 0); }
    T ceil() const { return n / d + (n % d && n >= 0); }
    
    friend std::ostream& operator<<(std::ostream& os, const Fraction &v) {
        os << v.n;
        if (!FracFmt::omit_one || v.d != T(1))
            os << FracFmt::sep << v.d;
        return os;
    }
};
