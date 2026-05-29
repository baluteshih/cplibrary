#pragma once
// Reference: Atcoder Library https://github.com/atcoder/ac-library

#ifdef _MSC_VER
#include <intrin.h>
#endif

struct barrett {
    unsigned int _m;
    unsigned long long im;
    explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}
    unsigned int umod() const { return _m; }
    unsigned int modulo(unsigned long long z) const {
        if (_m == 1) return 0;
#ifdef _MSC_VER
        unsigned long long x;
        _umul128(z, im, &x);
#else
        unsigned long long x = (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
        unsigned long long y = x * _m;
        return (z - y + (z < y ? _m : 0));
    }
    unsigned int mul(unsigned int a, unsigned int b) const {
        return modulo((unsigned long long)a * b);
    }
    unsigned long long floor(unsigned long long z) const {
        if (_m == 1) return z;
        unsigned long long x = (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
        unsigned long long y = x * _m;
        return (z < y ? x - 1 : x);
    }
    std::pair<unsigned long long, unsigned int> divmod(unsigned long long z) const {
        if (_m == 1) return {z, 0};
        unsigned long long x = (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
        unsigned long long y = x * _m;
        if (z < y) return {x - 1, z - y + _m};
        return {x, z - y};
    }
};
