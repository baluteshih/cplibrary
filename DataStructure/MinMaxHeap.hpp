#pragma once

#include "DataStructure/LazyDeleteHeap.hpp"

template<typename T>
class MinMaxHeap {
private:
    LazyDeleteHeap<std::priority_queue<T>> max_heap;
    LazyDeleteHeap<std::priority_queue<T, std::vector<T>, std::greater<T>>> min_heap;
public: 
    void push(const T& val) {
        max_heap.push(val);
        min_heap.push(val);
    }
    void erase(const T& val) {
        max_heap.erase(val);
        min_heap.erase(val);
    }
    void pop_min() {
        assert(!min_heap.empty());
        max_heap.erase(min_heap.top());
        min_heap.pop();
    }
    void pop_max() {
        assert(!max_heap.empty());
        min_heap.erase(max_heap.top());
        max_heap.pop();
    }
    const T& top_min() {
        return min_heap.top();
    }
    const T& top_max() {
        return max_heap.top();
    }
    size_t size() const {
        return max_heap.size(); 
    }
    bool empty() const {
        return size() == 0;
    }
    void swap(MinMaxHeap &other) {
        max_heap.swap(other.max_heap);
        min_heap.swap(other.min_heap);
    }
    void clear() {
        max_heap.clear();
        min_heap.clear();
    }
};
