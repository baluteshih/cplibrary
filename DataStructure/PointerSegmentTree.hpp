#pragma once

#include "DataStructure/DefaultAllocator.hpp"

template<typename Value = int, typename Tag = void, bool pushdown = true, template<typename> class Allocator = DefaultAllocator, bool dynamic = false, bool persistent = false>
class PointerSegmentTree {
    static constexpr bool hasTag = !std::is_same_v<Tag, void>;
    static constexpr bool hasGet = requires(int l, int r) { Value::get(l, r); };
    static_assert(pushdown || hasTag, "Lazy tag must exist when pushdown is false");
    int n;
    struct Empty {};
    template <bool Condition, typename T>
    static auto get_default() {
        if constexpr (Condition) return T();
        else return Empty{};
    }
    struct node {
        node *l = nullptr, *r = nullptr;
        Value val;
        [[no_unique_address]] std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag, Tag>();
        Value get_val() {
            if constexpr (pushdown) return val;
            else return val + lazy;
        }
        void up() {
            val = l->get_val() + r->get_val();
        }
        void give_tag(const auto &tag) requires (hasTag) {
            if constexpr (pushdown) val = val + tag;
            lazy = lazy + tag;
        }
        void down() requires (hasTag && pushdown) {
            bool need_tag = false;
            if constexpr (hasTag) { 
                if constexpr (std::equality_comparable<Tag>) need_tag = (lazy != Tag());
                else need_tag = true;
            }
            if (!need_tag) return;
            if constexpr (persistent) {
                if constexpr (persistent) l = NodeAlloc::allocate(*l);
                if constexpr (persistent) r = NodeAlloc::allocate(*r);
            }
            l->give_tag(lazy);
            r->give_tag(lazy);
            lazy = Tag();
        }
        node() = default;
        node(const auto &v) : val(v) {}
    };
    node *root = nullptr;
    using NodeAlloc = Allocator<node>;
    void initialize(int l, int r, node *&p, const vector<Value> &data) {
        if (r - l == 1) 
            return p = NodeAlloc::allocate(data[l]), void();
        p = NodeAlloc::allocate();
        int mid = (l + r) >> 1;
        initialize(l, mid, p->l, data);
        initialize(mid, r, p->r, data);
        p->up();
    }
    Value range_prod(int L, int R, int l, int r, node *p) {
        if constexpr (dynamic) {
            if (!p) {
                if constexpr (hasGet) return Value::get(std::max(L, l), std::min(R, r));
                return Value();
            }
        }
        if (L <= l && R >= r)
            return p->get_val();
        if constexpr (hasTag && pushdown) p->down();
        int mid = (l + r) >> 1;
        if constexpr (pushdown) {
            if (R <= mid) return range_prod(L, R, l, mid, p->l);
            if (L >= mid) return range_prod(L, R, mid, r, p->r);
            return range_prod(L, R, l, mid, p->l) + range_prod(L, R, mid, r, p->r); 
        }
        else {
            if (R <= mid) return range_prod(L, R, l, mid, p->l) + p->lazy;
            if (L >= mid) return range_prod(L, R, mid, r, p->r) + p->lazy;
            return range_prod(L, R, l, mid, p->l) + range_prod(L, R, mid, r, p->r) + p->lazy;
        }
    }
    void check_node(node *&p, int l, int r) requires (dynamic || persistent) {
        bool allocated = false; 
        if constexpr (dynamic) if (!p) {
            allocated = true;
            if constexpr (hasGet) p = NodeAlloc::allocate(Value::get(l, r));
            else p = NodeAlloc::allocate();
        }
        if constexpr (persistent) if (!allocated) p = NodeAlloc::allocate(*p);
    }
    void modify(int x, int l, int r, node *&p, const Value &v) {
        if constexpr (dynamic || persistent) check_node(p, l, r);
        if (r - l == 1)
            return p->val = v, void();
        if constexpr (hasTag && pushdown) p->down();
        int mid = (l + r) >> 1;
        if constexpr (pushdown) {
            if (x < mid) modify(x, l, mid, p->l, v);
            else modify(x, mid, r, p->r, v);
        }
        else {
            if (x < mid) modify(x, l, mid, p->l, v - p->lazy);
            else modify(x, mid, r, p->r, v - p->lazy);
        }
        p->up();
    }
    void transform(int x, int l, int r, node *&p, const auto &func) {
        if constexpr (dynamic || persistent) check_node(p, l, r);
        if (r - l == 1)
            return func(p->val), void();
        if constexpr (hasTag && pushdown) p->down();
        int mid = (l + r) >> 1;
        if (x < mid) transform(x, l, mid, p->l, func);
        else transform(x, mid, r, p->r, func);
        p->up();
    }
    void range_transform(int L, int R, int l, int r, node *&p, const auto &tag) requires (hasTag) {
        if constexpr (dynamic || persistent) check_node(p, l, r);
        if (L <= l && R >= r)
            return p->give_tag(tag);
        if constexpr (pushdown) p->down();
        int mid = (l + r) >> 1;
        if (L < mid) range_transform(L, R, l, mid, p->l, tag);
        if (R > mid) range_transform(L, R, mid, r, p->r, tag);
        p->up();
    }
    void range_transform_beats(int L, int R, int l, int r, node *&p, const auto &tag, const auto &tag_condition, auto... tag_sum) requires (hasTag) {
        if constexpr (dynamic || persistent) check_node(p, l, r);
        if (L <= l && R >= r && tag_condition([&]{ if constexpr(pushdown) return p->val; else return p->get_val() + (..., tag_sum); }()))
            return p->give_tag(tag);
        assert(r - l > 1);
        if constexpr (pushdown) p->down();
        else ((tag_sum = tag_sum + p->lazy), ...);
        int mid = (l + r) >> 1;
        if (L < mid) range_transform_beats(L, R, l, mid, p->l, tag, tag_condition, tag_sum...);
        if (R > mid) range_transform_beats(L, R, mid, r, p->r, tag, tag_condition, tag_sum...);
        p->up();
    }
    int range_left_search(int L, int R, int l, int r, node *p, const auto &condition, auto... tag_sum) {
        if constexpr (!dynamic) if (!p) return R;
        if (r - l == 1) {
            if (!condition([&]{ if constexpr(pushdown) return p->val; else return p->get_val() + (..., tag_sum); }()))
                return R;
            return l;
        }
        int mid = (l + r) >> 1;
        if constexpr (hasTag && pushdown) p->down();
        if constexpr (!pushdown) ((tag_sum = tag_sum + p->lazy), ...);
        if (L <= l && R >= r) {
            if (p->l && condition([&]{ if constexpr(pushdown) return p->l->val; else return p->l->get_val() + (..., tag_sum); }()))
                return range_left_search(L, R, l, mid, p->l, condition, tag_sum...);
            return range_left_search(L, R, mid, r, p->r, condition, tag_sum...);
        }
        int left = R;
        if (L < mid) left = range_left_search(L, R, l, mid, p->l, condition, tag_sum...);
        if (left == R) {
            if (R > mid) return range_left_search(L, R, mid, r, p->r, condition, tag_sum...);
            return R;
        }
        return left;
    }
    int range_right_search(int L, int R, int l, int r, node *p, const auto &condition, auto... tag_sum) {
        if constexpr (!dynamic) if (!p) return L - 1;
        if (r - l == 1) {
            if (!condition([&]{ if constexpr(pushdown) return p->val; else return p->get_val() + (..., tag_sum); }()))
                return L - 1;
            return l;
        }
        int mid = (l + r) >> 1;
        if constexpr (hasTag && pushdown) p->down();
        if constexpr (!pushdown) ((tag_sum = tag_sum + p->lazy), ...);
        if (L <= l && R >= r) {
            if (p->r && condition([&]{ if constexpr(pushdown) return p->r->val; else return p->r->get_val() + (..., tag_sum); }()))
                return range_right_search(L, R, mid, r, p->r, condition, tag_sum...);
            return range_right_search(L, R, l, mid, p->l, condition, tag_sum...);
        }
        int right = L - 1;
        if (R > mid) right = range_right_search(L, R, mid, r, p->r, condition, tag_sum...);
        if (right == L - 1) {
            if (L < mid) return range_right_search(L, R, l, mid, p->l, condition, tag_sum...);
            return L - 1;
        }
        return right;
    }
    Value get(int x, int l, int r, node *p) {
        [[no_unique_address]] std::conditional_t<!pushdown, Tag, Empty> tag;
        while (r - l > 1) {
            if constexpr (hasTag && pushdown) p->down();
            if constexpr (!pushdown) tag = tag + p->lazy;
            int mid = (l + r) >> 1;
            if (x < mid) r = mid, p = p->l;
            else l = mid, p = p->r;
            if constexpr (dynamic || persistent) if (!p) {
                if constexpr (hasGet) return Value::get(x, x + 1) + tag;
                else return Value() + tag;
            }
        }
        if constexpr (pushdown) return p->val;
        else return p->get_val() + tag;
    }
    void range_copy(int L, int R, int l, int r, node *&p, node *&q) requires (pushdown && persistent) {
        if (L <= l && R >= r)
            return p = q, void();
        if constexpr (dynamic || persistent) check_node(p, l, r);
        if constexpr (hasTag && pushdown) p->down(), q->down();
        int mid = (l + r) >> 1;
        if (L < mid) range_copy(L, R, l, mid, p->l, q->l);
        if (R > mid) range_copy(L, R, mid, r, p->r, q->r);
        p->up();
    }
    void printnode(int l, int r, node *p) {
        std::cerr << "[" << l << ", " << r << "): ";
        if constexpr (hasTag) std::cerr << "val = " << p->val << ", tag = " << p->lazy;
        else std::cerr << p->val;
        std::cerr << "\n";
    }
    void printinfo(int L, int R, int l, int r, node *p) {
        printnode(l, r, p);
        if (L <= l && R >= r)
            return;
        int mid = (l + r) >> 1;
        if (L < mid) printinfo(L, R, l, mid, p->l);
        if (R > mid) printinfo(L, R, mid, r, p->r);
    }
    void printall(int l, int r, node *p) {
        printnode(l, r, p);
        if (r - l == 1) return;
        int mid = (l + r) >> 1;
        printall(l, mid, p->l);
        printall(mid, r, p->r);
    }
public:
    PointerSegmentTree(const vector<Value> &data): n(data.size()), root(nullptr) { 
        initialize(0, n, root, data);
    }
    PointerSegmentTree(int size) requires (!dynamic) : PointerSegmentTree(vector<Value>(size)) {}
    PointerSegmentTree(int size = 0) requires (dynamic || persistent) : n(size), root(nullptr) {}
    Value get(int x) {
        assert(0 <= x && x < n);
        return get(x, 0, n, root);
    }
    Value range_prod(int l, int r) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l == r) return Value();
        return range_prod(l, r, 0, n, root);
    }
    void modify(int x, const Value &v) {
        assert(0 <= x && x < n);
        modify(x, 0, n, root, v);
    }
    void transform(int x, const auto &func) {
        assert(0 <= x && x < n);
        transform(x, 0, n, root, func);
    }
    void range_transform(int l, int r, const auto &tag) requires (hasTag) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l < r)
            range_transform(l, r, 0, n, root, tag);
    }
    void range_transform_beats(int l, int r, const auto &tag, const auto &tag_condition) requires (hasTag) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l < r)
            range_transform_beats(l, r, 0, n, root, tag, tag_condition);
    }
    /*
       For the given element range [l, r)
       Perform segment tree binary search within the range with left half first 
       return fail if the node is empty
     */
    int range_left_search(const auto &condition, int l = -1, int r = -1) {
        if (l == -1 && r == -1) l = 0, r = n;
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l == r) return r;
        return range_left_search(l, r, 0, n, root, condition);
    }
    /*
       For the given element range (l, r]
       Perform segment tree binary search within the range with right half first 
     */
    int range_right_search(const auto &condition, int l = -1, int r = -1) {
        if (l == -1 && r == -1) l = -1, r = n - 1;
        ++l, ++r;
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l == r) return l - 1;
        return range_right_search(l, r, 0, n, root, condition);
    }
    void range_copy(int l, int r, PointerSegmentTree &other) requires (pushdown && persistent) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l < r)
            range_copy(l, r, 0, n, root, other.root);
    }
    void printinfo(int l, int r) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        std::cerr << "\e[1;33mInfo [" << l << ", " << r << "):\n";
        if (l < r) 
            printinfo(l, r, 0, n, root);
        cerr << "\e[0m\n";
    }
    void printall() {
        std::cerr << "\e[1;33mInfo all:\n";
        printall(0, n, root);
        cerr << "\e[0m\n";
    }
};
