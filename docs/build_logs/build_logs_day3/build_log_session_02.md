**Date:** 3 July 2026 | **Time:** 4:00 - 6:00

## Session 2 – HashMap Foundation and Iterator Support

During this session, I began implementing a generic `HashMap<K, V>` using separate chaining for collision resolution. Before writing the insertion logic, I spent time understanding how bucket storage should be organized and how manual object lifetime management interacts with my custom allocator.

The first design decision was choosing the bucket representation. Initially, I considered storing buckets using my custom `DynamicArray`, but I realized that my `DynamicArray` follows lazy construction, where memory is allocated without immediately constructing objects. Since a hash table requires every bucket to exist as an empty container from the beginning, I decided to allocate an array of `LinkedList<Entry>` objects manually using `MyAllocator`. Each bucket is explicitly constructed using placement new through `allocator.Construct(&buckets[i])`. This helped me understand the difference between raw allocated memory and constructed objects.

I implemented the internal `Entry` class to represent a key-value pair stored inside each bucket. I also implemented a simple modulo-based hash function to compute the bucket index for integer keys and wrote the `findEntry()` helper function to search the linked list of a bucket for an existing key.

Next, I implemented the `insert()` operation. The insertion process first searches for an existing key using `findEntry()`. If the key already exists, its associated value is updated. Otherwise, a new `Entry` object is appended to the corresponding linked list. After every successful insertion, the current load factor is calculated. When the load factor exceeds `0.75`, the hash map automatically performs rehashing.

The `rehash()` function doubles the bucket capacity, allocates a new array of buckets, constructs each bucket individually, and reinserts every existing key-value pair into the new bucket array using the updated hash function. After all entries have been transferred, the old buckets are properly destroyed and their memory is deallocated using the custom allocator. This process reinforced my understanding of manual memory management and object lifetime.

In addition to the hash map implementation, I also implemented an iterator for my custom `DynamicArray`, similar to the iterator already available in my `LinkedList`. This allows the dynamic array to support traversal using `begin()` and `end()`, making the interface more consistent across my custom containers and preparing them for use with generic algorithms.

During this session, I also developed a much deeper understanding of placement new and explicit object construction. I learned that memory allocation and object construction are separate operations. Allocating memory simply reserves raw storage, while `allocator.Construct()` creates an object at a specific memory address using placement new. This explains why `allocator.Construct(&buckets[i])` requires the address of the allocated memory rather than the object itself.

Overall, this session established the core infrastructure of my custom hash map. I successfully implemented bucket allocation, collision handling using separate chaining, insertion, load factor calculation, automatic rehashing, and iterator support for the dynamic array. These components provide a strong foundation for implementing lookup, deletion, and additional hash map operations in future development sessions.
```
