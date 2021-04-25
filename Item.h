#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

// abstract class
class Item {
    protected:
        string name;
        int rarity, // range is 1 to 5
            quantity;
    public:
        // constructors
        Item();
        Item(string name, int quantity);
        // getters
        string get_name() const;
        int get_rarity() const;
        int get_quantity() const;
        int get_type() const;

        // setters
        void set_name(string name);
        void set_rarity(int rarity);
        void set_quantity(int quantity);

        virtual string get_details();

        friend ostream& operator<< (ostream& out, const Item& item);
};

#endif
