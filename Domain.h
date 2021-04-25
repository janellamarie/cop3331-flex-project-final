#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>
#include "Challenge.h"

using namespace std;

class Domain {
    private:
        static int cost;
        string name;
        vector<Challenge> challenges;

    public:
        // getters
        string get_name();
        int get_cost() const;
        vector<Challenge> get_challenges();

        // setters
        void set_name(string name);
        void set_cost(int cost);
        void set_challenges(vector<Challenge> challenges);

        // other functions
        int find_challenge_from_drop(const string& drop);
        string create_string();
        void farming_details(int quantity, string material);
};


#endif //DOMAIN_H
