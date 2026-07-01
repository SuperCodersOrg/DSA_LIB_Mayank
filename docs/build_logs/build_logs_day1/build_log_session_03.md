# Build Log – Session 3: DynamicArray Completion + Git Finalization

**Date:** July 1, 2026  
**Session Duration:** 12:30 – 14:00  

---

## 🎯 Objective

To complete the `DynamicArray` implementation by adding utility methods, finalize Git workflow, and stabilize the container into a mini STL-like `std::vector`.

---

## 🧱 Major Features Completed

### 1. Core Container Finalization

Final `DynamicArray` supports:

✔ Dynamic memory allocation  
✔ Automatic resizing  
✔ Insert / remove operations  
✔ Append (copy + move)  
✔ operator[] overloading  
✔ Size / capacity tracking  

---

### 2. Utility Methods Implemented

---

## 🧹 clear()

### Functionality:
Removes all elements without freeing memory.

### Implementation concept:
- Destroy all constructed objects
- Reset size to 0

### Issues Faced:
❌ Initially unclear difference between:
- clearing data
- deallocating memory

✔ Fixed by separating:
- `Destroy()` vs `Deallocate()`

---

## 🔍 find(const T& value)

### Functionality:
Returns index of element or -1 if not found

### Issues Faced:
❌ Confusion between:
- `size_t` (unsigned)
- returning `-1`

✔ Solution:
- Cast index using `static_cast<int>`
- Understood signed vs unsigned mismatch

---

## 🖨 print()

### Functionality:
Displays all elements in array

### Issues Faced:
❌ Dependency on type `T`

Problem:
- `T` must support `operator<<`

✔ Learned:
- Template constraints are implicit in C++

---

## 🔄 reverse()

### Functionality:
Reverses array in-place

### Issues Faced:

❌ 1. Swapping confusion  
Initially unclear whether to use:
- copy swap
- move swap

✔ Final solution:
- Used swap logic with temporary variable or `std::move`

---

❌ 2. Loop boundary mistakes  
- Reverse indexing errors using `size_t`
- Underflow risk in loops

✔ Fixed using:
- `i < j` two-pointer approach

---

## ⚙️ Git Workflow Finalization

### Branch Structure:
main
└── features/dynamicarray
### Merge Command Used:

```bash
git checkout main
git merge features/dynamicarray --no-edit
