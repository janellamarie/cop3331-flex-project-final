#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Character.h"
#include "Item.h"

// users' current inventory
class Inventory {
    private:
        vector<Character> characters;
        vector<Weapon> weapons;
        vector<Artifact> artifacts;
        vector<Item> items;

        void show_details(Item& item);

    public:
        // constructors
        // getters
        vector<Character> get_characters() const;
        vector<Item> get_items() const;
        vector<Weapon> get_weapons() const;
        vector<Artifact> get_artifacts() const;

        // setters
        void set_characters(vector<Character> characters);
        void set_items(vector<Item> items);
        void set_weapons(vector<Weapon> weapons);
        void set_artifacts(vector<Artifact> artifacts);

        // other functions
        void display_all_items();
        void display_all_characters();
        void display_all_weapons();
        void display_all_weapons(string type);
        void display_all_artifacts();

        void add_character(const Character& character);
        void add_weapon(const Weapon& weapon);
        void add_item(const Item& item);

        void replace_weapon(int index, Weapon new_weapon);
        void replace_character(int index, Character new_character);
        void replace_item(int index, Item new_item);

        void remove_character(int index);
        void remove_weapon(int index);
        void remove_item(int index);

        friend int find_character(string to_find, Inventory& inventory);
        friend int find_weapon(string to_find, Inventory& inventory);
        friend int find_item(string to_find, Inventory& inventory);


};

#endif
