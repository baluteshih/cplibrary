#pragma once

template <typename T, int MAX_BIT, bool MaintainPos = false, bool MaintainTrace = false>
struct XorBasis {
    using TraceMask = std::conditional_t<MAX_BIT <= 32, uint32_t,
                      std::conditional_t<MAX_BIT <= 64, uint64_t,
                      std::bitset<MAX_BIT>>>;

    std::array<T, MAX_BIT> basis{};
    std::vector<T> rref;
    struct Empty {};

    [[no_unique_address]] std::conditional_t<MaintainPos, std::array<int, MAX_BIT>, Empty> pos{};
    [[no_unique_address]] std::conditional_t<MaintainTrace, std::array<TraceMask, MAX_BIT>, Empty> trace{};
    [[no_unique_address]] std::conditional_t<MaintainTrace, TraceMask, Empty> non_basis_used_mask{};

    int sz = 0;
    bool has_zero = false;
    bool is_rebuilt = false;

private:
    static void set_trace_bit(TraceMask &mask, int p) {
        if constexpr (MAX_BIT <= 64) mask |= (1ULL << p);
        else mask.set(p);
    }

    static bool test_trace_bit(const TraceMask &mask, int p) {
        if constexpr (MAX_BIT <= 64) return (mask >> p) & 1;
        else return mask.test(p);
    }

    static bool test_val_bit(const T &val, int p) {
        if constexpr (std::is_integral_v<T>) return (val >> p) & 1;
        else return val.test(p);
    }

public:
    XorBasis() {
        basis.fill(T{});
        if constexpr (MaintainPos) pos.fill(-1);
        if constexpr (MaintainTrace) {
            trace.fill(TraceMask{});
            non_basis_used_mask = TraceMask{};
        }
    }

    bool insert(T x, int p = 0, int id = -1) {
        is_rebuilt = false;
        TraceMask cur_trace{}; 
        
        if constexpr (MaintainTrace) {
            assert(id >= 0 && id < MAX_BIT);
            if (id != -1) set_trace_bit(cur_trace, id);
        }

        for (int i = MAX_BIT - 1; i >= 0; --i) {
            if (test_val_bit(x, i)) {
                if (!test_val_bit(basis[i], i)) {
                    basis[i] = x;
                    if constexpr (MaintainPos) pos[i] = p;
                    if constexpr (MaintainTrace) trace[i] = cur_trace;
                    sz++;
                    return true;
                }
                
                if constexpr (MaintainPos) {
                    if (pos[i] < p) {
                        std::swap(basis[i], x);
                        std::swap(pos[i], p);
                        if constexpr (MaintainTrace) std::swap(trace[i], cur_trace);
                    }
                }
                
                x ^= basis[i];
                if constexpr (MaintainTrace) cur_trace ^= trace[i];
            }
        }
        
        has_zero = true;
        if constexpr (MaintainTrace) {
            non_basis_used_mask |= cur_trace; 
        }
        return false;
    }

    T reduce(T x) const {
        for (int i = MAX_BIT - 1; i >= 0; --i) {
            if (test_val_bit(x, i)) {
                if (!test_val_bit(basis[i], i)) break;
                x ^= basis[i];
            }
        }
        return x;
    }

    bool can_represent(T x) const {
        return reduce(x) == T{};
    }

    T max_xor(T initial = T{}) const {
        T res = initial;
        for (int i = MAX_BIT - 1; i >= 0; --i) {
            if (test_val_bit(basis[i], i)) {
                if constexpr (std::is_integral_v<T>) {
                    res = std::max(res, res ^ basis[i]);
                } else {
                    if (!res.test(i)) res ^= basis[i];
                }
            }
        }
        return res;
    }

    T max_xor_range(int L, T initial = T{}) const requires (MaintainPos) {
        T res = initial;
        for (int i = MAX_BIT - 1; i >= 0; --i) {
            if (test_val_bit(basis[i], i) && pos[i] >= L) {
                if constexpr (std::is_integral_v<T>) {
                    res = std::max(res, res ^ basis[i]);
                } else {
                    if (!res.test(i)) res ^= basis[i];
                }
            }
        }
        return res;
    }

    T min_xor() const {
        if (has_zero) return T{};
        for (int i = 0; i < MAX_BIT; ++i) {
            if (test_val_bit(basis[i], i)) return basis[i];
        }
        return T{}; 
    }

    void rebuild() {
        if (is_rebuilt) return;
        for (int i = MAX_BIT - 1; i >= 0; --i) {
            if (!test_val_bit(basis[i], i)) continue;
            for (int j = i - 1; j >= 0; --j) {
                if (!test_val_bit(basis[j], j)) continue;
                if (test_val_bit(basis[i], j)) {
                    basis[i] ^= basis[j];
                }
            }
        }
        rref.clear();
        for (int i = 0; i < MAX_BIT; ++i) {
            if (test_val_bit(basis[i], i)) rref.push_back(basis[i]);
        }
        is_rebuilt = true;
    }

    T kth(long long k) {
        rebuild();
        if (has_zero) k--; 
        if (k == 0) return 0;
        
        if (k >= (1LL << rref.size())) return -1; 

        T res{};
        for (int i = 0; i < (int)rref.size(); ++i) {
            if ((k >> i) & 1) {
                res ^= rref[i];
            }
        }
        return res;
    }

    bool is_essential(int id) const requires (MaintainTrace) {
        bool in_basis = false;
        for (int i = 0; i < MAX_BIT; ++i) {
            TraceMask target{};
            set_trace_bit(target, id);
            
            if (test_val_bit(basis[i], i) && trace[i] == target) {
                in_basis = true;
                break;
            }
        }
        if (!in_basis) return false;

        if (test_trace_bit(non_basis_used_mask, id)) return false;

        return true;
    }

    XorBasis& operator+=(const XorBasis& rhs) {
        for (int i = 0; i < MAX_BIT; ++i) {
            if (test_val_bit(rhs.basis[i], i)) {
                insert(rhs.basis[i]);
            }
        }
        has_zero |= rhs.has_zero;
        return *this;
    }

    friend XorBasis operator+(XorBasis lhs, const XorBasis& rhs) {
        lhs += rhs;
        return lhs;
    }
};

using Basis32 = XorBasis<uint32_t, 32>;
using Basis64 = XorBasis<uint64_t, 64>;
