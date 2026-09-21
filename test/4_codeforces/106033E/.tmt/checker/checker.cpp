#include "testlib.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

inline void wrong_answer(const std::string &msg) {
    quitf(_wa, "%s", msg.c_str());
}

inline void accept() {
    quitf(_ok, "Accepted");
}

inline void judge_error(const std::string &msg) {
    quitf(_fail, "%s", msg.c_str());
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    int N = inf.readInt();
    int M = inf.readInt();
    std::vector<std::vector<long long>> capacity(N, std::vector<long long>(N, 0));
    for (int i = 0; i < M; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        long long c = inf.readLong();
        --u, --v;
        capacity[u][v] += c;
    }

    long long ansv = ans.readLong();
    
    long long outv = ouf.readLong(0, 1'000'000'000'000'000'000LL);
    long long sumv = 0;
    std::vector<std::vector<long long>> total(N, std::vector<long long>(N, 0));
    if (outv < ansv) wrong_answer("The participant tends to give a smaller answer");
    int path = ouf.readInt(0, 50'000);
    for (int i = 0; i < path; ++i) {
        long long x = ouf.readLong(0, 1'000'000'001LL);
        sumv += x;
        if (sumv > outv) wrong_answer("The sum of all flow value is not equal to the output value");
        int k = ouf.readInt(2, 1'000'000'000);
        int lst = -1;
        for (int j = 0; j < k; ++j) {
            int cur = ouf.readInt(1, N);
            --cur;
            if (lst != -1) {
                total[lst][cur] += x;
                if (total[lst][cur] > capacity[lst][cur])
                    wrong_answer("Flow on the edge (" + std::to_string(lst + 1) + " -> " + std::to_string(cur + 1) + ") exceeds its capacity " + std::to_string(capacity[lst][cur]));
            }
            else {
                if (cur != 0)
                    wrong_answer("Path " + std::to_string(i + 1) + " does not start at 1");
            }
            lst = cur;
        }
        if (lst != N - 1)
            wrong_answer("Path " + std::to_string(i + 1) + " does not end with N");
    }

    if (sumv != outv)
        wrong_answer("The sum of all flow value is not equal to the output value");

    if (outv > ansv)
        judge_error("The participant found a larger flow Orz");

    accept();
}
