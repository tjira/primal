#include "include/sieve.h"
#include "include/timer.h"
#include <argparse/argparse.hpp>

int main(int argc, char** argv) {
    // initialize the argument parser and container for the arguments
    argparse::ArgumentParser program("Primal", "1.0", argparse::default_arguments::none);

    // add options to the parser
    program.add_argument("-h").help("Display this help message and exit.").default_value(false).implicit_value(true);
    program.add_argument("--timer").help("Display this help message and exit.").default_value(false).implicit_value(true);
    program.add_argument("--prime").help("Generates first n prime numbers.");
    program.add_argument("--mersenne").help("Generates first n Mersenne prime numbers.");
    program.add_argument("--isprime").help("Check if the given number is a prime.");
    program.add_argument("--ismersenne").help("Check if the given number is a Mersenne prime.");

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

    // if generate calculation specified
    if (program.is_used("--prime")) {

        // print the first prime
        std::cout << "1 2 00:00:00.000" << std::endl;

        // run the generate function
        for (mpz_class i = 2, n = 3; i <= mpz_class(program.get("--prime")); i++) {

            // get the prime number
            n = Sieve::nextPrime(n);

            // print the prime number
            std::cout << i.get_str() << " " << n.get_str() << " " << Timer::format(Timer::elapsed(timestamp)) << std::endl;
        }

    // if Mersenne primes requested
    } else if (program.is_used("--mersenne")) {

        // print the first Mersenne prime
        std::cout << "1 2 00:00:00.000" << std::endl;

        // run the generate function
        for (mpz_class i = 2, p = 2; i <= mpz_class(program.get("--mersenne")); i++) {

            // get the next mersenne prime
            p = Sieve::nextMersenne(p);

            // print the prime
            std::cout << i.get_str() << " " << p.get_str() << " " << Timer::format(Timer::elapsed(timestamp)) << std::endl;
        }

    // if prime check calculation specified
    } else if (program.is_used("--isprime")) {

        // check for primality
        bool prime = Sieve::isPrime(mpz_class(program.get("--isprime").c_str(), 10));

        // print the result
        std::cout << "The number " << program.get("--isprime") << " is " << (prime ? "" : "not ") << "a prime." << std::endl;

    // if mersenne check requested
    } else if (program.is_used("--ismersenne")) {

        // check if Mersenne prime
        bool prime = Sieve::isMersenne(mpz_class(program.get("--ismersenne").c_str(), 10));

        // print the result
        std::cout << "The number " << program.get("--ismersenne") << " is " << (prime ? "" : "not ") << "a Mersenne prime." << std::endl;
    }

    // print the total time if requested
    if (program.get<bool>("--timer")) std::cout << "\nExecution time: " <<  Timer::format(Timer::elapsed(timestamp)) << std::endl;
}
