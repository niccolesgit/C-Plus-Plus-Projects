#ifndef kitchenlist_h //header file guard
#define kitchenlist_h //header file guard 
#include <string> //includes strings
#include <list>//includes lists
//creates Item class
class Item{
    public:
    //constructor
    Item( int& c_time, std::string& n);
    //accessors
    int getCTime() const;
    std::string getName() const;
    //modifiers
    void changeCT();

    //private variables
    private:
    std::string name;
    int cook_time;
};
//bool for sorting
bool sort_by_timec(Item & item1, Item & item2);


#endif