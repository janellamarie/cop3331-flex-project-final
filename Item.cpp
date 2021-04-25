#include "Item.h"
#include <iostream>
#include <utility>

Item::Item() {

}

Item::Item(string name, int quantity) {
    set_name(std::move(name));
    set_quantity(quantity);
}

/*------------ GETTERS ------------*/
string Item::get_name() const {
    return name;
}

int Item::get_rarity() const {
    return rarity;
}

/*------------ SETTERS ------------*/
void Item::set_name(string name) {
    this->name = name;
}

void Item::set_rarity(int rarity) {
    this->rarity = rarity;
}

int Item::get_quantity() const {
    return quantity;
}

void Item::set_quantity(int quantity) {
    this->quantity = quantity;
}

/*------------ OTHER FUNCTIONS ------------*/
ostream &operator<<(ostream &out, const Item& item) {
    out << item.name << " (" << item.quantity << ") " << endl;
    return out;
}

string Item::get_details() {
    return name + " (" + to_string(quantity) + ")\n";
}
