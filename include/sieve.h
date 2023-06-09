#pragma once

#include <gmpxx.h>

class Sieve {
public:
    static mpz_class nextPrime(mpz_class n);
    static bool isMersenne(mpz_class p);
    static mpz_class nextMersenne(mpz_class p);
    static bool isPrime(mpz_class n);
};
