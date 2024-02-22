# minimum cmake requirement
cmake_minimum_required(VERSION 3.18)

# project name
project(Primal)

# include plugins
include(FetchContent)

# set cmake flags
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

# set compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -pg -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-mavx -s -O3")

# static link on windows
if (WIN32)
    string(APPEND CMAKE_CXX_FLAGS_RELEASE " -static")
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " -static")
endif()

# declare libraries
FetchContent_Declare(argparse SYSTEM GIT_REPOSITORY https://github.com/p-ranav/argparse.git GIT_TAG ac4c578f6020d5164f66ccb26b4727dea657a12b)

# fetch the libraries
FetchContent_MakeAvailable(argparse)

# find packages
find_package(OpenMP REQUIRED)
find_package(Boost REQUIRED)

# include directories
include_directories(include ${argparse_SOURCE_DIR}/include/argparse)

# add fractoid executable
add_executable(primal src/main.cpp src/pi.cpp src/sieve.cpp src/timer.cpp)
target_link_libraries(primal Boost::boost)

# link OpenMP on build type
if(CMAKE_BUILD_TYPE STREQUAL Release)
    target_link_libraries(primal OpenMP::OpenMP_CXX)
endif()
