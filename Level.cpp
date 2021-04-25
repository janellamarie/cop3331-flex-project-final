#include "Level.h"
#include <vector>
#include <iostream>

/*------------ CONSTRUCTORS ------------*/
Level::Level() {

}

Level::Level(int current_lvl) {
    set_current_lvl(current_lvl);
}

/*------------ GETTERS ------------*/
int Level::get_current_lvl() const {
    return current_lvl;
}

/*------------ SETTERS ------------*/
void Level::set_current_lvl(int current_lvl) {
    this->current_lvl = current_lvl;
}

/*------------ OTHER ------------*/
string Level::create_string() {
    return to_string(current_lvl);
}