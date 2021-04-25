#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <vector>
#include <string>
#include "Equipment.h"

using namespace std;

class Challenge {
    private:
        string name;
        vector<int> avail; // 0 - sunday -> 6 - saturday
        vector<Item> drops;

    public:
        // constructors
        Challenge();
        // getters
        string get_name() const;
        vector<int> get_avail() const;
        vector<Item> get_drops() const;

        // setters
        void set_name(string name);
        void set_avail(vector<int> avail);
        void set_drops(vector<Item> drops);

        string to_string();
};

#endif