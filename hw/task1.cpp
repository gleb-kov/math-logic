#include <iostream>
#include <vector>

#include "recursive.h"

using namespace recursive;
using namespace recursive::primitives;
using namespace recursive::operations;

using namespace std;

#include "typelist.h"

int main() {
    using te = TypeList<U<3,1,ull>, U<3,2,ull>>;
    cout << te() << ' ' << Length<te>::value << endl;

    ull a = 3, b = 2;
    cout << "ADD: " << add<ull>::compute({a, b});
    cout << endl;
    cout << "MUL: " << mul<ull>::compute({a, b});
    cout << endl;
    cout << "BOUNDED_SUB1: " << bounded_sub1<ull>::compute({a});
    cout << endl;
    cout << "BOUNDED_SUB: " << bounded_sub<ull>::compute({a, b});
    cout << endl;
    cout << "BOUNDED_SUB(2): " << bounded_sub<ull>::compute({b, a});
    cout << endl;
    cout << "LESS: " << operations::less<ull>::compute({a, b});
    cout << endl;
    cout << "LESS(2): " << operations::less<ull>::compute({b, a});
    cout << endl;
    cout << "DIV: " << operations::div<ull>::compute({a, b});
    cout << endl;
    cout << "MODULO: " << modulo<ull>::compute({a, b});
    cout << endl;
    cout << "POW: " << pow<ull>::compute({a, b});
    cout << endl;
    cout << "PLOG: " << plog<ull>::compute({72, 6});
    cout << endl;
    cout << "FACTORIAL: " << factorial<ull>::compute({a});
    cout << endl;
    cout << "ISPRIME: " << is_prime<ull>::compute({a});
    cout << endl;
    cout << "NEXT PRIME2: " << next_prime<ull>::compute({2});
    cout << endl;
    cout << "NEXT PRIME7: " << next_prime<ull>::compute({7});
    cout << endl;
    cout << "KTH PRIME: " << kth_prime<ull>::compute({3});
    cout << endl;
    cout << "KTH BIT: " << kth_bit<ull>::compute({3, 0}) << ' ' << kth_bit<ull>::compute({3, 1}) << ' ' << kth_bit<ull>::compute({3, 2});
    cout << endl;
    cout << "BITWISE AND: " << bitwise_and<ull>::compute({a, b});
    cout << endl;
    cout << "BITWISE XOR: " << bitwise_xor<ull>::compute({a, b});
}
