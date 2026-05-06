---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Geometry/base.hpp
    title: Geometry/base.hpp
  _extendedRequiredBy:
  - icon: ':x:'
    path: Geometry/convexHull3D.hpp
    title: Geometry/convexHull3D.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/3_qoj/6445.test.cpp
    title: test/3_qoj/6445.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Geometry/Point3D.hpp\"\n    \n#line 2 \"Geometry/base.hpp\"\
    \n    \ntemplate <typename T>\nusing DefaultFloat = std::conditional_t<std::is_floating_point_v<T>,\
    \ T, double>;\n\ntemplate <typename T>\nconstexpr T get_default_eps() {\n    if\
    \ constexpr (std::is_same_v<T, float>)\n        return T(1e-6);\n    else if constexpr\
    \ (std::is_same_v<T, double>)\n        return T(1e-9);\n    else if constexpr\
    \ (std::is_same_v<T, long double>)\n        return T(1e-12);\n    else\n     \
    \   return T(0); \n}\n\ntemplate <typename T, T eps = get_default_eps<T>()>\n\
    struct Geometry {\n    static int sign(T x) {\n        if constexpr (std::is_floating_point_v<T>)\
    \ {\n            return (x > eps) - (x < -eps); \n        }\n        else {\n\
    \            return (x > 0) - (x < 0);\n        }\n    }\n    static int cmp(T\
    \ a, T b) {\n        return sign(a - b);\n    }\n};\n\ntemplate<typename T, T\
    \ eps = get_default_eps<T>(), typename MulT = T>\nstruct Pt : Geometry<T, eps>\
    \ {\n    using value_type = T;\n    using Geometry<MulT, eps>::sign;\n    using\
    \ Geometry<MulT, eps>::cmp;\n    static constexpr T eps_val = eps;\n    T x =\
    \ 0, y = 0;\n    Pt() : x(0), y(0) {}\n    Pt(T x_, T y_) : x(x_), y(y_) {}\n\
    \    friend istream& operator>>(istream &is, Pt &p) { return is >> p.x >> p.y;\
    \ }\n    friend ostream& operator<<(ostream &os, const Pt &p) { return os << p.x\
    \ << ' ' << p.y; }\n    friend bool operator==(const Pt &a, const Pt &b) { \n\
    \        return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0; \n    }\n    friend\
    \ bool operator!=(const Pt &a, const Pt &b) { return !(a == b); }\n    Pt operator-()\
    \ { return Pt(-x, -y); }\n    Pt& operator+=(const Pt &a) {\n        x += a.x,\
    \ y += a.y;\n        return *this;\n    }\n    Pt& operator-=(const Pt &a) {\n\
    \        x -= a.x, y -= a.y;\n        return *this;\n    }\n    Pt& operator*=(T\
    \ d) {\n        x *= d, y *= d;\n        return *this;\n    }\n    Pt& operator/=(T\
    \ d) {\n        x /= d, y /= d;\n        return *this;\n    }\n    friend Pt operator+(const\
    \ Pt &a, const Pt &b) { return Pt(a) += b; }\n    friend Pt operator-(const Pt\
    \ &a, const Pt &b) { return Pt(a) -= b; }\n    friend Pt operator*(const Pt &a,\
    \ T d) { return Pt(a) *= d; }\n    friend Pt operator/(const Pt &a, T d) { return\
    \ Pt(a) /= d; }\n    friend bool operator<(const Pt &a, const Pt &b) {\n     \
    \   int sx = cmp(a.x, b.x);\n        return sx != 0 ? sx == -1 : cmp(a.y, b.y)\
    \ == -1;\n    }\n    friend bool operator>(const Pt &a, const Pt &b) { return\
    \ b < a; }\n    friend bool operator<=(const Pt &a, const Pt &b) { return !(b\
    \ < a); }\n    friend bool operator>=(const Pt &a, const Pt &b) { return !(a <\
    \ b); }\n    template <typename U, U _eps, typename _MulT>\n    Pt(const Pt<U,\
    \ _eps, _MulT>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))\
    \ {}\n    friend MulT dot(const Pt &a, const Pt &b) {\n        return MulT(a.x)\
    \ * MulT(b.x) + MulT(a.y) * MulT(b.y);\n    }\n    friend MulT cross(const Pt\
    \ &a, const Pt &b) {\n        return MulT(a.x) * MulT(b.y) - MulT(a.y) * MulT(b.x);\n\
    \    }\n    friend MulT square(const Pt &a) {\n        return dot(a, a);\n   \
    \ }\n    friend MulT dist2(const Pt &a, const Pt &b) {\n        return square(a\
    \ - b);\n    }\n    template <typename Ret = DefaultFloat<T>>\n    friend Ret\
    \ length(const Pt &a) {\n        return std::sqrt(static_cast<Ret>(square(a)));\
    \ \n    }\n    template <typename Ret = DefaultFloat<T>>\n    friend Ret dist(const\
    \ Pt &a, const Pt &b) {\n        return length<Ret>(a - b); \n    }\n    template\
    \ <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(),\
    \ typename _MulT = Ret>\n    friend Pt<Ret, _eps, _MulT> normal(const Pt &a) {\n\
    \        Ret len = length(a);\n        return Pt<Ret, _eps, _MulT>(a) / len;\n\
    \    }\n    friend MulT cross(const Pt &p, const Pt &a, const Pt &b) {\n     \
    \   return cross(a - p, b - p);\n    }\n    // 1 if on a->b's left\n    friend\
    \ int side(const Pt &p, const Pt &a, const Pt &b) {\n        return sign(cross(p,\
    \ a, b));\n    }\n    friend bool collinear(const Pt &a, const Pt &b, const Pt\
    \ &c) {\n        return side(a, b, c) == 0;\n    }\n    friend bool up(const Pt\
    \ &a) { \n        return sign(a.y) > 0 || (sign(a.y) == 0 && sign(a.x) > 0);\n\
    \    }\n    // 3 colinear? please remember to remove (0, 0)\n    friend bool polar(const\
    \ Pt &a, const Pt &b) {\n        bool ua = up(a), ub = up(b);\n        return\
    \ ua != ub ? ua : sign(cross(a, b)) == 1;\n    }\n    friend bool polar(const\
    \ Pt &a, const Pt &b, const Pt &base) {\n        bool ua = sign(cross(base, a))\
    \ > 0 || sameDirection(base, a);\n        bool ub = sign(cross(base, b)) > 0 ||\
    \ sameDirection(base, b);\n        return ua != ub ? ua : sign(cross(a, b)) ==\
    \ 1;\n    }\n    friend bool parallel(const Pt &a, const Pt &b) {\n        return\
    \ sign(cross(a, b)) == 0;\n    }\n    friend bool sameDirection(const Pt &a, const\
    \ Pt &b) {\n        return sign(cross(a, b)) == 0 && sign(dot(a, b)) == 1;\n \
    \   }\n    friend Pt rotate90(const Pt &p) {\n        return {-p.y, p.x};\n  \
    \  }\n    friend Pt rotate270(const Pt &p) {\n        return rotate90(-p);\n \
    \   }\n    template <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T,\
    \ Ret> ? eps : get_default_eps<Ret>(), typename _MulT = Ret>\n    friend Pt<Ret,\
    \ _eps, _MulT> rotate(const Pt &p, Ret ang) {\n        return {Ret(p.x) * std::cos(ang)\
    \ - Ret(p.y) * std::sin(ang), Ret(p.x) * std::sin(ang) + Ret(p.y) * std::cos(ang)};\n\
    \    }\n    template <typename Ret = DefaultFloat<T>>\n    friend Ret angle(const\
    \ Pt &p) {\n        return std::atan2(Ret(p.y), Ret(p.x));\n    }\n    friend\
    \ bool _betweenAngle(const Pt &o, const Pt &a, const Pt &b, const Pt &p, int strict)\
    \ {\n        return side(o, a, p) >= strict && side(o, p, b) >= strict;\n    }\n\
    \    // whether op located between the counter-clockwise interval of oa and ob\
    \ \n    friend bool betweenAngle(const Pt &o, const Pt &a, const Pt &b, const\
    \ Pt &p, int strict) {\n        if (side(o, a, b) >= 0) return _betweenAngle(o,\
    \ a, b, p, strict);\n        return !_betweenAngle(o, b, a, p, !strict);\n   \
    \ }\n};\n#line 4 \"Geometry/Point3D.hpp\"\n\ntemplate<typename T, T eps = get_default_eps<T>(),\
    \ typename MulT = T>\nstruct Pt3 : Geometry<T, eps> {\n    using value_type =\
    \ T;\n    using Geometry<MulT, eps>::sign;\n    using Geometry<MulT, eps>::cmp;\n\
    \    static constexpr T eps_val = eps;\n    T x = 0, y = 0, z = 0;\n    Pt3()\
    \ : x(0), y(0), z(0) {}\n    Pt3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}\n\
    \    friend istream& operator>>(istream &is, Pt3 &p) { return is >> p.x >> p.y\
    \ >> p.z; }\n    friend ostream& operator<<(ostream &os, const Pt3 &p) { return\
    \ os << p.x << ' ' << p.y << ' ' << p.z; }\n    friend bool operator==(const Pt3\
    \ &a, const Pt3 &b) {\n        return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0\
    \ && cmp(a.z, b.z) == 0; \n    }\n    friend bool operator!=(const Pt3 &a, const\
    \ Pt3 &b) { return !(a == b); }\n    Pt3 operator-() { return Pt(-x, -y, -z);\
    \ }\n    Pt3& operator+=(const Pt3 &a) {\n        x += a.x, y += a.y, z += a.z;\n\
    \        return *this;\n    }\n    Pt3& operator-=(const Pt3 &a) {\n        x\
    \ -= a.x, y -= a.y, z -= a.z;\n        return *this;\n    }\n    Pt3& operator*=(T\
    \ d) {\n        x *= d, y *= d, z *= d;\n        return *this;\n    }\n    Pt3&\
    \ operator/=(T d) {\n        x /= d, y /= d, z /= d;\n        return *this;\n\
    \    }\n    friend Pt3 operator+(const Pt3 &a, const Pt3 &b) { return Pt3(a) +=\
    \ b; }\n    friend Pt3 operator-(const Pt3 &a, const Pt3 &b) { return Pt3(a) -=\
    \ b; }\n    friend Pt3 operator*(const Pt3 &a, T d) { return Pt3(a) *= d; }\n\
    \    friend Pt3 operator/(const Pt3 &a, T d) { return Pt3(a) /= d; }\n    friend\
    \ bool operator<(const Pt3 &a, const Pt3 &b) {\n        int sx = cmp(a.x, b.x);\n\
    \        if (sx != 0) return sx == -1;\n        int sy = cmp(a.y, b.y);\n    \
    \    return sy != 0 ? sy == -1 : cmp(a.z, b.z) == -1;\n    }\n    friend bool\
    \ operator>(const Pt3 &a, const Pt3 &b) { return b < a; }\n    friend bool operator<=(const\
    \ Pt3 &a, const Pt3 &b) { return !(b < a); }\n    friend bool operator>=(const\
    \ Pt3 &a, const Pt3 &b) { return !(a < b); }\n    template <typename U, U _eps,\
    \ typename _MulT>\n    Pt3(const Pt3<U, _eps, _MulT>& other) : x(static_cast<T>(other.x)),\
    \ y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {}\n    template <typename\
    \ U, U _eps, typename _MulT>\n    Pt3(const Pt<U, _eps, _MulT>& other) : x(static_cast<T>(other.x)),\
    \ y(static_cast<T>(other.y)), z(static_cast<T>(square(other))) {}\n    friend\
    \ MulT dot(const Pt3 &a, const Pt3 &b) {\n        return MulT(a.x) * MulT(b.x)\
    \ + MulT(a.y) * MulT(b.y) + MulT(a.z) * MulT(b.z);\n    }\n    friend Pt3 cross(const\
    \ Pt3 &a, const Pt3 &b) {\n        return Pt3(MulT(a.y) * MulT(b.z) - MulT(a.z)\
    \ * MulT(b.y), MulT(a.z) * MulT(b.x) - MulT(a.x) * MulT(b.z), MulT(a.x) * MulT(b.y)\
    \ - MulT(a.y) * MulT(b.x));\n    }\n    friend MulT square(const Pt3 &a) {\n \
    \       return dot(a, a);\n    }\n    friend MulT dist2(const Pt3 &a, const Pt3\
    \ &b) {\n        return square(a - b);\n    }\n    template <typename Ret = DefaultFloat<T>>\n\
    \    friend Ret length(const Pt3 &a) {\n        return std::sqrt(static_cast<Ret>(square(a)));\
    \ \n    }\n    template <typename Ret = DefaultFloat<T>>\n    friend Ret dist(const\
    \ Pt3 &a, const Pt3 &b) {\n        return length<Ret>(a - b); \n    }\n    template\
    \ <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(),\
    \ typename _MulT = Ret>\n    friend Pt3<Ret, _eps, _MulT> normal(const Pt3 &a)\
    \ {\n        Ret len = length(a);\n        return Pt3<Ret, _eps, _MulT>(a) / len;\n\
    \    }\n    friend Pt3 cross(const Pt3 &p, const Pt3 &a, const Pt3 &b) {\n   \
    \     return cross(a - p, b - p);\n    }\n    template <typename Ret = DefaultFloat<T>>\n\
    \    friend Ret area(const Pt3 &a, const Pt3 &b, const Pt3 &c) {\n        return\
    \ length<Ret>(cross(a, b, c));\n    }\n    friend MulT volume(const Pt3 &a, const\
    \ Pt3 &b, const Pt3 &c, const Pt3 &d) {\n        return dot(cross(a, b, c), d\
    \ - a);\n    }\n    // Azimuthal angle (longitude) to x-axis in interval [-pi,\
    \ pi]\n    template <typename Ret = DefaultFloat<T>>\n    friend Ret phi(const\
    \ Pt3 &p) {\n        return std::atan2(Ret(p.y), Ret(p.x));\n    }\n    // Zenith\
    \ angle (latitude) to the z-axis in interval [0, pi]\n    template <typename Ret\
    \ = DefaultFloat<T>>\n    friend Ret theta(const Pt3 &p) {\n        return std::atan2(std::sqrt(Ret(p.x)\
    \ * Ret(p.x) + Ret(p.y) * Ret(p.y)), Ret(p.z));\n    }\n    template <typename\
    \ Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(),\
    \ typename _MulT = Ret>\n    friend Pt3 masscenter(const Pt3 &a, const Pt3 &b,\
    \ const Pt3 &c, const Pt3 &d) {\n        return Pt3<Ret, _eps, _MulT>(a + b +\
    \ c + d) / Ret(4);\n    }\n    // proj. u to the plane of a, b, and c\n    template\
    \ <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(),\
    \ typename _MulT = Ret>\n    friend Pt<Ret, _eps, _MulT> proj(const Pt3 &a, const\
    \ Pt3 &b, const Pt3 &c, const Pt3 &u) {\n        Pt3<Ret, _eps, _MulT> e1 = b\
    \ - a;\n        Pt3<Ret, _eps, _MulT> e2 = c - a;\n        e1 = e1 / length<Ret>(e1);\n\
    \        e2 = e2 - e1 * Ret(dot(e2, e1));\n        e2 = e2 / length<Ret>(e2);\n\
    \        Pt3<Ret, _eps, _MulT> p = u - a;\n        return Pt<Ret, _eps, _MulT>(Ret(dot(p,\
    \ e1)), Ret(dot(p, e2)));\n    }\n    template <typename Ret = DefaultFloat<T>,\
    \ Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT\
    \ = Ret>\n    friend Pt3<Ret, _eps, _MulT> rotate_around(const Pt3 &p, Ret angle,\
    \ const Pt3 &axis) {\n        Ret s = std::sin(angle), c = std::cos(angle);\n\
    \        Pt3<Ret, _eps, _MulT> u = Pt3<Ret, _eps, _MulT>(axis) / length<Ret>(axis);\n\
    \        return u * Ret(dot(u, p)) * (1 - c) + Pt3<Ret, _eps, _MulT>(p) * c +\
    \ cross(u, Pt3<Ret, _eps, _MulT>(p)) * s;\n    }\n};\n"
  code: "#pragma once\n    \n#include \"Geometry/base.hpp\"\n\ntemplate<typename T,\
    \ T eps = get_default_eps<T>(), typename MulT = T>\nstruct Pt3 : Geometry<T, eps>\
    \ {\n    using value_type = T;\n    using Geometry<MulT, eps>::sign;\n    using\
    \ Geometry<MulT, eps>::cmp;\n    static constexpr T eps_val = eps;\n    T x =\
    \ 0, y = 0, z = 0;\n    Pt3() : x(0), y(0), z(0) {}\n    Pt3(T x_, T y_, T z_)\
    \ : x(x_), y(y_), z(z_) {}\n    friend istream& operator>>(istream &is, Pt3 &p)\
    \ { return is >> p.x >> p.y >> p.z; }\n    friend ostream& operator<<(ostream\
    \ &os, const Pt3 &p) { return os << p.x << ' ' << p.y << ' ' << p.z; }\n    friend\
    \ bool operator==(const Pt3 &a, const Pt3 &b) {\n        return cmp(a.x, b.x)\
    \ == 0 && cmp(a.y, b.y) == 0 && cmp(a.z, b.z) == 0; \n    }\n    friend bool operator!=(const\
    \ Pt3 &a, const Pt3 &b) { return !(a == b); }\n    Pt3 operator-() { return Pt(-x,\
    \ -y, -z); }\n    Pt3& operator+=(const Pt3 &a) {\n        x += a.x, y += a.y,\
    \ z += a.z;\n        return *this;\n    }\n    Pt3& operator-=(const Pt3 &a) {\n\
    \        x -= a.x, y -= a.y, z -= a.z;\n        return *this;\n    }\n    Pt3&\
    \ operator*=(T d) {\n        x *= d, y *= d, z *= d;\n        return *this;\n\
    \    }\n    Pt3& operator/=(T d) {\n        x /= d, y /= d, z /= d;\n        return\
    \ *this;\n    }\n    friend Pt3 operator+(const Pt3 &a, const Pt3 &b) { return\
    \ Pt3(a) += b; }\n    friend Pt3 operator-(const Pt3 &a, const Pt3 &b) { return\
    \ Pt3(a) -= b; }\n    friend Pt3 operator*(const Pt3 &a, T d) { return Pt3(a)\
    \ *= d; }\n    friend Pt3 operator/(const Pt3 &a, T d) { return Pt3(a) /= d; }\n\
    \    friend bool operator<(const Pt3 &a, const Pt3 &b) {\n        int sx = cmp(a.x,\
    \ b.x);\n        if (sx != 0) return sx == -1;\n        int sy = cmp(a.y, b.y);\n\
    \        return sy != 0 ? sy == -1 : cmp(a.z, b.z) == -1;\n    }\n    friend bool\
    \ operator>(const Pt3 &a, const Pt3 &b) { return b < a; }\n    friend bool operator<=(const\
    \ Pt3 &a, const Pt3 &b) { return !(b < a); }\n    friend bool operator>=(const\
    \ Pt3 &a, const Pt3 &b) { return !(a < b); }\n    template <typename U, U _eps,\
    \ typename _MulT>\n    Pt3(const Pt3<U, _eps, _MulT>& other) : x(static_cast<T>(other.x)),\
    \ y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {}\n    template <typename\
    \ U, U _eps, typename _MulT>\n    Pt3(const Pt<U, _eps, _MulT>& other) : x(static_cast<T>(other.x)),\
    \ y(static_cast<T>(other.y)), z(static_cast<T>(square(other))) {}\n    friend\
    \ MulT dot(const Pt3 &a, const Pt3 &b) {\n        return MulT(a.x) * MulT(b.x)\
    \ + MulT(a.y) * MulT(b.y) + MulT(a.z) * MulT(b.z);\n    }\n    friend Pt3 cross(const\
    \ Pt3 &a, const Pt3 &b) {\n        return Pt3(MulT(a.y) * MulT(b.z) - MulT(a.z)\
    \ * MulT(b.y), MulT(a.z) * MulT(b.x) - MulT(a.x) * MulT(b.z), MulT(a.x) * MulT(b.y)\
    \ - MulT(a.y) * MulT(b.x));\n    }\n    friend MulT square(const Pt3 &a) {\n \
    \       return dot(a, a);\n    }\n    friend MulT dist2(const Pt3 &a, const Pt3\
    \ &b) {\n        return square(a - b);\n    }\n    template <typename Ret = DefaultFloat<T>>\n\
    \    friend Ret length(const Pt3 &a) {\n        return std::sqrt(static_cast<Ret>(square(a)));\
    \ \n    }\n    template <typename Ret = DefaultFloat<T>>\n    friend Ret dist(const\
    \ Pt3 &a, const Pt3 &b) {\n        return length<Ret>(a - b); \n    }\n    template\
    \ <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(),\
    \ typename _MulT = Ret>\n    friend Pt3<Ret, _eps, _MulT> normal(const Pt3 &a)\
    \ {\n        Ret len = length(a);\n        return Pt3<Ret, _eps, _MulT>(a) / len;\n\
    \    }\n    friend Pt3 cross(const Pt3 &p, const Pt3 &a, const Pt3 &b) {\n   \
    \     return cross(a - p, b - p);\n    }\n    template <typename Ret = DefaultFloat<T>>\n\
    \    friend Ret area(const Pt3 &a, const Pt3 &b, const Pt3 &c) {\n        return\
    \ length<Ret>(cross(a, b, c));\n    }\n    friend MulT volume(const Pt3 &a, const\
    \ Pt3 &b, const Pt3 &c, const Pt3 &d) {\n        return dot(cross(a, b, c), d\
    \ - a);\n    }\n    // Azimuthal angle (longitude) to x-axis in interval [-pi,\
    \ pi]\n    template <typename Ret = DefaultFloat<T>>\n    friend Ret phi(const\
    \ Pt3 &p) {\n        return std::atan2(Ret(p.y), Ret(p.x));\n    }\n    // Zenith\
    \ angle (latitude) to the z-axis in interval [0, pi]\n    template <typename Ret\
    \ = DefaultFloat<T>>\n    friend Ret theta(const Pt3 &p) {\n        return std::atan2(std::sqrt(Ret(p.x)\
    \ * Ret(p.x) + Ret(p.y) * Ret(p.y)), Ret(p.z));\n    }\n    template <typename\
    \ Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(),\
    \ typename _MulT = Ret>\n    friend Pt3 masscenter(const Pt3 &a, const Pt3 &b,\
    \ const Pt3 &c, const Pt3 &d) {\n        return Pt3<Ret, _eps, _MulT>(a + b +\
    \ c + d) / Ret(4);\n    }\n    // proj. u to the plane of a, b, and c\n    template\
    \ <typename Ret = DefaultFloat<T>, Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(),\
    \ typename _MulT = Ret>\n    friend Pt<Ret, _eps, _MulT> proj(const Pt3 &a, const\
    \ Pt3 &b, const Pt3 &c, const Pt3 &u) {\n        Pt3<Ret, _eps, _MulT> e1 = b\
    \ - a;\n        Pt3<Ret, _eps, _MulT> e2 = c - a;\n        e1 = e1 / length<Ret>(e1);\n\
    \        e2 = e2 - e1 * Ret(dot(e2, e1));\n        e2 = e2 / length<Ret>(e2);\n\
    \        Pt3<Ret, _eps, _MulT> p = u - a;\n        return Pt<Ret, _eps, _MulT>(Ret(dot(p,\
    \ e1)), Ret(dot(p, e2)));\n    }\n    template <typename Ret = DefaultFloat<T>,\
    \ Ret _eps = std::is_same_v<T, Ret> ? eps : get_default_eps<Ret>(), typename _MulT\
    \ = Ret>\n    friend Pt3<Ret, _eps, _MulT> rotate_around(const Pt3 &p, Ret angle,\
    \ const Pt3 &axis) {\n        Ret s = std::sin(angle), c = std::cos(angle);\n\
    \        Pt3<Ret, _eps, _MulT> u = Pt3<Ret, _eps, _MulT>(axis) / length<Ret>(axis);\n\
    \        return u * Ret(dot(u, p)) * (1 - c) + Pt3<Ret, _eps, _MulT>(p) * c +\
    \ cross(u, Pt3<Ret, _eps, _MulT>(p)) * s;\n    }\n};\n"
  dependsOn:
  - Geometry/base.hpp
  isVerificationFile: false
  path: Geometry/Point3D.hpp
  requiredBy:
  - Geometry/convexHull3D.hpp
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/3_qoj/6445.test.cpp
documentation_of: Geometry/Point3D.hpp
layout: document
redirect_from:
- /library/Geometry/Point3D.hpp
- /library/Geometry/Point3D.hpp.html
title: Geometry/Point3D.hpp
---
