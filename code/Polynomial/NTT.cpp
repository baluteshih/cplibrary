#ifndef __NTT__
#define __NTT__
template<class T>
class NTT {
    int max_size;
    vector<T> w;
    T root;
public:
    NTT(int n, T _root) : max_size(1), root(_root) {
        while (max_size <= n) max_size <<= 1;
        w.resize(max_size, 1);
        T dw = root.pow((T().mod() - 1) / max_size);
        for (int s = max_size / 2; s; s >>= 1, dw *= dw) {
            w[s] = 1;
            for (int j = 1; j < s; ++j) 
                w[s + j] = w[s + j - 1] * dw;
        }
    }
    void ntt(vector<T> &a, bool inv = false) { //0 <= a[i] < P
        int n = a.size();
        assert((n & (n - 1)) == 0);
        assert(n <= max_size);
        for (int i = 0, j = 1; j < n - 1; ++j) {
            for (int k = n >> 1; (i ^= k) < k; k >>= 1);
            if (j < i) swap(a[i], a[j]);
        }
        for (int s = 1; s < n; s <<= 1) {
            for (int i = 0; i < n; i += s * 2) {
                for (int j = 0; j < s; ++j) {
                    T tmp = a[i + s + j] * w[s + j];
                    a[i + s + j] = a[i + j] - tmp;
                    a[i + j] += tmp;
                }
            }
        }
        if (!inv) return;
        T iv = T(n).inv(); 
        reverse(a.begin() + 1, a.begin() + n);
        for (int i = 0; i < n; ++i) a[i] *= iv;
    }
    size_t maxsize() {
        return max_size;
    }
    vector<T> convolution(vector<T> a, vector<T> b) {
        if (a.empty() || b.empty()) return vector<T>();
        int n = 1, sz = int(a.size()) + int(b.size()) - 1;
        while (n < sz) n <<= 1;
        a.resize(n), b.resize(n);
        ntt(a), ntt(b);
        for (int i = 0; i < n; ++i)
            a[i] = a[i] * b[i];
        ntt(a, true);
        a.resize(sz);
        return a;
    }
};
#endif // __NTT__
