---
title: Treap
documentation_of: ../../DataStructure/Treap.hpp
---

A highly flexible, randomized balanced binary search tree (Treap). It supports sequences, ordered sets/maps, lazy propagation, range reversals, and persistence.

## Template Parameters

```cpp
template<
    typename Key = void, 
    typename Value = size_v,
    typename Tag = void, 
    bool Rev = false,
    template<typename> class Allocator = DefaultAllocator,
    bool persistent = false
>
class Treap;
```

* `Key`: The type of search keys.
    * Use `void` for sequence-only usage.
* `Value`: The type of elements or range aggregates. Defaults to `size_v`.
    * Must support associative `operator+` for merging (commutative or non-commutative).
    * Must have a default constructor `Value()` acting as the identity element.
    * Requires a member function `size()` for size-based operations.
* `Tag`: The type of lazy tags.
    * Must support `operator+` for tag composition (`Tag + Tag`) and application to a value (`Value + Tag`).
    * Must have a default constructor `Tag()` acting as the identity tag.
* `Rev`: If `true`, supports range reversals (`range_reverse`).
    * If `Value` has a `reverse()` member function, it is called for the node value and composed value during propagation.
* `Allocator`: The allocator used for node management.
* `persistent`: If `true`, operations create new nodes to maintain previous versions. Iterators and parent-pointer-based methods are disabled.

---

## Node Structure

The `node` struct contains the following members. Some members are conditionally present based on the template parameters.

```cpp
struct node {
    node *l, *r;
    node *f;        // Present only if persistent is false
    Key key;        // Present only if Key is not void
    Value org;      // Present only if Value is not void
    Value val;      // Present only if Value is not void
    Tag lazy;       // Present only if Tag is not void
    int rev;        // Present only if Rev is true
    unsigned pri;   // Present only if persistent is false
};
```

* `l`, `r`: Pointers to the left and right children.
* `f`: Pointer to the parent node. Used for iterator movement.
* `key`: The search key of the current node.
* `org`: The value stored in this node.
* `val`: The aggregate value of the entire subtree rooted at this node (includes `l`, `r`, and `org`).
* `lazy`: The pending lazy tag to be propagated to children.
* `rev`: A flag indicating if the subtree needs to be reversed.
* `pri`: A random priority used to maintain the Treap's balanced heap property.
    * To change the seed of the random engine, define the variable `RNGSEED` before including header.

### `operator<<`

```cpp
friend ostream& operator<<(ostream& os, const node &v);
```

* $O(1)$ time (assuming $O(1)$ for `Key` and `Value` output)

Functionalities:
* Outputs the content of the node to the stream.
* If both `Key` and `Value` are present, outputs `{key = ..., org = ...}`. Otherwise, outputs only the present one.

### debuginfo

```cpp
void debuginfo() const;
```

* $O(1)$ time

Functionalities:
* Prints debugging information for the node to `std::cerr`, including its children and parent pointers (if present).

---

## Iterator

The `Iterator` is a bidirectional iterator, available only when `persistent` is `false`.

### `operator*` / `operator->`

```cpp
node& operator*() const;
node* operator->() const;
```

* $O(1)$ time

Returns the reference or pointer to the underlying node.

### begin / end / rbegin

```cpp
Iterator begin() const;
Iterator end() const;
Iterator rbegin() const;
```

* $O(\log N)$ time

Returns the corresponding iterators for traversing the Treap.

### `operator++` / `operator--`

```cpp
Iterator& operator++();
Iterator operator++(int);
Iterator& operator--();
Iterator operator--(int);
```

* $O(\log N)$ time

Moves the iterator to the next or previous element. Disabled when `persistent` is `true`.

### `operator==` / `operator!=`

```cpp
bool operator==(const Iterator& a, const Iterator& b);
bool operator!=(const Iterator& a, const Iterator& b);
```

* $O(1)$ time

Compares two iterators for equality.

### `access_ptr`

```cpp
void access_ptr();
```

* $O(\log N)$ time

Functionalities:
* Ensures all lazy tags and reverse flags on the path from the root to the node pointed by the iterator are propagated.
* Requires `persistent` to be `false`.

---

## Searching (Iterators)

These methods return an `Iterator` to a node satisfying specific conditions.

### lower_bound / upper_bound (Key)

```cpp
template<typename K, typename Comp = std::less<Key>>
Iterator lower_bound(const K &k, const Comp &cmp = Comp());

template<typename K, typename Comp = std::less<Key>>
Iterator upper_bound(const K &k, const Comp &cmp = Comp());
```

* Requires `Key` not to be `void`.
* $O(\log N)$ time

Functionalities:
* `lower_bound` finds the iterator of the node such that:
    * All nodes on its left satisfy `cmp(node->key, k) == true`.
    * All nodes on its right satisfy `cmp(node->key, k) == false`.
    * The node itself satisfies `cmp(node->key, k) == false`.
* `upper_bound` finds the iterator of the node such that:
    * All nodes on its left satisfy `cmp(k, node->key) == false`.
    * All nodes on its right satisfy `cmp(k, node->key) == true`.
    * The node itself satisfies `cmp(k, node->key) == true`.

Assumes the Treap is ordered by `Key`.

### lower_bound_value / upper_bound_value (Value)

```cpp
template<typename V, typename Comp = std::less<Value>>
Iterator lower_bound_value(const V &v, const Comp &cmp = Comp());

template<typename V, typename Comp = std::less<Value>>
Iterator upper_bound_value(const V &v, const Comp &cmp = Comp());
```

* Requires `Value` not to be `void`.
* $O(\log N)$ time

Functionalities:
* `lower_bound_value` finds the iterator of the node such that:
    * The product `res` of all nodes on its left satisfies `cmp(res, v) == true`.
    * The node itself satisfies `cmp(res + node->org, v) == false`.
* `upper_bound_value` finds the iterator of the node such that:
    * The product `res` of all nodes on its left satisfies `cmp(v, res) == false`.
    * The node itself satisfies `cmp(v, res + node->org) == true`.

Assumes monotonicity of prefix products with respect to the comparison.

### bound_condition

```cpp
Iterator bound_condition(const auto &condition);
Iterator bound_condition_value(const auto &condition);
```

* $O(\log N)$ time

Functionalities:
* `bound_condition` finds the iterator of the node such that:
    * All nodes on its left satisfy `condition(node*) == true`.
    * All nodes on its right satisfy `condition(node*) == false`.
    * The node itself satisfies `condition(node*) == false`.
* `bound_condition_value` finds the iterator of the node such that:
    * The product `res` of all nodes on its left satisfies `condition(res) == true`.
    * The node itself satisfies `condition(res + node->org) == false`.

Assumes a `true, ..., true, false, ..., false` distribution.

### kth

```cpp
Iterator kth(int k);
```

* Requires `size()` member function for `Value`.
* $O(\log N)$ time

Functionalities:
* Returns the iterator of the node such that:
    * The number of nodes on its left is exactly `k`.
    * The node is the $k$-th element ($0$-based) in the Treap.

---

## Core Operations

### merge

```cpp
static Treap merge(Treap &&left, Treap &&right);
Treap& left_merge(Treap &&left);
Treap& right_merge(Treap &&right);
```

* $O(\log N)$ time

Functionalities:
* Merges two Treaps into one.
* The relative order of nodes in `left` and `right` is preserved, with all nodes from `left` appearing before nodes from `right`.
* The original Treaps passed by move will have their roots set to `nullptr`.

### split

```cpp
Treap split_key(const auto &condition);
Treap split_key_lt(const K &k, ...);
Treap split_key_leq(const K &k, ...);
Treap split_value(const auto &condition);
Treap split_size(int k);
```

* $O(\log N)$ time

Functionalities:
* Splits the Treap into two parts. Returns a new Treap containing the prefix; the remaining suffix stays in the original Treap.
* `split_key` assumes all nodes satisfying `condition(node*) == true` form a prefix.
* `split_key_lt` assumes all nodes satisfying `cmp(node->key, k) == true` form a prefix.
* `split_key_leq` assumes all nodes satisfying `cmp(k, node->key) == false` form a prefix.
* `split_value` assumes all nodes satisfying `condition(prefix_product) == true` form a prefix.
* `split_size` returns a Treap containing the leftmost `k` nodes.

---

## Modifiers

### push_back / push_front

```cpp
void push_back(const auto &v);
void push_back(const auto &k, const auto &v);
void push_front(const auto &v);
void push_front(const auto &k, const auto &v);
```

* $O(\log N)$ time

Functionalities:
* Inserts a new node at the end (`push_back`) or at the beginning (`push_front`) of the Treap.
* The number of arguments depends on whether `Key` and `Value` are `void`.

### erase

```cpp
template<bool try_access = true>
void erase(Iterator it);
```

* $O(\log N)$ time

Functionalities:
* Removes the node pointed to by the iterator from the Treap.
* Requires `persistent` to be `false`.
* If `try_access` is `true`, it ensures the path to the node is updated (useful with lazy propagation).

### swap

```cpp
void swap(Treap &rhs);
```

* $O(1)$ time

Functionalities:
* Swaps the entire content (root pointer and metadata) with another Treap.

### transform

```cpp
void transform(const Tag &tag);
```

* $O(1)$ time

Functionalities:
* Applies the lazy tag `tag` to the entire Treap by updating the root's lazy field.

### reverse

```cpp
void reverse();
```

* $O(1)$ time

Functionalities:
* Reverses the entire Treap by toggling the root's reverse flag. Requires `Rev` to be `true`.

### destruct

```cpp
void destruct();
```

* $O(N)$ time

Functionalities:
* Recursively deallocates all nodes in the Treap. Essential for manual memory management when not using a pool allocator.

---

## Range Operations

Requires `size()` member function for `Value`.

### split_range

```cpp
std::array<Treap, 2> split_range(int l, int r);
```

* $O(\log N)$ time

Functionalities:
* Splits the Treap into three parts: `[0, l)`, `[l, r)`, and `[r, N)`.
* The middle range `[l, r)` stays in the original Treap object.
* The returned array contains the prefix `[0, l)` and suffix `[r, N)`.

### range_prod

```cpp
Value range_prod(int l, int r);
```

* $O(\log N)$ time

Functionalities:
* Returns the aggregate value (product) of all nodes in the range `[l, r)`.

### range_transform

```cpp
void range_transform(int l, int r, const Tag &tag);
```

* $O(\log N)$ time

Functionalities:
* Applies the lazy tag `tag` to all nodes in the range `[l, r)`.

### range_reverse

```cpp
void range_reverse(int l, int r);
```

* $O(\log N)$ time

Functionalities:
* Reverses the order of elements in the range `[l, r)`. Requires `Rev` to be `true`.

---

## Queries

### empty

```cpp
bool empty();
```

* $O(1)$ time

Functionalities:
* Returns `true` if the Treap contains no nodes (root is `nullptr`).

### size

```cpp
int size();
```

* $O(1)$ time

Functionalities:
* Returns the total number of elements in the Treap. Requires `size()` in `Value`.

### get_key

```cpp
Key get_key();
```

* $O(1)$ time

Functionalities:
* Returns the key stored at the root node. Requires `Key` not to be `void`.

### product

```cpp
Value product();
```

* $O(1)$ time

Functionalities:
* Returns the pre-calculated aggregate value (`val`) of the entire Treap.

### prefix_product

```cpp
Value prefix_product_key_lt(const K &k, ...);
Value prefix_product_key_leq(const K &k, ...);
Value prefix_product_cond(const auto &condition);
```

* $O(\log N)$ time

Functionalities:
* `prefix_product_key_lt` returns the product of all nodes with `key < k`.
* `prefix_product_key_leq` returns the product of all nodes with `key <= k`.
* `prefix_product_cond` returns the product of the longest prefix satisfying `condition(prefix_product)`.
* Assumes monotonicity where applicable.
