# Daily Journal

 **Date: ** 4 July 2026

## Objective

Continue the implementation of the custom generic  `HashMap ` and complete most of the fundamental operations while ensuring proper memory management using the custom allocator. The goal was also to strengthen my understanding of const-correctness, deep copying, and ownership in container implementations.

 ---

# Work Completed

## 1. Implemented Core HashMap Operations

Successfully implemented the following member functions:

 -  `put() `

 -  `get() `

 -  `containsKey() `

 -  `remove() `

 -  `clear() `

 -  `isEmpty() `

 -  `getKeys() `

 -  `getValues() `

During implementation I made sure every inserted  `Entry ` object is allocated using my custom allocator and destroyed correctly when removed.

 ---

## 2. Learned Pointer Ownership

While implementing  `remove() ` and  `clear() ` I understood the ownership model of the HashMap.

The linked list only stores pointers ( `Entry * `).

Removing a node from the linked list does  * *not * * destroy the actual  `Entry ` object.

Therefore every removal requires:

 ` ` `cpp

allocator.Destroy(entry);

allocator.Deallocate(entry);

 ` ` `

Otherwise memory would leak.

 ---

## 3. Implemented Deep Copy

Implemented

 - Copy Constructor

 - Copy Assignment Operator

Instead of copying pointer addresses, I recreated every entry using  `put() `.

This gave the HashMap proper deep copy semantics.

 ---

## 4. Understood Self Assignment

Learned why assignment operator starts with

 ` ` `cpp

if(this == &other)

return  *this;

 ` ` `

Without this check,

 ` ` `cpp

map = map;

 ` ` `

would first erase the current object before copying from itself.

 ---

## 5. Implemented getKeys() and getValues()

Initially I attempted to manually allocate an array using my allocator.

Example:

 ` ` `cpp

K * keys = allocator.Allocate(size);

 ` ` `

This required the caller to manually destroy and deallocate the returned memory.

I realized this design is error-prone because ownership becomes the user's responsibility.

I replaced it with

 ` ` `cpp

DynamicArray getKeys();

DynamicArray getValues();

 ` ` `

This follows RAII and automatically manages memory.

 ---

## 6. Created Comprehensive Test Cases

Created a dedicated testing file covering nearly every implemented feature.

Tests include:

 - Basic insertion

 - Updating existing keys

 - Collision handling

 - Searching

 - Reference return from  `get() `

 - Removing keys

 - Removing missing keys

 -  `containsKey() `

 -  `getKeys() `

 -  `getValues() `

 - Copy constructor

 - Copy assignment

 - Self assignment

 - Automatic rehashing

 -  `clear() `

 - Exception handling

This helped verify correctness after every implementation step.

 ---

# Problems Faced

## 1. Const Correctness Errors

While experimenting with const objects, compilation failed because const member functions were calling non-const functions.

Example issues:

 -  `hash() ` was not const.

 -  `LinkedList::begin() ` and  `end() ` lacked const overloads.

This helped me understand why containers usually provide both

 ` ` `cpp

Iterator begin();

ConstIterator begin() const;

 ` ` `

 ---

## 2. Returning Dynamically Allocated Arrays

Initially I wanted

 ` ` `cpp

K * getKeys();

 ` ` `

but realized the caller would need to manually free the memory.

I learned that returning a container object ( `DynamicArray `) is much safer and avoids ownership confusion.

 ---

## 3. Understanding Deep Copy

At first I considered copying bucket pointers directly.

After studying the design, I realized that would result in multiple HashMaps owning the same  `Entry ` objects, causing double deletion and undefined behavior.

Using  `put() ` inside the copy constructor creates entirely new entries and avoids this issue.

 ---

## 4. Manual Memory Management

I spent time understanding exactly when

 ` ` `cpp

Allocate()

Construct()

Destroy()

Deallocate()

 ` ` `

should be called.

I now have a much clearer understanding of object lifetime management.

 ---

# Concepts Learned Today

 - Deep copy vs shallow copy

 - Copy constructor implementation

 - Copy assignment implementation

 - Self assignment protection

 - Ownership of dynamically allocated objects

 - Manual object lifetime management

 - Why RAII containers are preferable to raw pointers

 - Returning references from member functions

 - Collision handling using separate chaining

 - Rehashing workflow

 - Const correctness in container classes

 - Importance of comprehensive unit testing

 ---

# Outcome

Today's session significantly improved my understanding of implementing STL-like containers from scratch.

The HashMap now supports:

 - insertion

 - searching

 - updating

 - deletion

 - clearing

 - copying

 - key/value extraction

 - automatic rehashing

 - exception handling

I also created a comprehensive test suite that validates nearly all implemented functionality, making future development and debugging much easier.