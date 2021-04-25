#include <iostream>
#include <string>
#include <ctime>

#include "Challenge.h"
#include "Domain.h"
#include "Goal.h"
#include "FileIO.h"
#include "Character.h"
#include "console.h"

using namespace std;

string FileIO::db_artifacts_file = "db_artifacts.txt";
string FileIO::db_characters_file = "db_characters.txt";
string FileIO::goal_file = "goals.txt";

int Domain::cost = 20;

vector<Domain> all_domains;
vector<Artifact> all_artifacts;
vector<Weapon> all_weapons;
vector<Character> all_characters;

vector<Goal> goals;
Inventory inventory;

/*------------ DISPLAY FUNCTIONS ------------*/
// shows all goals, complete and in-progress
void display_all_goals() {
    int counter = 1;
    cout << endl;
    for(Goal g : goals) {
        string complete = g.is_complete() ? " (COMPLETE)" : " (IN-PROGRESS)";
        cout << counter << ": " << g << complete << endl;
        ++counter;
    }
}

// shows all the IN PROGRESS goals
void display_incomplete_goals() {
    int counter = 1;
    cout << endl;
    for(Goal g : goals) {
        if(!g.is_complete()) {
            cout << counter << ": " << g << endl;
            ++counter;
        }
    }
}

// show all the weapons available today
void show_available_domains(const string& d) {
    int day;

    if(d == "Sun")
        day = 0;
    else if(d == "Mon")
        day = 1;
    else if(d ==  "Tue")
        day = 2;
    else if(d == "Wed")
        day = 3;
    else if (d == "Thu")
        day = 4;
    else if(d == "Fri")
        day = 5;
    else if(d == "Sat")
        day = 6;

    vector<Challenge> avail;

    for(Domain d : all_domains)
        for(Challenge c : d.get_challenges())
            for(int i : c.get_avail())
                if(i == day)
                    cout << endl << "\t" << c.get_name() << " (" << d.get_name() << ")";
}

// shows the current day
void show_day() {
    time_t now = time(0);
    string t = ctime(&now), day;

    for(int i = 0; i < 3; ++i)
        day += t.at(i);

    cout << "\nIt is currently " << day << endl << endl
         << "Available Domains: " << endl;

    show_available_domains(day);
}

// display all the weapons in the database
void display_all_weapons(const string& type) {
    for(Weapon w : all_weapons) {
        if(w.get_type() == type)
            cout << w << endl;
    }
}

/*------------ INPUT VALIDATION FUNCTIONS ------------*/
int get_valid_menu_input(const string& prompt, int max) {
    int command;
    bool valid = false;
    do {
        cout << prompt;
        cin >> command;

        if(cin.good() && command <= max)
            valid = true;
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Please enter a valid input." << endl;
        }

    } while(!valid);

    return command;
}

char get_valid_menu_input(const string& prompt) {
    char command;
    bool valid = false;
    do {
        cout << prompt;
        cin >> command;

        if(cin.good() && (command == 'y' || command == 'n'))
            valid = true;
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Please enter a valid input." << endl;
        }

    } while(!valid);

    return command;
}

/*------------ FIND FUNCTIONS ------------*/
// find a domain given an item
int find_domain_from_drop(string drop) {
    int counter = 0;
    for(Domain d : all_domains) {
        for(Challenge c : d.get_challenges()) {
            for(Item i : c.get_drops()) {
                if(i.get_name().find(drop) != string::npos) {
                    return counter;
                }
            }
        }
        ++counter;
    }

    return -1;
}

// find a specific goal from the list of goals
int find_goal(const Goal& to_find) {
    int index = 0;
    for(Goal g : goals) {
        if(to_find == g)
            return index;
        ++index;
    }

    return -1;
}

// finds a weapon from the existing data
int find_weapon_db(const string& to_find) {
    int counter = 0;
    for(Weapon w : all_weapons) {
        if(to_find == w.get_name()) {
            return counter;
        }
        ++counter;
    }
    return -1;
}

// finds a character from the existing data
int find_character_db(const string& to_find) {
    int counter = 0;
    for(Character c : all_characters) {
        if(to_find == c.get_name()) {
            return counter;
        }
        ++counter;
    }
    return -1;
}

vector<Item> get_all_items_db() {
    vector<Item> items;
    for(Domain d : all_domains) {
        for(Challenge c : d.get_challenges()) {
            for(Item i : c.get_drops())
                items.push_back(i);
        }
    }
    return items;
}

// get all Talent Level Up Materials
vector<Item> get_all_talentmat_db() {
    vector<Item> talent_mat;
    vector<int> domain_index = {7,9};
    for(int d : domain_index) {
        for(Challenge c : all_domains.at(d).get_challenges()) {
            for(Item i : c.get_drops())
                talent_mat.push_back(i);
        }
    }
    return talent_mat;
}

// get all Weapon Ascension Materials
vector<Item> get_all_wpnascmat_db() {
    vector<Item> wpnasc_mat;
    vector<int> domain_index = {1,6};
    for(int d : domain_index) {
        for(Challenge c : all_domains.at(d).get_challenges()) {
            for(Item i : c.get_drops()) {
                wpnasc_mat.push_back(i);
            }
        }
    }
    return wpnasc_mat;
}

// find an item from the loaded database
int find_item_db(const string& to_find, int type) {
    int counter = 0;;
    if(type == 1) {
        for(const Item& i : get_all_wpnascmat_db()) {
            if(to_find == i.get_name())
                return counter;
            ++counter;
        }
    } else if(type == 2) {
        for(const Item& i : get_all_talentmat_db()) {
            if (to_find == i.get_name())
                return counter;
            ++counter;
        }
    }
    return -1;
}

// allows the user to modify the Level of a Item object
void modify_weapon(int index_to_modify) {
    Weapon temp_w = inventory.get_weapons().at(index_to_modify-1);
    int new_level = get_valid_menu_input("\nEnter new level (0 to cancel): ", 90);
    if(new_level != 0) {
        Level level = Level(new_level);
        temp_w.set_level(level);
        inventory.replace_weapon(index_to_modify-1, temp_w);
        cout << "Updated: " << endl << temp_w << endl;
    }
}

// allows the user to modify the quantity of a Item object
void modify_item(int index_to_modify) {
    Item i = inventory.get_items().at(index_to_modify-1);
    int new_quantity = get_valid_menu_input("\nEnter new quantity (0 to cancel): ", 999);
    if(new_quantity != 0) {
        Item item = Item(i.get_name(), new_quantity);
        inventory.replace_item(index_to_modify-1, item);
    }
}

// allows the user to modify the details of a Character object
void modify_character(int index_to_modify) {
    cout << inventory.get_characters().at(index_to_modify-1)
         << "What would you like to modify?" << endl
         << "1 - Level" << endl
         << "2 - Equipped Weapon" << endl
         << "3 - Equipped Weapon Level" << endl
         << "0 - Cancel" << endl << endl;

    int command = get_valid_menu_input("Command: ", 3);

    Character temp_c = inventory.get_characters().at(index_to_modify-1);

    // user wants to modify the Level of a Character
    if(command == 1) {
        int new_level = get_valid_menu_input("\nEnter new level (0 to cancel): ", 90);
        if(new_level != 0) {
            Level level = Level(new_level);
            temp_c.set_level(level);
        }
    // user wants to modify the Character's Equipped Weapon (aka equip a new weapoon)
    } else if(command == 2) {
        string temp;
        inventory.display_all_weapons(temp_c.get_wpn_type());
        cout << "Enter Weapon name (0 to cancel): ";
        cin.ignore();
        getline(cin, temp);

        if(temp != "0") {
            // create Weapon object from existing Weapons in Inventory
            Weapon temp_w = inventory.get_weapons().at(find_weapon(temp, inventory));
            temp_c.set_equipped_wpn(temp_w);
        }
    // user wants to modify the Level of the currently equpped weapon
    } else if(command == 3) {
        Weapon temp_w = temp_c.get_equipped_wpn();
        cout << temp_c.get_equipped_wpn().get_details();
        int new_level = get_valid_menu_input("\nEnter new level (0 to cancel): ", 90);
        if(new_level != 0) {
            // create new Level object to set to the Weapon
            Level level = Level(new_level);
            temp_w.set_level(level);
        }
        temp_c.set_equipped_wpn(temp_w);
    }

    inventory.replace_character(index_to_modify-1, temp_c);
    cout << endl << inventory.get_characters().at(index_to_modify-1);
}

/*------------ GOAL-RELATED FUNCTIONS ------------*/
// returns a vector that contains all Goals whose status is "IN PROGRESS"
vector<Goal> get_incomplete_goals() {
    vector<Goal> inc;
    for(Goal g : goals) {
        if (!g.is_complete()) {
            inc.push_back(g);
        }
    }
    return inc;
}

// sets the progress of the goal as complete
void mark_goal_as_complete() {
    char conf, again;
    int goal_index;

    do {
        display_incomplete_goals();
        cout << endl;
        string prompt = "Enter the number of the Goal you want to mark as complete (0 to cancel): ";
        goal_index = get_valid_menu_input(prompt, goals.size());

        if(goal_index != 0) {
            cout << "Do you want to set \"" << get_incomplete_goals().at(goal_index-1) << "\" as complete? (y/n) ";
            cin >> conf;

            if(conf == 'y') {
                // set Goal as complete
                int temp_index = find_goal(get_incomplete_goals().at(goal_index-1));

                // update Goal object
                goals.at(temp_index).set_complete(true);

                if(goals.at(temp_index).get_type() == "CHARACTER") {
                    // update Character in Inventory
                    vector <string> split_goal = goals.at(temp_index).split_description();
                    int char_index = find_character(split_goal.at(1), inventory);
                    if(char_index != -1) {
                        Level level = Level(stoi(split_goal.at(split_goal.size()-1)));
                        Character temp_c = inventory.get_characters().at(char_index);
                        temp_c.set_level(level);

                        // replace the Character object in Inventory at the given index
                        inventory.replace_character(char_index, temp_c);
                        cout << "Updated: " << endl << inventory.get_weapons().at(char_index);
                    } else
                        cout << "Character not found!" << endl;
                } else if (goals.at(temp_index).get_type() == "WEAPON") {
                    // update Character in Inventory
                    vector <string> split_goal = goals.at(temp_index).split_description();

                    string weapon_string;
                    for(string s : split_goal) {
                        if(s == "to")
                            break;

                        if(s != "Get")
                            weapon_string += s + " ";
                    }

                    // append a null character at the end of the string
                    weapon_string.replace(weapon_string.end()-1, weapon_string.end(), "\0");
                    int weapon_index = find_weapon(weapon_string, inventory);

                    if(weapon_index != -1) {
                        Level level = Level(stoi(split_goal.at(split_goal.size()-1)));
                        Weapon temp_w = inventory.get_weapons().at(weapon_index);
                        temp_w.set_level(level);

                        // replace the Weapon object in Inventory at the given index
                        inventory.replace_weapon(weapon_index, temp_w);
                        cout << "Updated: " << endl << inventory.get_weapons().at(weapon_index);
                    } else
                        cout << "Weapon not found!" << endl;
                } else {
                        vector<string> split_goal = goals.at(temp_index).split_description();
                        string item_string;
                        for(string s : split_goal) {
                            if (isdigit(s[0]))
                                break;

                            if (s != "Farm")
                                item_string += s + " ";
                        }

                        // find Item in Inventory, otherwise create an Item
                        int item_index = find_item(item_string, inventory);
                        Item item = Item(item_string, stoi(split_goal.at(split_goal.size()-1)));

                        if(item_index == -1) {
                            inventory.add_item(item);
                            cout << "Updated: " << endl << inventory.get_items().back();
                        } else {
                            inventory.replace_item(item_index, item);
                            cout << "Updated: " << endl << inventory.get_items().at(item_index);
                        }
                }
            }

            again = get_valid_menu_input("Do you want to set another goal as complete? (y/n) ");

            if(again == 'n')
                break;
        }
    } while(goal_index != 0);
}

// views the specifics of the Goal
void view_goal_detail() {
    int goal_index, index;
    cout << endl;

    goal_index = get_valid_menu_input("Which goal would you like to view? (Input their number from the list, 0 to cancel) ", goals.size());

    if(goal_index != 0) {
        Goal temp_goal = goals.at(goal_index-1);
        vector<string> results = temp_goal.split_description();

        // user wants to view a Character-related goal
        if(temp_goal.get_type() == "CHARACTER") {
            index = find_character(results.at(1), inventory);
            if(index != -1)
                inventory.get_characters().at(index).calculate_next_exp(stoi(results.at(4)));
            else
                cout << "Could not find Character in Inventory." << endl;
            cin.get();
        } else if (temp_goal.get_type() == "WEAPON") {
            // get weapon name from Goal description
            string weapon_string;
            for(string s : results) {
                if(s == "to")
                    break;

                if(s != "Get")
                    weapon_string += s + " ";
            }
            // append a null character at the end of the string
            weapon_string.replace(weapon_string.end()-1, weapon_string.end(), "\0");

            index = find_weapon(weapon_string,inventory);
            if(index != -1)
                inventory.get_weapons().at(index).calculate_next_exp(stoi(results.at(results.size()-1)));
            else
                cout << "Could not find Weapon in Inventory." << endl; // Weapon does not exist in Inventory
            cin.get();
        } else if (temp_goal.get_type() == "ITEM") {
            string item_string;
            for(string s : results) {
                if (isdigit(s[0]))
                    break;

                if (s != "Farm")
                    item_string += s + " ";
            }
            item_string.replace(item_string.end()-1, item_string.end(), "\0");

            // find the Domain where the drop can be found
            index = find_domain_from_drop(item_string);

            all_domains.at(index).farming_details(stoi(results.at(results.size()-1)), item_string);
        }
    }
}

void add_weapon_levelling_goal() {
    string name;
    char command, again;
    int level_goal, index;

    do {
        cin.ignore();
        cout << "\nHere are your Weapons: " << endl << endl;
        inventory.display_all_weapons();
        cout << "\nWhich weapon would you like to level? (Number in list/Name, 0 to cancel) ";
        getline(cin, name);

        if(name == "0")
            break;

        index = find_weapon(name, inventory);
        if(index != -1){
            Weapon temp_weapon = inventory.get_weapons().at(index);
            cout << temp_weapon;

            if(temp_weapon.get_level().get_current_lvl() < 90) {
                do {
                    cout << endl;
                    string prompt = "What is your level goal? (Must be greater than " + temp_weapon.get_level().create_string() + ", 0 to cancel) ";
                    level_goal = get_valid_menu_input(prompt, 90);

                    if(level_goal == 0)
                        break;

                    if (level_goal <= temp_weapon.get_level().get_current_lvl())
                        cout << "Level goal must be greater than " << temp_weapon.get_level().create_string() << endl << endl;
                    else if (level_goal > 90)
                        cout << "Max level is 90." << endl << endl;
                    cin.get();
                } while (level_goal <= temp_weapon.get_level().get_current_lvl() || level_goal > 90);

                if(level_goal) // a valid level goal was given
                    temp_weapon.calculate_next_exp(level_goal);

                command = get_valid_menu_input("\n\nWould you like to add this to your goals? (y/n) ");

                if (command == 'y'){
                    string description = "Get " + temp_weapon.get_name() + " to Lvl " + to_string(level_goal);
                    Goal goal = Goal("WEAPON", description);
                    goals.push_back(goal);
                    cout << "Successfully added \"" + description + "\" to goals list.\n";
                    cout << "\nWould you like to add another one? (y/n) ";
                    cin >> again;
                }

                if(again == 'n')
                    break;
            } else {
                cout << "\nWeapon is already at max level!" << endl;
            }
        } else {
            cout << "\nDid not find weapon! Please try again." << endl;
        }

    } while(index == -1 || name != "0" || again == 'y');

}

// adds a Goal to the list about getting a Character to a specific level
void add_character_levelling_goal() {
    string name;
    char command, again;
    int level_goal, index;

    do {
        cin.ignore();
        cout << "\nHere are your Characters: " << endl << endl;
        inventory.display_all_characters();
        cout << "\nWhich character would you like to level? (Name, 0 to cancel) ";
        getline(cin, name);

        if(name == "0")
            break;

        index = find_character(name, inventory);
        if(index != -1){
            Character temp_character = inventory.get_characters().at(index);
            cout << temp_character;

            if(temp_character.get_level().get_current_lvl() < 90) {
                do {
                    string prompt = "What is your level goal? (Must be greater than " + temp_character.get_level().create_string() + ", 0 to cancel) ";
                    level_goal = get_valid_menu_input(prompt, 90);

                    if(level_goal == 0)
                        break;

                    if (level_goal <= temp_character.get_level().get_current_lvl())
                        cout << "Level goal must be greater than " << temp_character.get_level().create_string() << endl << endl;
                    else if (level_goal > 90)
                        cout << "Max level is 90." << endl << endl;
                } while (level_goal <= temp_character.get_level().get_current_lvl() || level_goal > 90);

                if(level_goal) // a valid level goal was given
                    temp_character.calculate_next_exp(level_goal);

                cout << "\n\nWould you like to add this to your goals? (y/n) ";
                cin >> command;

                if (command == 'y'){
                    // Get (Character Name) to Lvl (desired level)
                    string description = "Get " + temp_character.get_name() + " to Lvl " + to_string(level_goal);
                    Goal goal = Goal("CHARACTER", description);
                    goals.push_back(goal);
                    cout << "Successfully added \"" + description + "\" to goals list.\n";
                    cout << "\nWould you like to add another one? (y/n) ";
                    cin >> again;
                }

                if(again == 'n')
                    break;
            } else {
                cout << "\nCharacter is already at max level!" << endl;
            }

        } else {
            cout << "\nDid not find character! Please try again." << endl;
        }
    } while(index == -1 || name != "0" || again == 'y');
}

/* Cecilia Garden, Taishan Mansion, Forsaken Rift, Hidden Palace of Lianshan Formula */
// add a Goal related to Talent Level Up Material
void add_talent_farming_goal() {
    int command;
    char again, command_2;

    do {
        vector<string> material_string = {"Freedom", "Resistance", "Ballad", "Prosperity", "Diligence", "Gold"}; // all types of Talent Level Up material
        cout << "\nTalent Level Up Materials: " << endl;
        for(int i = 0; i < material_string.size(); ++i)
            cout << (i+1) << " - " << material_string.at(i) << endl;

        // ask user the general type of item they want
        command = get_valid_menu_input("\nWhat would you like to add to your goals? (Enter the number from the list, 0 to cancel) ", 6);

        if(command != 0) {
            int found = find_domain_from_drop(material_string.at(command-1));
            if(found != -1) {
                cout << endl;

                int chall_index = all_domains.at(found).find_challenge_from_drop(material_string.at(command-1));
                int counter = 1;

                // display the specific items
                for(Item i : all_domains.at(found).get_challenges().at(chall_index).get_drops()) {
                    cout << counter << " - " << i.get_name() << endl;
                    ++counter;
                }
                int item_index = get_valid_menu_input("What would you like to add to your Goals? (Enter the name, 0 to cancel) ",
                                                       all_domains.at(found).get_challenges().at(chall_index).get_drops().size());
                string temp_string = all_domains.at(found).get_challenges().at(chall_index).get_drops().at(item_index-1).get_name();

                int qty;
                cout << "Enter the amount you need: ";
                cin >> qty;

                all_domains.at(found).farming_details(qty, temp_string);
                Goal goal = Goal("ITEM", "Farm " + temp_string + " " + to_string(qty));
                cout << endl << goal << endl;

                command_2 = get_valid_menu_input("\n\nWould you like to add this to your goals? (y/n) ");

                if (command_2 == 'y'){
                    goals.push_back(goal);
                    cout << "Successfully added \"" + goal.get_description() + "\" to goals list.\n";
                    again = get_valid_menu_input("\nWould you like to add another one? (y/n) ");
                }

                if(again == 'n')
                    break;

            }
        }
    } while (command != 0);
}

// shows the menu for adding a Goal
void add_goal() {
    int command, command_2;
    do {
        cout << "\nWhat would you like to do?" << endl
             << "1 - Character" << endl
             << "2 - Weapon" << endl
             << "3 - Item" << endl
             << "0 - Return to previous menu" << endl << endl;

        command = get_valid_menu_input("Command: ", 3);

        switch(command) {
            case 1: do {
                        cout << "\nWhat would you like to do?" << endl
                             << "1 - Get a Character to a specific level" << endl
                             << "0 - Return to previous menu" << endl << endl;
                        command_2 = get_valid_menu_input("Command: ", 1);

                        switch(command_2) {
                            case 1: add_character_levelling_goal();
                                break;
                        }
                    } while(command_2 != 0);
                    break;
            case 2: do {
                        cout << "\nWhat would you like to do?" << endl
                             << "1 - Get a Weapon to a specific level" << endl
                             << "0 - Return to previous menu" << endl << endl;
                        command_2 = get_valid_menu_input("Command: ", 1);

                        switch(command_2) {
                            case 1: add_weapon_levelling_goal();
                                break;
                        }
                    } while(command_2 != 0);
                    break;
            case 3: do {
                        cout << "\nWhat would you like to do?" << endl
                             << "1 - Add a Talent Level Up material farming goal" << endl
                             << "0 - Return to previous menu" << endl << endl;
                        command_2 = get_valid_menu_input("Command: ", 2);
                        switch(command_2) {
                            case 1: add_talent_farming_goal();
                                    break;
                        }
                    } while(command_2 != 0);
                    break;
        }
    } while(command != 0);
}

// removes a goal from the Goal vector
void remove_goal() {
    char again;
    do {
        cout << "Here are your Goals: " << endl;
        display_all_goals();
        cout << endl;

        // ask the user for the index of the Goal they want to remove
        int to_remove = get_valid_menu_input("Enter the number of the Goal you want to remove: ", goals.size());
        string prompt = "Do you want to remove \"" + goals.at(to_remove-1).get_description() + "\"? (y/n) ";
        char conf = get_valid_menu_input(prompt);
        if(conf == 'y') {
            goals.erase(goals.begin() + (to_remove - 1));
            cout << "Succesfully erased Goal." << endl;
            again = get_valid_menu_input("\nDo you want to remove another Goal? (y/n) ");
        }
    } while(again == 'y');
}

int main() {
    int main_command, temp_command, temp_command_2;

    // initialize database (files in database files folder)
    all_artifacts = FileIO::initialize_artifacts();
    all_domains = FileIO::initialize_domains(all_artifacts);
    all_weapons = FileIO::initialize_weapons();
    all_characters = FileIO::initialize_characters();

    cout << "\n[--- Genshin Impact Grinding Guide ---]" << endl << endl;

    cout << "Ad Astra Abyssosque, Traveller!";
    // load all Invetory related files
    inventory = FileIO::load_inventory(all_characters, all_weapons, all_artifacts, get_all_items_db());
    goals = FileIO::load_goals();

    do {
        cout << "\n[---- MAIN MENU ----]" << endl
             << "1 - Goals" << endl
             << "2 - Inventory" << endl
             << "3 - Database" << endl
             << "0 - Exit" << endl << endl;

        main_command = get_valid_menu_input("Command: ", 3);

        switch(main_command) {
            // Goal menu
            case 1: do {
                    cout << "\n[---- GOAL MENU ----]" << endl
                         << "1 - View Current Goals" << endl
                         << "2 - View All Goals" << endl
                         << "3 - Add a Goal" << endl
                         << "4 - Mark a Goal as complete" << endl
                         << "5 - Remove a Goal" << endl
                         << "0 - Return to previous menu" << endl << endl;

                    temp_command = get_valid_menu_input("Command: ", 6);

                    switch(temp_command) {
                        // view all incomplete goals
                        case 1: display_incomplete_goals();
                                view_goal_detail();
                                cout << endl;
                                break;
                        // view all goals, even complete ones
                        case 2: display_all_goals();
                                cout << endl;
                                break;
                        // add a Goal to the list
                        case 3: add_goal();
                                break;
                        // set a Goal as complete
                        case 4: mark_goal_as_complete();
                                break;
                        // remove Goal from list
                        case 5: remove_goal();
                                break;
                    }
                } while(temp_command != 0);
                break;
            // Inventory menu
            case 2:
                do {
                    int index_modify;
                    // ask user what they want to with the Inventory
                    cout << "\n[--- INVENTORY ---]" << endl
                         << "1 - View Inventory" << endl
                         << "2 - Modify Inventory" << endl
                         << "0 - Return to previous menu" << endl << endl;

                    temp_command = get_valid_menu_input("Command: ", 2);

                    switch(temp_command) {
                        // view Inventory
                        case 1: cout << "\n[--- VIEW INVENTORY ---]" << endl
                                     << "1 - Show all Characters" << endl
                                     << "2 - Show all Weapons" << endl
                                     << "3 - Show all Artifacts" << endl
                                     << "4 - Show all Items" << endl
                                     << "0 - Return to previous menu" << endl << endl;

                            temp_command_2 = get_valid_menu_input("Command: ", 4);

                            // display functions
                            switch (temp_command_2) {
                                case 1: inventory.display_all_characters();
                                    cin.get();
                                    break;
                                case 2: inventory.display_all_weapons();
                                    cin.get();
                                    break;
                                case 3: inventory.display_all_artifacts();
                                    cin.get();
                                    break;
                                case 4: inventory.display_all_items();
                                    cin.get();

                            }
                            break;
                        // modify contents of Inventory
                        case 2: int inv_command;
                                cout << "\n[--- MODIFY INVENTORY ---]" << endl
                                     << "1 - Add to Inventory" << endl
                                     << "2 - Remove from Inventory" << endl
                                     << "3 - Modify object in Inventory" << endl
                                     << "0 - Return to previous menu" << endl << endl;

                                inv_command = get_valid_menu_input("Command: ", 4);

                                int inv_command_2;
                                switch(inv_command) {
                                    case 1: { // user wants to add an object to the Inventory
                                        cout << "\nWhat would you like to add to your Inventory?" << endl
                                             << "1 - Character" << endl
                                             << "2 - Weapon" << endl
                                             << "3 - Item" << endl
                                             << "0 - Cancel" << endl << endl;

                                        inv_command_2 = get_valid_menu_input("Command: ", 3);

                                        int found;
                                        string temp;

                                        switch (inv_command_2) {
                                            // user wants to add a Character to Inventory
                                            case 1: cout << "Enter name of Character to add (0 to cancel): ";
                                                    cin.ignore();
                                                    getline(cin, temp);

                                                    if(temp == "0")
                                                        break;

                                                    // look for the Character in the database
                                                    found = find_character_db(temp);

                                                    if (found != -1) {
                                                        Character temp_c = all_characters.at(found);

                                                        cout << "\nHere are all the Weapons in your inventory that can be equipped: " << endl << endl;
                                                        inventory.display_all_weapons(temp_c.get_wpn_type());

                                                        cout << "Enter Weapon name (0 to cancel): ";
                                                        getline(cin, temp);

                                                        if(temp == "0")
                                                            break;

                                                        // create Weapon object from existing Weapons in Inventory
                                                        Weapon temp_w = inventory.get_weapons().at(find_weapon(temp, inventory));
                                                        temp_c.set_equipped_wpn(temp_w);

                                                        string prompt = "Enter " + temp_c.get_name() + "\'s level (0 to cancel): ";
                                                        int level = get_valid_menu_input(prompt, 90);

                                                        if(level == 0)
                                                            break;

                                                        // create Weapon object for Weapon
                                                        Level temp_lv = Level(level);
                                                        temp_c.set_level(temp_lv);

                                                        // TODO: set equipped artifacts
                                                        inventory.add_character(temp_c);
                                                        cout << "\nAdded " << temp_c;
                                                    } else
                                                        cout << "\nCharacter not found!" << endl;

                                                break;
                                            // user wants to add a Weapon to their Inventory
                                            case 2: cout << "Enter name of Weapon to add (0 to cancel): ";
                                                    cin.ignore();
                                                    getline(cin, temp);

                                                    if(temp == "0")
                                                        break;

                                                    found = find_weapon_db(temp);

                                                    if (found != -1) {
                                                        Weapon temp_w = all_weapons.at(found);

                                                        string prompt = "Enter " + temp_w.get_name() + "\'s level (0 to cancel): ";
                                                        int level = get_valid_menu_input(prompt, 90);

                                                        if(level == 0)
                                                            break;

                                                        // create Weapon object for Weapon
                                                        Level temp_lv = Level(level);
                                                        temp_w.set_level(temp_lv);

                                                        inventory.add_weapon(temp_w);
                                                        cout << "\nAdded " << temp_w;
                                                    } else
                                                        cout << "\nCharacter not found!" << endl;
                                                    break;
                                            case 3: // user wants to add an Item
                                                    cout << "Enter Item type to add: "  << endl
                                                         << "1 - Weapon Ascenscion Material" << endl
                                                         << "2 - Talent Level Up Material" << endl
                                                         << "0 - Cancel" << endl << endl;

                                                    int type = get_valid_menu_input("Command: ", 2);

                                                    cout << "Enter item name (0 to cancel): ";
                                                    cin.ignore();
                                                    getline(cin, temp);

                                                    if(temp == "0")
                                                        break;

                                                    found = find_item_db(temp, type);

                                                    if (found != -1) {
                                                        Item temp_i;
                                                        if(type == 1)
                                                            temp_i = get_all_wpnascmat_db().at(found);
                                                        else
                                                            temp_i = get_all_talentmat_db().at(found);
                                                            cout << temp_i;

                                                        string prompt = "Enter " + temp_i.get_name() + "\'s quantity (0 to cancel): ";
                                                        int qty = get_valid_menu_input(prompt, 999);

                                                        if(qty == 0)
                                                            break;

                                                        temp_i.set_quantity(qty);
                                                        inventory.add_item(temp_i);
                                                        cout << "\nAdded " << temp_i.get_name() << " (" << temp_i.get_quantity() << ") ";
                                                    } else
                                                        cout << "\nItem not found!" << endl;
                                                break;
                                        }

                                        break;
                                    // remove from Inventory
                                    } case 2: {
                                        cout << "\nWhat would you like to remove from your Inventory?" << endl
                                             << "1 - Character" << endl
                                             << "2 - Weapon" << endl
                                             << "3 - Item" << endl
                                             << "0 - Cancel" << endl << endl;

                                        inv_command_2 = get_valid_menu_input("Command: ", 3);

                                        int temp;
                                        switch (inv_command_2) {
                                            case 1: // user wants to remove a Character from Inventory
                                                inventory.display_all_characters();
                                                temp = get_valid_menu_input("Enter number of Character to remove (0 to cancel): ", inventory.get_characters().size());

                                                if(temp == 0)
                                                    break;

                                                inventory.remove_character(temp);
                                                inventory.display_all_characters();
                                                break;

                                            case 2: // user wants to remove a Weapon from Inventory
                                                inventory.display_all_weapons();
                                                temp = get_valid_menu_input("Enter number of Weapon to remove (0 to cancel): ", inventory.get_weapons().size());

                                                if(temp == 0)
                                                    break;

                                                inventory.remove_weapon(temp);
                                                inventory.display_all_weapons();
                                                break;

                                            case 3: // user wants to remove an Item from Inventory
                                                inventory.display_all_items();
                                                temp = get_valid_menu_input("Enter number of Character to remove (0 to cancel): ", inventory.get_items().size());

                                                if(temp == 0)
                                                    break;

                                                inventory.remove_item(temp);
                                                inventory.display_all_items();
                                                break;
                                        }
                                    } break;
                                    case 3: { // ask user what type of object they want to modify
                                        cout << "\nWhat would you like to modify from your Inventory?" << endl
                                             << "1 - Character" << endl
                                             << "2 - Weapon" << endl
                                             << "3 - Item" << endl
                                             << "0 - Cancel" << endl << endl;

                                        inv_command_2 = get_valid_menu_input("Command: ", 3);

                                        int temp;
                                        switch (inv_command_2) {
                                            case 1: // user wants to modify a Character from Inventory
                                                inventory.display_all_characters();
                                                temp = get_valid_menu_input("Enter number of Character to modify (0 to cancel): ",
                                                        inventory.get_characters().size());

                                                if (temp == 0)
                                                    break;

                                                modify_character(temp);
                                                break;

                                            case 2: // user wants to modify a Weapon from Inventory
                                                inventory.display_all_weapons();
                                                temp = get_valid_menu_input(
                                                        "Enter number of Weapon to modify (0 to cancel): ",
                                                        inventory.get_weapons().size());

                                                if (temp == 0)
                                                    break;

                                                modify_weapon(temp);
                                                inventory.display_all_weapons();
                                                break;

                                            case 3: // user wants to modify an Item from Inventory
                                                inventory.display_all_items();
                                                temp = get_valid_menu_input(
                                                        "Enter number of Item to modify (0 to cancel): ",
                                                        inventory.get_items().size());

                                                if (temp == 0)
                                                    break;

                                                modify_item(temp);
                                                inventory.display_all_items();
                                                break;
                                        }
                                        break;
                                    }
                                }

                            break;
                    }
                } while (temp_command != 0);
                break;
            // user wants to view data from the loaded database
            case 3: do {
                        cout << "\n[--- DATABASE ---]" << endl
                             << "1 - Find a Character" << endl
                             << "2 - Find a Weapon" << endl
                             << "3 - Find an Item" << endl
                             << "4 - Find Domain by Availability" << endl
                             << "0 - Return to previous menu" << endl << endl;
                        temp_command = get_valid_menu_input("Command: ", 4);

                        char again;
                        string to_find;
                        int found;

                        switch(temp_command) {
                            case 1: do {
                                        cout << "\nEnter Character name (0 to cancel): ";
                                        cin.ignore();
                                        getline(cin, to_find);
                                        if(to_find == "0")
                                            break;
                                        found = find_character_db(to_find);
                                        if(found != -1)
                                            cout << endl << all_characters.at(find_character_db(to_find));
                                        else
                                            cout << "Character not found!" << endl;
                                        again = get_valid_menu_input("\nWould you like to look for another Character? (y/n) ");
                                    } while (again == 'y');
                                    break;
                            case 2: do {
                                        cout << "\nEnter Weapon name (0 to cancel): ";
                                        cin.ignore();
                                        getline(cin, to_find);

                                        if(to_find == "0")
                                            break;

                                        found = find_weapon_db(to_find);
                                        if(found != -1)
                                            cout << endl << all_weapons.at(find_weapon_db(to_find));
                                        else
                                            cout << "Weapon not found!" << endl;
                                        again = get_valid_menu_input("\nWould you like to look for another Weapon? (y/n) ");
                                    } while (again == 'y');
                                    break;
                            case 3: do {
                                        cout << "\nEnter Item name (0 to cancel): ";
                                        cin.ignore();
                                        getline(cin, to_find);
                                        if(to_find == "0")
                                            break;
                                        found = find_domain_from_drop(to_find);
                                        if(found != -1)
                                            cout << all_domains.at(found).create_string();
                                        else
                                            cout << "Item not found!" << endl;
                                        again = get_valid_menu_input("\nWould you like to look for another Item? (y/n) ");
                                    } while (again == 'y');
                                    break;
                            case 4: cout << "Domains available today: ";
                                    show_day();
                                    cout << endl;
                                    break;
                        }
                    } while(temp_command != 0);
                    break;
        }
    } while (main_command != 0);

    FileIO::save_goal_file(goals);
    FileIO::save_inventory_file(inventory);

    return 0;
}