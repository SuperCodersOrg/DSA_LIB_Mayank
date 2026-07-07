# Daily Journal

**Date:** 3 July 2026

## Overview

Today I continued working on my custom C++ data structures library by starting the implementation of a generic `HashMap<K, V>`. Before writing the complete implementation, I spent considerable time understanding how hash tables manage buckets, collisions, memory allocation, and object lifetime when using a custom allocator. I also implemented an iterator for my `DynamicArray` to make its interface more consistent with my `LinkedList`.

## Work Completed

- Started implementing a generic `HashMap<K, V>`.
- Implemented the internal `Entry` class to store key-value pairs.
- Implemented a simple modulo-based hash function for integer keys.
- Implemented the `findEntry()` helper function to search for existing keys inside a bucket.
- Implemented the `insert()` operation with key update support.
- Implemented load factor calculation.
- Implemented automatic rehashing when the load factor exceeds the defined threshold.
- Implemented an iterator for `DynamicArray`, allowing traversal using `begin()` and `end()` similar to `LinkedList`.

## Problems Faced

### 1. Understanding Bucket Storage

Initially, I was confused about why the hash map stores buckets as:

```cpp
LinkedList<Entry>* buckets;
```

instead of using my custom `DynamicArray`.

My first assumption was that a hash table should always use a dynamic array for bucket storage. After exploring the implementation in detail, I realized that the important requirement is to have an array of buckets where each bucket can store multiple entries. Whether the array is managed manually or through a custom dynamic array is a design choice.

### 2. Lazy Construction in DynamicArray

Another issue I encountered was understanding why my `DynamicArray` constructor allocates memory without constructing objects.

Initially, I thought constructing all objects immediately would simplify the implementation and have little performance impact. However, I learned that separating memory allocation from object construction provides much greater flexibility. Objects are only constructed when they are actually inserted into the container, which avoids unnecessary constructor calls and allows the container to work with types that do not have default constructors.

This also explained why my current `DynamicArray` is not immediately suitable for storing hash map buckets without first constructing each bucket object.

### 3. Placement New and Object Construction

I also struggled to understand why the following statement is required:

```cpp
allocator.Construct(&buckets[i]);
```

At first, I expected `Construct()` to receive the object directly. After reviewing placement new, I understood that `Allocate()` only reserves raw memory. The `Construct()` function requires the address of that memory because it creates an object at that specific location. This clarified the difference between allocated memory and constructed objects.

### 4. Designing the Bucket Array

I spent time comparing different possible designs, including:

- `LinkedList<Entry>* buckets`
- `DynamicArray<LinkedList<Entry>>`
- `DynamicArray<Entry*>`

This comparison helped me understand why each bucket must itself be a container capable of storing multiple entries, since different keys may hash to the same bucket.

## Concepts Learned

Today I gained a much deeper understanding of:

- The internal structure of a hash table.
- Collision handling using separate chaining.
- Bucket allocation and initialization.
- Load factor and its role in determining when to rehash.
- The difference between allocated memory and constructed objects.
- Placement new and explicit object lifetime management.
- Why lazy construction is commonly used in generic containers.
- How iterators make custom containers easier to traverse and use.

## Reflection

Today's session involved more design analysis than coding. Although I spent a significant amount of time understanding memory management and bucket organization, these concepts helped clarify several aspects of generic container implementation that had previously been confusing. By the end of the session, I had a much stronger understanding of how a hash map is built internally and how custom allocators interact with object construction and destruction. This foundation will make it easier to implement lookup, deletion, and additional hash map features in the next development session.
````
