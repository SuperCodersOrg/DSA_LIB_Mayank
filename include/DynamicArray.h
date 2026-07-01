#pragma once

#include <stdexcept>
#include <utility>
#include "Allocator.h"

template <typename T>
class DynamicArray{
private:
    T* data;
    size_t size;
    size_t capacity;
    MyAllocator<T> allocator;
    void resize(){
        size_t newcapacity=capacity*2;
        T* newdata = allocator.Allocate(newcapacity);
        for (size_t i = 0; i < size; i++) {
            allocator.Construct(newdata + i, data[i]);
        }

        for (size_t i = 0; i < size; i++) {
            allocator.Destroy(data + i);
        }
        allocator.Deallocate(data);
        data=newdata;
        capacity=newcapacity;
    }
public:
    DynamicArray(){
        size=0;
        capacity=1;
        data = allocator.Allocate(capacity);
    }

    DynamicArray(size_t n){
        size=n;
        capacity=n;
        data = allocator.Allocate(capacity);
        for(size_t i=0;i<n;i++){
            allocator.Construct(data+i);
        }

    }

    ~DynamicArray(){
        for(size_t i=0;i<size;i++){
            allocator.Destroy(data+i);
        }
        allocator.Deallocate(data);
    }


};