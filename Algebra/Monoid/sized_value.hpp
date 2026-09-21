template <typename T, typename size_type = int>
struct sized_value {
    T val;
    size_type sz;
    sized_value() : val(), sz(0) {}
    sized_value(T v, size_type s = 1) : val(v), sz(s) {}
    sized_value operator+(const sized_value &rhs) const {
        return sized_value(val + rhs.val, sz + rhs.sz);
    }
    template <typename Tag>
    sized_value operator+(const Tag &tag) const {
        if constexpr (requires { val.apply(tag, sz); }) {
            return sized_value(val.apply(tag, sz), sz);
        }
        else if constexpr (requires { val + tag; }) {
            return sized_value(val + tag, sz);
        }
        else {
            static_assert(!sizeof(Tag*), "Type T must implement either apply(Tag, size_type) or operator+(Tag)");
            return *this;
        }
    }
    size_type size() const { return sz; }
    friend std::ostream& operator<<(std::ostream& os, const sized_value &v) requires requires(std::ostream& out, const T& inner_val) { out << inner_val; } {
        os << v.val << " " << v.sz;
        return os;
    }
};
