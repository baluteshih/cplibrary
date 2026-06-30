struct Value {
    int val;
    Value(int _v = 0): val(_v) {}
    Value operator+(const Value &rhs) const {
        return Value(min(val, rhs.val));
    }
    friend ostream& operator<<(ostream& os, const Value &v) {
        os << v.val;
        return os;
    }
    friend istream& operator>>(istream& is, Value &v) {
        is >> v.val;
        return is;
    }
};
