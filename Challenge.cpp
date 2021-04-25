#include "Challenge.h"
#include <iostream>

// constructors
Challenge::Challenge() = default;

// getters

string Challenge::get_name() const {
    return name;
}

vector<int> Challenge::get_avail() const {
    return avail;
}

vector<Item> Challenge::get_drops() const {
    return drops;
}

// setters
void Challenge::set_name(string name) {
    this->name = name;
}

void Challenge::set_avail(vector<int> avail) {
    this->avail = avail;
}

void Challenge::set_drops(vector<Item> drops) {
    this->drops = drops;
}

string Challenge::to_string() {
    string final = name;
    string days, delim;
    days = "Availability: ";
    for (int x : avail) {
        switch (x) {
            case 0: days += delim + "Sunday";
                    delim = ", ";
                    break;
            case 1: days += delim + "Monday";
                    delim = ", ";
                    break;
            case 2: days += delim + "Tuesday";
                    delim = ", ";
                    break;
            case 3: days += delim + "Wednesday";
                    delim = ", ";
                    break;
            case 4: days += delim + "Thursday";
                    delim = ", ";
                    break;
            case 5: days += delim + "Friday";
                    delim = ", ";
                    break;
            case 6: days += delim + "Saturday";
                    delim = ", ";
                    break;
        }
    }

    return final + "\n\t" + days;
}


