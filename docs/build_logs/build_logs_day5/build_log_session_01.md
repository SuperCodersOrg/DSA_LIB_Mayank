**Date:** 7 July 2026 | **Time:** 9:00 - 11:00

Session: Custom Hash Function Integration for HashMap
-----------------------------------------------------

### Objective

Improve the HashMap implementation by introducing a flexible hashing mechanism that supports multiple key types and allows users to provide custom hash functions for their own classes.

Work Completed
--------------

### 1\. Refactored Hashing Design

Redesigned the hashing mechanism from a static utility class to a template-based hash functor.

Previous approach:

*   MyHash contained only static hash() functions.
    
*   The design could not be used naturally with a generic HashMap.
    
*   It did not support user-defined hashers.
    

New approach:

*   Converted MyHash into a template.
    
*   Added template specializations for supported types.
    
*   Implemented operator() so hash objects behave like callable functions.
    

This allows the HashMap to use:

Hash hasher;  return hasher(key);

instead of manually calling static functions.

### 2\. Added Default Hash Specializations

Implemented default hash functors for:

*   int
    
*   long
    
*   char
    
*   float
    
*   double
    
*   std::string
    

This enables users to create hash maps without explicitly providing a hash function for common built-in types.

### 3\. Improved Floating-Point Hashing

The initial implementation simply multiplied floating-point values by a constant before converting them to integers.

Example:

static_cast(key * 1000);

Limitations:

*   Poor distribution.
    
*   Higher chance of collisions.
    
*   Loss of precision.
    
*   Not suitable for a production-quality hash function.
    

The implementation was replaced with a stronger approach:

*   Copy the raw IEEE-754 bit representation using std::memcpy.
    
*   Apply multiple XOR and multiplication steps to mix the bits.
    
*   Produce a well-distributed hash value.
    

This significantly improves hash quality for both float and double.

### 4\. Studied Hash Mixing

Spent time understanding why modern hash functions perform multiple mixing operations.

Topics explored:

*   Raw bit representation of floating-point numbers.
    
*   Why std::memcpy is preferred over pointer casting.
    
*   XOR-based bit mixing.
    
*   Right-shift operations.
    
*   Multiplication using carefully selected constants.
    
*   Avalanche effect.
    
*   Inspiration from MurmurHash-style finalization.
    

### 5\. HashMap Integration

Updated HashMap to work with the new hash functor design.

The class now stores:

Hash hasher; 

and computes bucket indices using:

hasher(key) % capacity;

This makes the implementation extensible while keeping the hashing logic independent of the hash table itself.

Problems Encountered
--------------------

### Compilation Errors

Initially encountered errors such as:

*   'MyHash' is not a template
    
*   no match for call to '(const MyHash)(const int&)'
    

Reason:

The original MyHash contained only static member functions, while HashMap expected a callable object using operator().

Resolution:

*   Redesigned MyHash as a template.
    
*   Added specializations for supported types.
    
*   Implemented operator() in each specialization.
    

Key Learning
------------

This session provided a deeper understanding of how generic hashing is implemented in modern C++ libraries.

Major takeaways include:

*   Template specialization for type-specific behavior.
    
*   Function objects (operator()) and their advantages.
    
*   Compile-time selection of hash implementations.
    
*   Strong hashing techniques for floating-point values.
    
*   Separation of hashing logic from container implementation.
    

Current Status
--------------

*   ✅ Template-based hash functor implemented.
    
*   ✅ Built-in hash support for common primitive types.
    
*   ✅ Strong hashing implemented for float and double.
    
*   ✅ HashMap now supports custom hash functors for user-defined key types.
    
*   ✅ Design is now much closer to the architecture used by std::unordered\_map.
    

Next Steps
----------

*   Improve hashing for integer types using bit mixing.
    
*   Add support for additional key types such as long long.
    
*   Implement iterator support for HashMap.
    
*   Add unit tests for different key types and collision scenarios.
    
*   Benchmark hash distribution and performance under varying loads.