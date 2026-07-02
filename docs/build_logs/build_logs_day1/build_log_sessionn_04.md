# Build Log – Session 4

**Date:** 1 July 2026

## Objective

During this session, I continued improving my custom `DynamicArray<T>` implementation after integrating my custom allocator and placement-new based object management. The primary goal was to verify that all array operations worked correctly while manually managing object lifetime.

---

## Testing Process

I tested the following operations:

- Constructors
- `append()`
- `insert()`
- `remove()`
- `resize()`
- `clear()`
- `reverse()`
- `find()`
- Destructor
- Capacity expansion

The tests were performed using both primitive types (`int`) and user-defined classes to ensure that constructors and destructors were being called correctly.

---

## Bugs Found

### 1. Incorrect Size Initialization

While implementing the parameterized constructor:

```cpp
DynamicArray(size_t n)
```

I initially wrote:

```cpp
size = n;
capacity = n;
```

This was incorrect because the constructor only allocated storage; it did not logically contain `n` elements.

As a result, the array behaved as if valid objects already existed. Functions such as `append()`, `insert()`, iteration, and the destructor assumed that every position already contained a constructed object, leading to incorrect behavior.

The correct implementation is:

```cpp
size = 0;
capacity = n;
```

Objects should only be constructed when elements are actually inserted into the array.

---

### 2. Resize Logic

While testing automatic resizing, I found that simply allocating a larger memory block was not sufficient.

Each existing object had to be individually copy-constructed (or move-constructed) into the new storage using placement new.

After successfully constructing every element in the new storage, the old objects had to be destroyed before deallocating the previous memory block.

This reinforced the idea that allocation and construction are two separate operations.

---

### 3. Insert Operation

Testing insertion revealed several bugs in the shifting logic.

Elements must be shifted from the end of the array toward the insertion position.

The correct sequence is:

1. Construct the new object in the destination position.
2. Move the previous object.
3. Destroy the old object.

Performing these operations in the wrong order caused overwritten objects, duplicate objects, or invalid object lifetimes.

---

### 4. Remove Operation

While testing `remove()`, I verified that the object being removed must first be destroyed.

The remaining elements are then move-constructed into the previous position, followed by destruction of their old locations.

Incorrect ordering could result in duplicate objects or double destruction.

---

### 5. Size vs Capacity

Several bugs were caused by confusing **size** with **capacity**.

- **capacity** represents the amount of allocated storage.
- **size** represents the number of constructed objects currently stored.

Maintaining a clear distinction between these two variables fixed multiple logical errors throughout the implementation.

---

### 6. Object Lifetime Management

Working with the custom allocator reinforced that allocation and construction are completely separate operations.

The allocator only provides raw memory.

Every object must be explicitly constructed before use and explicitly destroyed before the memory is deallocated.

This became especially important while implementing `append()`, `insert()`, `remove()`, and `resize()`.

---

## Lessons Learned

This debugging session significantly improved my understanding of:

- Placement new
- Manual object lifetime management
- Difference between allocation and construction
- Difference between destruction and deallocation
- Correct implementation of allocator-based containers
- Importance of maintaining correct `size` and `capacity`
- Correct ordering of construct, move, destroy, and deallocate operations

---

## Outcome

After fixing the identified issues, the `DynamicArray<T>` implementation correctly handled resizing, insertion, removal, destruction, and memory cleanup using the custom allocator.

This session also strengthened my understanding of how allocator-based containers such as `std::vector` internally manage raw memory and object lifetimes.