#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <vector>

#include "Domain.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Goal.h"

using namespace std;

class FileIO {
    private:
        static string db_artifacts_file;
        static string db_characters_file;
        static string goal_file;

        static vector<Character> load_characters(const vector<Character>& all_characters, const vector<Weapon>& all_weapons, vector<Artifact> all_artifacts);
        static vector<Weapon> load_weapons(const vector<Weapon>& all_weapons);
        static vector<Artifact> load_artifacts(const vector<Artifact>& all_artifacts);
        static void save_characters(const vector<Character>& characters);
        static void save_weapons(const vector<Weapon>& weapons);

    public:
        static vector<Domain> initialize_domains(const vector<Artifact>& artifacts);
        static vector<Artifact> initialize_artifacts();
        static vector<Weapon> initialize_weapons();
        static vector<Character> initialize_characters();
        static Inventory load_inventory(const vector<Character>& all_characters, const vector<Weapon>& all_weapons, vector<Artifact> all_artifacts);
        static vector<Goal> load_goals();
        static void save_inventory_file(Inventory& inventory);
        static void save_goal_file(vector<Goal> goals);
};

#endif
