#pragma once

#ifndef POOL_SIZE
    #define POOL_SIZE 10000000
#endif

template<typename T, int _POOL_SIZE = POOL_SIZE>
struct PoolAllocator {
    static T pool[_POOL_SIZE];
    static int ptr;
    template<typename... Args>
    static T* allocate(Args&&... args) { 
        T* p = &pool[ptr++];
        return new (p) T(std::forward<Args>(args)...);
    }
    static void deallocate(T* p) {}
    static void reset() { ptr = 0; }
};

template<typename T, int _POOL_SIZE>
T PoolAllocator<T, _POOL_SIZE>::pool[_POOL_SIZE];

template<typename T, int _POOL_SIZE>
int PoolAllocator<T, _POOL_SIZE>::ptr = 0;
