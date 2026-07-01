# Build Log – Custom DynamicArray (STL-like Vector Implementation)

**Session:** 2 | **Date:** July 1, 2026 | **Time:** 10:00 – 12:30  

---

## 🎯 Objective

To build a **dynamic array (vector-like container)** using the previously implemented `MyAllocator`, and understand:

- Dynamic memory growth
- Object lifecycle management
- Insert / remove operations
- Move semantics in containers
- STL-like internal behavior of `std::vector`

---

## 🧱 Final Features Implemented

### 1. Dynamic Memory Container
- Built `DynamicArray<T>` template class
- Stores elements in raw allocated memory
- Uses `MyAllocator` for all memory operations

---

### 2. Core Data Members
- `T* data` → raw storage pointer
- `size_t size` → number of active elements
- `size_t capacity` → allocated memory size

---

### 3. Dynamic Resizing System

- Automatic resizing when full
- Capacity doubles on overflow
- Steps:
  - Allocate new memory
  - Copy construct elements
  - Destroy old elements
  - Free old memory
  - Update pointer and capacity

---

### 4. Element Insertion (Insert Operation)

- Insert element at any valid index
- Supports shifting elements to the right
- Uses move semantics for performance

#### Behavior:
- Shift elements from end → index
- Construct new positions using moved values
- Destroy old positions
- Insert new value at target index

---

### 5. Element Removal (Erase Operation)

- Remove element at given index
- Shift elements left
- Maintain array continuity
- Reduce size properly

#### Behavior:
- Destroy target element
- Move shift remaining elements left
- Decrease size

---

### 6. Append Operations

- `append(const T&)` → copy append
- `append(T&&)` → move append
- Automatically triggers resize when needed

---

### 7. Utility Functions

- `get_size()` → returns number of elements
- `get_capacity()` → returns allocated capacity

---

## 🔥 Key Concepts Learned

### 1. Object Lifecycle Control
- Allocation ≠ Construction
- Must manually:
  - Construct objects
  - Destroy objects

---

### 2. Placement New Usage
- Objects constructed inside pre-allocated memory
- Enables custom container design like STL

---

### 3. Move Semantics in Containers
- Used during insert shifting
- Reduces unnecessary copying
- Improves performance for heavy objects

---

### 4. Vector Growth Strategy
- Capacity doubling strategy (amortized O(1) append)
- Efficient memory reallocation model

---

### 5. Index Validation Rules
- Insert: `index <= size`
- Remove: `index < size`

---

## ⚠️ Issues Faced During Development

### ❌ 1. Reverse loop underflow bug
- Using `size_t` incorrectly in reverse loops
- Fixed using `i > index` condition

---

### ❌ 2. Insert boundary confusion
- Misunderstanding `index == size` validity
- Fixed based on STL vector rules

---

### ❌ 3. Move vs copy confusion
- Initially unclear when to use move semantics
- Resolved during insert optimization

---

### ❌ 4. Memory lifecycle mistakes
- Destroy order confusion during shifting
- Fixed by enforcing strict Construct → Destroy order

---

## 🧠 Final Architecture Achieved

The final implementation behaves like a simplified:

> **std::vector-like dynamic array with manual memory control**

---

## 📌 Current Status

✔ Dynamic allocation working  
✔ Automatic resizing working  
✔ Append operations working  
✔ Insert operation working  
✔ Remove operation working  
✔ Move-based shifting implemented  
✔ Memory cleanup correct  

---

## 🏁 Summary

This session successfully transformed a basic allocator into a **fully functional dynamic array container**, implementing core STL concepts such as:

- Dynamic resizing
- Memory management separation
- Move semantics usage
- Insert/remove operations
- Container design principles

This forms a strong foundation for implementing full STL-style containers in future sessions.