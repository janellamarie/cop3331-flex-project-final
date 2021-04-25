#include "Goal.h"
#include <sstream>

Goal::Goal() {

}

Goal::Goal(string type, string description) {
    set_type(type);
    set_description(description);
    set_complete(false);
}

/*------------ GETTERS ------------*/
string Goal::get_type() const {
    return type;
}

string Goal::get_description() const {
    return description;
}

bool Goal::is_complete() const {
    return complete;
}

/*------------ SETTERS ------------*/
void Goal::set_description(string description) {
    this->description = description;

}

void Goal::set_complete(bool complete) {
    this->complete = complete;
}

void Goal::set_type(string type) {
    this->type = type;
}

/*------------ OTHER ------------*/
ostream &operator<<(ostream &out, const Goal &goal) {
    out << goal.description;
    return out;
}

vector<string> Goal::split_description() {
    string temp;
    stringstream ss(description);

    vector<string> results;

    while(getline(ss, temp, ' '))
        results.push_back(temp);

    return results;
}

bool Goal::operator==(const Goal& rhs) const {
    bool equal = false;
    if(description == rhs.get_description() && type == rhs.get_type())
        equal = true;
    return equal;
}



