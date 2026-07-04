#pragma once

#include"./LinkedList.h"
#include"./DynamicArray.h"
#include"./Allocator.h"
#include<iostream>

template<typename K, typename V>
class HashMap{
    private:
    class Entry{
        public:
        K key;
        V value;
        Entry(const K& key,const V& value){
            this->key=key;
            this->value=value;
        }
    };
    int size;
    int capacity;
    double MAX_LOAD_FACTOR=0.75;
    DynamicArray<LinkedList<Entry*>> buckets;
    MyAllocator<Entry> allocator;

    size_t hash(const K& key){
        return key%capacity;
    }
    public:
    HashMap():buckets(8){
        std::cout<<"constructor called";
        size=0;
        capacity=8;
        for(int i=0;i<capacity;i++){
            buckets.append(LinkedList<Entry*>());
        }
    }

    void put(const K& key, const V& value){
        int bucket_index=hash(key);
        
    }

    ~HashMap(){
        std::cout<<"Destructor called";
        for (int i = 0; i < capacity; i++){
            for (auto it = buckets[i].begin(); it != buckets[i].end(); ++it){
                Entry* entry = *it;

                allocator.Destroy(entry);
                allocator.Deallocate(entry);
            }
        }
    }


};