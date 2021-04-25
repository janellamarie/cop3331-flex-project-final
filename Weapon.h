#ifndef WEAPON_H
#define WEAPON_H

#include "Equipment.h"
#include "Stat.h"

class Weapon : public Equipment {
    private:
        Stat substat;
        string type;
    public:
        // constructors
        Weapon();
        Weapon(Level level);
        // getters
        Stat get_substat() const;
        string get_type() const;

        // setters
        void set_substat(Stat substat);
        void set_type(string type);

        // override
        void calculate_next_exp(int level_goal) const override;
        string get_details() override;

        // other functions
        void copy_weapon(Weapon& weapon);
        string create_comma_string();

        friend ostream& operator<< (ostream& out, Weapon& weapon);
};

#endif
