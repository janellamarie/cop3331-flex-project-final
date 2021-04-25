#include "Character.h"
#include "Level.h"

#include <iostream>
#include <string>

/*------------ GETTERS ------------*/
string Character::get_name() const {
    return name;
}

string Character::get_element() const {
    return element;
}

int Character::get_rarity() const {
    return rarity;
}

Level Character::get_level() const {
    return level;
}

string Character::get_wpn_type() const {
    return wpn_type;
}

Weapon Character::get_equipped_wpn() const {
    return equipped_wpn;
}

vector<Artifact> Character::get_equipped_artifacts() const {
    return equipped_artifacts;
}

/*------------ SETTERS ------------*/
void Character::set_name(string name) {
    this->name = name;
}

void Character::set_element(string element) {
    this->element = element;
}

void Character::set_rarity(int rarity) {
    this->rarity = rarity;
}

void Character::set_level(Level level) {
    this->level = level;
}

void Character::set_wpn_type(string wpn_type) {
    this->wpn_type = wpn_type;
}

void Character::set_equipped_wpn(Weapon equipped_wpn) {
    this->equipped_wpn = equipped_wpn;
}

void Character::set_equipped_artifacts(vector<Artifact> artifacts) {
    equipped_artifacts = artifacts;
}

/*------------ OTHER FUNCTIONS ------------*/
void Character::copy_character(Character &character) {
    set_name(character.get_name());
    set_rarity(character.get_rarity());
    set_element(character.get_element());
    set_wpn_type(character.get_wpn_type());
    set_equipped_wpn(character.get_equipped_wpn());
    set_equipped_artifacts(character.get_equipped_artifacts());
}

/*
 * Wanderer's Advice (Green) : 1,000 EXP
 * Adventurer's Experience (Blue) : 5,000 EXP
 * Hero's Wit (Purple): 20,000 EXP
 */

void Character::calculate_next_exp(int level_goal) {
    int total = 0;
    // exp table contains all the values to get to each level, for example, index 0 contains the information to get to level 2
    vector<int> exptable = {1000,1325,1700,2150,2625,3150,3725,4350,5000,5700,
                            6450,7225,8050,8925,9825,10750,11725,12725,13775,14875,
                            16800,18000,19250,20550,21875,23250,24650,26100,27575,29100,
                            30650,32250,33875,35550,37250,38975,40750,42575,44425,46300,
                            50625,52700,54775,56900,59075,61275,63525,65800,69125,70475,
                            76500,79050,81650,84275,86950,89650,92400,95175,98000,100875,
                            108950,112050,115175,118325,121525,124775,128075,131400,134775,138175,
                            148700,152375,156075,159825,163600,167425,171300,175225,179175,183175,
                            216225,243025,273100,306800,344600,386950,434425,487625,547200};

    for(int i = level.get_current_lvl()-1; i < level_goal-1; ++i)
        total += exptable.at(i);

    cout << "\nTo get to Level " + to_string(level_goal) + " you need:\n\t"
         << to_string(total) + " EXP\n\t"
         << to_string(total/1000) + " Wanderer's Advice OR\n\t"
         << to_string(total/5000) + " Adventurer's Experience OR\n\t"
         << to_string(total/20000) + " Hero's Wit\n";

    cout << "\nAt WL 8, 6-7 Adventurer's Experience and 6-7 Hero's Wit drops from Ley Line - Blossom of Revelation\n"
         << "To get " + to_string(total/20000) + " Hero's Wit, you need at least: "
         << to_string((total/20000)/6) << " runs (" << to_string(20*((total/20000)/6)) << " Resin). ";
}

// creates a string for text file saving
string Character::create_comma_string() {
    string final, delim;

    // format: name,character level,equipped weapon name,equipped weapon level,artifact 1,artifact 2,artifact 3,artifact 4,artifact 5
    final += name + "," + to_string(level.get_current_lvl()) + "," + equipped_wpn.get_name() + "," + to_string(equipped_wpn.get_level().get_current_lvl()) + ",";

    for(int i = 0; i < 5; i++) {
        if(!equipped_artifacts.empty())
            final += delim + equipped_artifacts.at(i).get_name();
        else
            final += delim;
        delim = ",";
    }

    return final;
}

ostream &operator<<(ostream & out, const Character & character) {
    string stars;

    for (int i = 0; i < character.rarity; ++i)
        stars += '*';

    string temp;

    out << character.name << " (" << stars << ") "
        << "\n\tElement: " << character.element
        << "\n\tLevel: " << character.level.get_current_lvl()
        << "\n\tWeapon Type: " << character.wpn_type
        << "\n\tEquipped Weapon: " << character.equipped_wpn.get_name()
        << " (Lvl. " << character.equipped_wpn.get_level().get_current_lvl() << ") "
        << "\n\tEquipped Artifacts: ";


    string artifacts = "[", delim;
    for(Artifact a : character.equipped_artifacts) {
        artifacts += delim + a.get_name();
        delim = ", ";
    }

    artifacts += "]";

    out << artifacts << endl << endl;

    return out;
}