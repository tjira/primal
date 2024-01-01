#include "pi.h"

cpp_int Gospers::next() {
    // initialize n
    n = (q * (27 * i - 12) + 5 * r) / (5 * t);

    // do the loop
    while(n != (q * (675 * i - 216) + 125 * r) / (125 * t)) {
        // calculate r
        r = 3 * (3 * i + 1) * (3 * i + 2) * ((5 * i - 2) * q + r);

        // calculate q and t
        q = i * (2 * i - 1) * q; t = 3 * (3 * i + 1) * (3 * i + 2) * t;

        // increment i and calculate n
        i++, n = (q * (27 * i - 12) + 5 * r) / (5 * t);
    }

    // calculate q and r
    q = 10 * q, r = 10 * r - 10 * n * t;

    // return the result
    return n;
}
