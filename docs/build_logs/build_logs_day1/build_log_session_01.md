# Build Log – Custom Memory Allocator (`MyAllocator`)

**Date:** July 1, 2026 **Time:** 09:00 - 10:00

## Objective

Implemented a custom generic memory allocator to understand and replicate the core functionality of C++'s `std::allocator`.

---

## Features Implemented

### 1. Memory Allocation

- Added `Allocate(size_t n = 1)` function.
- Uses `malloc()` to allocate raw, uninitialized memory.
- Supports allocation for both single objects and arrays.
- Throws `std::bad_alloc` if memory allocation fails.

### 2. Memory Deallocation

- Added `Deallocate(T* ptr)` function.
- Releases previously allocated memory using `free()`.

### 3. Object Construction

- Added variadic template `Construct(T* ptr, Args&&... args)`.
- Uses **placement new** to construct an object in pre-allocated memory.
- Allows constructor arguments to be passed to the object's constructor.

### 4. Object Destruction

- Added `Destroy(T* ptr)` function.
- Explicitly invokes the object's destructor without deallocating memory.
- Separates **object lifetime management** from **memory management**.

---

## Concepts Learned

- Difference between **raw memory allocation** and **object construction**.
- How **placement new** constructs an object in existing memory.
- Explicit destructor invocation.
- Variadic templates for generic object construction.
- Separation of **allocation/deallocation** from **construction/destruction**.

---

## Current Status

- ✅ Raw memory allocation implemented.
- ✅ Raw memory deallocation implemented.
- ✅ Placement object construction implemented.
- ✅ Explicit object destruction implemented.
- ✅ Generic template-based allocator completed.

---

## Next Steps

- Integrate `MyAllocator` into custom containers such as `DynamicArray`.
- Replace direct `new`/`delete` usage with allocator operations.
- Improve `Construct()` using `std::forward` for perfect forwarding.
- Explore allocator-aware container design similar to the C++ Standard Library.
- Implement exception-safe object construction for multiple objects.
- Study how `std::allocator_traits` extends allocator functionality.

---

## Summary

Successfully implemented a basic custom allocator that separates memory allocation from object construction. This allocator provides the essential operations required by custom data structures and serves as a foundation for building STL-like containers and understanding C++ memory management internals.