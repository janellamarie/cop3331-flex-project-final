#include <iostream>
#include <string>
#include <limits>

namespace console {
    // declare helper functions
    void discard_remaining_chars();
    void handle_invalid_number();
    bool check_range(double num, double min, double max);

    // define general-purpose functions
    double get_double(std::string prompt, double min, double max) {
        double num = 0.0;
        bool is_valid = false;
        while (!is_valid) {
            std::cout << prompt;
            if (!(std::cin >> num)) {
                handle_invalid_number();
            }
            else {
                discard_remaining_chars();
                is_valid = check_range(num, min, max);
            }
        }
        return num;
    }

    int get_int(std::string prompt, int min, int max) {
        int num = 0;
        bool is_valid = false;
        while (!is_valid) {
            std::cout << prompt;
            if (!(std::cin >> num)) {
                handle_invalid_number();
            }
            else {
                discard_remaining_chars();
                is_valid = check_range(num, min, max);
            }
        }
        return num;
    }

    char get_char(std::string prompt, bool add_blank_line = true) {
        char choice = 'n';
        std::cout << prompt;
        std::cin >> choice;
        if (add_blank_line)
            std::cout << std::endl;

        discard_remaining_chars();
        return choice;
    }

    // define helper functions
    void discard_remaining_chars() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void handle_invalid_number() {
        std::cout << "Error! Invalid number. Try again.\n";
        std::cin.clear();              // clear the failure flag
        discard_remaining_chars();
    }

    bool check_range(double num, double min, double max) {
        if (num < min) {
            std::cout << "Error! Number must be greater than "
                << min << ". Try again.\n";
            return false;
        }
        else if (num > max) {
            std::cout << "Error! Number must be less than "
                << max << ". Try again.\n";
            return false;
        }
        else {
            return true;
        }
    }
}