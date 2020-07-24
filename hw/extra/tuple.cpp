#include <iostream>
#include <vector>

#include "ct_tuple.h"

using namespace ct_tuple;

int main() {
    using t1 = tuple<>;
    using t2 = tuple<10>;
    using t3 = tuple<1, 2, 3>;

    std::cout << is_nil<t1>::value << ' ' << is_nil<t2>::value << ' ' << is_nil<t3>::value;
    std::cout << std::endl;
    std::cout << head<t3>::value;
    std::cout << std::endl;
    std::cout << tail<t3>::value;
    std::cout << std::endl;
    std::cout << kth<t3, 2>();
    std::cout << std::endl;
    std::cout << length<t1>::value << ' ' << length<t2>::value << ' ' << length<t3>::value;
    std::cout << std::endl;
    std::cout << length<conc2<t2, t3>::type>::value;
}
