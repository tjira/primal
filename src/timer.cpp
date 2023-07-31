#include "timer.h"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> timepoint;
typedef std::chrono::milliseconds millis;

long Timer::elapsed(timepoint start) {
    return std::chrono::duration_cast<millis>(now() - start).count();
};

std::string Timer::format(long ms) {
    // get the hours, minutes, second and milliseconds
    long hours = ms / 3600000, mins = ms % 3600000 / 60000;
    long secs = ms % 60000 / 1000; ms = ms % 1000;

    // create the stringstream
    std::stringstream ss; ss << std::setfill('0');

    // print the values
    ss << std::setw(2) << hours <<  ":";
    ss << std::setw(2) << mins << ":";
    ss << std::setw(2) << secs << ".";
    ss << std::setw(3) << ms;

    // return the string
    return ss.str();
}

timepoint Timer::now() {
    return std::chrono::high_resolution_clock().now();
};
