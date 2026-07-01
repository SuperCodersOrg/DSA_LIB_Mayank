#pragma once
#include <cstdlib>
#include <stdexcept>
#include <new>
template<typename T>
class MyAllocator {
public:
    T* Allocate(size_t n=1){
       T* ptr = (T*)malloc(sizeof(T) * n);
       if (ptr == nullptr) {
            throw std::bad_alloc();
        }
        return ptr;
    }

    void Deallocate(T* ptr){
        free(ptr);
    }

    template<typename... Args>
    void Construct(T* ptr, Args&&... args){
        new (ptr) T(args...);
    }
    void Destroy(T* ptr){
        ptr->~T();
    }
};