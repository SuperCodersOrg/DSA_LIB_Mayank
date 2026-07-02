# Build Log – Session 1

**Date:** 2 July 2026 | **Time:** 10:00 - 12:00
## Objective

After successfully completing my custom `DynamicArray<T>` implementation using a custom allocator and manual object lifetime management, I began implementing the next data structure in my library: a generic `LinkedList<T>`.

The objective of this session was to understand the internal design of a linked list and implement its basic structure while continuing to use my custom allocator for dynamic memory management.

---

## Preparation

Before writing code, I prepared a detailed proposal explaining:

- The limitations of contiguous memory allocation.
- Memory fragmentation.
- Why dynamic arrays require contiguous memory.
- How linked lists solve this limitation.
- The concept of storing data using nodes connected through pointers.
- The purpose of `head` and `tail` pointers.
- The operations required in a linked list.
- Time complexity analysis for every planned operation.

Creating the proposal helped me understand the design before beginning implementation.

---

## Implementation Progress

During this session, I implemented the initial version of a generic `LinkedList<T>`.

The following components were completed:

- Nested `Node` class
- `head` pointer
- `tail` pointer
- `length` member
- Default constructor
- `initializer_list` constructor
- `push_front()`
- `push_back()`
- `print()`

Unlike my `DynamicArray`, every element in the linked list is stored inside an individually allocated node.

To maintain consistency across my library, every node is allocated using my custom allocator instead of using `new`.

---

## Challenges and Problems Faced

### 1. Understanding `std::initializer_list`

While studying STL containers, I wanted my linked list to support syntax such as:

```cpp
LinkedList<int> list = {10, 20, 30};
```

Initially, I assumed that the compiler somehow created a temporary linked list whose head pointer could be accessed.

After studying `std::initializer_list`, I learned that the compiler actually creates a temporary array and passes it to the constructor.

The linked list constructor is responsible for creating every node individually by iterating through the initializer list.

---

### 2. Confusion Between `T&` and `&T`

While implementing constructors and member functions, I explored the difference between:

```cpp
T&
```

and

```cpp
&T
```

I learned that:

- `T&` represents a reference to type `T`.
- `&T` is not valid C++ syntax.

This improved my understanding of reference declarations in templates.

---

### 3. Using the Custom Allocator with Linked List

Initially, I attempted to reuse the same allocator design used in my dynamic array.

My first idea was to declare:

```cpp
MyAllocator<T> allocator;
```

During implementation, I realized this allocator allocates objects of type `T`, whereas a linked list stores **Node** objects.

The correct solution was:

```cpp
MyAllocator<Node> allocator;
```

This allocates complete nodes containing both the stored value and the pointer to the next node.

This helped me understand that a linked list manages nodes rather than raw data values.

---

### 4. Constructing Nodes

Since my allocator only allocates raw memory, I needed to explicitly construct every node using placement new.

The construction process became:

```cpp
Node* newNode = allocator.Allocate();
allocator.Construct(newNode, value);
```

This reinforced the separation between memory allocation and object construction.

---

### 5. Implementing `push_front()`

While implementing `push_front()`, I studied how the `head` pointer changes under different conditions.

For an empty list:

- `head` points to the new node.
- `tail` also points to the new node.

For a non-empty list:

- The new node points to the current head.
- `head` is updated to the new node.

Testing these cases improved my understanding of pointer manipulation.

---

### 6. Implementing `push_back()`

While implementing insertion at the end of the list, I focused on maintaining the `tail` pointer.

If the list is empty:

- Both `head` and `tail` point to the new node.

Otherwise:

- The current tail is linked to the new node.
- `tail` is updated.

Maintaining the tail pointer allows insertion at the end in constant time.

---

### 7. Tracking List Size

I introduced a `length` member to keep track of the number of stored nodes.

While implementing the `initializer_list` constructor, I initially incremented `length` both inside `push_back()` and again inside the constructor.

Testing revealed that this caused the stored size to become larger than the actual number of nodes.

This highlighted the importance of ensuring that only one function is responsible for updating the list size.

---

## Concepts Reinforced

This session strengthened my understanding of:

- Linked list architecture
- Node-based memory allocation
- Pointer manipulation
- Head and tail pointer management
- Custom allocators with node-based data structures
- Placement new
- Object lifetime management
- `std::initializer_list`
- Template programming
- Reference types in C++

---

## Current Status

Successfully implemented:

- Generic `LinkedList<T>`
- Nested `Node` class
- Custom allocator integration
- Default constructor
- Initializer list constructor
- `push_front()`
- `push_back()`
- `print()`

The linked list can now dynamically allocate nodes, maintain correct head and tail pointers, and traverse all stored elements.

---

## Next Steps

The next development session will focus on implementing:

- `insert()`
- `remove()`
- `find()`
- `contains()`
- `get()`
- `clear()`
- Destructor
- Copy constructor
- Copy assignment operator
- Move constructor
- Move assignment operator
- Iterator support

---

## Outcome

This session marked the successful beginning of my custom `LinkedList<T>` implementation. Beyond writing the initial code, I gained a much deeper understanding of node-based data structures, pointer manipulation, allocator-based memory management, and how linked lists fundamentally differ from contiguous-memory containers such as dynamic arrays. The implementation provides a strong foundation for completing the remaining linked list operations in future development sessions.