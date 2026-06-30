#pragma once

#include "Algebra/size_value.hpp"
#include "DataStructure/DefaultAllocator.hpp"
#include "Algebra/ValidOperation.hpp"

template<typename Key = int,
         typename Tag = void,
         typename Info = void,
         template<typename> class Allocator = DefaultAllocator,
         bool persistent = false
>
class LeftistTree { 
    static constexpr bool hasTag = !std::is_same_v<Tag, void>;
    static constexpr bool hasInfo = !std::is_same_v<Info, void>;
    struct Empty {};
    template <bool Condition, typename T>
    static auto get_default() {
        if constexpr (Condition) return T();
        else return Empty{};
    }
    static_assert(!hasTag || Addable<Key, Tag>);
    struct node {
        node *l = nullptr, *r = nullptr;
        Key key;
        [[no_unique_address]] std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag, Tag>();
        [[no_unique_address]] std::conditional_t<hasInfo, Info, Empty> info = get_default<hasInfo, Info>();
        int rank = 0;
        void up() {
            if (get_rank(r) > get_rank(l)) std::swap(r, l);
            rank = get_rank(r) + 1;
        }
        void give_tag(const auto &tag) requires (hasTag) {
            key = key + tag;
            lazy = lazy + tag;
        }
        void down() requires (hasTag) {
            bool need_tag = false;
            if constexpr (std::equality_comparable<Tag>) need_tag = (lazy != Tag());
            else need_tag = true;
            if (!need_tag) return;
            if (l) {
                if constexpr (persistent) l = NodeAlloc::allocate(*l);
                l->give_tag(lazy);
            }
            if (r) {
                if constexpr (persistent) r = NodeAlloc::allocate(*r);
                r->give_tag(lazy);
            }
            lazy = Tag();
        }
        node() = default;
        node(const auto &v) requires (!hasInfo) : key(v) {}
        node(const auto &k, const auto &v) requires (hasInfo) : key(k), info(v) {}
        friend std::ostream& operator<<(std::ostream& os, const node &v) {
            if constexpr (hasInfo) os << "{key = " << v.key << ", info = " << v.info << "}";
            else os << v.key;
            return os;
        }
    };
    using NodeAlloc = Allocator<node>;
    node *root = nullptr;
    int sz = 0;
    static node *merge(node *left, node *right) {
        if (!left || !right) return left ? left : right;
        if (right->key < left->key) std::swap(left, right);
        if constexpr (persistent) left = NodeAlloc::allocate(*left); 
        left->down();
        left->r = merge(left->r, right);
        left->up();
        return left;
    }
    void erase(node *&o) {
        if constexpr (persistent) o = NodeAlloc::allocate(*o);
        o->down();
        node *tmp = o;
        o = merge(o->l, o->r);
        NodeAlloc::deallocate(tmp);
    }
    static void free(node *&ptr) requires (!persistent) {
        if (ptr == nullptr) return;
        free(ptr->l);
        free(ptr->r);
        NodeAlloc::deallocate(ptr);
        ptr = nullptr;
    }
    static int get_rank(node *p) { return p ? p->rank : -1; }
public:
    LeftistTree() = default;
    LeftistTree(node *root_) : root(root_) {}
    LeftistTree(const auto &v) requires (!hasInfo) : root(NodeAlloc::allocate(v)), sz(1) {}
    LeftistTree(const auto &k, const auto &v) requires (hasInfo) : root(NodeAlloc::allocate(k, v)), sz(1) {}
    void destruct() requires (!persistent) {
        free(root);
        sz = 0;
    }
    void transform(const auto &tag) requires (hasTag) {
        if (root) {
            if constexpr (persistent) root = NodeAlloc::allocate(*root);
            root->give_tag(tag);
        }
    }
    void swap(LeftistTree &rhs) {
        std::swap(root, rhs.root);
        std::swap(sz, rhs.sz);
    }
    bool empty() {
        return root == nullptr;
    }
    int size() {
        return sz;
    }
    void clear() {
        root = nullptr;
        sz = 0;
    }
    Key top() {
        return root->key;
    }
    auto topinfo() requires (hasInfo) {
        return root->info;
    }
    void pop() {
        erase(root);
        --sz;
    }
    void join(LeftistTree &rhs) {
        root = merge(root, rhs.root);
        sz += rhs.sz;
        rhs.clear();
    }
    template<typename... Args>
    void push(Args&&... args) {
        root = merge(root, NodeAlloc::allocate(std::forward<Args>(args)...));
        sz += 1;
    }
};
