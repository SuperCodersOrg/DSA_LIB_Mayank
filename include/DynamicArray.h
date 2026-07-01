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

    void append(const T& value){
        if(size == capacity){
            resize();
        }
        allocator.Construct(data + size, value);
        size++;
    }

    void append(T&& value){
        if(size == capacity){
            resize();
        }
        allocator.Construct(data + size, std::move(value));
        size++;
    }

    size_t get_size() const{
        return size;
    }

    size_t get_capacity() const{
        return capacity;
    }

    void insert(size_t index,const T& value){
        if (index > size) {
        throw std::out_of_range("Invalid index");
        }
        if(size==capacity){
            resize();
        }
        for(size_t i=size;i>index;i--){
            allocator.Construct(data + i, std::move(data[i - 1]));
            allocator.Destroy(data + i - 1);
        }
        allocator.Construct(data + index, value);
        size++;
    }

    void remove(size_t index){ 
        if(index >= size){ 
            throw std::out_of_range("Invalid index"); 
        } 
        allocator.Destroy(data + index); 
        for (size_t i = index; i < size - 1; i++) { 
            allocator.Construct(data + i, std::move(data[i + 1])); 
            allocator.Destroy(data + i + 1); 
        } size--; 
    }

    ~DynamicArray(){
        for(size_t i=0;i<size;i++){
            allocator.Destroy(data+i);
        }
        allocator.Deallocate(data);
    }


};