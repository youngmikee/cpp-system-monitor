#include <string>
#include <iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int s, m, h;
    std::ostringstream stream;

    s = seconds % 60;
    m = seconds / 60;
    h = m / 60;
    m = m % 60;

    stream << std::setw(2) << std::setfill('0') << h <<
            ":" << std::setw(2) << std::setfill('0') <<
            m << ":" << std::setw(2) << std::setfill('0') << s;

    return stream.str(); 
}