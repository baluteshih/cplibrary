---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':question:'
    path: Algebra/size_value.hpp
    title: Algebra/size_value.hpp
  - icon: ':question:'
    path: DataStructure/DefaultAllocator.hpp
    title: Default Allocator
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Graph/minimum_arborescence.hpp
    title: Graph/minimum_arborescence.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/directedmst.test.cpp
    title: test/1_library_checker/graph/directedmst.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/LeftistTree.hpp\"\n\n#line 2 \"Algebra/size_value.hpp\"\
    \n\nstruct size_v {\n    int sz;\n    size_v(int sz_ = 0): sz(sz_) {}\n    size_v\
    \ operator+(const size_v &rhs) const {\n        return size_v(sz + rhs.sz);\n\
    \    }\n    int size() const {\n        return sz; \n    }\n    friend std::ostream&\
    \ operator<<(std::ostream& os, const size_v &v) {\n        os << v.sz;\n     \
    \   return os;\n    }\n};\n#line 2 \"DataStructure/DefaultAllocator.hpp\"\n\n\
    template<typename T>\nstruct DefaultAllocator {\n    template<typename... Args>\n\
    \    static T* allocate(Args&&... args) { \n        return new T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) { delete p; }\n};\n#line 2 \"Algebra/ValidOperation.hpp\"\
    \n\ntemplate<typename T, typename Fallback>\nusing ReplaceVoid = std::conditional_t<std::same_as<T,\
    \ void>, Fallback, T>;\n\ntemplate <typename A, typename B>\nconcept ValidAddableState\
    \ =\n    requires(const ReplaceVoid<A, B>& a, \n             const ReplaceVoid<B,\
    \ A>& b) {\n        a + b;\n    };\n\ntemplate <typename A, typename B>\nconcept\
    \ ValidSubtractableState = \n    requires(const ReplaceVoid<A, B>& a, \n     \
    \        const ReplaceVoid<B, A>& b) {\n        a - b;\n    };\n#line 6 \"DataStructure/LeftistTree.hpp\"\
    \n\ntemplate<typename Key = int,\n         typename Tag = void,\n         typename\
    \ Info = void,\n         template<typename> class Allocator = DefaultAllocator,\n\
    \         bool persistent = false\n>\nclass LeftistTree { \n    static constexpr\
    \ bool hasTag = !std::is_same_v<Tag, void>;\n    static constexpr bool hasInfo\
    \ = !std::is_same_v<Info, void>;\n    struct Empty {};\n    template <bool Condition,\
    \ typename T>\n    static auto get_default() {\n        if constexpr (Condition)\
    \ return T();\n        else return Empty{};\n    }\n    static_assert(!hasTag\
    \ || ValidAddableState<Key, Tag>);\n    struct node {\n        node *l = nullptr,\
    \ *r = nullptr;\n        Key key;\n        [[no_unique_address]] std::conditional_t<hasTag,\
    \ Tag, Empty> lazy = get_default<hasTag, Tag>();\n        [[no_unique_address]]\
    \ std::conditional_t<hasInfo, Info, Empty> info = get_default<hasInfo, Info>();\n\
    \        int rank = 0;\n        void up() {\n            if (get_rank(r) > get_rank(l))\
    \ std::swap(r, l);\n            rank = get_rank(r) + 1;\n        }\n        void\
    \ give_tag(const auto &tag) requires (hasTag) {\n            key = key + tag;\n\
    \            lazy = lazy + tag;\n        }\n        void down() requires (hasTag)\
    \ {\n            bool need_tag = false;\n            if constexpr (std::equality_comparable<Tag>)\
    \ need_tag = (lazy != Tag());\n            else need_tag = true;\n           \
    \ if (!need_tag) return;\n            if (l) {\n                if constexpr (persistent)\
    \ l = NodeAlloc::allocate(*l);\n                l->give_tag(lazy);\n         \
    \   }\n            if (r) {\n                if constexpr (persistent) r = NodeAlloc::allocate(*r);\n\
    \                r->give_tag(lazy);\n            }\n            lazy = Tag();\n\
    \        }\n        node() = default;\n        node(const auto &v) requires (!hasInfo)\
    \ : key(v) {}\n        node(const auto &k, const auto &v) requires (hasInfo) :\
    \ key(k), info(v) {}\n        friend std::ostream& operator<<(std::ostream& os,\
    \ const node &v) {\n            if constexpr (hasInfo) os << \"{key = \" << v.key\
    \ << \", info = \" << v.info << \"}\";\n            else os << v.key;\n      \
    \      return os;\n        }\n    };\n    using NodeAlloc = Allocator<node>;\n\
    \    node *root = nullptr;\n    int sz = 0;\n    static node *merge(node *left,\
    \ node *right) {\n        if (!left || !right) return left ? left : right;\n \
    \       if (right->key < left->key) std::swap(left, right);\n        if constexpr\
    \ (persistent) left = NodeAlloc::allocate(*left); \n        left->down();\n  \
    \      left->r = merge(left->r, right);\n        left->up();\n        return left;\n\
    \    }\n    void erase(node *&o) {\n        if constexpr (persistent) o = NodeAlloc::allocate(*o);\n\
    \        o->down();\n        node *tmp = o;\n        o = merge(o->l, o->r);\n\
    \        NodeAlloc::deallocate(tmp);\n    }\n    static void free(node *&ptr)\
    \ requires (!persistent) {\n        if (ptr == nullptr) return;\n        free(ptr->l);\n\
    \        free(ptr->r);\n        NodeAlloc::deallocate(ptr);\n        ptr = nullptr;\n\
    \    }\n    static int get_rank(node *p) { return p ? p->rank : -1; }\npublic:\n\
    \    LeftistTree() = default;\n    LeftistTree(node *root_) : root(root_) {}\n\
    \    LeftistTree(const auto &v) requires (!hasInfo) : root(NodeAlloc::allocate(v)),\
    \ sz(1) {}\n    LeftistTree(const auto &k, const auto &v) requires (hasInfo) :\
    \ root(NodeAlloc::allocate(k, v)), sz(1) {}\n    void destruct() requires (!persistent)\
    \ {\n        free(root);\n        sz = 0;\n    }\n    void transform(const auto\
    \ &tag) requires (hasTag) {\n        if (root) {\n            if constexpr (persistent)\
    \ root = NodeAlloc::allocate(*root);\n            root->give_tag(tag);\n     \
    \   }\n    }\n    void swap(LeftistTree &rhs) {\n        std::swap(root, rhs.root);\n\
    \        std::swap(sz, rhs.sz);\n    }\n    bool empty() {\n        return root\
    \ == nullptr;\n    }\n    int size() {\n        return sz;\n    }\n    void clear()\
    \ {\n        root = nullptr;\n        sz = 0;\n    }\n    Key top() {\n      \
    \  return root->key;\n    }\n    auto topinfo() requires (hasInfo) {\n       \
    \ return root->info;\n    }\n    void pop() {\n        erase(root);\n        --sz;\n\
    \    }\n    void join(LeftistTree &rhs) {\n        root = merge(root, rhs.root);\n\
    \        sz += rhs.sz;\n        rhs.clear();\n    }\n    template<typename...\
    \ Args>\n    void push(Args&&... args) {\n        root = merge(root, NodeAlloc::allocate(std::forward<Args>(args)...));\n\
    \        sz += 1;\n    }\n};\n"
  code: "#pragma once\n\n#include \"Algebra/size_value.hpp\"\n#include \"DataStructure/DefaultAllocator.hpp\"\
    \n#include \"Algebra/ValidOperation.hpp\"\n\ntemplate<typename Key = int,\n  \
    \       typename Tag = void,\n         typename Info = void,\n         template<typename>\
    \ class Allocator = DefaultAllocator,\n         bool persistent = false\n>\nclass\
    \ LeftistTree { \n    static constexpr bool hasTag = !std::is_same_v<Tag, void>;\n\
    \    static constexpr bool hasInfo = !std::is_same_v<Info, void>;\n    struct\
    \ Empty {};\n    template <bool Condition, typename T>\n    static auto get_default()\
    \ {\n        if constexpr (Condition) return T();\n        else return Empty{};\n\
    \    }\n    static_assert(!hasTag || ValidAddableState<Key, Tag>);\n    struct\
    \ node {\n        node *l = nullptr, *r = nullptr;\n        Key key;\n       \
    \ [[no_unique_address]] std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag,\
    \ Tag>();\n        [[no_unique_address]] std::conditional_t<hasInfo, Info, Empty>\
    \ info = get_default<hasInfo, Info>();\n        int rank = 0;\n        void up()\
    \ {\n            if (get_rank(r) > get_rank(l)) std::swap(r, l);\n           \
    \ rank = get_rank(r) + 1;\n        }\n        void give_tag(const auto &tag) requires\
    \ (hasTag) {\n            key = key + tag;\n            lazy = lazy + tag;\n \
    \       }\n        void down() requires (hasTag) {\n            bool need_tag\
    \ = false;\n            if constexpr (std::equality_comparable<Tag>) need_tag\
    \ = (lazy != Tag());\n            else need_tag = true;\n            if (!need_tag)\
    \ return;\n            if (l) {\n                if constexpr (persistent) l =\
    \ NodeAlloc::allocate(*l);\n                l->give_tag(lazy);\n            }\n\
    \            if (r) {\n                if constexpr (persistent) r = NodeAlloc::allocate(*r);\n\
    \                r->give_tag(lazy);\n            }\n            lazy = Tag();\n\
    \        }\n        node() = default;\n        node(const auto &v) requires (!hasInfo)\
    \ : key(v) {}\n        node(const auto &k, const auto &v) requires (hasInfo) :\
    \ key(k), info(v) {}\n        friend std::ostream& operator<<(std::ostream& os,\
    \ const node &v) {\n            if constexpr (hasInfo) os << \"{key = \" << v.key\
    \ << \", info = \" << v.info << \"}\";\n            else os << v.key;\n      \
    \      return os;\n        }\n    };\n    using NodeAlloc = Allocator<node>;\n\
    \    node *root = nullptr;\n    int sz = 0;\n    static node *merge(node *left,\
    \ node *right) {\n        if (!left || !right) return left ? left : right;\n \
    \       if (right->key < left->key) std::swap(left, right);\n        if constexpr\
    \ (persistent) left = NodeAlloc::allocate(*left); \n        left->down();\n  \
    \      left->r = merge(left->r, right);\n        left->up();\n        return left;\n\
    \    }\n    void erase(node *&o) {\n        if constexpr (persistent) o = NodeAlloc::allocate(*o);\n\
    \        o->down();\n        node *tmp = o;\n        o = merge(o->l, o->r);\n\
    \        NodeAlloc::deallocate(tmp);\n    }\n    static void free(node *&ptr)\
    \ requires (!persistent) {\n        if (ptr == nullptr) return;\n        free(ptr->l);\n\
    \        free(ptr->r);\n        NodeAlloc::deallocate(ptr);\n        ptr = nullptr;\n\
    \    }\n    static int get_rank(node *p) { return p ? p->rank : -1; }\npublic:\n\
    \    LeftistTree() = default;\n    LeftistTree(node *root_) : root(root_) {}\n\
    \    LeftistTree(const auto &v) requires (!hasInfo) : root(NodeAlloc::allocate(v)),\
    \ sz(1) {}\n    LeftistTree(const auto &k, const auto &v) requires (hasInfo) :\
    \ root(NodeAlloc::allocate(k, v)), sz(1) {}\n    void destruct() requires (!persistent)\
    \ {\n        free(root);\n        sz = 0;\n    }\n    void transform(const auto\
    \ &tag) requires (hasTag) {\n        if (root) {\n            if constexpr (persistent)\
    \ root = NodeAlloc::allocate(*root);\n            root->give_tag(tag);\n     \
    \   }\n    }\n    void swap(LeftistTree &rhs) {\n        std::swap(root, rhs.root);\n\
    \        std::swap(sz, rhs.sz);\n    }\n    bool empty() {\n        return root\
    \ == nullptr;\n    }\n    int size() {\n        return sz;\n    }\n    void clear()\
    \ {\n        root = nullptr;\n        sz = 0;\n    }\n    Key top() {\n      \
    \  return root->key;\n    }\n    auto topinfo() requires (hasInfo) {\n       \
    \ return root->info;\n    }\n    void pop() {\n        erase(root);\n        --sz;\n\
    \    }\n    void join(LeftistTree &rhs) {\n        root = merge(root, rhs.root);\n\
    \        sz += rhs.sz;\n        rhs.clear();\n    }\n    template<typename...\
    \ Args>\n    void push(Args&&... args) {\n        root = merge(root, NodeAlloc::allocate(std::forward<Args>(args)...));\n\
    \        sz += 1;\n    }\n};\n"
  dependsOn:
  - Algebra/size_value.hpp
  - DataStructure/DefaultAllocator.hpp
  - Algebra/ValidOperation.hpp
  isVerificationFile: false
  path: DataStructure/LeftistTree.hpp
  requiredBy:
  - Graph/minimum_arborescence.hpp
  timestamp: '2026-06-18 22:20:51+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/graph/directedmst.test.cpp
documentation_of: DataStructure/LeftistTree.hpp
layout: document
title: Leftist Tree
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
