struct treap_v {
    int sz;
    treap_v(int sz_ = 0): sz(sz_) {}
    treap_v operator+(const treap_v &rhs) const {
        return treap_v(sz + rhs.sz);
    }
    int size() const {
        return sz; 
    }
    friend ostream& operator<<(ostream& os, const treap_v &v) {
        os << v.sz;
        return os;
    }
};
