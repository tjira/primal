#include "sieve.h"

bool Sieve::isMersenne(cpp_int p) {
    cpp_int M = (cpp_int(2) << (unsigned int)p - 1) - 1, s = 4;
    for (cpp_int i = 0; i < p - 2; i++) {
        s = (s * s - 2) % M;
    }
    return s == 0 || p == 2;
}

bool Sieve::isPrime(cpp_int n) {
    if (n % 2 == 1) {
        for (cpp_int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
	return n > 2;
    } else return n == 2;
}

cpp_int Sieve::nextMersenne(cpp_int p) {
    for (p = nextPrime(p); !isMersenne(p); p = nextPrime(p)) {} return p;
}

cpp_int Sieve::nextPrime(cpp_int n) {
    for (n += n < 2 ? 2 - n : cpp_int(n % 2 + 1); !isPrime(n); n += 2) {} return n;
}

