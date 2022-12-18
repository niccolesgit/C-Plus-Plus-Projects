#include "order.h" //includes order.h header file
#include <string> //including strings
#include <list> //including list
//constructs order and sets private variables to sent in variables
Order::Order(int id_, int ptime_, const std::list<std::string>& items_){
        id = id_;
        ptime = ptime_;
        items = items_;
    }
//returns the items list
const std::list <std::string>& Order::getItems() const{
    return items;
}
//returns the id of the order
int Order::getID()const{
    return id;
}
//returns the promised time of the order
int Order::getPTime() const {
    return ptime;
}
//decreases the promised time
void Order::changePT(){
    ptime -=1;
}
//returns a bool for the sort functions
bool sort_by_time(Order & order1, Order & order2){
    //sorts based on the time, but if they are the same, sorts based on id 
    return order1.getPTime() < order2.getPTime() || (order1.getPTime() == order2.getPTime() && order1.getID() < order2.getID());
}
//returns a bool for sort functions
bool sort_by_ID(Order & order1, Order & order2){
    //sorts based on id (all are unique)
    return order1.getID() < order2.getID();
}