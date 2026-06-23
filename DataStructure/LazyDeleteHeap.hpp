#pragma once

template <typename Container>
class LazyDeleteHeap {
private:
    Container main_q;
    Container del_q;
    void normalize() {
        while (!main_q.empty() && !del_q.empty() && main_q.top() == del_q.top()) {
            main_q.pop();
            del_q.pop();
        }
    }
public:
    using value_type = typename Container::value_type;
    void push(const value_type& val) {
        main_q.push(val);
    }
    void erase(const value_type& val) {
        del_q.push(val);
    }
    void pop() {
        normalize();
        assert(!main_q.empty());
        main_q.pop();
    }
    const value_type& top() {
        normalize();
        return main_q.top();
    }
    size_t size() const {
        return main_q.size() - del_q.size();
    }
    bool empty() const {
        return size() == 0;
    }
    void swap(LazyDeleteHeap &other) {
        main_q.swap(other.main_q);
        del_q.swap(other.del_q);
    }
    void clear() {
        Container().swap(main_q); 
        Container().swap(del_q); 
    }
};
