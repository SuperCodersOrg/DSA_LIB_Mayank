# Build Log – Session 2 (LinkedList Implementation)

**Date:** 2 July 2026 | **Time:** 12:00 - 1:00

## Objective

The objective of this session was to continue the implementation of my generic `LinkedList<T>` after completing the initial structure in the previous session. My focus was on expanding the functionality of the container by adding commonly used utility functions and improving the interface to resemble the C++ Standard Library.

---

## Progress Made

During this session, I extended the linked list implementation with several additional features.

The following functionality was implemented:

- `size()`
- `isEmpty()`
- `front()`
- `back()`
- `operator[]`
- Const and non-const overloads for element access
- Improved `initializer_list` constructor

The linked list now supports initialization using brace syntax:

```cpp
LinkedList<int> list = {10, 20, 30};
```

---

## Challenges and Problems Faced

### 1. Understanding `const` Member Function Overloading

While implementing `front()` and `back()`, I initially attempted to overload them as:

```cpp
T& front();

const T& front();
```

The compiler reported that these functions could not be overloaded.

After investigating, I learned that **the return type is not part of a function's signature in C++**. Since both functions had the same name and parameter list, the compiler treated them as identical.

The correct implementation is:

```cpp
T& front();

const T& front() const;
```

The additional `const` after the function declaration changes the type of the implicit `this` pointer, allowing the functions to be overloaded correctly.

This improved my understanding of const-correctness in C++.

---

### 2. Understanding Why STL Provides Two Versions

While learning about `front()` and `back()`, I explored why the Standard Library provides both const and non-const versions.

I learned that:

- Non-const objects should allow modification of stored elements.
- Const objects should only allow read-only access.

Providing both overloads enables the compiler to automatically select the correct function depending on whether the container itself is const.

---

### 3. Fixing the `initializer_list` Constructor

During testing, I discovered that the list length was larger than expected.

Initially, I incremented `length` inside both:

- `push_back()`
- `initializer_list` constructor

Since `push_back()` already updates the size, the constructor was counting every inserted element twice.

Removing the extra increment corrected the list size.

This reinforced the importance of ensuring that each member variable has a single responsibility for updates.

---

### 4. Implementing Random Access Operator

I implemented the subscript operator:

```cpp
operator[](size_t index)
```

Although linked lists do not support constant-time random access, this function provides convenient syntax similar to arrays:

```cpp
list[2]
```

Internally, the implementation traverses the linked list node by node until the requested index is reached.

This exercise highlighted one of the major differences between dynamic arrays and linked lists.

---

### 5. Const and Non-Const `operator[]`

After implementing `operator[]`, I also created both const and non-const overloads.

This allows:

- Modification when the linked list is mutable.
- Read-only access when the linked list is declared as const.

This further strengthened my understanding of const-correct API design.

---

### 6. Improving the Public Interface

Compared to the previous session, the linked list now provides utility functions commonly found in STL containers:

- `size()`
- `isEmpty()`
- `front()`
- `back()`
- `operator[]`

Adding these operations made the class feel much closer to a standard container.

---

## Concepts Reinforced

This session strengthened my understanding of:

- Const correctness
- Function overloading
- Const member functions
- Reference return types
- Difference between returning by value and by reference
- Read-only interfaces
- Random access in linked lists
- Index traversal
- STL container design principles

---

## Current Status

Successfully implemented:

- Nested `Node` class
- Custom allocator integration
- Default constructor
- Initializer list constructor
- `push_front()`
- `push_back()`
- `size()`
- `isEmpty()`
- `front()`
- `back()`
- Const overloads
- `operator[]`
- `print()`

The linked list now supports insertion, traversal, element access, size tracking, and both mutable and immutable interfaces.

---

## Next Steps

The next session will focus on implementing:

- `insert()`
- `remove()`
- `find()`
- `contains()`
- `clear()`
- Destructor
- Copy constructor
- Copy assignment operator
- Move constructor
- Move assignment operator
- Iterator support

---

## Outcome

This session significantly expanded the functionality of my custom `LinkedList<T>`. Besides implementing several new operations, I developed a deeper understanding of const-correctness, function overloading, and designing container interfaces similar to those provided by the C++ Standard Library. The linked list now has a solid foundation for implementing more advanced operations in future sessions.