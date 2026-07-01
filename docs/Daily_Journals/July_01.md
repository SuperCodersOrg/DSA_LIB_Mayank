**Date:** 1 July 2026

---

# Section 1 – Specific Bugs

Today I focused on testing and improving my custom `DynamicArray<T>` implementation after introducing a custom allocator and manual object lifetime management.

During testing, I encountered multiple issues.

The first issue appeared while testing `insert()` and `remove()`. Although the program compiled successfully, elements were not always shifted correctly after insertion or deletion. This caused incorrect output for some test cases, especially when inserting or removing elements from the middle of the array.

The second issue was discovered while testing the container with `std::string` and a custom `Person` class. Primitive types such as `int` worked correctly, but complex objects exposed problems in object lifetime management. During resizing and element shifting, some objects were destroyed more than once or moved incorrectly, leading to heap corruption and unstable behavior.

The third issue occurred while writing test cases for user-defined classes. My `Person` class could not be printed using `print()` because the stream insertion operator (`operator<<`) had not been overloaded. Similarly, searching for a `Person` object required implementing `operator==`.

---

# Section 2 – Failed Attempts

Initially, I believed that the same logic used for primitive data types would also work correctly for strings and custom objects. After running several tests with integers, everything appeared to function normally.

However, once I began testing with `std::string` and `Person`, I observed unexpected behavior including incorrect element movement, object corruption during resize operations, and crashes caused by invalid destruction of objects.

My first implementation of the shifting logic destroyed objects immediately after moving them, which created overlapping object lifetimes during insertion and removal. After reviewing the implementation, I redesigned the shifting process so that objects are constructed in their new locations before the old objects are destroyed.

I also modified the resize logic to move every existing element into newly allocated memory before destroying the original objects and releasing the old memory block.

Finally, I implemented `operator<<` and `operator==` for the `Person` class so that the container could correctly print and compare user-defined objects during testing.

---

# Section 3 – Memory Diagram

Memory diagrams prepared today:

- DynamicArray during insert operation
- DynamicArray during remove operation
- DynamicArray before and after resize
- Object movement using placement new and custom allocator

> **Note:** Hand-drawn memory diagrams have been submitted separately as required.

---

# Section 4 – Code Reference

## DynamicArray Testing

### Tasks Completed

- Created comprehensive test cases for primitive types.
- Tested the container with `std::string`.
- Tested the container with a custom `Person` class.
- Verified resize behavior under repeated insertions.
- Verified `reverse()`, `find()`, `clear()`, and indexing operations.

## Bug Fixes

### Major Fixes Completed

- Corrected `insert()` shifting logic.
- Corrected `remove()` shifting logic.
- Improved `resize()` implementation using move semantics.
- Fixed object destruction order.
- Added support for custom object comparison.
- Added stream output support for user-defined classes.

### Files Modified

- `DynamicArray.h`
- `Allocator.h`
- `main.cpp`

### Functions Tested

- `append()`
- `insert()`
- `remove()`
- `resize()`
- `clear()`
- `reverse()`
- `find()`
- `operator[]`
- Destructor

---

# Section 5 – Learning Reflection

Today's work helped me understand that implementing a generic container is much more than simply storing values in memory.

Testing with primitive data types alone was not enough to verify correctness. By introducing `std::string` and custom classes, I learned how important proper object lifetime management is when implementing containers in C++.

I also gained a deeper understanding of move semantics and placement new. Correctly constructing objects in new memory before destroying the originals is essential for preventing memory corruption and ensuring exception-safe behavior.

Another important lesson was that generic containers depend on the interfaces provided by user-defined types. Implementing operators such as `operator<<` and `operator==` allowed my container to work seamlessly with custom classes during printing and searching.

After today's testing and debugging, my `DynamicArray` implementation is significantly more stable and correctly supports primitive types, standard library objects, and user-defined classes.