#pragma once

template<typename T>
T mod_inv(T val, T mod) {
    if (mod == 0) return 0;
    mod = std::abs(mod);
    val %= mod;
    if (val < 0) val += mod;
    T a = val, b = mod, u = 1, v = 0, t;
    while (b > 0) {
        t = a / b;
        swap(a -= t * b, b), swap(u -= t * v, v);
    }
    if (u < 0) u += mod;
    return u;
}
