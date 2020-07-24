#include <vector>
#include <iostream>

#include "godel.h"

using namespace godel;

using namespace std;

int main() {
    //for (ull i = 0; i < 7; i++) {
    //    cout << i << ' ' << max_len_bound<ull>::compute({i}) << endl;
    //}

    cout << plog<ull>::compute({3, 3});

    cout << len<ull>::compute({0}) << ' ' << len<ull>::compute({1}) << ' ' << len<ull>::compute({2});
    cout << endl;
    cout << len<ull>::compute({4}) << ' ' << len<ull>::compute({3}) << ' ' << len<ull>::compute({6});
    cout << endl;
    cout << len<ull>::compute({5}) << ' ' << len<ull>::compute({7}) << ' ' << len<ull>::compute({8});
}