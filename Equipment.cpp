#include "Equipment.h"

/*------------ SETTERS ------------*/
void Equipment::set_level(Level level) {
    this->level = level;
}

void Equipment::set_main_stat(Stat main_stat) {
    this->main_stat = main_stat;
}

/*------------ GETTERS ------------*/
Level Equipment::get_level() const {
    return level;
}

Stat Equipment::get_main_stat() const {
    return main_stat;
}
