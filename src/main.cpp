#include "pi.h"
#include "sieve.h"
#include "timer.h"
#include "argparse.hpp"

int main(int argc, char** argv) {
    // initialize the argument parser and container for the arguments
    argparse::ArgumentParser program("Primal", "1.0", argparse::default_arguments::none);

    // add options to the parser
    program.add_argument("-h", "--help").help("Display this help message and exit.").default_value(false).implicit_value(true);
    program.add_argument("--ismersenne").help("Check if the given exponent corresponds to a Mersenne prime.");
    program.add_argument("--isprime").help("Check if the given number is a prime.");
    program.add_argument("--mersenne").help("Generates nth Mersenne prime number.").default_value("1");
    program.add_argument("--mersennes").help("Generates first n Mersenne prime numbers.").default_value("1");
    program.add_argument("--pidigit").help("Generates nth digit of pi.").default_value("1");
    program.add_argument("--pidigits").help("Generates n digits of pi.").default_value("1");
    program.add_argument("--prime").help("Generates nth prime number.").default_value("1");
    program.add_argument("--primes").help("Generates first n prime numbers.").default_value("1");

    // check if some arguments were privided
    if (argc == 1) throw std::runtime_error("YOU HAVE TO PROVIDE SOME ARGUMENTS");

    // extract the variables from the command line
    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &error) {
        std::cerr << error.what() << std::endl << std::endl << program; return EXIT_FAILURE;
    }

    // print help if the help flag was provided
    if (program.get<bool>("-h")) {
        std::cout << program.help().str(); return EXIT_SUCCESS;
    }

    // start the timer
    auto timestamp = Timer::now();

    // pi generation
    if (auto lim = cpp_int(program.get("--pidigit")); program.is_used("--pidigit")) {
        Gospers pi; for (cpp_int i = 1, n = 1; i <= lim && ((n = pi.next()) || true); i++) {
            if (i == lim) std::printf("%s %s %s\n", i.str().c_str(), n.str().c_str(), Timer::format(Timer::elapsed(timestamp)).c_str());
        }
    } else if (auto lim = cpp_int(program.get("--pidigits")); program.is_used("--pidigits")) {
        Gospers pi; for (cpp_int i = 1, n = 1; i <= lim && ((n = pi.next()) || true); i++) {
            std::printf("%s %s %s\n", i.str().c_str(), n.str().c_str(), Timer::format(Timer::elapsed(timestamp)).c_str());
        }
    }

    // prime generation
    else if (auto lim = cpp_int(program.get("--prime")); program.is_used("--prime")) {
        for (cpp_int i = 1, n = 1; i <= lim && (n = Sieve::nextPrime(n)); i++) {
            if (i == lim) std::printf("%s %s %s\n", i.str().c_str(), n.str().c_str(), Timer::format(Timer::elapsed(timestamp)).c_str());
        }
    } else if (auto lim = cpp_int(program.get("--primes")); program.is_used("--primes")) {
        for (cpp_int i = 1, n = 1; i <= lim && (n = Sieve::nextPrime(n)); i++) {
            std::printf("%s %s %s\n", i.str().c_str(), n.str().c_str(), Timer::format(Timer::elapsed(timestamp)).c_str());
        }
    }

    // mersenne prime generation
    else if (auto lim = cpp_int(program.get("--mersenne")); program.is_used("--mersenne")) {
        for (cpp_int i = 1, p = 1; i <= lim && (p = Sieve::nextMersenne(p)); i++) {
            if (i == lim) std::printf("%s %s %s\n", i.str().c_str(), p.str().c_str(), Timer::format(Timer::elapsed(timestamp)).c_str());
        }
    } else if (auto lim = cpp_int(program.get("--mersennes")); program.is_used("--mersennes")) {
        for (cpp_int i = 1, p = 1; i <= lim && (p = Sieve::nextMersenne(p)); i++) {
            std::printf("%s %s %s\n", i.str().c_str(), p.str().c_str(), Timer::format(Timer::elapsed(timestamp)).c_str());
        }
    }

    // prime check calculation
    else if (cpp_int n = program.is_used("--isprime") ? cpp_int(program.get("--isprime")) : 0; program.is_used("--isprime")) {
        std::printf("%s %s\n", Sieve::isPrime(n) ? "True" : "False", Timer::format(Timer::elapsed(timestamp)).c_str());
    }

    // mersenne prime check calculation
    else if (cpp_int n = program.is_used("--ismersenne") ? cpp_int(program.get("--ismersenne")) : 0; program.is_used("--ismersenne")) {
        std::printf("%s %s\n", Sieve::isMersenne(n) ? "True" : "False", Timer::format(Timer::elapsed(timestamp)).c_str());
    }
}
