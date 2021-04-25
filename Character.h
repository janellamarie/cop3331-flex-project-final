#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "Level.h"
#include "Stat.h"
#include "Weapon.h"
#include "Artifact.h"

using namespace std;

class Character {
    private:
        string name, element;
        int rarity; // ranges from 3 to 5
        Level level; // min 1, max of 90 when in Inventory
        string wpn_type;
        Weapon equipped_wpn;
        vector<Artifact> equipped_artifacts;

    public:
        // constructor
        // getters
        string get_name() const;
        string get_element() const;
        int get_rarity() const;
        Level get_level() const;
        string get_wpn_type() const;
        Weapon get_equipped_wpn() const;
        vector<Artifact> get_equipped_artifacts() const;

        // setters
        void set_name(string name);
        void set_element(string element);
        void set_rarity(int rarity);
        void set_level(Level level);
        void set_wpn_type(string wpn_type);
        void set_equipped_wpn(Weapon equipped_wpn);
        void set_equipped_artifacts(vector<Artifact> artifacts);

        void copy_character(Character& character);
        void calculate_next_exp(int level_goal);
        string create_comma_string();

        friend ostream& operator<< (ostream& out, const Character& character);
};


#endif