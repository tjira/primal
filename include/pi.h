#pragma once

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class Gospers {
public:    
    // contructor
    Gospers() : i(1), q(1), r(0), t(1) {}

    // getters
    cpp_int next();

private:
    cpp_int i, q, r, t, n;
};
