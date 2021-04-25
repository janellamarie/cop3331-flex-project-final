#include "Weapon.h"
#include <iostream>
#include <vector>

/*------------ CONSTRUCTORS ------------*/
Weapon::Weapon() {

}

Weapon::Weapon(Level level) {
    set_level(level);
}

/*------------ GETTERS ------------*/
Stat Weapon::get_substat() const {
    return substat;
}

string Weapon::get_type() const {
    return type;
}

/*------------ SETTERS ------------*/
void Weapon::set_substat(Stat substat) {
    this->substat = substat;
}

void Weapon::set_type(string type) {
    this->type = type;
}

/*------------ OTHER ------------*/
ostream &operator<<(ostream & out, Weapon& weapon) {
    out << weapon.get_details();
    return out;
}

void Weapon::copy_weapon(Weapon& weapon) {
    set_name(weapon.get_name());
    set_type(weapon.get_type());
    set_rarity(weapon.get_rarity());
    set_quantity(weapon.get_quantity());
    set_main_stat(weapon.get_main_stat());
    set_substat(weapon.get_substat());
    set_level(weapon.get_level());
}

// overrides the virtual function in Item
string Weapon::get_details() {
    string stars, final;

    for(int i = 0; i < rarity; ++i)
        stars += '*';

    final += name + " (" + stars + ") Lvl. " + to_string(level.get_current_lvl())
             + "\n\t" + main_stat.create_string()
             + "\n\t" + substat.create_string() + "\n";

    return final;
}

// overrides the pure virtual function in Equipment
void Weapon::calculate_next_exp(int level_goal) const {
    int total = 0;
    vector<int> exptable;

    switch(rarity) {
        case 1: exptable = {125,200,275,350,475,575,700,850,1000,1150,1300,1475,1650,1850,2050,2250,2450,2675,2925,3150,
                            3575,3825,4100,4400,4700,5000,5300,5600,5925,6275,6600,6950,7325,7675,8050,8425,8825,9225,9625,10025,
                            10975,11425,11875,12350,12825,13300,13775,14275,14800,15300,16625,17175,17725,18300,18875,19475,20075,20675,21300,21925,
                            23675,24350,25025,25700,26400,27125,27825,28550,29275};
                            break;
        case 2: exptable = {175,275,400,550,700,875,1050,1250,1475,1700,1950,2225,2475,2775,3050,3375,3700,4025,4375,4725,
                            5350,5750,6175,6600,7025,7475,7950,8425,8900,9400,9900,10450,10975,11525,12075,12650,13225,13825,14425,15050,
                            16450,17125,17825,18525,19225,19950,20675,21425,22175,22950,24925,25750,26600,27450,28325,29225,30100,31025,31950,32875,
                            35500,36500,37525,38575,39600,40675,41750,42825,43900};
                            break;
        case 3: exptable = {275,425,600,800,1025,1275,1550,1850,2175,2500,2875,3250,3650,4050,4500,4950,5400,5900,6425,6925,
                           7850,8425,9050,9675,10325,10975,11650,12350,13050,13800,14525,15300,16100,16900,17700,18550,19400,20275,21175,22050,
                           24150,25125,26125,27150,28200,29250,30325,31425,32550,33650,36550,37775,39000,40275,41550,42850,44150,45500,46850,
                           48225,52075,53550,55050,56550,58100,59650,61225,62800,64400,66025,71075,72825,74575,76350,78150,80000,81850,83700,85575,87500,
                           103275,116075,130425,146500,164550,184775,207400,232775,261200};
                            break;
        case 4: exptable = {400,625,900,1200,1550,1950,2350,2800,3300,3800,
                            4350,4925,5525,6150,6800,7500,8200,8950,9725,10500,
                            11900,12775,13700,14650,15625,16625,17650,18700,19775,20900,
                            22025,23200,24375,25600,26825,28100,29400,30725,32075,33425,
                            36575,38075,39600,41150,42725,44325,45950,47600,49300,51000,
                            55375,57225,59100,61025,62950,64925,66900,68925,70975,73050,
                            78900,81125,83400,85700,88025,90375,92750,95150,97575,100050,
                            107675,110325,113000,115700,118425,121200,124000,126825,129675,132575,
                            156475,175875,197600,221975,249300,279950,314250,352700,395775};
                            break;
        case 5: exptable = {600,950,1350,1800,2325,2925,3525,4200,4950,5700,
                            6525,7400,8300,9225,10200,11250,12300,13425,14600,15750,
                            17850,19175,20550,21975,23450,24950,26475,28050,29675,31350,
                            33050,34800,36575,38400,40250,42150,44100,46100,48125,50150,
                            54875,57125,59400,61725,64100,66500,68925,71400,73950,76500,
                            83075,85850,88650,91550,94425,97400,100350,103400,106475,109575,
                            118350,121700,125100,128550,132050,135575,139125,142725,146375,150075,
                            161525,165500,169500,173550,177650,181800,186000,190250,194525,198875,
                            234725,263825,296400,332975,373950,419925,471375,529050,593675};
                            break;
    }

    for(int i = level.get_current_lvl()-1; i < level_goal-1; ++i)
        total += exptable.at(i);

    cout << "\nTo get to Level " + to_string(level_goal) + " you need:\n\t"
         << to_string(total/400) + " Enhancement Ore OR\n\t"
         << to_string(total/2000) + " Fine Enhancement Ore OR\n\t"
         << to_string(total/10000) + " Mystic Enhancement Ore\n\t";
}

// creates a string for text file saving
string Weapon::create_comma_string() {
    return name + "," + to_string(level.get_current_lvl());
}
