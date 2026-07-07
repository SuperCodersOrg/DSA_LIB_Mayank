#pragma once

#include"./LinkedList.h"
#include"./DynamicArray.h"
#include"./Allocator.h"
#include"./Myhash.h"
#include<iostream>

template<typename K, typename V, typename Hash=MyHash<K>>
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
    Hash hasher;
    size_t hash(const K& key)const{
        return hasher(key) % capacity;
    }

    double loadFactor(){
        return (double)size/capacity;
    }

    void rehash(){
        // std::cout<<"Rehash"<<std::endl;
        int oldCapacity=capacity;
        int newCapacity=oldCapacity*2;
        capacity=capacity*2;
        DynamicArray<LinkedList<Entry*>> newBuckets(capacity);
        for(int i=0;i<newCapacity;i++){
            newBuckets.append(LinkedList<Entry*>());
        }
        for(int i=0;i<oldCapacity;i++){
            for(auto it=buckets[i].begin(); it!=buckets[i].end();++it){
                Entry *entry=*it;
                int newIndex=hash(entry->key);
                newBuckets[newIndex].push_back(entry);
            }
        }
        buckets=newBuckets;
    }

    public:
    
    HashMap():buckets(8){
        // std::cout<<"constructor called"<<std::endl;
        size=0;
        capacity=8;
        for(int i=0;i<capacity;i++){
            buckets.append(LinkedList<Entry*>());
        }
    }

    HashMap(HashMap& other): buckets(other.capacity){
        size = 0;
        capacity = other.capacity;
        MAX_LOAD_FACTOR = other.MAX_LOAD_FACTOR;
        for(int i = 0; i < capacity; i++){
            buckets.append(LinkedList<Entry*>());
        }
        for(int i = 0; i < capacity; i++){
            for(auto it = other.buckets[i].begin(); it != other.buckets[i].end(); ++it){
                Entry* entry = *it;
                put(entry->key, entry->value);
            }
        }
    }

    int get_size(){
        return size;
    }
    int get_capacity(){
        return capacity;
    }

    void put(const K& key, const V& value){
        int bucket_index=hash(key);
        auto& bucket=buckets[bucket_index];
        for(auto it=bucket.begin();it!=bucket.end();++it){
            Entry* entry = *it;
            if(entry->key == key){
                entry->value=value;
                return;
            }
        }
        Entry* newEntry=allocator.Allocate();
        allocator.Construct(newEntry,key,value);
        bucket.push_back(newEntry);
        size++;
        // std::cout<<std::endl;
        if(loadFactor()>0.75){
            rehash();
        }
    }

    V& get(const K& key){
        int bucket_index=hash(key);
        auto& bucket=buckets[bucket_index];

        for(auto it=bucket.begin(); it!=bucket.end();++it){
            Entry *entry=*it;
            if(entry->key  == key){
                return (entry->value);
            }
        }
        throw std::out_of_range("Key not found");
    }

    bool containsKey(const K& key){
        int bucket_index=hash(key);
        auto& bucket=buckets[bucket_index];

        for(auto it=bucket.begin(); it!=bucket.end();++it){
            Entry *entry=*it;
            if(entry->key  == key){
                return true;
            }
        }
        return false;
    }

    bool isEmpty() const{
        return size == 0;
    }

    bool remove(const K& key){
        int bucket_index=hash(key);
        auto& bucket=buckets[bucket_index];
        int index=0;

        for (auto it = bucket.begin(); it != bucket.end(); ++it){
            Entry* entry = *it;

            if (entry->key == key)
            {
                Entry* removedEntry = bucket.remove(index);

                allocator.Destroy(removedEntry);
                allocator.Deallocate(removedEntry);

                size--;

                return true;
            }

            index++;
        }
        return false;
    }

    void clear(){
        for(int i = 0; i < capacity; i++){
            auto& bucket = buckets[i];

            while(!bucket.isEmpty()){
                Entry* entry = bucket.remove(0);
                allocator.Destroy(entry);
                allocator.Deallocate(entry);
            }
        }

        size = 0;
    }

    // K* getKeys(){
    //     // DynamicArray<K> keys(size);
    //     MyAllocator<K> keyallocator;
    //     K* keys=keyallocator.Allocate(size);
    //     int index=0;
    //     for(int i = 0; i < capacity; i++){
    //         for(auto it = buckets[i].begin(); it != buckets[i].end(); ++it){
    //             Entry* entry = *it;
    //             keyallocator.Construct(keys+index,entry->key);
    //             index++;
    //         }
    //     }

    //     return keys;
    // }
     DynamicArray<K> getKeys(){
        DynamicArray<K> Keys(size);

        for(int i = 0; i < capacity; i++){
            for(auto it = buckets[i].begin(); it != buckets[i].end(); ++it){
                Entry* entry = *it;
                Keys.append(entry->key);
            }
        }

        return Keys;
    }
    DynamicArray<V> getValues(){
        DynamicArray<V> values(size);

        for(int i = 0; i < capacity; i++){
            for(auto it = buckets[i].begin(); it != buckets[i].end(); ++it){
                Entry* entry = *it;
                values.append(entry->value);
            }
        }

        return values;
    }

    void print(){
        std::cout<<std::endl;
        for(int i=0;i<capacity;i++){
            for(auto it=buckets[i].begin();it!=buckets[i].end();++it){
                Entry *entry=*it;
                std::cout<<i<<"-"<<entry->value;
            }
            std::cout<<std::endl;
        }
    }
    
    HashMap& operator=(HashMap& other){
        if(this == &other) return *this;
        
        clear();
        buckets.clear();

        capacity = other.capacity;
        size = 0;
        MAX_LOAD_FACTOR = other.MAX_LOAD_FACTOR;

        for(int i = 0; i < capacity; i++){
            buckets.append(LinkedList<Entry*>());
        }

        for(int i = 0; i < capacity; i++){
            for(auto it = other.buckets[i].begin();it != other.buckets[i].end();++it)
            {
                Entry* entry = *it;
                put(entry->key, entry->value);
            }
        }

        return *this;
    }

    ~HashMap(){
        // std::cout<<"Destructor called";
        for (int i = 0; i < capacity; i++){
            for (auto it = buckets[i].begin(); it != buckets[i].end(); ++it){
                Entry* entry = *it;

                allocator.Destroy(entry);
                allocator.Deallocate(entry);
            }
        }
    }


};