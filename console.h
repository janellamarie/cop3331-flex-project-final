#ifndef MURACH_CONSOLE_H
#define MURACH_CONSOLE_H

#include <string>
#include <limits>

namespace console {
    // declare general-purpose functions
    double get_double(std::string prompt,
        double min = std::numeric_limits<double>::min(),
        double max = std::numeric_limits<double>::max());
    int get_int(std::string prompt,
        int min = std::numeric_limits<int>::min(),
        int max = std::numeric_limits<int>::max());
    char get_char(std::string prompt,
        bool add_blank_line = true);

}

#endif // MURACH_CONSOLE_H
