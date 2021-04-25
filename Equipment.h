#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Level.h"
#include "Stat.h"
#include "Item.h"

// abstract class, contains a virtual function
class Equipment : public Item {
protected:
    Level level;
    Stat main_stat;
public:
    // constructors

    // getters
    Level get_level() const;
    Stat get_main_stat() const;

    //setters
    void set_level(Level level);
    void set_main_stat(Stat main_stat);

    virtual void calculate_next_exp(int level_goal) const = 0;
};

#endif