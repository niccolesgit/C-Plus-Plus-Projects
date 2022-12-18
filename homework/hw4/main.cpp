// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

//include files
#include <cassert>
#include <iostream>
#include <string>
#include <list>

//include my own header files
#include "order.h"
#include "item.h"

//sets typedef to Order and Item Lists
typedef std::list<Order> OrderList;
typedef std::list<Item> KitchenList;
//Needed for CanFillOrder()
typedef std::list <KitchenList::const_iterator> OrderFillList;

//Helper function
//Returns true if order can be fulfilled, and false otherwise. If true, then
//items_to_remove has iterators to kitchen_completed for all items that are used 
//in the order.
bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove);
//function that decreases the time in the orders and cooking list
void ChangeTime(std::list<Order>& orderl, std::list<Item> &fcook);

//provided code:
int main() {
  //creates a list of order objects
  OrderList orders;
  //creates lists of item objects
  KitchenList food_cooking;
  KitchenList food_completed;
  //creates a string for the command
  std::string token;
  //gets the command from the user
  while (std::cin >> token) {
    //if the user add_order
    if (token == "add_order") {
      //sets the id, promised time, and num of items
      int id, promised_time, n_items = 0;
      //creates a string for the items in the order
      std::string next_item;
      //creates a list of strings to hold the order itenms
      std::list <std::string> order_items;
      //gets the id, promised time, and n items
      std::cin >> id >> promised_time >> n_items;
      //makes sure that there are items to store
      assert(n_items > 0);
      //adds the items to the items list
      for (int i = 0; i < n_items; i++) {
        std::cin >> next_item;
        order_items.push_back(next_item);
  
      }
      //creates order object
      Order o (id, promised_time, order_items);
      //prints that it recieved the order
      std::cout << "Received new order #" << o.getID() << " due in " << o.getPTime() << " minute(s):" << std::endl;
      //creates an iterator to go through all the item sin the list
      std::list<std::string>::iterator item_it;
      //loops through and prints all the items in the order
      for(item_it = order_items.begin(); item_it != order_items.end(); item_it++) {
        std::cout << "  " << *item_it << std::endl;
      }
      //adds the order object to the orders list
      orders.push_back(o);
      //sorts the order object by promised time
      orders.sort(sort_by_time);



      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "add_item") {
      //creates a cook time variable
      int cook_time = -1;
      //creates a name variable
      std::string name;
      //gets the cook time and name from the input
      std::cin >> cook_time >> name;
      //make sure the cook time is greater than or equal to 0
      //(since we don't want negative cooking time)
      assert(cook_time >= 0);
      //creates the item object
      Item i (cook_time, name);
      //prints that it's creating a new item in the kitchen
      std::cout << "Cooking new " << i.getName() << " with " << i.getCTime() <<" minute(s) left."<<std::endl;
      //adds it to the cooking list
      food_cooking.push_back(i);
      //sorts the cooking list by cook time 
      food_cooking.sort(sort_by_timec);

      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "print_orders_by_time"){ 
      //prints how many orders by the promised time (already sorted by time)
      std::cout << "Printing " << orders.size() << " order(s) by promised time remaining:" << std::endl;
      //creates an iterator to go through the order list with order objects
      std::list<Order>::iterator order_it;
      //loops through the orders
      for(order_it = orders.begin(); order_it != orders.end(); order_it++) {
        //prints the order and its promised time
        std::cout << "  #" << order_it->getID() << " (" << order_it->getPTime() << " minute(s) left):" << std::endl;
        //sets an empty item list to the items in the order
        std::list<std::string> items = order_it->getItems();
        //creates an iterator for the items
        std::list<std::string>::iterator item_it;
        //loops thrugh the items and prints them
        for(item_it = items.begin(); item_it != items.end(); item_it++) {
        std::cout << "    " << *item_it << std::endl;
        }
      }


      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "print_orders_by_id") {
      //sorts the orders by its ID
      orders.sort(sort_by_ID);
      //prints how many orders there are by ID
      std::cout << "Printing " << orders.size() << " order(s) by ID:" << std::endl;
      //iterator for the order class
      std::list<Order>::iterator order_it;
      //goes through all the orders and prints their ID and minutes
      for(order_it = orders.begin(); order_it != orders.end(); order_it++) {
        std::cout << "  #" << order_it->getID() << " (" << order_it->getPTime() << " minute(s) left):" << std::endl;
        //sets an empry list to the orders items
        std::list<std::string> items = order_it->getItems();
        //iterator for the items
        std::list<std::string>::iterator item_it;
        //loops through the items and prints them
        for(item_it = items.begin(); item_it != items.end(); item_it++) {
        std::cout << "    " << *item_it << std::endl;
        }
      }
      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "print_kitchen_is_cooking") {
      //prints the items in the food_cooking list
      std::cout << "Printing " << food_cooking.size() <<" items being cooked:" << std::endl;
      //creates an iterator for the food cooking list
      std::list<Item>::iterator item_it;
      //loops through the items and prints the name and its cooked time
      for(item_it = food_cooking.begin(); item_it != food_cooking.end(); item_it++) {
        std::cout << "  " << item_it->getName() << " (" << item_it->getCTime() << " minute(s) left)"<< std::endl;
      }
      
      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "print_kitchen_has_completed") {
      //prints the items in the food_cooking list
      std::cout << "Printing " << food_completed.size() <<" completely cooked items:" << std::endl;
      //creates an iterator for the food cooking list
      std::list<Item>::iterator item_it;
      //loops through the items and prints the name and its cooked time
      for(item_it = food_completed.begin(); item_it != food_completed.end(); item_it++) {
        std::cout << "  " << item_it->getName() << std::endl;
      }
      /* YOU MUST FINISH THIS IMPLEMENT22ATION */
    } else if (token == "run_for_time") {
      //creates a run time variable
      int run_time = 0;
      //gets the runtime from the user
      std::cin >> run_time;
      //make sure the cook time is greater than or equal to 0
      //(since we don't want negative run time)
      assert(run_time >= 0);
      //counter to chekc how many minutes have passed
      int minpass = 0;
      //prints the start of run_time
      std::cout << "===Starting run of " << run_time << " minute(s)===" << std::endl;
      //loops while the minutes passed are less than or equal to the run time
      while(minpass <= run_time){
        //checks if the item is cooked:
        //creates an iterator for the cooking items
        std::list<Item>::iterator item_it = food_cooking.begin();
        //while you're not at the end of the list
        while(item_it != food_cooking.end()) {
          //if the cook time is 0
          if(item_it->getCTime() == 0){
            //finishes cooking
            std::cout << "Finished cooking " << item_it->getName() << std::endl;
            //adds the item to the completed food list
            food_completed.push_back(*item_it);
            //removes item from the cooking list
            item_it = food_cooking.erase(item_it);
          }
          else {
            //else, increment to check other items
            item_it++;
          }
      }
      //checks if it can fill the order:
      //resort items by time 
      orders.sort(sort_by_time);
      //creates an iterator for the orders 
      std::list<Order>::iterator order_it = orders.begin();
      //creates an empty OrderFillList list to be sent into the function
      OrderFillList ritems;
      //iterates through the orders
      while(order_it != orders.end()) {
        //gets bool from CanFillOrder function
        bool fill = CanFillOrder(*order_it, food_completed, ritems);
          if (fill){
            //if it can be filled, fills the order
            std::cout << "Filled order #" << order_it->getID() << std::endl;
            //creates an iterator for the iterator list
            OrderFillList::iterator it_it;
          it_it = ritems.begin();
          //erases the order if it is fufilled 
          order_it = orders.erase(order_it);
          //gets an iterator for the food completed list
          std::list<Item>::iterator item2_it = food_completed.begin();
          //loops through to get the item removed
          while(it_it != ritems.end()){
            //dereferences it twice to get the item name
            std::cout <<"Removed a " << (*(it_it))->getName()<< " from completed items." << std::endl;
            //erases the item from the food completed list
            item2_it = food_completed.erase((*(it_it)));
            //increments the iterator to check all of the items that can be removed
            it_it++;
          }
          //increments the item iterator to do it for all orders
          order_it++;

        }else{
          //if can't be filled check if the order expires:
          //if the promised time is 0
          if(order_it->getPTime() == 0){
            //means the order expired
            std::cout << "Order # " << order_it->getID()<<" expired." << std::endl;
            //removes the order from the order list because it expired
            order_it = orders.erase(order_it);
            }
            else {
              //else, iterates to check if other orders expired
              order_it++;
            }
          }
        }
        //if no events occur:
        //increments how many minutes passed
        minpass +=1;
        //if the minutes passes are still less than or equal to the run time
        if (minpass <= run_time) {
          //decreases the time of the orders and food cooking
          ChangeTime(orders, food_cooking);
        }
        
      }
      //after all events have been found after run time, say its complete
      std::cout << "===Run for specified time is complete===" << std::endl;
      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "run_until_next") {
      //starts running until next even occurs
      std::cout << "Running until next event." << std::endl;
      //sets a bool for the event
      bool event = true;
      //counter to check how many minutes have passed
      int minpass = 0;
      //while there isnt an event (meaning true)
      while(event){
        //if there are no orders and no food cooking, then no events can run
        if(orders.size() == 0 && food_cooking.size() == 0){
          std::cout << "No events waiting to process." << std::endl;
          //breaks from the while loop
          break;
        }
        //creates the iterator for the food cooking 
        std::list<Item>::iterator item_it = food_cooking.begin();
        //while it goes through the food cooking
        while(item_it != food_cooking.end()) {
          //if the cook time is 0
          if(item_it->getCTime() == 0){
            //items is finished cooking
            std::cout << "Finished cooking " << item_it->getName() << std::endl;
            //adds it to the food completed list 
            food_completed.push_back(*item_it);
            //removes it from the food cooking list
            item_it = food_cooking.erase(item_it);
            //sets the event to false (meaning the event occured)
            event = false;
            //breaks from the for loop
            break;
          }else{
            //else, iterates through to check if other items are cooked
            item_it++;
            }
          }
        //checks if the event occured
        if(event == false){
          //if it did, print how many minutes passed
          std::cout << minpass << " minute(s) have passed." << std::endl;
          //break from the while loop
          break;
        }
      //if the event didn't occur, check next event:
      //resorts the orders by time again
      orders.sort(sort_by_time);
      //creates an iterator for the orders
      std::list<Order>::iterator order_it = orders.begin();
      //creates an empty OrderFillList list to be sent into the function
      OrderFillList ritems;
      //while going through the order list
      while(order_it != orders.end()) {
        //creates a bool from the CanFillOrder function
        bool fill = CanFillOrder(*order_it, food_completed, ritems);
        //if the order can be filled 
        if (fill){
          //prints that it fills the order
          std::cout << "Filled order #" << order_it->getID() << std::endl;
          //creates an iterator for the OrderFillList
          OrderFillList::iterator it_it;
          it_it = ritems.begin();
          //erases the order from the orders list if its filled
          order_it = orders.erase(order_it);
          //makes an iterator to go through the items in the iterator list
          std::list<Item>::iterator item2_it = food_completed.begin();
          while(it_it != ritems.end()){
            //prints what is removed from the list using a double dereference
            std::cout <<"Removed a " << (*(it_it))->getName()<< " from completed items." << std::endl;
            //removes the item from food completed
            item2_it = food_completed.erase((*(it_it)));
            //increments to check if there is another item needed to be removed
            it_it++;
            //sets the event to be false
            event = false;
            //breaks from the for loop
            break;
          }
          //iteratees through all the orders
          order_it++;
        }else{
          //else, check if the order expires:
          // if the promised time is 0, it expires
          if(order_it->getPTime() == 0){
            //prints the expired order and removes it from the orders list
            std::cout << "Order # " << order_it->getID()<<" expired." << std::endl;
            order_it = orders.erase(order_it);
            //sets the event to false
            event = false;
            //breaks from the for loop
            break;
            }
            //else it iterates through the rest of the orders
            else {
              order_it++;
            }
          }
        }
        //if the event occured
        if(event == false){
          //print how many minutes have passed
          std::cout << minpass << " minute(s) have passed." << std::endl;
          //breaks out of the while loop
          break;
        }
        //increments the minutes that have passed
      minpass++;
      //decreases the time for the orders and food cooking
      ChangeTime(orders, food_cooking);
      }

    }
  }

  return 0;
}
//function that changes (decreases) the promised and cook time
void ChangeTime(std::list<Order>& orderl, std::list<Item> &fcook){
  //creates an iterator that iterates through the orders
  std::list<Order>::iterator order_it;
  for(order_it = orderl.begin(); order_it != orderl.end(); order_it++) {
    //changes the promised time by decreasing it by 1
    order_it->changePT();
  }
  //creates an iterator thta iterates through the cooking items
  std::list<Item>::iterator item_it;
  for(item_it = fcook.begin(); item_it != fcook.end(); item_it++) {
    //changes the cook time by decreasing it by 1
    item_it->changeCT();
  }
}

bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove) {
  items_to_remove.clear(); //We will use this to return iterators in kitchen_completed

  //Simple solution is nested for loop, but I can do better with sorting...

  std::list <std::string> order_items = order.getItems();
  order_items.sort();

  std::list<std::string>::const_iterator item_it;
  std::string prev_item = "";
  KitchenList::const_iterator kitchen_it;

  for (item_it = order_items.begin(); item_it != order_items.end(); item_it++) {
    bool found = false;

    /*Start back at beginnging of list if we're looking for something else
     *Thanks to sorting the order_items list copy, we know we're done with
       whatever kind of item prev_item was!*/
    if (prev_item != *item_it) {
      kitchen_it = kitchen_completed.begin();
      prev_item = *item_it;
    }

    /*Resume search wherever we left off last time (or beginning if it's a
    new kind of item*/
    for (; !found && kitchen_it != kitchen_completed.end(); kitchen_it++) {
      if (kitchen_it->getName() == *item_it) {
        items_to_remove.push_back(kitchen_it);
        found = true;
      }
    }

    //If we failed to satisfy an element of the order, no point continuing the search
    if (!found) {
      break;
    }
  }

  //If we couldn't fulfill the order, return an empty list
  if (items_to_remove.size() != order_items.size()) {
    items_to_remove.clear();
    return false;
  }

  return true;
}


