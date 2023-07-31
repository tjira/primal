#include "sieve.h"
#include "timer.h"
#include "argparse.hpp"

int main(int argc, char** argv) {
    // initialize the argument parser and container for the arguments
    argparse::ArgumentParser program("Primal", "1.0", argparse::default_arguments::none);

    // add options to the parser
    program.add_argument("-h", "--help").help("Display this help message and exit.").default_value(false).implicit_value(true);
    program.add_argument("--ismersenne").help("Check if the given number is a Mersenne prime.");
    program.add_argument("--isprime").help("Check if the given number is a prime.");
    program.add_argument("--mersenne").help("Generates first n Mersenne prime numbers.");
    program.add_argument("--prime").help("Generates first n prime numbers.");
    program.add_argument("--timer").help("Prints the elapsed time at the end of the calculation.").default_value(false).implicit_value(true);

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

    // prime generation
    if (program.is_used("--prime")) {
        for (mpz_class i = 1, n = 2; i <= mpz_class(program.get("--prime")); i++, n = Sieve::nextPrime(n)) {
            std::cout << i.get_str() << " " << n.get_str() << " " << Timer::format(Timer::elapsed(timestamp)) << std::endl;
        }
    }

    // mersenne prime generation
    else if (program.is_used("--mersenne")) {
        for (mpz_class i = 1, p = 2; i <= mpz_class(program.get("--mersenne")); i++, p = Sieve::nextMersenne(p)) {
            std::cout << i.get_str() << " " << p.get_str() << " " << Timer::format(Timer::elapsed(timestamp)) << std::endl;
        }
    }

    // prime check calculation
    else if (mpz_class n = program.is_used("--isprime") ? mpz_class(program.get("--isprime")) : 0; program.is_used("--isprime")) {
        std::cout << "The number " << program.get("--isprime") << " is " << (Sieve::isPrime(n) ? "" : "not ") << "a prime." << std::endl;
    }

    // mersenne prime check calculation
    else if (mpz_class n = program.is_used("--ismersenne") ? mpz_class(program.get("--ismersenne")) : 0; program.is_used("--ismersenne")) {
        std::cout << "The number 2^" << program.get("--ismersenne") << "-1 is " << (Sieve::isMersenne(n) ? "" : "not ") << "a Mersenne prime." << std::endl;
    }

    // print the total time if requested
    if (program.get<bool>("--timer")) std::cout << "\nExecution time: " <<  Timer::format(Timer::elapsed(timestamp)) << std::endl;
}
