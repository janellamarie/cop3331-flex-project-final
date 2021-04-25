#ifndef FLEX_PROJECT_STAT_H
#define FLEX_PROJECT_STAT_H

#include <string>

using namespace std;

class Stat {
    private:
        string name;
        double value;
    public:
        // constructors
        Stat();
        Stat(string name, double value);
        // getters
        string get_name() const;
        double get_value() const;

        // setters
        void set_name(string name);
        void set_value(double value);

        string create_string();

        // other functions
        friend ostream& operator<< (ostream& out, const Stat& stat);
};

#endif
