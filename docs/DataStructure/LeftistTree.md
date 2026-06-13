---
title: Leftist Tree
documentation_of: ../../DataStructure/LeftistTree.hpp
---

A Leftist Tree (or Leftist Heap) is a priority queue implemented with a binary tree. It supports merging two heaps in $O(\log N)$ time. It also supports optional lazy propagation and persistence.

## Template Parameters

```cpp
template<typename Key = int,
         typename Tag = void,
         typename Info = void,
         template<typename> class Allocator = DefaultAllocator,
         bool persistent = false
>
class LeftistTree;
```

* `Key`: The type of elements used for priority.
    * Must support `operator<` for comparison (the element with the smallest `Key` will be at the top).
    * If `Tag` is not `void`, must support `Key + Tag`.
* `Tag`: The type of lazy tags. Use `void` if no lazy propagation is needed.
    * Must support `Tag + Tag` for tag composition and `Key + Tag` for applying to a key.
    * Must have a default constructor `Tag()` acting as the identity tag.
* `Info`: Additional information stored in each node. Use `void` if not needed.
* `Allocator`: The allocator for nodes. Defaults to `DefaultAllocator`.
* `persistent`: If `true`, the tree operations will be persistent.

---

## Constructor

```cpp
LeftistTree();
LeftistTree(const Key &k); // If Info is void
LeftistTree(const Key &k, const Info &v); // If Info is not void
```

* $O(1)$ time

Constructs an empty tree or a tree with a single element.

---

## empty / size

```cpp
bool empty();
int size();
```

* $O(1)$ time

Returns whether the tree is empty and the number of elements in the tree, respectively.

---

## top / topinfo

```cpp
Key top();
Info topinfo(); // Requires Info is not void
```

* $O(1)$ time

Returns the key or the additional information of the top element (the one with the minimum key).

---

## push

```cpp
template<typename... Args>
void push(Args&&... args);
```

* $O(\log N)$ time

Inserts a new element into the tree. `args` are passed to the `node` constructor.

---

## pop

```cpp
void pop();
```

* $O(\log N)$ time

Removes the top element from the tree.

---

## join

```cpp
void join(LeftistTree &rhs);
```

* $O(\log N + \log M)$ time

Merges the tree `rhs` into the current tree. `rhs` will be cleared after the operation.

---

## transform

```cpp
void transform(const Tag &tag);
```

* Requires `Tag` not to be `void`.
* $O(1)$ time (lazy propagation)

Applies the lazy tag `tag` to all elements in the tree.

---

## clear / destruct

```cpp
void clear();
void destruct(); // Requires !persistent
```

* `clear()`: $O(1)$ time. Clears the root pointer and size without deallocating nodes.
* `destruct()`: $O(N)$ time. Recursively deallocates all nodes in the tree. Only available if not persistent.

---

## swap

```cpp
void swap(LeftistTree &rhs);
```

* $O(1)$ time

Swaps the content with another `LeftistTree`.
