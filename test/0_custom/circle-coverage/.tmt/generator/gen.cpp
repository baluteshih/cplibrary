#include "testlib.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    std::string mode = opt<std::string>(1);
    int n = opt<int>(2);
    std::vector<std::array<int, 3>> circles;
    for (int i = 0; i < n; ++i) {
        int x = 0, y = 0, r = 1;
        if (mode == "identical") {
            x = 9'999;
            y = -9'999;
            r = 10'000;
        }
        else if (mode == "chain") {
            x = i;
            r = 10'000 - 3 * i;
        }
        else if (mode == "concentric") {
            r = 1 + 19 * i;
        }
        else if (mode == "weighted") {
            r = 1 + 100 * (i % 13);
        }
        else if (mode == "disjoint") {
            x = -9'900 + 30 * (i % 40);
            y = 9'900 - 30 * (i / 40);
            r = 1 + i % 7;
        }
        else if (mode == "common") {
            const std::array<std::array<int, 3>, 8> pattern = {{{5, 0, 5}, {0, 5, 5}, {-5, 0, 5}, {0, -5, 5}, {3, 4, 5}, {-3, 4, 5}, {3, -4, 5}, {-3, -4, 5}}};
            circles.push_back(pattern[static_cast<std::size_t>(i % 8)]);
            continue;
        }
        else if (mode == "grid") {
            x = (i % 23) * 15 - 150;
            y = (i / 23) * 15 - 150;
            r = 100;
        }
        else {
            int span = mode == "small" ? 10 : mode == "dense" ? 100 : 10'000;
            x = rnd.next(-span, span);
            y = rnd.next(-span, span);
            r = rnd.next(1, mode == "small" ? 10 : mode == "dense" ? 10'000 : 5'000);
            if (mode == "duplicates" && i % 3 != 0) {
                circles.push_back(circles.back());
                continue;
            }
        }
        circles.push_back({x, y, r});
    }
    shuffle(circles.begin(), circles.end());
    std::cout << n << '\n';
    for (auto circle : circles) {
        std::cout << circle[0] << ' ' << circle[1] << ' ' << circle[2] << '\n';
    }
}
