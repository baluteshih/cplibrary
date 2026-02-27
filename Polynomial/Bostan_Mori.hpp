#pragma once
   
#include "Polynomial/Polynomial.hpp"

template<class T>
T Bostan_Mori(const Poly<T> &f, const Poly<T> &g, ll k) { // [f(x)/g(x)][x^k]
    assert(f.size() + 1 <= g.size());
    Poly<T> F(f);
    Poly<T> G(g);
    for (; k; k >>= 1) {
        Poly<T> H = G;
        int m = 1;
        while (m < (int)G.size() * 2) m <<= 1;
        for (int i = 1; i < (int)H.size(); i += 2) H[i] = -H[i];
        F.dft(m), G.dft(m), H.dft(m);
        F.imul(H), G.imul(H);
        F.idft(m), G.idft(m);
        for (int i = 0; i * 2 + (k & 1) < (int)F.size(); ++i) F[i] = F[i * 2 + (k & 1)];
        for (int i = 0; i * 2 < (int)G.size(); ++i) G[i] = G[i * 2];
        F.isz(((int)F.size() + 1 - (k & 1)) / 2), G.isz(((int)G.size() + 1) / 2);
    }
    return F[0] / G[0];
}
