---
title: Dynamic Bitset
documentation_of: ../../DataStructure/DynamicBitset.hpp
---

A dynamically sized bitset that supports bitwise operations, arithmetic operations (addition, subtraction, negation), shifting, and bit searching. It is optimized to perform operations 64 bits at a time using `uint64_t` blocks, and leverages x86 intrinsics for fast addition/subtraction carry propagation.

---

## Constructor (Size)

```cpp
DynamicBitset(int n = 0);
```

* $O(N / 64)$ time

Constructs an empty `DynamicBitset` of size `n` with all bits initialized to `0`.

---

## Constructor (String)

```cpp
DynamicBitset(std::string_view s);
```

* $O(\lvert s\rvert)$ time

Constructs a `DynamicBitset` from a binary string `s` (consisting of `'0'` and `'1'`). The least significant bit (index `0`) corresponds to the last character of the string `s` (i.e. `s.back()`).

---

## clean

```cpp
void clean();
```

* $O(1)$ time

Clears/zeros out the unused/trailing bits in the last `uint64_t` block that lie beyond the bounds of the bitset size `n`. Usually called internally after shift or arithmetic operations.

---

## size

```cpp
int size() const;
```

* $O(1)$ time

Returns the number of bits in the bitset.

---

## count

```cpp
int count() const;
```

* $O(N / 64)$ time

Returns the number of bits that are set to `1`.

---

## test

```cpp
bool test(int i) const;
```

* $O(1)$ time

Returns the value of the bit at index `i`.

---

## set

```cpp
void set(int i);
```

* $O(1)$ time

Sets the bit at index `i` to `1`.

---

## reset

```cpp
void reset(int i);
```

* $O(1)$ time

Sets the bit at index `i` to `0`.

---

## flip

```cpp
void flip(int i);
```

* $O(1)$ time

Flips the value of the bit at index `i`.

---

## operator[]

```cpp
reference operator[](int i);
bool operator[](int i) const;
```

* $O(1)$ time

Accesses the bit at index `i`. The non-const version returns a proxy helper class `reference` which allows modification (e.g. `b[i] = 1`).

---

## _Find_first

```cpp
int _Find_first() const;
```

* $O(N / 64)$ time

Returns the index of the first (lowest) bit set to `1`. If no such bit exists, returns the size of the bitset.

---

## _Find_last

```cpp
int _Find_last() const;
```

* $O(N / 64)$ time

Returns the index of the last (highest) bit set to `1`. If no such bit exists, returns `-1`.

---

## _Find_next

```cpp
int _Find_next(int i) const;
```

* $O(N / 64)$ time

Returns the index of the first set bit after index `i` (greater than `i`). If no such bit exists, returns the size of the bitset.

---

## _Find_prev

```cpp
int _Find_prev(int i) const;
```

* $O(N / 64)$ time

Returns the index of the first set bit before index `i` (less than `i`). If no such bit exists, returns `-1`.

---

## swap

```cpp
void swap(DynamicBitset &o);
```

* $O(1)$ time

Swaps the contents of this bitset with another bitset `o`.

---

## to_string

```cpp
std::string to_string() const;
```

* $O(N)$ time

Returns the binary string representation of the bitset.

---

## Bitwise Operators

```cpp
DynamicBitset operator~() const;
DynamicBitset& flip();

DynamicBitset& operator&=(const DynamicBitset& o);
DynamicBitset& operator|=(const DynamicBitset& o);
DynamicBitset& operator^=(const DynamicBitset& o);

DynamicBitset operator&(const DynamicBitset& o) const;
DynamicBitset operator|(const DynamicBitset& o) const;
DynamicBitset operator^(const DynamicBitset& o) const;
```

* $O(N / 64)$ time

Performs standard bitwise operations (NOT, AND, OR, XOR).
* `flip()` is equivalent to `operator~` but modifies the bitset in-place and returns `*this`.

---

## Shift Operators

```cpp
DynamicBitset& operator<<=(int k);
DynamicBitset& operator>>=(int k);

DynamicBitset operator<<(int k) const;
DynamicBitset operator>>(int k) const;
```

* $O(N / 64)$ time

Performs left and right bit-shifts by `k` positions.

---

## Arithmetic Operators

```cpp
DynamicBitset& operator+=(const DynamicBitset& o);
DynamicBitset& operator-=(const DynamicBitset& o);

DynamicBitset operator+(const DynamicBitset& o) const;
DynamicBitset operator-(const DynamicBitset& o) const;
DynamicBitset operator-() const;
```

* $O(N / 64)$ time

Performs arithmetic addition, subtraction, or negation (two's complement) treating the bitset as a large binary integer.
* Utilizes x86 hardware carry/borrow instructions (`_addcarry_u64` / `_subborrow_u64`) when compiled on `__x86_64__` architecture.

---

## Comparison Operators

```cpp
bool operator==(const DynamicBitset&) const = default;
```

* $O(N / 64)$ time

Checks if two bitsets are equal.

---

## Stream I/O

```cpp
friend std::ostream& operator<<(std::ostream& os, const DynamicBitset& b);
friend std::istream& operator>>(std::istream& is, DynamicBitset& b);
```

Allows direct input/output of the bitset from/to streams using binary strings.
