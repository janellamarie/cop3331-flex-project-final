#ifndef LEVEL_H
#define LEVEL_H

#include <string>

using namespace std;

class Level {
    protected:
        int current_lvl;
    public:
        // constructors
        Level();
        Level(int current_lvl);
        // getters
        int get_current_lvl() const;

        // setters
        void set_current_lvl(int current_lvl);

        // other functions
        string create_string();
};

#endif