#include "Inventory.h"
#include <iostream>

/*------------ GETTERS ------------*/
vector<Character> Inventory::get_characters() const {
    return characters;
}

vector<Item> Inventory::get_items() const {
    return items;
}
vector<Weapon> Inventory::get_weapons() const {
    return weapons;
}

vector<Artifact> Inventory::get_artifacts() const {
    return artifacts;
}

/*------------ SETTERS ------------*/
void Inventory::set_characters(vector<Character> characters) {
    this->characters = characters;
}

void Inventory::set_items(vector<Item> items) {
    this->items = items;
}

void Inventory::set_weapons(vector<Weapon> weapons) {
    this->weapons = weapons;
}

void Inventory::set_artifacts(vector<Artifact> artifacts) {
    this->artifacts = artifacts;
}

/*------------ OTHERS ------------*/
// displays all the Items in the Inventory
void Inventory::display_all_items() {
    int counter = 1;
    for(Item i : items) {
        cout << counter << ": ";
        show_details(i);
        ++counter;
    }
}

// displays all the Characters in the Inventory
void Inventory::display_all_characters() {
    int counter = 1;
    for(Character c : characters) {
        cout << counter << ": " << c;
        ++counter;
    }
}

// displays all the Artifacts in the Inventory
void Inventory::display_all_artifacts() {
    int counter = 1;
    for(Artifact a : artifacts) {
        cout << counter << ": ";
        show_details(a);
        ++counter;
    }
}

// displays all the Weapons in the Inventory
void Inventory::display_all_weapons() {
    int counter = 1;
    for(Weapon w : weapons) {
        cout << counter << ": ";
        show_details(w);
        ++counter;
    }
}

// displays all the Weapons of a given type in the Inventory
void Inventory::display_all_weapons(string type) {
    int counter = 1;
    for(Weapon w : weapons) {
        if(type == w.get_type()) {
            cout << counter << ": ";
            show_details(w);
            ++counter;
        }
    }
}

void Inventory::show_details(Item &item) {
    cout << item.get_details() << endl;
}

// find a Character object with the name to_find in the Inventory, returns the index if it is found, otherwise returns -1
int find_character(string to_find, Inventory& inventory) {
    int index = 0;
    for(Character c : inventory.get_characters()) {
        if(c.get_name() == to_find)
            return index;
        ++index;
    }

    return -1;
}

// find a Weapon object with the name to_find in the Inventory, returns the index if it is found, otherwise returns -1
int find_weapon(string to_find, Inventory& inventory) {
    int index = 0;
    if(isdigit(to_find[0]))
        return stoi(to_find);
    else {
        for(Weapon w : inventory.get_weapons()) {
            if(w.get_name() == to_find)
                return index;
            ++index;
        }
    }

    return -1;
}

void Inventory::add_character(const Character& character) {
    characters.push_back(character);
}

void Inventory::add_weapon(const Weapon& weapon) {
    weapons.push_back(weapon);
}

void Inventory::add_item(const Item &item) {
    items.push_back(item);
}

void Inventory::replace_weapon(int index, Weapon new_weapon) {
    weapons[index] = new_weapon;
}

void Inventory::replace_character(int index, Character new_character) {
    characters[index] = new_character;
}

void Inventory::replace_item(int index, Item new_item) {
    items[index] = new_item;
}

// find an Item object with the name to_find in the Inventory, returns the index if it is found, otherwise returns -1
int find_item(string to_find, Inventory &inventory) {
    int found = 0;
    for (Item i : inventory.items) {
        if (to_find == i.get_name())
            return found;
        ++found;
    }
    return -1;
}

void Inventory::remove_character(int index) {
    characters.erase(characters.begin() + (index-1));
}

void Inventory::remove_weapon(int index) {
    weapons.erase(weapons.begin() + (index-1));
}

void Inventory::remove_item(int index) {
    items.erase(items.begin() + (index-1));
}



