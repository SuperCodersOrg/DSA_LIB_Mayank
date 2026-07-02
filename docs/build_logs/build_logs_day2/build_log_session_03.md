# Build Log – Session 3 (LinkedList Implementation)

**Date:** 2 July 2026 | **Time:** 3:00 - 5:00

## Objective

The objective of this session was to continue expanding my custom generic `LinkedList<T>` implementation using my custom allocator. During this session, I focused on implementing the core modification operations of the linked list along with proper memory management. I also worked on ensuring that dynamically allocated nodes were correctly destroyed and deallocated.

---

## Progress Made

During this session, I implemented the following member functions:

- `pop_front()`
- `pop_back()`
- `find()`
- `insert()`
- `remove()`
- `clear()`
- Destructor
- Copy Constructor

The linked list now supports insertion, deletion, searching, clearing the entire container, deep copying through the copy constructor, and automatic cleanup when the object goes out of scope.

---

## Challenges and Problems Faced

### 1. Implementing `pop_front()`

While implementing `pop_front()`, I initially focused only on updating the `head` pointer and returning the removed value.

During testing, I realized that removing a node also requires:

- Calling the node destructor
- Deallocating the memory through the custom allocator
- Updating both `head` and `tail` when removing the last remaining node
- Decreasing the list size

This reinforced that removing a node involves both pointer manipulation and proper memory management.

---

### 2. Implementing `pop_back()`

Implementing `pop_back()` was more challenging than `pop_front()` because a singly linked list cannot directly access the previous node.

To remove the last node, I had to:

- Traverse the list until reaching the second last node.
- Update its `next` pointer to `nullptr`.
- Update the `tail` pointer.
- Destroy and deallocate the removed node.

Special handling was also required when the list contained only one node.

This highlighted one of the limitations of singly linked lists.

---

### 3. Returning Removed Elements

While implementing both `pop_front()` and `pop_back()`, I initially made mistakes in the return types.

At one point:

- A function returning `void` attempted to return a value.
- I also experimented with returning references to temporary local variables.

Both issues resulted in compiler errors or warnings.

After reviewing the implementation, I learned that removed elements should be returned **by value**, since the local variable storing the removed data is destroyed when the function exits.

---

### 4. Implementing `remove()`

The `remove()` function required handling multiple cases.

Depending on the requested index, removal may involve:

- Removing the first node.
- Removing the last node.
- Removing a node from the middle.

To avoid duplicating logic, I reused the existing `pop_front()` and `pop_back()` functions whenever possible.

For middle nodes, I traversed the list, adjusted the links, destroyed the removed node, deallocated its memory, and updated the list size.

This demonstrated the importance of reusing existing functions instead of rewriting similar logic.

---

### 5. Implementing `find()`

I added a linear search function that traverses the linked list until the requested value is found.

The function returns:

- The index if the value exists.
- `-1` otherwise.

This reinforced traversal techniques used throughout linked list operations.

---

### 6. Implementing `insert()`

Insertion required handling three scenarios:

- Beginning of the list
- End of the list
- Middle of the list

The middle insertion required locating the node before the insertion position and correctly updating the `next` pointers without losing the remaining portion of the list.

This strengthened my understanding of pointer manipulation.

---

### 7. Implementing `clear()`

Initially, I considered repeatedly calling `pop_front()` to remove every node.

Later, I implemented a dedicated traversal that:

- Stores the next pointer.
- Destroys the current node.
- Deallocates its memory.
- Continues until the list becomes empty.

Finally, the function resets:

- `head`
- `tail`
- `length`

This implementation is simple and efficiently releases every allocated node.

---

### 8. Implementing the Destructor

After creating `clear()`, implementing the destructor became straightforward.

Instead of duplicating cleanup logic, the destructor simply calls:

```cpp
clear();
```

This ensures every dynamically allocated node is destroyed and deallocated automatically when the linked list object goes out of scope.

---

### 9. Implementing the Copy Constructor

I implemented a deep copy constructor.

Instead of copying internal pointers, the constructor:

- Initializes an empty linked list.
- Traverses the source list.
- Inserts each value using `push_back()`.

This guarantees that the copied list owns its own nodes and both objects manage independent memory.

While testing, I also observed the difference between the copy constructor and copy assignment operator. I found that writing:

```cpp
LinkedList<int> list2 = list1;
```

uses the copy constructor, whereas:

```cpp
list2 = list1;
```

uses the copy assignment operator, which I have not implemented yet. This helped clarify the distinction between object initialization and assignment.

---

## Concepts Reinforced

This session strengthened my understanding of:

- Dynamic memory management
- Node destruction and deallocation
- Deep copying
- Copy constructors
- Difference between copy construction and copy assignment
- Pointer manipulation
- Linked list traversal
- Reusing existing functions
- Edge case handling
- Resource cleanup

---

## Current Status

Successfully implemented:

- Nested `Node` class
- Custom allocator integration
- Default constructor
- Initializer list constructor
- Copy constructor
- `push_front()`
- `push_back()`
- `pop_front()`
- `pop_back()`
- `insert()`
- `remove()`
- `find()`
- `size()`
- `isEmpty()`
- `front()`
- `back()`
- `operator[]`
- `clear()`
- Destructor
- `print()`

The linked list now supports insertion, deletion, searching, traversal, deep copying through the copy constructor, automatic memory cleanup, and complete lifecycle management using the custom allocator.

---
## Outcome

This session significantly improved the functionality and robustness of my custom `LinkedList<T>`. Beyond implementing several core operations, I gained practical experience with dynamic memory management, deep copying, resource cleanup, and handling various edge cases. The linked list is now capable of managing its own memory safely using my custom allocator and provides a much more complete container implementation.