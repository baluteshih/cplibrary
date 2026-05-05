#pragma once

#ifndef POOL_SIZE
    #define POOL_SIZE 10000000
#endif

template<typename T, int _POOL_SIZE = POOL_SIZE>
struct StackPoolAllocator {
    static T pool[_POOL_SIZE];
    static T* recycle[_POOL_SIZE];
    static int ptr, top;
    template<typename... Args>
    static T* allocate(Args&&... args) { 
        T* p;
        if (top > 0) p = recycle[--top];
        else p = &pool[ptr++];
        return new (p) T(std::forward<Args>(args)...);
    }
    static void deallocate(T* p) { recycle[top++] = p; }
    static void reset() { ptr = top = 0; }
};

template<typename T, int _POOL_SIZE>
T StackPoolAllocator<T, _POOL_SIZE>::pool[_POOL_SIZE];

template<typename T, int _POOL_SIZE>
T* StackPoolAllocator<T, _POOL_SIZE>::recycle[_POOL_SIZE];

template<typename T, int _POOL_SIZE>
int StackPoolAllocator<T, _POOL_SIZE>::ptr = 0;

template<typename T, int _POOL_SIZE>
int StackPoolAllocator<T, _POOL_SIZE>::top = 0;
