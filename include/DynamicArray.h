#pragma once

#include <stdexcept>
#include<iostream>
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
        size=0;
        capacity=n;
        data = allocator.Allocate(capacity);
    }

    DynamicArray(const DynamicArray& other) {
        size = other.size;
        capacity = other.capacity;

        data = allocator.Allocate(capacity);

        for (size_t i = 0; i < size; i++) {
            allocator.Construct(data + i, other.data[i]);
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other)
            return *this;

        clear();
        allocator.Deallocate(data);

        size = other.size;
        capacity = other.capacity;

        data = allocator.Allocate(capacity);

        for (size_t i = 0; i < size; i++) {
            allocator.Construct(data + i, other.data[i]);
        }

        return *this;
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
    
    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
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

    void clear() {
        for (size_t i = 0; i < size; i++) {
            allocator.Destroy(data + i);
        }
        size = 0;
    }

    void reverse() {
        if (size <= 1) return;
        size_t i = 0;
        size_t j = size - 1;

        while (i < j) {
            T temp = std::move(data[i]);
            data[i] = std::move(data[j]);
            data[j] = std::move(temp);
            i++;
            j--;
        }
    }

    int find(const T& value) {
        for (size_t i = 0; i < size; i++) {
            if (data[i] == value) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void print() {
        for (size_t i = 0; i < size; i++) {
            std::cout<< data[i] << " ";
        }
        std::cout << "\n";
    }
    
    ~DynamicArray(){
        for(size_t i=0;i<size;i++){
            allocator.Destroy(data+i);
        }
        allocator.Deallocate(data);
    }
};