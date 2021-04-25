#include "Stat.h"
#include <string>
#include <sstream>
#include <iomanip>

/*------------ CONSTRUCTORS ------------*/
Stat::Stat() {

}

Stat::Stat(string name, double value) {
    set_name(name);
    set_value(value);
}

/*------------ GETTERS ------------*/
string Stat::get_name() const {
    return name;
}

double Stat::get_value() const {
    return value;
}

/*------------ SETTERS ------------*/
void Stat::set_name(string name) {
    this->name = name;
}

void Stat::set_value(double value) {
    this->value = value;
}

/*------------ OTHER FUNCTIONS ------------*/
ostream &operator<<(ostream &out, const Stat &stat) {
    out << setw(18) << left << stat.name << stat.value;
    return out;
}

string Stat::create_string() {
    stringstream stream;
    stream << setw(18) << left << name << setprecision(2) << value;
    return stream.str();
}