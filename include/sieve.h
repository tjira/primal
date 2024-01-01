#pragma once

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class Sieve {
public:
    static cpp_int nextPrime(cpp_int n);
    static bool isMersenne(cpp_int p);
    static cpp_int nextMersenne(cpp_int p);
    static bool isPrime(cpp_int n);
};
