---
title: Splay
documentation_of: ../../DataStructure/Splay.hpp
---

A highly flexible self-adjusting binary search tree (Splay Tree). It supports sequences, ordered sets/maps, lazy propagation, and range reversals. Accessed nodes are splayed to the root using tree rotations, achieving amortized $O(\log N)$ time per operation without requiring random priorities or tree height balancing.

## Template Parameters

```cpp
template<
    typename Key = void, 
    typename Value = size_v,
    typename Tag = void, 
    bool Rev = false,
    template<typename> class Allocator = DefaultAllocator
>
class Splay;
```

* `Key`: The type of search keys.
    * Use `void` for sequence-only usage.
* `Value`: The type of elements or range aggregates. Defaults to `size_v`.
    * Must support associative `operator+` for merging (commutative or non-commutative).
    * Must have a default constructor `Value()` acting as the identity element.
    * Requires a member function `size()` for size-based operations.
* `Tag`: The type of lazy tags.
    * Must support `operator+` for tag composition (`Tag + Tag`).
    * Must have a default constructor `Tag()` acting as the identity tag.
    * If `operator+` between `Value` and `Tag` is supported, the lazy tag will be applied to `Value`.
    * If `operator+` between `Key` and `Tag` is supported, the lazy tag will be applied to `Key`.
    * **WARNING**: It is recommended to use a custom struct to implement the `Tag` to prevent unexpected application. 
* `Rev`: If `true`, supports range reversals (`range_reverse`).
    * If `Value` has a `reverse()` member function, it is called for the node value and composed value during propagation.
* `Allocator`: The allocator used for node management. Defaults to `DefaultAllocator`.

---

## Node Structure

The `node` struct contains the following members. Some members are conditionally present based on the template parameters.

```cpp
struct node {
    node *l, *r;
    node *f;
    Key key;        // Present only if Key is not void
    Value org;      // Present only if Value is not void
    Value val;      // Present only if Value is not void
    Tag lazy;       // Present only if Tag is not void
    int rev;        // Present only if Rev is true
};
```

* `l`, `r`: Pointers to the left and right children.
* `f`: Pointer to the parent node. Used for tree rotations and iterator movement.
* `key`: The search key of the current node.
* `org`: The value stored in this node.
* `val`: The aggregate value of the entire subtree rooted at this node (includes `l`, `r`, and `org`).
* `lazy`: The pending lazy tag to be propagated to children.
* `rev`: A flag indicating if the subtree needs to be reversed.

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
* Prints debugging information for the node to `std::cerr`, including its children and parent pointers.

---

## Iterator

The `Iterator` is a bidirectional iterator.

### `operator*` / `operator->`

```cpp
node& operator*() const;
node* operator->() const;
```

* $O(1)$ time

Returns the reference or pointer to the underlying node.

### begin / end / rbegin

```cpp
Iterator begin();
Iterator end();
Iterator rbegin();
```

* Amortized $O(\log N)$ time for `begin` and `rbegin`; $O(1)$ time for `end`

Returns the corresponding iterators for traversing the Splay tree.

### `operator++` / `operator--`

```cpp
Iterator& operator++();
Iterator operator++(int);
Iterator& operator--();
Iterator operator--(int);
```

* Amortized $O(\log N)$ time

Moves the iterator to the next or previous element in in-order traversal. Automatically pushes down pending lazy tags and reverse flags on the path.

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
* Amortized $O(\log N)$ time

Functionalities:
* `lower_bound` finds the iterator of the node such that:
    * All nodes on its left satisfy `cmp(node->key, k) == true`.
    * All nodes on its right satisfy `cmp(node->key, k) == false`.
    * The node itself satisfies `cmp(node->key, k) == false`.
* `upper_bound` finds the iterator of the node such that:
    * All nodes on its left satisfy `cmp(k, node->key) == false`.
    * All nodes on its right satisfy `cmp(k, node->key) == true`.
    * The node itself satisfies `cmp(k, node->key) == true`.
* Splays the found node (or the last visited node) to the root.

Assumes the Splay tree is ordered by `Key`.

### lower_bound_value / upper_bound_value (Value)

```cpp
template<typename V, typename Comp = std::less<Value>>
Iterator lower_bound_value(const V &v, const Comp &cmp = Comp());

template<typename V, typename Comp = std::less<Value>>
Iterator upper_bound_value(const V &v, const Comp &cmp = Comp());
```

* Requires `Value` not to be `void`.
* Amortized $O(\log N)$ time

Functionalities:
* `lower_bound_value` finds the iterator of the node such that:
    * The product `res` of all nodes on its left satisfies `cmp(res, v) == true`.
    * The node itself satisfies `cmp(res + node->org, v) == false`.
* `upper_bound_value` finds the iterator of the node such that:
    * The product `res` of all nodes on its left satisfies `cmp(v, res) == false`.
    * The node itself satisfies `cmp(v, res + node->org) == true`.
* Splays the found node (or the last visited node) to the root.

Assumes monotonicity of prefix products with respect to the comparison.

### bound_condition

```cpp
Iterator bound_condition(const auto &condition);
Iterator bound_condition_value(const auto &condition);
```

* `bound_condition_value` requires `Value` not to be `void`.
* Amortized $O(\log N)$ time

Functionalities:
* `bound_condition` finds the iterator of the node such that:
    * All nodes on its left satisfy `condition(node*) == true`.
    * All nodes on its right satisfy `condition(node*) == false`.
    * The node itself satisfies `condition(node*) == false`.
* `bound_condition_value` finds the iterator of the node such that:
    * The product `res` of all nodes on its left satisfies `condition(res) == true`.
    * The node itself satisfies `condition(res + node->org) == false`.
* Splays the found node (or the last visited node) to the root.

Assumes a `true, ..., true, false, ..., false` distribution.

### kth

```cpp
Iterator kth(int k);
```

* Requires `size()` member function for `Value`.
* Amortized $O(\log N)$ time

Functionalities:
* Returns the iterator of the node such that:
    * The number of nodes on its left is exactly `k`.
    * The node is the $k$-th element ($0$-based) in the Splay tree.
* Splays the $k$-th node to the root.

---

## Core Operations

### splay

```cpp
void splay(Iterator it);
```

* Amortized $O(\log N)$ time

Functionalities:
* Splays the node pointed to by `it` to the root of the tree using tree rotations.
* Ensures all lazy tags and reverse flags on the path from the root to the node are propagated before rotating.
* If `it == end()`, does nothing.

### merge

```cpp
static Splay merge(auto&& left, auto&& right);
Splay& left_merge(auto&& left);
Splay& right_merge(auto&& right);
```

* Amortized $O(\log N)$ time

Functionalities:
* Merges two Splay trees into one.
* The relative order of nodes in `left` and `right` is preserved, with all nodes from `left` appearing before nodes from `right`.
* Splays the maximum element of `left` to its root, making its right child `nullptr`, then attaches `right` as its right child.
* The original Splay trees passed by move will have their roots set to `nullptr`.

### split

```cpp
Splay split_key(const auto &condition);
template<typename K, typename Comp = std::less<Key>>
Splay split_key_lt(const K &k, const Comp &cmp = Comp());
template<typename K, typename Comp = std::less<Key>>
Splay split_key_leq(const K &k, const Comp &cmp = Comp());
Splay split_value(const auto &condition);
Splay split_size(const int &k);
```

* Amortized $O(\log N)$ time

Functionalities:
* Splits the Splay tree into two parts. Returns a new Splay tree containing the prefix; the remaining suffix stays in the original Splay tree (`*this`).
* `split_key` assumes all nodes satisfying `condition(node*) == true` form a prefix.
* `split_key_lt` assumes all nodes satisfying `cmp(node->key, k) == true` form a prefix. Requires `Key` not to be `void`.
* `split_key_leq` assumes all nodes satisfying `cmp(k, node->key) == false` form a prefix. Requires `Key` not to be `void`.
* `split_value` assumes all nodes satisfying `condition(prefix_product) == true` form a prefix. Requires `Value` not to be `void`.
* `split_size` returns a Splay tree containing the leftmost `k` nodes. Requires `size()` in `Value`.

---

## Modifiers

### push_back / push_front

```cpp
void push_back(const auto &v);
void push_back(const auto &k, const auto &v);
void push_front(const auto &v);
void push_front(const auto &k, const auto &v);
```

* Amortized $O(\log N)$ time

Functionalities:
* Inserts a new node at the end (`push_back`) or at the beginning (`push_front`) of the Splay tree.
* The number of arguments depends on whether `Key` and `Value` are `void`.

### erase

```cpp
void erase(Iterator it);
```

* Amortized $O(\log N)$ time

Functionalities:
* Removes the node pointed to by the iterator from the Splay tree.
* Splays the target node to the root, disconnects its left and right subtrees, merges them, and deallocates the erased node.
* If `it == end()`, does nothing.

### swap

```cpp
void swap(Splay &rhs);
```

* $O(1)$ time

Functionalities:
* Swaps the entire content (root pointer) with another Splay tree.

### transform

```cpp
void transform(const auto &tag);
```

* $O(1)$ time
* Requires `Tag` not to be `void`.

Functionalities:
* Applies the lazy tag `tag` to the entire Splay tree by updating the root's lazy field.

### reverse

```cpp
void reverse();
```

* $O(1)$ time
* Requires `Rev` to be `true`.

Functionalities:
* Reverses the entire Splay tree by toggling the root's reverse flag.

### destruct

```cpp
void destruct();
```

* $O(N)$ time

Functionalities:
* Recursively deallocates all nodes in the Splay tree. Essential for manual memory management when not using a pool allocator.

---

## Range Operations

Requires `size()` member function for `Value`.

### split_range

```cpp
std::array<Splay, 2> split_range(int l, int r);
```

* Amortized $O(\log N)$ time

Functionalities:
* Splits the Splay tree into three parts: `[0, l)`, `[l, r)`, and `[r, N)`.
* The middle range `[l, r)` stays in the original Splay object (`*this`).
* The returned array contains the prefix `[0, l)` and suffix `[r, N)`.

### range_prod

```cpp
Value range_prod(int l, int r);
```

* Requires `Value` not to be `void`.
* Amortized $O(\log N)$ time

Functionalities:
* Returns the aggregate value (product) of all nodes in the range `[l, r)`.

### range_transform

```cpp
void range_transform(int l, int r, const auto &tag);
```

* Requires `Tag` not to be `void`.
* Amortized $O(\log N)$ time

Functionalities:
* Applies the lazy tag `tag` to all nodes in the range `[l, r)`.

### range_reverse

```cpp
void range_reverse(int l, int r);
```

* Requires `Rev` to be `true`.
* Amortized $O(\log N)$ time

Functionalities:
* Reverses the order of elements in the range `[l, r)`.

---

## Queries

### empty

```cpp
bool empty() const;
```

* $O(1)$ time

Functionalities:
* Returns `true` if the Splay tree contains no nodes (`root == nullptr`).

### size

```cpp
int size() const;
```

* $O(1)$ time
* Requires `size()` in `Value`.

Functionalities:
* Returns the total number of elements in the Splay tree.

### get_key

```cpp
Key get_key();
```

* $O(1)$ time
* Requires `Key` not to be `void`.

Functionalities:
* Returns the key stored at the root node.

### product

```cpp
Value product();
```

* $O(1)$ time
* Requires `Value` not to be `void`.

Functionalities:
* Returns the pre-calculated aggregate value (`val`) of the entire Splay tree (stored at the root).

### prefix_product

```cpp
template<typename K, typename Comp = std::less<Key>>
Value prefix_product_key_lt(const K &k, const Comp &cmp = Comp());

template<typename K, typename Comp = std::less<Key>>
Value prefix_product_key_leq(const K &k, const Comp &cmp = Comp());

Value prefix_product_cond(const auto &condition);
```

* Requires `Value` not to be `void`.
* Amortized $O(\log N)$ time

Functionalities:
* `prefix_product_key_lt` returns the product of all nodes with `key < k`. Requires `Key` not to be `void`.
* `prefix_product_key_leq` returns the product of all nodes with `key <= k`. Requires `Key` not to be `void`.
* `prefix_product_cond` returns the product of the longest prefix satisfying `condition(prefix_product)`.
* Splays the last visited node to the root.
* Assumes monotonicity where applicable.
