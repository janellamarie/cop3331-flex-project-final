#ifndef GOAL_H
#define GOAL_H

#include <string>
#include <vector>

using namespace std;

class Goal {
    private:
        string type, description;
        bool complete;

    public:
        // constructors
        Goal();
        Goal(string type, string description);

        // getters
        string get_type() const;
        string get_description() const;
        bool is_complete() const;

        // setters
        void set_type(string type);
        void set_description(string description);
        void set_complete(bool complete);
        bool operator==(const Goal & rhs) const;

        vector<string> split_description();
        friend ostream& operator<< (ostream& out, const Goal& goal);
};


#endif //GOAL_H
