#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

#include "FileIO.h"
#include "Equipment.h"
#include "Artifact.h"
#include "Domain.h"
#include "Character.h"
#include "Stat.h"
#include "Character.h"

/*------------ PRIVATE METHODS ------------*/
// database initialization
vector<Domain> FileIO::initialize_domains(const vector<Artifact>& artifacts) {
    fstream file;
    string line;
    vector<Domain> temp_domains;

    for (int i = 1; i <= 10; ++i) {
        int line_counter = 1;

        // open text file
        file.open("domains_" + to_string(i)+".txt");

        // create Domain object
        Domain temp_domain;

        // first line of the text file is the Domain name
        getline(file, line);
        // set the name of the Domain
        temp_domain.set_name(line);
        ++line_counter;

        vector<Challenge> temp_challenges;
        Challenge temp_challenge;

        while (getline(file, line)) {

            switch(line_counter) {
                // set name of Challenge
                case 2: temp_challenge.set_name(line);
                    ++line_counter;
                    break;
                // set drops of Challenge
                case 3: {
                    vector<Item> temp_drops;
                    istringstream ss(line);
                    while (ss) {
                        string temp_item;
                        getline(ss, temp_item, ',');
                        if(!temp_item.empty()) {
                            Item item = Item(temp_item, 0);
                            temp_drops.push_back(item);
                        }
                    }
                    temp_challenge.set_drops(temp_drops);
                    ++line_counter;
                    break;
                }
                // set availability of Challenge
                case 4: {
                    vector<int> temp_avail;
                    istringstream ss(line);
                    string temp_day;
                    while(getline(ss, temp_day, ',')) {
                        string day;
                        if(temp_day == "Every") { // everyday
                            for(int j = 0; j < 7; j++)
                                temp_avail.push_back(j);
                        } else if (temp_day == "Sun")
                            temp_avail.push_back(0);
                        else if (temp_day == "Mon")
                            temp_avail.push_back(1);
                        else if (temp_day == "Tue")
                            temp_avail.push_back(2);
                        else if (temp_day == "Wed")
                            temp_avail.push_back(3);
                        else if (temp_day == "Thu")
                            temp_avail.push_back(4);
                        else if (temp_day == "Fri")
                            temp_avail.push_back(5);
                        else if (temp_day == "Sat")
                            temp_avail.push_back(6);
                    }
                    temp_challenge.set_avail(temp_avail);
                    temp_challenges.push_back(temp_challenge);
                    line_counter = 2;
                    break;
                }
            }
        }

        temp_domain.set_challenges(temp_challenges);
        temp_domains.push_back(temp_domain);

        file.close();
    }

    return temp_domains;
}

vector<Artifact> FileIO::initialize_artifacts() {
    fstream file;
    string line;
    vector<Artifact> artifacts;

    // open text file
    file.open(db_artifacts_file);
    while (getline(file, line)) {

        // create Artifact object
        Artifact temp;

        temp.set_name(line);
        artifacts.push_back(temp);
    }

    file.close();

    return artifacts;
}

vector<Weapon> FileIO::initialize_weapons() {
    fstream file;
    string line;
    vector<Weapon> temp_weapons;

    for(int i = 0; i < 5; ++i) {
        file.open("weapons_" + to_string(i) + ".txt");

        getline(file,line);
        string type = line;

        while (getline(file, line)) {

            // create Weapon object
            Weapon temp;
            string temp_string;

            Stat temp_stat = Stat();

            istringstream ss(line);
            int counter = 1;
            while (getline(ss, temp_string, ',')) {
                switch (counter) {
                    case 1: temp.set_name(temp_string);
                            ++counter;
                            break;
                    case 2: temp.set_rarity(stoi(temp_string));
                            ++counter;
                            break;
                    case 3: temp_stat.set_name(temp_string);
                            ++counter;
                            break;
                    case 4: temp_stat.set_value(stod(temp_string));
                            temp.set_main_stat(temp_stat);
                            ++counter;
                            break;
                    case 5: temp_stat.set_name(temp_string);
                            ++counter;
                            break;
                    case 6: temp_stat.set_value(stod(temp_string));
                            temp.set_substat(temp_stat);
                            ++counter;
                            break;
                }
            }

            temp.set_quantity(0);
            temp.set_type(type);
            temp.set_level(Level(0));
            temp_weapons.push_back(temp);
        }

        file.close();
    }

    return temp_weapons;
}

vector<Character> FileIO::initialize_characters() {
    string line;
    fstream file;

    vector<Character> all_characters;

    // open text file
    file.open(db_characters_file);

    while (getline(file, line)) {
        istringstream ss(line);
        string temp_string;
        // new Character object
        Character temp_char;
        int counter = 1;
        while (getline(ss, temp_string, ',')) {
            switch(counter) {
                // set the name of the Character
                case 1: temp_char.set_name(temp_string);
                        ++counter;
                        break;
                // set the element of the Character
                case 2: temp_char.set_element(temp_string);
                        ++counter;
                        break;
                // set the rarity of the Character
                case 3: temp_char.set_rarity(stoi(temp_string));
                        ++counter;
                        break;
                // set the equipped weapon of the Character, because this is the database, the values are set to 0
                case 4: temp_char.set_wpn_type(temp_string);
                        temp_char.set_equipped_wpn(Weapon(Level(0)));
                        temp_char.set_level(Level(0));
                        all_characters.push_back(temp_char);
                        break;
            }
        }
    }

    file.close();
    return all_characters;
}

// loads all the corresponding Inventory related text files (.txt files with prefix inv_)
Inventory FileIO::load_inventory(const vector<Character>& all_characters, const vector<Weapon>& all_weapons, vector<Artifact> all_artifacts) {
    Inventory temp_inv;

    // load the inv_characters.txt file
    temp_inv.set_characters(load_characters(all_characters, all_weapons, all_artifacts));

    // load the inv_weapons.txt file
    temp_inv.set_weapons(load_weapons(all_weapons));

    // load the inv_artifacts.txt file
    temp_inv.set_artifacts(load_artifacts(all_artifacts));

    return temp_inv;
}

vector<Character> FileIO::load_characters(const vector<Character>& all_characters, const vector<Weapon>& all_weapons, vector<Artifact> all_artifacts) {
    fstream file;
    file.open("inv_characters.txt");

    vector<Character> inv_characters;
    Character temp_character;

    string line;

    while (getline(file, line)) {

        vector<Artifact> temp_equipped_artifacts;

        istringstream ss(line);
        string temp_string;

        int counter = 1;
        Weapon temp_weapon;
        while (getline(ss, temp_string, ',')) {
            switch(counter) {
                // get the Character information from the database and copy it into the new Character object
                case 1: for(Character c : all_characters) {
                            if(c.get_name() == temp_string)
                                temp_character.copy_character(c);
                        }
                        ++counter;
                        break;
                // set the Level of the Character
                case 2: {
                        Level temp_level(stoi(temp_string));
                        temp_character.set_level(temp_level);
                        ++counter;
                        break;
                }
                // copy the data of a Weapon from the database
                case 3: {
                        for(Weapon w : all_weapons) {
                            if(w.get_name() == temp_string){
                                temp_weapon.copy_weapon(w);
                                temp_weapon.set_quantity(temp_weapon.get_quantity()+1);
                            }
                        }
                        ++counter;
                        break;
                }
                // set the Level of the Weapon and set the equipped_wpn field of the Character
                case 4: {
                        Level temp_level = Level(stoi(temp_string));
                        temp_weapon.set_level(temp_level);
                        temp_character.set_equipped_wpn(temp_weapon);
                        ++counter;
                        break;
                }
                // remaining lines are the character's equipped Artifacts
                case 5:
                case 6:
                case 7:
                case 8:
                case 9: for(Artifact a : all_artifacts) {
                            if(a.get_name() == temp_string)
                                temp_equipped_artifacts.push_back(a);
                        }
                        temp_character.set_equipped_artifacts(temp_equipped_artifacts);
                        ++counter;
                        break;
            }
        }

        inv_characters.push_back(temp_character);
    }

    file.close();
    return inv_characters;
}

vector<Weapon> FileIO::load_weapons(const vector<Weapon>& all_weapons) {
    vector<Weapon> inv_weapons;

    fstream file;
    file.open("inv_weapons.txt");

    string line;

    while (getline(file, line)) {
        istringstream ss(line);
        string temp_string;

        int counter = 1;

        Weapon temp_weapon;

        while (getline(ss, temp_string, ',')) {

            switch (counter) {
                // get the Weapon information from the database and copy it into the new Weapon object
                case 1: for(Weapon w : all_weapons) {
                            if(w.get_name() == temp_string) {
                                temp_weapon.copy_weapon(w);
                                temp_weapon.set_quantity(temp_weapon.get_quantity()+1);
                            }
                        }
                        ++counter;
                        break;
                // set the Level of the Weapon
                case 2: {
                        Level temp_level = Level(stoi(temp_string));
                        temp_weapon.set_level(temp_level);
                }
            }
        }
        inv_weapons.push_back(temp_weapon);
    }

    file.close();

    return inv_weapons;
}

vector<Artifact> FileIO::load_artifacts(const vector<Artifact>& all_artifacts) {
    vector<Artifact> temp_artifacts;

    fstream file;
    string line;

    // open text file
    file.open("inv_artifacts.txt");
    while (getline(file, line)) {

        // create Artifact object
        Artifact temp;

        istringstream ss(line);
        string temp_string;

        getline(ss, temp_string, ',');
        temp.set_name(temp_string);
        int counter = 2;
        vector<Stat> substats;
        Stat new_stat;

        while(getline(ss, temp_string, ',')) {
            switch(counter) {
                // set the name of the main_stat of the Artifact
                case 2: new_stat.set_name(temp_string);
                        ++counter;
                        break;
                 // set the name of the value of the main_stat of the Artifact
                case 3: new_stat.set_value(stoi(temp_string));
                        temp.set_main_stat(new_stat);
                        ++counter;
                        break;
                // cases 4 and 5 sets the Stat object's data members
                case 4: new_stat.set_name(temp_string);
                        ++counter;
                        break;
                case 5: new_stat.set_value(stoi(temp_string));
                        substats.push_back(new_stat);
                        if(substats.size() < 5)
                            counter = 4;

                        break;
            }
            temp.set_substats(substats);
        }
        temp_artifacts.push_back(temp);
    }

    file.close();

    return temp_artifacts;

}

vector<Goal> FileIO::load_goals() {
    vector<Goal> temp_goals;
    string type;

    fstream file;
    string line;

    file.open(goal_file);
    if(file.good()) {
        while(getline(file,line)) {
            int count = 0;
            for(char i : line) {
                if(isupper(i) != 0)
                    ++count;
            }

            // push the Goal object into the vector if isn't the capitalized text telling the type of Goal
            if (count != line.length()){
               temp_goals.push_back(Goal(type, line));
            }

            type = line;
        }
    } else {
        cout << "Could not open " << goal_file << endl;
    }
	
    file.close();
	
    return temp_goals;
}

// save the current state of the characters data member of an Inventory object into the text file
void FileIO::save_characters(const vector<Character>& characters) {
    ofstream file;
    file.open("inv_characters.txt");
    for (Character c : characters) {
        file << c.create_comma_string() << endl;
    }
    file.close();
}

// save the current state of the weapons data member of an Inventory object into the text file
void FileIO::save_weapons(const vector<Weapon>& weapons) {
    ofstream file;
    file.open("inv_weapons.txt");
    for (Weapon w : weapons) {
        file << w.create_comma_string() << endl;
    }
    file.close();
}

// save the current state Inventory object into the text file
void FileIO::save_inventory_file(Inventory& inventory) {
    save_characters(inventory.get_characters());
    save_weapons(inventory.get_weapons());
}

// saves all INCOMPLETE goals
void FileIO::save_goal_file(vector<Goal> goals) {
    ofstream file;
    vector<string> types = {"CHARACTER", "WEAPON", "ITEM"};
    file.open(goal_file);
    for(int i = 0; i < 3; ++i) {
        file << types.at(i) << endl;
        for(Goal g : goals) {
            if(g.get_type() == types.at(i) && !g.is_complete())
                file << g << endl;
        }
    }

    file.close();
}
