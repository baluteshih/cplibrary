#pragma once

template<typename T>
struct DefaultAllocator {
    template<typename... Args>
    static T* allocate(Args&&... args) { 
        return new T(std::forward<Args>(args)...);
    }
    static void deallocate(T* p) { delete p; }
};
