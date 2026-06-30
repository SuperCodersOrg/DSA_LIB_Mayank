# Why Do We Need Another Data Structure?

Our data collection library currently provides two foundational structures: **Dynamic Arrays** and **Linked Lists**. Both are highly capable of storing linear sequences of data, but they struggle significantly under modern real-world search constraints.

---

## 1. The Key-Value Mapping Requirement

Imagine building a student management system where you must look up information using a distinct identifier:

$$\text{Student ID (Key)} \longrightarrow \text{Student Name (Value)}$$

* `101` $\rightarrow$ Aman
* `102` $\rightarrow$ Jatin
* `103` $\rightarrow$ Amit

### The Retrieval Performance Penalty

If we want to find the student whose ID is `103` using our existing structures, look at the required computational work:

* **Dynamic Array:** Must scan sequentially through `[101, Aman]`, then `[102, Jatin]`, and finally find `[103, Amit]`. Time Complexity: **O(n)**
* **Linked List:** Must traverse node-by-node starting from the head pointer until it hits the matching key node. Time Complexity: **O(n)**

> **The Problem:** The amount of lookup work scales linearly alongside the volume of data. If your system holds **1,000,000 records**, searching for an unindexed or late entry means validating up to 1,000,000 individual elements.

---

## 2. The Birth of the HashMap

What if we stop searching sequentially and start **calculating** directly instead? 

### The Real-World Analogy
Think of a classroom where students are assigned traditional roll numbers. If a teacher asks, *"Who is Roll Number 3?"*, they do not step through the room asking every student their number one by one. They walk directly to location/desk number 3 because the identifier explicitly names the structural location.

### The Core Hash Concept
Instead of storing elements sequentially down a line, we pass our unique **Key** through a special calculation formula known as a **Hash Function**. This function instantly tells us exactly where the record lives in memory.


```

```
   [ Unique Key ] 
         │
         ▼
 ┌───────────────┐
 │ Hash Function │ (Translates Key to Index location)
 └───────────────┘
         │
         ▼

```

[ Direct Bucket Index ] ───> Go straight to data without searching!

```

This brings us to the **HashMap**, a structure exclusively optimized around **Key-Based Lookup** rather than indexing or raw node links. Its structural goal is pure execution efficiency:
* **Insert:** O(1) Average
* **Search:** O(1) Average
* **Delete:** O(1) Average

---

## 3. Core Architecture: Buckets & Entries

To pack both elements safely into memory together, a basic primitive variable cannot cut it. We must encapsulate data into an internal **Entry** object (often called a Key-Value pair) mapped inside an internal storage array called **Buckets**.

```cpp
template<typename K, typename V>
class HashMap {
private:
    class Entry {
    public:
        K key;
        V value;
        Entry(const K& k, const V& v) : key(k), value(v) {}
    };

    LinkedList<Entry>* buckets; // Array of buckets tracking entry chains
    int capacity;               // Number of total buckets available
    int size;                   // Total number of active entries
};

```

### Choosing a Bucket Index

If our internal array capacity is `7`, we apply a fundamental mathematical constraint via the modulus operator to guarantee our hash output fits within the array bounds:

$$\text{Bucket Index} = \text{Key} \pmod{\text{Capacity}}$$

* **Key 101:** $101 \pmod 7 = 3 \longrightarrow$ Store at Bucket 3 (`101 -> Aman`)
* **Key 102:** $102 \pmod 7 = 4 \longrightarrow$ Store at Bucket 4 (`102 -> Jatin`)
* **Key 103:** $103 \pmod 7 = 5 \longrightarrow$ Store at Bucket 5 (`103 -> Amit`)

To find `102`, we simply compute $102 \pmod 7 = 4$ and jump directly to bucket 4. Performance no longer depends on the total count of elements.

---

## 4. Collision Handling via Separate Chaining

Because our bucket array has a limited size, it is mathematically inevitable that two completely unique keys will eventually compute to the exact same bucket index. This phenomenon is a **Collision**.

$$\text{If Key } 102 \pmod 7 = 4 \quad \text{and} \quad \text{Key } 109 \pmod 7 = 4$$

Both keys demand access to Bucket 4. Collisions are not program bugs; they are expected architectural characteristics.

### Separate Chaining Mechanics

To handle collisions cleanly, we combine our structures: instead of storing a raw entry directly inside the bucket box, **every bucket slot acts as the Head pointer to a Linked List of Entries**.

```
Bucket Array
 [ 0 ] ──> NULL
 [ 1 ] ──> NULL
 [ 2 ] ──> NULL
 [ 3 ] ──> [ 101 | Aman ] ──> NULL
 [ 4 ] ──> [ 102 | Jatin ] ──> [ 109 | Kartik ] ──> NULL
 [ 5 ] ──> [ 103 | Amit ] ──> NULL
 [ 6 ] ──> NULL

```

### Searching Inside a Chained Bucket

When searching for key `109`:

1. Calculate bucket location: $109 \pmod 7 = 4$.
2. Jump straight to Bucket 4.
3. Traverse *only* the small isolated linked list attached to that specific bucket (`102` $\rightarrow$ `109` $\rightarrow$ **Found**). The rest of the table remains completely untouched.

---

## 5. Load Factor & The Need for Rehashing

If we insert 1,000 entries into 8 slots, our lists will grow long, causing search performance to degrade from O(1) back toward O(n). To measure how crowded our table is, we calculate the **Load Factor ($\alpha$)**:

$$\text{Load Factor } (\alpha) = \frac{\text{Total Number of Entries (Size)}}{\text{Total Number of Buckets (Capacity)}}$$

### The 0.75 Load Factor Threshold Trade-Off

Most production environments choose **0.75** as their default maximum load factor threshold because it strikes an ideal engineering balance:

* **Low Threshold (e.g., 0.25):** Almost zero collisions, lightning-fast lookups, but massive memory waste as empty buckets prompt premature array expansion.
* **High Threshold (e.g., 1.50):** Highly dense memory efficiency, but leads to long bucket chains, high collision rates, and slower lookup speeds.
* **Balanced Option (0.75):** Keeps lists short and lookups efficient while maintaining strong structural memory optimization.

### The Rehashing Process

When $\alpha > 0.75$, **Rehashing** is triggered. The map creates a brand-new internal array (typically doubling the capacity size) and systematically redistributes every single entry.

> **Important:** You cannot simply copy the memory blocks directly. Because the capacity changes (e.g., from `% 8` to `% 16`), every key's bucket index must be explicitly recalculated.

While rehashing reads all elements—costing $O(n)$ in that single instance—it occurs exponentially less often as capacity grows. Thus, its impact is spread out perfectly, maintaining an **O(1) Amortized** insertion average.

---

## 6. Designing an Efficient Hash Function

A basic summation of text characters (e.g., adding ASCII values for `"abc"` vs `"cab"`) creates predictable collisions because order is ignored ($97+98+99 = 294$). To solve this, we use a **Polynomial Rolling Hash Function** where a character's spatial position acts as an exponential multiplier.

### The Mathematical Formula

$$hash = c_1 \times 31^0 + c_2 \times 31^1 + c_3 \times 31^2 + \dots + c_n \times 31^{n-1}$$

### Why the Prime Number 31?

Multiplying elements by a prime number like `31` breaks up repetitive patterns in text input strings, scattering computed hashes evenly across your map buckets. Additionally, $31$ is highly optimized for performance on modern CPUs because the multiplication can be replaced with a fast bitwise shift and subtraction: $31 \times x \equiv (x \ll 5) - x$.

### Efficient Factorization (Horner's Method)

Computing raw exponential powers repeatedly is slow. We can refactor the rolling formula cleanly so it evaluates sequentially using a single loop containing just one multiplication and one addition per character:

$$\text{New Hash} = (\text{Current Hash} \times 31) + \text{ASCII Value}$$

```cpp
int hash(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash = hash * 31 + ch;
    }
    return hash;
}

```

*Time Complexity to hash a key string:* **O(m)**, where $m$ is the length of the string.

---

## 7. Complete HashMap Class Blueprint

```cpp
template<typename K, typename V>
class HashMap {
private:
    class Entry {
    public:
        K key;
        V value;
        Entry() {}
        Entry(const K& key, const V& value) {
            this->key = key;
            this->value = value;
        }
    };

    LinkedList<Entry>* buckets;
    int currentCapacity;
    int currentSize;
    static constexpr double MAX_LOAD_FACTOR = 0.75;

    // Private Helper Utility Functions
    int bucketIndex(const K& key) const;
    void rehash();
    Entry* findEntry(const K& key);
    const Entry* findEntry(const K& key) const;

public:
    // Lifecycle Management
    HashMap();
    HashMap(int initialCapacity);
    ~HashMap();

    // Core Operational Methods
    void insert(const K& key, const V& value);
    bool remove(const K& key);
    V& get(const K& key);
    const V& get(const K& key) const;
    bool containsKey(const K& key) const;

    // Structural Metrics
    int size() const;
    bool isEmpty() const;
    void clear();
    int capacity() const;
    double loadFactor() const;
};

```

---

## 8. Comprehensive Complexity Metrics

### Public Operations Performance Matrix

| Operation | Average Case | Worst Case | Structural Operational Context |
| --- | --- | --- | --- |
| **`HashMap()`** | $O(1)$ | $O(1)$ | Spawns basic placeholder map with default bounds. |
| **`HashMap(capacity)`** | $O(\text{capacity})$ | $O(\text{capacity})$ | Allocates the array pointer slots across heap parameters. |
| **`~HashMap()`** | $O(n)$ | $O(n)$ | Must traverse all internal chains to free node memory. |
| **`insert()`** | $O(1)$ | $O(n)$ | Average case is direct placement; worst case triggers full $O(n)$ rehash. |
| **`get()`** | $O(1)$ | $O(n)$ | Constant speed access unless all items collapse into one bucket. |
| **`containsKey()`** | $O(1)$ | $O(n)$ | Computes target index and evaluates presence along chain. |
| **`remove()`** | $O(1)$ | $O(n)$ | Drops key matching entry node and splices linked pointers. |
| **`size()` / `isEmpty()**` | $O(1)$ | $O(1)$ | Instantly reads tracked internal primitive counters. |
| **`clear()`** | $O(n)$ | $O(n)$ | Disposes allocations but maintains table structure boundaries. |

### Private Internal Helper Complexities

| Private Helper | Complexity | Operational Focus |
| --- | --- | --- |
| **`bucketIndex(key)`** | $O(1)$ | Converts standard primitives instantly ($O(m)$ for string length). |
| **`findEntry(key)`** | $O(1)$ Avg / $O(n)$ Worst | Isolates matching node records inside a specified bucket chain. |
| **`rehash()`** | $O(n)$ | Allocates an expanded bucket array and maps all elements over. |

```

```