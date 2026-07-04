Build Log
==============

**Date:** 4 July 2026 || **Time:** 3:00 - 5:00

Session 3 – HashMap Core Functionality
--------------------------------------

During this session, I significantly expanded my HashMap implementation using separate chaining. The primary objective was to move beyond insertion and build a complete, reusable hash map while continuing to use my custom DynamicArray, LinkedList, and MyAllocator implementations.

### Major Design Change

One of the first changes I made was revisiting the bucket storage strategy. Initially, I considered using a linked list as the primary bucket container, but I realized that direct indexing into buckets would become inefficient. I changed the design to use a DynamicArray\>, where:

*   DynamicArray provides constant-time bucket access.
    
*   Each bucket is a LinkedList used for collision handling.
    
*   Each linked list stores pointers to dynamically allocated Entry objects.
    

This simplified bucket access while still supporting separate chaining.

### HashMap Construction

I implemented the constructor to:

*   Initialize the bucket array with an initial capacity of 8.
    
*   Create an empty linked list for every bucket.
    
*   Initialize the current size and capacity.
    

I also implemented a destructor that traverses every bucket, destroys every dynamically allocated Entry, and releases the allocated memory through my custom allocator.

### Insertion (put)

I implemented the insertion algorithm with the following behavior:

*   Compute the bucket index using the hash function.
    
*   Search the bucket for an existing key.
    
*   Update the value if the key already exists.
    
*   Otherwise allocate a new Entry, construct it using placement new, and insert it into the bucket.
    
*   Increase the element count.
    
*   Trigger rehashing whenever the load factor exceeds the maximum threshold.
    

### Rehashing

I implemented automatic resizing of the hash table.

The rehash process:

1.  Doubles the bucket capacity.
    
2.  Creates a new bucket array.
    
3.  Recomputes the hash index of every existing entry.
    
4.  Moves the existing Entry\* pointers into the appropriate new buckets.
    
5.  Replaces the old bucket array with the new one.
    

Instead of allocating new Entry objects, I reused the existing pointers, making the rehash operation more efficient.

### Lookup Operations

I implemented:

*   get()
    
*   containsKey()
    

The lookup operation traverses only the bucket corresponding to the hashed key instead of searching the entire table.

### Removal

I implemented remove() by:

*   Locating the correct bucket.
    
*   Finding the matching key.
    
*   Removing the node from the linked list.
    
*   Destroying the associated Entry.
    
*   Deallocating its memory.
    
*   Updating the element count.
    

### Utility Functions

I added several helper methods:

*   get\_size()
    
*   get\_capacity()
    
*   isEmpty()
    
*   clear()
    
*   print()
    

The clear() function removes every entry from every bucket while correctly destroying and deallocating all allocated objects.

### Copy Semantics

To ensure proper ownership of dynamically allocated entries, I implemented:

*   Copy constructor
    
*   Copy assignment operator
    

Instead of copying raw pointers, both implementations rebuild the new hash map using put(), resulting in a deep copy where every Entry is independently allocated.

### Retrieving Keys and Values

I implemented:

*   getKeys()
    
*   getValues()
    

Initially, I attempted to return a raw dynamically allocated array using my custom allocator. While this worked conceptually, I realized it introduced manual ownership problems because the caller would become responsible for destroying every constructed object and deallocating the array.

To avoid memory management issues and keep ownership automatic, I changed the implementation to return DynamicArray and DynamicArray. This follows RAII principles and integrates naturally with the rest of my custom container library.

Problems Faced
--------------

### 1\. Choosing the Bucket Representation

Initially I experimented with different bucket layouts before deciding on:

*   DynamicArray for bucket storage.
    
*   LinkedList for collision handling.
    

This provided efficient indexing while preserving separate chaining.

### 2\. Copying vs Referencing Buckets

While implementing put(), I accidentally wrote:

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   auto bucket = buckets[bucket_index];   `

This created a copy of the linked list, so insertions modified only the copy.

I corrected it by using:

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   auto& bucket = buckets[bucket_index];   `

which accesses the actual bucket inside the hash map.

### 3\. Rehash Logic

During rehash implementation, I initially iterated using the updated capacity instead of the old capacity, causing invalid bucket access.

I corrected this by storing:

*   oldCapacity
    
*   newCapacity
    

and iterating only through the old buckets while redistributing entries.

### 4\. Memory Management

Since every Entry is allocated manually, I needed to carefully distinguish between:

*   Removing a linked-list node.
    
*   Destroying an Entry.
    
*   Deallocating memory.
    

This helped me understand that deleting the linked-list node alone is insufficient because the Entry object itself must also be destroyed and deallocated.

### 5\. Returning Keys

My first implementation of getKeys() attempted to return a raw pointer allocated with my custom allocator.

Although it was technically possible, it shifted ownership to the caller and required manual destruction and deallocation of every key object.

After evaluating the design, I switched to returning a DynamicArray, which automatically manages memory and produces a much safer interface.

### 6\. Deep Copy

While implementing copy construction and copy assignment, I realized that copying bucket pointers directly would result in multiple hash maps sharing the same Entry objects, eventually causing double deletion.

I solved this by rebuilding the destination hash map using put(), ensuring that every copied entry is newly allocated.

Learning Outcome
----------------

This session gave me a much deeper understanding of implementing a hash table from scratch without relying on the C++ Standard Library. More importantly, it reinforced concepts such as ownership, deep copying, placement new, manual memory management, load-factor based resizing, collision handling, and the relationship between data structures and object lifetime. By the end of the session, my HashMap supports insertion, lookup, deletion, clearing, automatic rehashing, copying, and retrieval of all keys and values while integrating cleanly with my custom container library.