#pragma once

template <typename T> struct make_unsigned_cp { using type = std::make_unsigned_t<T>; };
template <> struct make_unsigned_cp<__int128_t> { using type = __uint128_t; };
template <> struct make_unsigned_cp<__uint128_t> { using type = __uint128_t; };
template <typename T> using make_unsigned_cp_t = typename make_unsigned_cp<T>::type;

template <typename T>
inline int ctz(T x) {
    if constexpr (sizeof(T) <= 4) return __builtin_ctz(x);
    else if constexpr (sizeof(T) <= 8) return __builtin_ctzll(x);
    else {
        uint64_t lo = x;
        return lo ? __builtin_ctzll(lo) : 64 + __builtin_ctzll(x >> 64);
    }
}

template <typename T>
inline T fast_gcd(T a, T b) {
    using U = make_unsigned_cp_t<T>;
    U ua, ub;

    if constexpr (T(-1) < T(0)) {
        ua = a < 0 ? -static_cast<U>(a) : static_cast<U>(a);
        ub = b < 0 ? -static_cast<U>(b) : static_cast<U>(b);
    }
    else {
        ua = a;
        ub = b;
    }

    if (!ua || !ub) return static_cast<T>(ua | ub);

    int shift = ctz(ua | ub);
    ua >>= ctz(ua);
    
    while (ub) {
        ub >>= ctz(ub);
        if (ua > ub) std::swap(ua, ub);
        ub -= ua;
    }
    
    return static_cast<T>(ua << shift);
}
