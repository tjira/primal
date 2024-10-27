#pragma once

#include <gmpxx.h>

class Gospers {
public:    
    Gospers() : i(1), q(1), r(0), t(1) {} mpz_class next();

private:
    mpz_class i, q, r, t, n;
};
