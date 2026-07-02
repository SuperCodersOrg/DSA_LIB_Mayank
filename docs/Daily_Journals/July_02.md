**Date:** 2 July 2026

---

# Section 1 – Specific Bugs

Today I focused on debugging and validating my custom `LinkedList<T>` implementation after completing most of its core operations.

During testing, I discovered several issues.

The first issue occurred when testing `front()` and `back()` on an empty linked list. These functions accessed `head` and `tail` without checking whether the list was empty, resulting in undefined behavior instead of throwing an exception.

The second issue appeared while testing `remove()`. The implementation did not correctly handle removing the first and last nodes, causing incorrect pointer updates and inconsistent list state.

The third issue was found while verifying copy behavior. Using assignment created a shallow copy because no copy assignment operator had been implemented yet. Although the copy constructor performed a deep copy correctly, assignment required future implementation.

Finally, I performed extensive testing using both normal and edge-case scenarios to verify the correctness of all implemented operations.

---

# Section 2 – Failed Attempts

Initially, I assumed that most operations were functioning correctly because basic insertion and deletion tests produced the expected output.

However, after writing comprehensive test cases, I found that several edge cases exposed hidden problems. Calling `front()` or `back()` on an empty list caused invalid memory access, and removing nodes from boundary positions required separate handling.

While testing copy semantics, I also learned that writing:

```cpp
list2 = list1;
```

does not invoke the copy constructor. Instead, it uses the compiler-generated copy assignment operator, which performs a shallow copy. Since I have not yet implemented the copy assignment operator, I limited testing to the copy constructor.

These debugging sessions reinforced the importance of testing edge cases instead of relying only on normal inputs.

---

# Section 3 – Testing Performed

The following scenarios were tested:

- Empty list operations
- Single-element list
- `push_front()` and `push_back()`
- `pop_front()` and `pop_back()`
- `insert()`
- `remove()`
- `find()`
- `operator[]`
- `front()` and `back()`
- `clear()`
- Copy constructor
- Exception handling for invalid operations

All implemented functionality passed the designed test cases successfully.

---

# Section 4 – Code Reference

## Bug Fixes

### Major Fixes Completed

- Added exception handling to `front()` and `back()` for empty lists.
- Corrected boundary handling in `remove()`.
- Verified proper node destruction in `clear()`, `pop_front()`, and `pop_back()`.
- Confirmed that the copy constructor performs a deep copy.
- Created comprehensive test cases covering normal and edge-case scenarios.

### Files Modified

- `LinkedList.h`
- `main.cpp`

### Functions Tested

- `push_front()`
- `push_back()`
- `pop_front()`
- `pop_back()`
- `insert()`
- `remove()`
- `find()`
- `front()`
- `back()`
- `operator[]`
- `clear()`
- Copy constructor
- Destructor

---

# Section 5 – Learning Reflection

Today's debugging session reinforced that implementing a linked list involves more than simply making operations work—it also requires careful handling of boundary conditions and proper memory management.

Writing dedicated test cases helped uncover issues that were not visible during normal execution. I gained a better understanding of exception safety, pointer manipulation, deep copying, and the distinction between the copy constructor and the copy assignment operator in C++.

After today's debugging and testing, the current implementation of `LinkedList<T>` is stable for all implemented operations and correctly handles both normal and edge-case scenarios.