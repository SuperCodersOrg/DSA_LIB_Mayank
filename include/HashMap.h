#pragma once

#include"./LinkedList.h"
#include"./Allocator.h"

template<typename K, typename V>
class HashMap{
    private:
        class Entry{
            public:
                K key;
                V value;
                Entry(const K& k, const V& v){
                    key=k;
                    value=v;
                }   
        };
        LinkedList<Entry>* buckets;
        size_t currentSize;
        size_t currentCapacity;
        double MAX_LOAD_FACTOR = 0.75;
        MyAllocator<LinkedList<Entry>> allocator;

        double loadFactor(){
            return (static_cast<double>(currentSize)/currentCapacity);
        }

        size_t bucketIndex(const K& key){
            return key%currentCapacity;
        }

        
        public:
            HashMap(){
                currentCapacity=8;
                currentSize=0;
                buckets = allocator.Allocate(currentCapacity);
                for (size_t i = 0; i < currentCapacity; i++){
                    allocator.Construct(&buckets[i]);
                }
            }
            ~HashMap(){
                for (size_t i = 0; i < currentCapacity; i++){
                    allocator.Destroy(&buckets[i]);
                }

                allocator.Deallocate(buckets);
            }
};
