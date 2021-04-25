#ifndef ARTIFACT_H
#define ARTIFACT_H

#include <vector>

#include "Equipment.h"
#include "Stat.h"
#include "Level.h"

class Artifact : public Equipment {
    private:
        vector<Stat> substats;

    public:
        // constructors
        // getters
        vector<Stat> get_substats() const;

        // setters
        void set_substats(vector<Stat> substats);

        // override
        string get_details() override;
        void calculate_next_exp(int level_goal) const override;

        friend ostream& operator<< (ostream& out, const Artifact& artifact);
};


#endif