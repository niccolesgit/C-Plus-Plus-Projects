#include "item.h" //includes item header file
#include <string> //including strings 
#include <list> //including lists 
//Item class constructors
Item::Item( int& c_time, std::string& n){
        cook_time = c_time;
        name = n;
}
//returns the cook time
int Item::getCTime() const{
    return cook_time;
}
//returns the item name
std::string Item::getName() const{
    return name;
}
//decreases the cook time
void Item::changeCT(){
    cook_time -=1;
}

//bool used for sorting functions
bool sort_by_timec(Item & item1, Item & item2){
    //sorts by cook time, but if the same, sorts by name 
    return item1.getCTime() < item2.getCTime() || (item1.getCTime() == item2.getCTime() && item1.getName() < item2.getName());
}