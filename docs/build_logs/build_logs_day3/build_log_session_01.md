# Design Journal

**Date:** 3 July 2026 | **Time:** 09:00 - 11:00

---

# Section 1 – Progress Made

Today I began implementing the foundation of my custom `HashMap<K, V>` using **separate chaining** with my own `LinkedList` and custom memory allocator.

I first designed the internal `Entry` class to store key-value pairs (`key` and `value`). Then I added the primary data members required by the hash map:

- `buckets` (dynamic array of linked lists)
- `currentSize`
- `currentCapacity`
- `MAX_LOAD_FACTOR`

Instead of using `new[]`, I used my custom allocator (`MyAllocator`) to allocate raw memory for the bucket array. Since my allocator internally uses `malloc()`, I learned that memory allocation only reserves raw memory and does not construct objects automatically.

To properly initialize each bucket, I manually constructed every `LinkedList<Entry>` object using placement new through `allocator.Construct()`.

I also implemented the destructor of `HashMap`, where every bucket is manually destroyed before the allocated memory is released. This helped me understand the complete lifecycle of objects when working with custom allocators.

The lifecycle is:

1. Allocate raw memory.
2. Construct objects.
3. Use the objects.
4. Destroy objects.
5. Deallocate memory.

---

# Section 2 – Helper Functions

I implemented the first two helper functions required for the hash map.

### `loadFactor()`

Calculates the current load factor of the hash map.

```cpp
double loadFactor() {
    return static_cast<double>(currentSize) / currentCapacity;
}
```

While implementing this function, I learned why `static_cast<double>()` is necessary to avoid integer division.

---

### `bucketIndex()`

Implemented a simple hash function for integer keys.

```cpp
size_t bucketIndex(const K& key) {
    return key % currentCapacity;
}
```

This function determines the bucket where a key should be stored.

---

# Section 3 – Improvements to LinkedList

While planning the implementation of `HashMap::insert()` and `HashMap::get()`, I realized that my `LinkedList` could not be traversed from outside the class because both `Node` and `head` were private.

To solve this, I implemented a custom **Iterator** inside `LinkedList`.

The iterator contains:

- Pointer to the current node.
- `operator*()` to access node data.
- `operator++()` to move to the next node.
- `operator==()` for comparison.
- `operator!=()` for comparison.

I also added:

```cpp
begin()
end()
```

These functions allow traversal of the linked list without exposing its internal implementation.

Example:

```cpp
for(auto it = list.begin(); it != list.end(); ++it)
{
    std::cout << *it << " ";
}
```

This made the linked list much more reusable and prepares it for use inside the hash map.

---

# Section 4 – Challenges Faced

Today's work involved several conceptual challenges.

### Understanding Bucket Allocation

Initially, I was confused about why `buckets` is declared as a pointer:

```cpp
LinkedList<Entry>* buckets;
```

After studying dynamic memory allocation, I understood that the hash map requires a runtime-sized array of buckets, which can only be created dynamically.

---

### Understanding Custom Allocators

I initially assumed that allocating memory would automatically create `LinkedList` objects.

Later I understood that:

- `malloc()` only allocates raw memory.
- Constructors are **not** called automatically.
- Every object must be explicitly constructed using placement new.
- Every object must also be manually destroyed before deallocation.

This clarified the difference between memory allocation and object construction.

---

### Understanding Iterators

Another major challenge was understanding why an iterator is required.

At first, I thought the linked list itself could simply traverse its nodes internally.

After studying the concept, I realized that because `Node` and `head` are private, external classes like `HashMap` cannot access them directly.

The iterator provides a safe interface for traversing the linked list while preserving encapsulation.

---

### Understanding Modern C++ Features

I also learned the purpose of:

- `static_cast<double>()`
- `auto`
- Placement new
- Prefix increment operator overloading
- Dereference operator overloading

These concepts helped me better understand how C++ containers are implemented internally.

---

# Section 5 – Current Status

At the end of today's session, the following components are complete:

- ✅ HashMap class skeleton
- ✅ Entry class
- ✅ Dynamic bucket allocation
- ✅ Constructor
- ✅ Destructor
- ✅ Load factor calculation
- ✅ Bucket index calculation
- ✅ Custom LinkedList iterator
- ✅ begin() and end() support

---

# Section 6 – Next Goals

In the next session, I plan to implement:

- `insert()`
- `get()`
- `containsKey()`
- `remove()`
- Rehashing when the load factor exceeds the maximum threshold

---

# Reflection

Today's work was focused more on understanding low-level container implementation than writing a large amount of code.

Although the implementation is still in its early stages, I gained a much deeper understanding of:

- Manual memory management
- Custom allocators
- Placement new
- Object lifetime
- Iterator implementation
- Encapsulation
- Internal design of C++ containers

These concepts will serve as the foundation for completing my custom `HashMap` implementation in the coming sessions.