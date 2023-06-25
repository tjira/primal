cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
project(Primal)

# set output flags
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -pg -O0 -fprofile-arcs -ftest-coverage -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-s -O3")

# static link if on Windows
if(WIN32)
    string(APPEND CMAKE_CXX_FLAGS_RELEASE " -static")
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " -static")
endif()

# include necessary directories
include_directories(include lib)

# find the necessary packages
find_package(OpenMP)

# define the source files
set(PRIMAL )

# add fractoid executable
add_executable(primal src/main.cpp src/sieve.cpp src/timer.cpp)
target_link_libraries(primal gmp gmpxx)

# link OpenMP on build type
if(OPENMP_FOUND AND ${CMAKE_BUILD_TYPE} STREQUAL Release)
    target_link_libraries(primal OpenMP::OpenMP_CXX)
endif()
