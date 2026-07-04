# Build Log

**Date:** 4 July 2026 | **Time:** 4:00 - 5:30

## Session 3 – HashMap Feature Completion and Comprehensive Testing

During this session, I completed most of the remaining functionality of my generic  `HashMap ` implementation. After finishing the core operations, I focused on validating the implementation by creating a dedicated test suite that exercises every major feature of the container. The goal of this session was not only to implement new methods but also to verify that the hash map behaves correctly under different scenarios such as collisions, rehashing, copying, and memory management.

 ---

## HashMap Features Implemented

### 1. Value Retrieval ( `get `)

Implemented a  `get() ` method that searches the appropriate bucket using the hash function and returns a reference to the stored value. Returning a reference allows the caller to modify the stored value directly without creating a copy.

If the requested key is not found, the method throws a  `std::out _of _range ` exception.

 ---

### 2. Key Lookup ( `containsKey `)

Added a method to determine whether a particular key exists inside the map.

The implementation hashes the key, traverses only the corresponding bucket, and returns a boolean indicating whether the key was found.

 ---

### 3. Empty Check ( `isEmpty `)

Implemented a simple helper function that checks whether the map currently stores any elements.

 ---

### 4. Remove Operation ( `remove `)

Implemented removal of key-value pairs.

The algorithm

 - Computes the bucket index.

 - Traverses the linked list.

 - Finds the matching key.

 - Removes the corresponding node from the bucket.

 - Destroys the dynamically allocated  `Entry `.

 - Releases its memory through the custom allocator.

 - Updates the current size.

 ---

### 5. Clear Operation ( `clear `)

Implemented a method to completely empty the hash map.

Each bucket is processed independently until every stored  `Entry ` has been destroyed and deallocated. After clearing all buckets, the map size is reset to zero.

 ---

### 6. Copy Constructor

Implemented a deep-copy constructor.

Instead of copying pointers, the constructor creates new buckets and reinserts every key-value pair using the existing  `put() ` function. This guarantees that both maps maintain independent memory ownership.

 ---

### 7. Copy Assignment Operator

Implemented deep copy assignment.

The assignment operator:

 - Checks for self-assignment.

 - Clears the current map.

 - Recreates bucket storage.

 - Reinserts every element from the source map.

This prevents memory leaks while preserving correct ownership.

 ---

### 8. Key Extraction ( `getKeys `)

Initially, I experimented with returning a dynamically allocated raw array of keys.

Although this approach worked, it required manual memory cleanup by the caller.

To simplify ownership and reduce the possibility of memory leaks, I redesigned the function to return a  `DynamicArray ` instead.

 ---

### 9. Value Extraction ( `getValues `)

Implemented a function that traverses every bucket and stores all values inside a  `DynamicArray ` before returning it.

This design matches the approach used by  `getKeys() `.

 ---

## Problems Encountered

### Bucket Organization

Earlier, I considered storing buckets differently, but eventually finalized the implementation using:

 ` ` `cpp

DynamicArray >

 ` ` `

This organization simplified bucket indexing and reduced implementation complexity.

 ---

### Returning References

While implementing  `get() `, I evaluated returning values versus references.

Returning a reference proved more efficient because it avoids unnecessary copying and enables direct modification of stored values.

 ---

### Memory Ownership During Removal

Implementing  `remove() ` and  `clear() ` required careful management of dynamically allocated  `Entry ` objects.

Removing a node from the linked list only disconnects the node—it does not destroy the dynamically allocated entry itself.

Therefore every successful removal explicitly performs:

 ` ` `cpp

allocator.Destroy(entry);

allocator.Deallocate(entry);

 ` ` `

to avoid memory leaks.

 ---

### Const Correctness

While implementing the copy constructor and copy assignment operator, compilation errors occurred because the source object is passed as a  `const HashMap& `.

The issue was traced to my custom  `LinkedList `, whose iterators ( `begin() ` and  `end() `) were only implemented for non-const objects.

This session reinforced the importance of designing containers with const-correct interfaces.

 ---

## Comprehensive HashMap Test Suite

After implementing the core functionality, I created a dedicated test file to verify the behavior of the hash map under different scenarios.

The test suite includes:

 - Basic insertion

 - Updating existing keys

 - Collision handling using separate chaining

 - Retrieving values

 - Verifying  `containsKey() `

 - Modifying values through references returned by  `get() `

 - Removing existing keys

 - Attempting to remove missing keys

 - Retrieving all keys using  `getKeys() `

 - Retrieving all values using  `getValues() `

 - Testing the copy constructor

 - Testing the copy assignment operator

 - Self-assignment verification

 - Automatic rehashing when the load factor exceeds the threshold

 - Clearing the map

 - Exception handling for missing keys

Creating this test suite significantly increased my confidence in the correctness of the implementation and helped expose issues that would have been difficult to identify through manual testing alone.

 ---

## Key Learnings

 - Returning references enables efficient in-place modification.

 - Deep copying is essential for containers that own dynamically allocated memory.

 - Returning container objects is safer than returning raw pointers.

 - Memory ownership must remain explicit when working without the STL.

 - Reusing existing insertion logic simplifies copy operations.

 - Const correctness becomes increasingly important as container implementations become more complete.

 - Writing comprehensive test cases is just as important as implementing the data structure itself, since systematic testing reveals edge cases that simple examples often miss.

 ---

## Current Status

The custom  `HashMap ` now supports:

 - Constructor

 - Destructor

 - Insertion ( `put `)

 - Retrieval ( `get `)

 - Updating existing values

 - Collision handling

 - Automatic rehashing

 -  `containsKey() `

 -  `isEmpty() `

 -  `remove() `

 -  `clear() `

 - Copy constructor

 - Copy assignment operator

 -  `getKeys() `

 -  `getValues() `

 - Comprehensive test suite covering all implemented functionality