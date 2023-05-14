#include "../include/sieve.h"

bool Sieve::isMersenne(mpz_class p) {
    mpz_class M = (mpz_class(2) << p.get_ui() - 1) - 1, s = 4;
    for (mpz_class i = 0; i < p - 2; i++) {
        s = (s * s - 2) % M;
    }
    return s == 0;
}

bool Sieve::isPrime(mpz_class n) {
    for (mpz_class i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

mpz_class Sieve::nextMersenne(mpz_class p) {
    for (p = nextPrime(p); !isMersenne(p); p = nextPrime(p)) {} return p;
}

mpz_class Sieve::nextPrime(mpz_class n) {
    for (n += n % mpz_class(2) + 1; !isPrime(n); n += 2) {} return n;
}

