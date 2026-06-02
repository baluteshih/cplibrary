#pragma once

// source: https://maspypy.github.io/library/poly/online/online_convolution.hpp

#include "Polynomial/NTT.hpp"

template<typename T>
struct OnlineConvolution {
    std::vector<T> f, g, h, fm, gm;
    int p;
    
    OnlineConvolution() : p(0) {}

    T query(int idx, T f_i, T g_i) {
        assert(idx == p);
        f.push_back(f_i), g.push_back(g_i);
        int z = __builtin_ctz(p + 2), w = 1 << z, s;
        std::vector<T> b0, b1;
        if (p + 2 == w) {
            b0 = f, b0.resize(2 * w);
            NTT<T>::ntt(b0, false);
            b1 = g, b1.resize(2 * w);
            NTT<T>::ntt(b1, false);
            fm.resize(w << 1), gm.resize(w << 1);
            for (int i = 0; i < w; ++i) fm[i + w] = b0[i * 2], gm[i + w] = b1[i * 2];
            for (int i = 0; i < 2 * w; ++i) b0[i] *= b1[i];
            s = w - 2;
            h.resize(2 * s + 2);
        }
        else {
            b0.assign(f.end() - w, f.end()), b0.resize(2 * w);
            NTT<T>::ntt(b0, false);
            for (int i = 0; i < 2 * w; ++i) b0[i] *= gm[i + (w << 1)];
            b1.assign(g.end() - w, g.end()), b1.resize(2 * w);
            NTT<T>::ntt(b1, false);
            for (int i = 0; i < 2 * w; ++i) b0[i] += b1[i] * fm[i + (w << 1)];
            s = w - 1;
        }
        NTT<T>::ntt(b0, true);
        for (int i = 0; i <= s; ++i) h[p + i] += b0[s + i];
        return h[p++];
    }
};
