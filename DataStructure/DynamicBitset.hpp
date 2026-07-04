#pragma once

#ifdef __x86_64__
    #include <x86intrin.h>
#endif

class DynamicBitset {
    int n;
    std::vector<uint64_t> a;
    inline static unsigned char add_carry(unsigned char c, uint64_t a, uint64_t b, uint64_t& out) {
    #ifdef __x86_64__
        return _addcarry_u64(c, a, b, (unsigned long long*)&out);
    #else
        uint64_t sum = a + b + c;
        out = sum;
        return (sum < a) || (c && sum == a);
    #endif
    }
    inline static unsigned char sub_borrow(unsigned char b, uint64_t x, uint64_t y, uint64_t& out) {
    #ifdef __x86_64__
        return _subborrow_u64(b, x, y, (unsigned long long*)&out);
    #else
        uint64_t sub = x - y - b;
        out = sub;
        return (x < y) || (b && x == y);
    #endif
    }
public:
    DynamicBitset(int _n = 0) : n(_n), a((n + 63) >> 6, 0) {}
    DynamicBitset(std::string_view s) : n(s.size()), a((n + 63) >> 6, 0) {
        for (int i = 0; i < n; ++i) 
            if (s[n - 1 - i] == '1') a[i >> 6] |= (1ULL << (i & 63));
    }
    void clean() { if (n & 63) a.back() &= (1ULL << (n & 63)) - 1; }
    struct reference {
        uint64_t& blk; int bit;
        reference(uint64_t& b, int idx) : blk(b), bit(idx) {}
        reference& operator=(bool v) { 
            v ? (blk |= (1ULL << bit)) : (blk &= ~(1ULL << bit)); 
            return *this; 
        }
        reference& operator=(const reference& o) { return *this = bool(o); }
        operator bool() const { return (blk >> bit) & 1; }
    };
    reference operator[](int i) { return reference(a[i >> 6], i & 63); }
    bool operator[](int i) const { return (a[i >> 6] >> (i & 63)) & 1; }

    void set(int i) { a[i >> 6] |= (1ULL << (i & 63)); }
    void reset(int i) { a[i >> 6] &= ~(1ULL << (i & 63)); }
    void flip(int i) { a[i >> 6] ^= (1ULL << (i & 63)); }
    bool test(int i) const { return (*this)[i]; }
    int size() const { return n; }
    int count() const { 
        int res = 0; 
        for (auto x : a) res += std::popcount(x); 
        return res; 
    }
    int _Find_first() const {
        for (size_t i = 0; i < a.size(); ++i)
            if (a[i]) return i * 64 + std::countr_zero(a[i]);
        return n;
    }
    int _Find_last() const {
        for (int i = (int)a.size() - 1; i >= 0; --i)
            if (a[i]) return i * 64 + 63 - std::countl_zero(a[i]);
        return -1;
    }
    int _Find_next(int i) const {
        if (++i >= n) return n;
        int blk = i >> 6, bit = i & 63;
        uint64_t x = a[blk] & (~0ULL << bit);
        if (x) return blk * 64 + std::countr_zero(x);
        for (size_t j = blk + 1; j < a.size(); ++j)
            if (a[j]) return j * 64 + std::countr_zero(a[j]);
        return n;
    }
    int _Find_prev(int i) const {
        if (i <= 0) return -1;
        i = std::min(i, n) - 1;
        int blk = i >> 6, bit = i & 63;
        uint64_t mask = ~0ULL >> (63 - bit);
        uint64_t x = a[blk] & mask;
        if (x) return blk * 64 + 63 - std::countl_zero(x);
        for (int j = blk - 1; j >= 0; --j)
            if (a[j]) return j * 64 + 63 - std::countl_zero(a[j]);
        return -1;
    }
    bool operator==(const DynamicBitset&) const = default;
    std::string to_string() const {
        std::string s(n, '0');
        for (int i = 0; i < n; ++i) if ((*this)[i]) s[n - 1 - i] = '1';
        return s;
    }
    void swap(DynamicBitset &o) { std::swap(n, o.n), a.swap(o.a); }

    friend std::ostream& operator<<(std::ostream& os, const DynamicBitset& b) { return os << b.to_string(); }
    friend std::istream& operator>>(std::istream& is, DynamicBitset& b) {
        std::string s; if (is >> s) b = DynamicBitset(s);
        return is;
    }
    DynamicBitset& operator&=(const DynamicBitset& o) { 
        size_t sz = a.size(); uint64_t* p = a.data(); const uint64_t* op = o.a.data();
        for(size_t i = 0; i < sz; ++i) p[i] &= op[i]; 
        return *this; 
    }
    DynamicBitset& operator|=(const DynamicBitset& o) { 
        size_t sz = a.size(); uint64_t* p = a.data(); const uint64_t* op = o.a.data();
        for(size_t i = 0; i < sz; ++i) p[i] |= op[i]; 
        return *this; 
    }
    DynamicBitset& operator^=(const DynamicBitset& o) { 
        size_t sz = a.size(); uint64_t* p = a.data(); const uint64_t* op = o.a.data();
        for(size_t i = 0; i < sz; ++i) p[i] ^= op[i]; 
        return *this; 
    }
    DynamicBitset& operator+=(const DynamicBitset& o) {
        unsigned char carry = 0;
        size_t sz = a.size(), osz = o.a.size();
        uint64_t* p = a.data(); const uint64_t* op = o.a.data();
        
        for (size_t i = 0; i < sz; ++i) {
            uint64_t v = (i < osz) ? op[i] : 0;
            carry = add_carry(carry, p[i], v, p[i]);
        }
        clean(); return *this;
    } 
    DynamicBitset& operator-=(const DynamicBitset& o) {
        unsigned char borrow = 0;
        size_t sz = a.size(), osz = o.a.size();
        uint64_t* p = a.data(); const uint64_t* op = o.a.data();
        
        for (size_t i = 0; i < sz; ++i) {
            uint64_t v = (i < osz) ? op[i] : 0;
            borrow = sub_borrow(borrow, p[i], v, p[i]);
        }
        clean(); return *this;
    } 
    DynamicBitset& operator<<=(int k) {
        if (k >= n) { memset(a.data(), 0, a.size() * sizeof(uint64_t)); return *this; }
        int blocks = k >> 6, bits = k & 63;
        int sz = (int)a.size();
        uint64_t* p = a.data();

        if (bits == 0)
            for (int i = sz - 1; i >= blocks; --i) p[i] = p[i - blocks];
        else {
            for (int i = sz - 1; i > blocks; --i)
                p[i] = (p[i - blocks] << bits) | (p[i - blocks - 1] >> (64 - bits));
            p[blocks] = p[0] << bits;
        }
        memset(p, 0, blocks * sizeof(uint64_t));
        clean(); return *this;
    } 
    DynamicBitset& operator>>=(int k) {
        if (k >= n) { memset(a.data(), 0, a.size() * sizeof(uint64_t)); return *this; }
        int blocks = k >> 6, bits = k & 63;
        int sz = (int)a.size();
        uint64_t* p = a.data();
        
        if (bits == 0)
            for (int i = 0; i < sz - blocks; ++i) p[i] = p[i + blocks];
        else {
            int limit = sz - blocks - 1;
            for (int i = 0; i < limit; ++i)
                p[i] = (p[i + blocks] >> bits) | (p[i + blocks + 1] << (64 - bits));
            p[limit] = p[sz - 1] >> bits;
        }
        memset(p + (sz - blocks), 0, blocks * sizeof(uint64_t));
        clean(); return *this;
    }
    DynamicBitset& flip() {
        size_t sz = a.size();
        uint64_t* p = a.data();
        for (size_t i = 0; i < sz; ++i) p[i] = ~p[i];
        clean();
        return *this;
    }

    DynamicBitset operator+(const DynamicBitset& o) const { auto res = *this; return res += o; }
    DynamicBitset operator-(const DynamicBitset& o) const { auto res = *this; return res -= o; }
    DynamicBitset operator&(const DynamicBitset& o) const { auto res = *this; return res &= o; }
    DynamicBitset operator|(const DynamicBitset& o) const { auto res = *this; return res |= o; }
    DynamicBitset operator^(const DynamicBitset& o) const { auto res = *this; return res ^= o; }
    DynamicBitset operator<<(int k) const { auto res = *this; return res <<= k; }
    DynamicBitset operator>>(int k) const { auto res = *this; return res >>= k; }
    DynamicBitset operator~() const { auto res = *this; return res.flip(); }
    DynamicBitset operator-() const {
        DynamicBitset res = ~(*this);
        uint64_t carry = 1;
        for (size_t i = 0; i < res.a.size() && carry; ++i) {
            res.a[i] += 1;
            carry = (res.a[i] == 0);
        }
        res.clean();
        return res;
    }
};
