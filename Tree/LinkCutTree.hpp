#pragma once

#include "DataStructure/Splay.hpp"
#include "Algebra/ValidOperation.hpp"
#include "DataStructure/DefaultAllocator.hpp"

template <
    typename Value = void,
    typename Path = void,
    typename Subtree = void,
    typename Tag = void,
    bool Rev = true,
    template<typename> class Allocator = DefaultAllocator
>
class LinkCutTree {
    static constexpr bool hasValue = !std::is_void_v<Value>;
    static constexpr bool hasPath = !std::is_void_v<Path>;
    static constexpr bool hasSubtree = !std::is_void_v<Subtree>;
    static constexpr bool hasTag = !std::is_void_v<Tag>;
    static constexpr bool hasInvertibleTag = hasTag && requires(Tag t) { -t; };
    struct Empty {};
    using SafeValue = std::conditional_t<hasValue, Value, Empty>;
    using SafeTag = std::conditional_t<hasTag, Tag, Empty>;
    struct CompositeInfo {
        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty> org;
        [[no_unique_address]] std::conditional_t<hasPath, Path, Empty> path_val;
        [[no_unique_address]] std::conditional_t<hasSubtree, Subtree, Empty> sub_val;
        [[no_unique_address]] std::conditional_t<hasSubtree, Subtree, Empty> vir;
        [[no_unique_address]] std::conditional_t<hasSubtree && hasInvertibleTag, Tag, Empty> vir_lazy;
        CompositeInfo() = default;
        CompositeInfo operator+(const CompositeInfo& rhs) const {
            CompositeInfo res;
            if constexpr (hasPath) res.path_val = this->path_val + rhs.path_val;
            if constexpr (hasSubtree) res.sub_val = this->sub_val + rhs.sub_val;
            return res;
        }
        CompositeInfo operator+(const SafeTag& t) const requires (hasTag) {
            CompositeInfo res = *this;
            if constexpr (Addable<Value, Tag>) res.org = res.org + t;
            if constexpr (Addable<Path, Tag>) res.path_val = res.path_val + t;
            if constexpr (Addable<Subtree, Tag>) res.sub_val = res.sub_val + t;
            if constexpr (hasSubtree && hasInvertibleTag) res.vir_lazy = res.vir_lazy + t;
            return res;
        }
        void reverse() {
            if constexpr (hasPath && requires { path_val.reverse(); }) path_val.reverse();
            if constexpr (hasSubtree && requires { sub_val.reverse(); }) sub_val.reverse();
        }
    };
public:
    using SplayTree = Splay<void, CompositeInfo, Tag, Rev, Allocator>;
    using node = typename SplayTree::node;
    void splay(node* x) {
        SplayTree::push_all(x);
        SplayTree::splay_node(x);
    }
    std::vector<node> tr;
    LinkCutTree(int n = 0) : tr(n) {}
    LinkCutTree(const std::vector<SafeValue>& vals) requires (!std::is_void_v<Value>) : tr(vals.size()) {
        for (size_t i = 0; i < vals.size(); ++i) {
            tr[i].org.org = vals[i];
            if constexpr (!std::is_void_v<Path>) tr[i].org.path_val = Path(vals[i]);
            if constexpr (!std::is_void_v<Subtree>) tr[i].org.sub_val = Subtree(vals[i]);
            tr[i].up();
        }
    }
    node* get_node(int x) { return &tr[x]; }
    const SafeValue& getdata(int x) const requires (!std::is_void_v<Value>) {
        access(x);
        return tr[x].org.org;
    }
    void set_val(int x, const SafeValue& v) requires (hasValue) {
        access(x);
        tr[x].org.org = v;
        if constexpr (hasPath) tr[x].org.path_val = Path(v);
        if constexpr (hasSubtree) {
            if constexpr (hasInvertibleTag) tr[x].org.sub_val = Subtree(v) + (tr[x].org.vir + tr[x].org.vir_lazy);
            else tr[x].org.sub_val = Subtree(v) + tr[x].org.vir;
        }
        tr[x].up();
    }
    void transform(int x, const auto& func) {
        access(x); 
        splay(&tr[x]);
        func(tr[x].org.org);
        if constexpr (hasPath) tr[x].org.path_val = Path(tr[x].org.org);
        if constexpr (hasSubtree) {
            if constexpr (hasInvertibleTag) tr[x].org.sub_val = Subtree(tr[x].org.org) + (tr[x].org.vir + tr[x].org.vir_lazy);
            else tr[x].org.sub_val = Subtree(tr[x].org.org) + tr[x].org.vir;
        }
        tr[x].up();
    }
    int access(int x) {
        node* curr = &tr[x];
        node* last = nullptr;
        for (node* y = curr; y; y = y->f) {
            splay(y);
            if constexpr (hasSubtree) {
                static_assert(Subtractable<Subtree, Subtree>, "Subtree requires operator- to maintain virtual trees");
                if (last) y->org.vir = y->org.vir - last->val.sub_val;
                if constexpr (hasInvertibleTag) {
                    if (y->r) y->r->give_tag(-y->org.vir_lazy);
                    if (last) last->give_tag(y->org.vir_lazy);
                }
                if (y->r) y->org.vir = y->org.vir + y->r->val.sub_val;
                if constexpr (hasInvertibleTag) y->org.sub_val = Subtree(y->org.org) + (y->org.vir + y->org.vir_lazy);
                else y->org.sub_val = Subtree(y->org.org) + y->org.vir;
            }
            y->r = last;
            y->up();
            last = y;
        }
        splay(curr);
        return last ? static_cast<int>(last - tr.data()) : -1;
    }
    int findroot(int x) {
        access(x);
        node* curr = &tr[x];
        while (true) {
            if constexpr (hasTag || Rev) curr->down();
            if (curr->l) curr = curr->l;
            else break;
        }
        splay(curr);
        return curr - &tr[0];
    }
    bool is_connected(int x, int y) {
        return findroot(x) == findroot(y);
    }
    int get_lca(int x, int y) {
        if (!is_connected(x, y)) return -1;
        access(x);
        return access(y);
    }
    void makeroot(int x) requires (Rev) {
        access(x);
        tr[x].reverse();
    }
    void split(int x, int y) requires (Rev) {
        makeroot(x);
        access(y);
    }
    bool link(int x, int y) requires (Rev) {
        makeroot(x);
        if (findroot(y) == x) return false;
        access(y);
        splay(&tr[y]);
        tr[x].f = &tr[y];
        if constexpr (hasSubtree) {
            if constexpr (hasInvertibleTag) {
                tr[x].give_tag(-tr[y].org.vir_lazy);
            }
            tr[y].org.vir = tr[y].org.vir + tr[x].val.sub_val;
            tr[y].org.sub_val = Subtree(tr[y].org.org) + (tr[y].org.vir + tr[y].org.vir_lazy);
            tr[y].up();
        }
        return true;
    }
    bool cut(int x, int y) requires (Rev) {
        makeroot(x);
        if (findroot(y) != x) return false;
        access(y);
        if (tr[y].l != &tr[x] || tr[x].r != nullptr) return false;
        tr[y].l = nullptr;
        tr[x].f = nullptr;
        tr[y].up();
        return true;
    }
    Path path_query(int x, int y) requires (hasPath && Rev) {
        makeroot(x);
        access(y);
        splay(&tr[y]);
        return tr[y].val.path_val;
    }
    void path_transform(int x, int y, const SafeTag& tag) requires (hasPath && hasTag && Rev) {
        makeroot(x);
        access(y);
        splay(&tr[y]);
        tr[y].give_tag(tag);
        tr[y].up();
    }
    Subtree subtree_query(int x) requires (hasSubtree) {
        access(x);
        splay(&tr[x]);
        return tr[x].org.sub_val;
    }
    void subtree_transform(int x, const SafeTag& tag) requires (hasSubtree && hasTag && hasInvertibleTag) {
        access(x);
        splay(&tr[x]);
        tr[x].org.org = tr[x].org.org + tag;
        tr[x].org.vir_lazy = tr[x].org.vir_lazy + tag;
        if constexpr (hasPath) tr[x].org.path_val = Path(tr[x].org.org);
        tr[x].org.sub_val = Subtree(tr[x].org.org) + (tr[x].org.vir + tr[x].org.vir_lazy);
        tr[x].up();
    }
    bool link_directed(int child, int parent) {
        if (is_connected(child, parent)) return false; 
        access(child);
        splay(&tr[child]);
        if (tr[child].l) return false;
        access(parent);
        splay(&tr[parent]);
        tr[child].f = &tr[parent];
        if constexpr (hasSubtree) {
            if constexpr (hasInvertibleTag) tr[child].give_tag(-tr[parent].org.vir_lazy);
            tr[parent].org.vir = tr[parent].org.vir + tr[child].val.sub_val;
            tr[parent].org.sub_val = Subtree(tr[parent].org.org) + (tr[parent].org.vir + tr[parent].org.vir_lazy);
            tr[parent].up();
        }
        return true;
    }
    bool cut_directed(int child) {
        access(child);
        splay(&tr[child]);
        if (!tr[child].l) return false; 
        tr[child].l->f = nullptr;
        tr[child].l = nullptr;
        tr[child].up();
        return true;
    }
};
