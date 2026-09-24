#pragma once

template<typename E, typename F_Add, typename F_Query, typename F_Undo>
void cdq_solver(const std::vector<E> &elements, F_Add add, F_Query query, F_Undo undo) {
    if (elements.empty()) return;
    std::vector<int> idx(elements.size()), temp(elements.size());
    std::iota(idx.begin(), idx.end(), 0);
    auto solve = [&](auto self, int l, int r) -> void {
        if (l == r) return;
        int mid = (l + r) >> 1;
        self(self, l, mid), self(self, mid + 1, r);
        int i = l, j = mid + 1, k = l;
        while (i <= mid && j <= r) {
            if (elements[idx[i]] < elements[idx[j]]) add(elements[temp[k++] = idx[i++]]);
            else query(elements[temp[k++] = idx[j++]]);
        }
        while (j <= r) query(elements[temp[k++] = idx[j++]]);
        std::copy(idx.begin() + i, idx.begin() + mid + 1, temp.begin() + k);
        while (i > l) undo(elements[idx[--i]]);
        std::copy(temp.begin() + l, temp.begin() + r + 1, idx.begin() + l);
    };
    solve(solve, 0, elements.size() - 1);
}
