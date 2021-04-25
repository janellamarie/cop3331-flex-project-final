#include "Domain.h"
#include <iostream>

/*------------ GETTERS ------------*/
string Domain::get_name() {
    return name;
}

int Domain::get_cost() const {
    return cost;
}

vector<Challenge> Domain::get_challenges() {
    return challenges;
}

/*------------ SETTERS ------------*/
void Domain::set_name(string name) {
    this->name = name;
}

void Domain::set_cost(int cost) {
    this->cost = cost;
}

void Domain::set_challenges(vector<Challenge> challenges) {
    this->challenges = challenges;
}

/*------------ OTHERS ------------*/
int Domain::find_challenge_from_drop(const string& drop) {
    int counter = 0;
    for(Challenge c : challenges) {
        for(Item i : c.get_drops()) {
            if(i.get_name().find(drop) != string::npos) {
                return counter;
            }
        }
        ++counter;
    }
    return -1;
}

string Domain::create_string() {
    string final = name + " (" + to_string(cost) + " Resin)" + "\n";

    // iterate through each Challenge object
    for(Challenge c : challenges) {
        string delim;
        final += "\n\t" + c.to_string()
                 + "\n\tDrops: ";
        for(Item i : c.get_drops()) {
            final += delim + i.get_name();
            delim = ", ";
        }
        final += "\n";
    }
    return final;
}

void Domain::farming_details(int quantity, string material) {
    cout << "To farm " << quantity << " of " << material << endl
         << "You need to run " << challenges.at(find_challenge_from_drop(material)).get_name()
         << " at least " << (quantity/2) << " times (" << (Domain::cost*(quantity/2)) << " Resin)."
         << endl;
}