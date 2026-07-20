#pragma once

template<typename T>
struct history_min_add_tag {
    T v, hv;
    history_min_add_tag() : v(), hv() {}
    history_min_add_tag(T _v, T _hv) : v(_v), hv(_hv) {}
    history_min_add_tag(T _v) : v(_v), hv(std::min(_v, 0)) {}
    history_min_add_tag operator+(const history_min_add_tag &rhs) const {
        return history_min_add_tag(v + rhs.v, std::min(hv, v + rhs.hv));
    }
    friend std::ostream& operator<<(std::ostream& os, const history_min_add_tag &v) {
        os << v.v << " " << v.hv;
        return os;
    }
};

template<typename T, T inf = std::numeric_limits<T>::max()>
struct history_min {
    T val, hval;
    history_min(T _val = inf, T _hval = inf) : val(_val), hval(_hval) {}
    history_min operator+(const history_min &rhs) const {
        return history_min(std::min(val, rhs.val), std::min(hval, rhs.hval));
    }
    template<typename U>
    history_min operator+(const history_min_add_tag<U> &tag) const {
        return history_min(val + tag.v, std::min(hval, val + tag.hv));
    }
    friend std::ostream& operator<<(std::ostream& os, const history_min &v) {
        os << v.hval;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, history_min &v) {
        is >> v.val;
        return is;
    }
};
