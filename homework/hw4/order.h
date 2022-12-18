#ifndef order_h //header guard
#define order_h //header guard
#include <string> //includes strings
#include <list>//includes list
//creates order class
class Order{
    public:
    //constructor
    Order(int id_, int ptime_, const std::list<std::string>& items_);
    //accessors
    const std::list <std::string>& getItems() const;
    int getID() const;
    int getPTime() const;
    //modifiers
    void changePT();

    //private variables for functions
    private:
    int id;
    int ptime;
    std::list <std::string> items;

};
//creates bools for sorting
bool sort_by_time(Order & order1, Order & order2);
bool sort_by_ID(Order & order1, Order & order2);
#endif //end guard