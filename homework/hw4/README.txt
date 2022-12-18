HOMEWORK 4: Pizza Event SimulaTOr (PESto)


NAME: Nicole Lee


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Kacy Adams, David Vasquez, Bhavya Chavali, William Zheng, Alexa Shaw, ALAC & Office Hour Mentors/TAs,
Submitty Notes on Lists/Iterators

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 36


ORDER NOTATION:
For each function, using the variables:

  c = number of items still being cooked
  d = number of items completely cooked, but not yet added to an order
  m = number of different item names available
  o = number of orders that have not been filled and are not expired
  p = min number of items per order
  q = max number of items per order

Include a short description of your order notation analysis.

add_order:
O(m)*(O(m)+O(1)+O(ologo))
Goes through a loop of string items, pushes it back and sorts

add_item:
O(1)*O(clogc)
Only pushes back and sorts the item

print_orders_by_time:
O(o)*O(m)
Loops through the orders and loops through the items
print_orders_by_id:
O(o)*O(m)
loops through the orders and loops through the items to print
print_kitchen_is_cooking:
O(c)
Only goes through 1 for loop to print what is cooking

print_kitchen_has_completed:
O(d)
Only goes through 1 for loop to print what the kitchen has completed

run_until_next:
(O(c)*(O(1))*O(ologo)*(O(c)+O(1)+O(1))*(O(o)*O(d)*O(1)+O(1))
Loops through the cooked items, erases and pushes back if occurs
sorts before checking if the order can be filled
loops through to check if the order can be filled
if so it erases the order
else it
loops through the orders and erases the order if expired

run_for_time:
O(q)*((O(c)O(1))*O(ologo)*(O(c)+O(1)+O(1))*(O(o)*O(d)*O(1)+O(1)))
BUT loops through a specified times
Loops through the cooked items, erases and pushes back if occurs
sorts before checking if the order can be filled
loops through to check if the order can be filled
if so it erases the order
else it
loops through the orders and erases the order if expired



MISC. COMMENTS TO GRADER:  
Wasn't sure if I was supposed to make functions for run_until_time & run_until_next,
should I in the future?






