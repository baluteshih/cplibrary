template<class T>
class BIT {
    int n;
    T total;
    vector<T> bit;
public:
    BIT(int _n): n(_n), total(), bit(n + 1) {}
    void modify(int x, T v) {
        for (++x; x <= n; x += x & -x)
            bit[x] = bit[x] + v;
    }
    T prefix(int x) {
        T res = T();
        for (++x; x; x -= x & -x)
            res = res + bit[x];
        return res;
    }
    T suffix(int x) {
        return total - prefix(x);
    }
};
