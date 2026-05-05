struct size_v {
    int sz;
    size_v(int sz_ = 0): sz(sz_) {}
    size_v operator+(const size_v &rhs) const {
        return size_v(sz + rhs.sz);
    }
    int size() const {
        return sz; 
    }
    friend ostream& operator<<(ostream& os, const size_v &v) {
        os << v.sz;
        return os;
    }
};
