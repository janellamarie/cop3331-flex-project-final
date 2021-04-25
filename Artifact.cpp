#include "Artifact.h"
#include <iostream>
#include <sstream>
#include <iomanip>

/*------------ GETTERS ------------*/
vector<Stat> Artifact::get_substats() const {
    return substats;
}

/*------------ SETTERS ------------*/
void Artifact::set_substats(vector<Stat> substats) {
    this->substats = substats;
}

/*------------ OVERRIDE ------------*/
ostream &operator<<(ostream &out, const Artifact& artifact) {
    out << artifact.get_name();
    return out;
}

// overrides the virtual function in Item
string Artifact::get_details() {
    string final = name;
    final += " (" + main_stat.create_string() + ")\n\t\t";
    for(Stat s : substats) {
        final += s.create_string() + "\n\t\t";
    }
    return final;
}

void Artifact::calculate_next_exp(int level_goal) const {
    int total = 0;
    vector<int> exptable;
    switch(rarity) {
        case 1: exptable = {600,750,875,1025};
                break;
        case 2: exptable = {1200,1500,1775,2050};
            break;
        case 3: exptable = {1800,2225,2650,3100,3550,4000,4500,5000,5525,6075,6625,7225};
                break;
        case 4: exptable = {2400,2975,3550,4125,4725,5350,6000,6675,7375,8100,8850,9625,10425,12125,14075,16300};
                break;
        case 5: exptable = {3000,3725,4425,5150,5900,6675,7500,8350,9225,10125,11050,12025,13025,15150,17600,20375,23500,27050,31050,35575};
                break;
    }

    for(int i = level.get_current_lvl()-1; i < level_goal-1; ++i)
        total += exptable.at(i);

    cout << "\nTo get to Level " + to_string(level_goal) + " you need:\n\t"
         << to_string(total/420) + " 1* Artifacts OR\n\t"
         << to_string(total/840) + " 2* Artifacts OR\n\t"
         << to_string(total/1260) + " 3* Artifacts\n\t"
         << to_string(total/2520) + " 4* Artifacts\n\t"
         << to_string(total/3780) + " 5* Artifacts\n\t";
}


