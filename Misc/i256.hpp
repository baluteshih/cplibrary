#pragma once

struct i256 {
    using u64 = std::uint64_t;
    using u128 = unsigned __int128;
    using s128 = __int128_t;

    std::array<u64, 4> a{};

    constexpr i256() = default;

    template <class T>
    requires (std::is_integral_v<T> && sizeof(T) <= 8)
    constexpr i256(T x) {
        if constexpr (std::is_signed_v<T>) {
            s128 y = static_cast<s128>(x);
            u128 z = static_cast<u128>(y);
            a[0] = static_cast<u64>(z);
            a[1] = static_cast<u64>(z >> 64);
            a[2] = a[3] = (y < 0 ? ~u64(0) : u64(0));
        } else {
            u128 z = static_cast<u128>(x);
            a[0] = static_cast<u64>(z);
            a[1] = static_cast<u64>(z >> 64);
            a[2] = a[3] = 0;
        }
    }

    constexpr i256(s128 x) {
        u128 z = static_cast<u128>(x);
        a[0] = static_cast<u64>(z);
        a[1] = static_cast<u64>(z >> 64);
        a[2] = a[3] = (x < 0 ? ~u64(0) : u64(0));
    }

    constexpr i256(u128 x) {
        a[0] = static_cast<u64>(x);
        a[1] = static_cast<u64>(x >> 64);
        a[2] = a[3] = 0;
    }

    constexpr bool negative() const {
        return a[3] >> 63;
    }

    static constexpr u128 abs128(s128 x) {
        u128 u = static_cast<u128>(x);
        return x < 0 ? (~u + 1) : u;
    }

    // Fast exact signed 128 x 128 -> signed 256.
    static constexpr i256 mul128(s128 x, s128 y) {
        u128 ux = abs128(x), uy = abs128(y);
        u64 x0 = static_cast<u64>(ux), x1 = static_cast<u64>(ux >> 64);
        u64 y0 = static_cast<u64>(uy), y1 = static_cast<u64>(uy >> 64);

        i256 r;
        // Base-2^64 schoolbook multiplication, only 2 x 2 limbs.
        r.a = {};
        u64 xs[2] = {x0, x1}, ys[2] = {y0, y1};
        for (int i = 0; i < 2; ++i) {
            u64 c = 0;
            for (int j = 0; j < 2; ++j) {
                u128 cur = u128(xs[i]) * ys[j] + r.a[i + j] + c;
                r.a[i + j] = static_cast<u64>(cur);
                c = static_cast<u64>(cur >> 64);
            }
            int k = i + 2;
            while (c && k < 4) {
                u128 cur = u128(r.a[k]) + c;
                r.a[k] = static_cast<u64>(cur);
                c = static_cast<u64>(cur >> 64);
                ++k;
            }
        }
        if ((x < 0) != (y < 0)) r = -r;
        return r;
    }

    friend constexpr bool operator==(const i256&, const i256&) = default;

    friend constexpr bool operator<(const i256& x, const i256& y) {
        bool sx = x.negative(), sy = y.negative();
        if (sx != sy) return sx;
        for (int i = 3; i >= 0; --i)
            if (x.a[i] != y.a[i])
                return x.a[i] < y.a[i];
        return false;
    }

    friend constexpr bool operator!=(const i256& x, const i256& y) { return !(x == y); }
    friend constexpr bool operator>(const i256& x, const i256& y) { return y < x; }
    friend constexpr bool operator<=(const i256& x, const i256& y) { return !(y < x); }
    friend constexpr bool operator>=(const i256& x, const i256& y) { return !(x < y); }

    constexpr i256 operator-() const {
        i256 r;
        for (int i = 0; i < 4; ++i) r.a[i] = ~a[i];
        for (int i = 0; i < 4; ++i)
            if (++r.a[i] != 0) break;
        return r;
    }

    constexpr i256& operator+=(const i256& o) {
        u64 carry = 0;
        for (int i = 0; i < 4; ++i) {
            u128 cur = u128(a[i]) + o.a[i] + carry;
            a[i] = static_cast<u64>(cur);
            carry = static_cast<u64>(cur >> 64);
        }
        return *this;
    }

    constexpr i256& operator-=(const i256& o) {
        return *this += -o;
    }

    constexpr i256& operator*=(const i256& o) {
        std::array<u64, 4> r{};
        for (int i = 0; i < 4; ++i) {
            u64 carry = 0;
            for (int j = 0; i + j < 4; ++j) {
                u128 cur = u128(a[i]) * o.a[j] + r[i + j] + carry;
                r[i + j] = static_cast<u64>(cur);
                carry = static_cast<u64>(cur >> 64);
            }
        }
        a = r;
        return *this;
    }

    friend constexpr i256 operator+(i256 x, const i256& y) { return x += y; }
    friend constexpr i256 operator-(i256 x, const i256& y) { return x -= y; }
    friend constexpr i256 operator*(i256 x, const i256& y) { return x *= y; }
};
