#include "testlib.h"
#include <string>
#include <vector>

struct Point {
    long long x, y;
    Point operator-(Point other) const {
        return {x - other.x, y - other.y};
    }
};

long long cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

long long dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), q = inf.readInt();
    std::vector<Point> polygon(static_cast<std::size_t>(n));
    for (auto &point : polygon) {
        point.x = inf.readLong();
        point.y = inf.readLong();
    }
    for (int query = 0; query < q; ++query) {
        std::string type = inf.readToken();
        Point point = {inf.readLong(), inf.readLong()};
        if (type == "I") {
            std::string expected = ans.readToken();
            std::string actual = ouf.readToken();
            if (actual != expected) {
                quitf(_wa, "query %d: expected %s, got %s", query + 1, expected.c_str(), actual.c_str());
            }
        }
        else if (type == "D") {
            int expected = ans.readInt(0, n - 1);
            int actual = ouf.readInt(0, n - 1);
            if (cross(point, polygon[actual]) != cross(point, polygon[expected])) {
                quitf(_wa, "query %d: vertex does not maximize cross(d,C_i)", query + 1);
            }
        }
        else {
            auto valid = [&](int actual, int expected) {
                if (actual == expected) {
                    return true;
                }
                if (actual != (expected + 1) % n && actual != (expected + n - 1) % n) {
                    return false;
                }
                Point a = polygon[actual] - point, b = polygon[expected] - point;
                return cross(a, b) == 0 && dot(a, b) > 0;
            };
            int expectedFirst = ans.readInt(0, n - 1);
            int expectedSecond = ans.readInt(0, n - 1);
            int actualFirst = ouf.readInt(0, n - 1);
            int actualSecond = ouf.readInt(0, n - 1);
            if (!valid(actualFirst, expectedFirst) || !valid(actualSecond, expectedSecond)) {
                quitf(_wa, "query %d: incorrect ordered tangent contacts", query + 1);
            }
        }
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output token");
    }
    quitf(_ok, "all %d queries valid, including support ties", q);
}
