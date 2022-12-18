//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN 
//       CHANGES TO MoreTests()
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <list>

#include "unrolled.h"

// ===================================================================
// This function compares an unrolled linked list to an STL list.  It
// returns true iff the lists are the same size, and contain the same
// elements in the same order.
template <class T>
bool SAME(UnrolledLL<T>& a, std::list<T> &b) { 
  if (a.size() != b.size()) return false;
  typename UnrolledLL<T>::iterator a_iter = a.begin();
  typename std::list<T>::iterator b_iter = b.begin();
  while (a_iter != a.end() && b_iter != b.end()) {
    if (*a_iter != *b_iter) return false;
    a_iter++;
    b_iter++;
  }
  assert (a_iter == a.end() && b_iter == b.end()); 
  return true;
}


// ===================================================================
void BasicTests();
void MoreTests();

int main() {
  BasicTests();
  MoreTests();
  std::cout << "Finished MoreTests()" << std::endl;
}


// ===================================================================
// NOTE: Your internal data structure may be different (& thus print
// differently), depending on how you implement your internal member
// functions.  That's ok!
void BasicTests() {

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.
  UnrolledLL<int> a;
  std::list<int> b;
  for (int i = 10; i < 30; ++i) {
    a.push_back(i);
    b.push_back(i);
  }  

  // iterate through the integers and print them out
  std::cout << "the integers from 10->29" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  assert (SAME(a,b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert (a.size() == 20);
  assert (a.front() == 10);
  assert (a.back() == 29);
  a.pop_front(); 
  b.pop_front();
  assert (a.size() == 19);
  assert (a.front() == 11);
  a.pop_back();
  b.pop_back();
  assert (a.size() == 18);
  assert (a.back() == 28);
  a.print(std::cout);
  std::cout << std::endl;
  assert (SAME(a,b));

  // more editing
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  a.pop_back();
  b.pop_back();
  a.print(std::cout);
  assert (a.size() == 12);
  assert (a.front() == 16);
  assert (a.back() == 27);
  a.push_front(90);
  a.push_front(91);
  a.push_front(92);
  a.push_front(93);
  b.push_front(90);
  b.push_front(91);
  b.push_front(92);
  b.push_front(93);
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 16);
  assert (a.front() == 93);
  assert (SAME(a,b));

  // erase the multiples of 3
  std::cout <<"erase the multiples of 3" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter % 3 == 0) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter % 3 == 0) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 10);
  assert (SAME(a,b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = a.insert(itr,77);
      itr++;
    } 
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = b.insert(itr,77);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 14);
  assert (SAME(a,b));
  
  // overflowing an insert
  std::cout << "insert that overflows the node" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 17) {
      itr = a.insert(itr,88);
      itr++;
    } 
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 17) {
      itr = b.insert(itr,88);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 15);
  assert (SAME(a,b));

  // more erasing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter == 77 || *a_iter == 16 || *a_iter == 88) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter == 77 || *b_iter == 16 || *b_iter == 88) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 9);
  assert (SAME(a,b));

}

// MORE TESTS
// ===================================================================
void MoreTests() {
  std::cout << "Trying Out More Tests: Double Datatype" << std::endl;
  //creates new UnrolledLL and lists for double datatype
  UnrolledLL<double> c;
  std::list<double> d;
  //pushing back random decimals
  c.push_back(2.25);
  d.push_back(2.25);
  c.push_back(2.67);
  d.push_back(2.67);
  c.push_back(3.01);
  d.push_back(3.01);
  c.push_back(3);
  d.push_back(3);
  c.push_back(4.45);
  d.push_back(4.45);
  c.push_back(5.35);
  d.push_back(5.35);
  c.push_back(5.98);
  d.push_back(5.98);
  c.push_back(6.72);
  d.push_back(6.72);
  c.push_back(8.84);
  d.push_back(8.84);
  c.push_back(9.11);
  d.push_back(9.11);

  // iterate through the decimals and prints them out
  std::cout << "prints random decimals between 2.25-9.11 " << std::endl;
  for (UnrolledLL<double>::iterator itr = c.begin(); itr != c.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  //asserts both lists are the same
  assert (SAME(c,d));

  // use the output operator to print the inital list
  std::cout << "initial list:" << std::endl;
  c.print(std::cout);
  std::cout << std::endl;

  //checks pop_front and pop_back
  std::cout << "some editing with pop & push" << std::endl;
  assert (c.size() == 10);
  assert (c.front() == 2.25);
  assert (c.back() == 9.11);
  c.pop_front(); 
  d.pop_front();
  assert (c.size() == 9);
  assert (c.front() == 2.67);
  c.pop_back();
  d.pop_back();
  assert (c.size() == 8);
  assert (c.back() == 8.84);
  //prints the final result
  c.print(std::cout);
  std::cout << std::endl;
  assert (SAME(c,d));

  // erase the integers
  //erases it from the UnrolledLL
  std::cout <<"erases integers" << std::endl;
  UnrolledLL<double>::iterator c_iter = c.begin();
  while (c_iter != c.end()) {
    int intIter = *c_iter;
    if (*c_iter - intIter == 0) {
      c_iter = c.erase(c_iter);
    } else {
      c_iter++;
    }
  }
  //erases it from the list
  std::list<double>::iterator d_iter = d.begin();
    while (d_iter != d.end()) {
        int intIter = *d_iter;
    if (*d_iter - intIter == 0) {
      d_iter = d.erase(d_iter);
    } else {
      d_iter++;
    }
  }
  //prints list without integers
  c.print(std::cout);
  std::cout << std::endl;
  assert (c.size() == 7);
  assert (SAME(c,d));
  
  // inserting random decimals
  std::cout << "inserting random decimals" << std::endl;
  // inserts it in the UnrolledLL
  for (UnrolledLL<double>::iterator itr = c.begin(); itr != c.end(); itr++) {
    if (*itr == 2.67 || *itr == 3.01) {
      itr = c.insert(itr,2.87);
      itr++;
    } 
  }
  //and in the list
  for (std::list<double>::iterator itr = d.begin(); itr != d.end(); itr++) {
    if (*itr == 2.67 || *itr == 3.01) {
      itr = d.insert(itr,2.87);
      itr++;
    } 
  }
  //prints results of insertion
  c.print(std::cout);
  std::cout << std::endl;
  assert (c.size() == 9);
  assert (SAME(c,d));

  // overflowing an insert so it moves elements
  //inserts it in UnrolledLL
  std::cout << "inserting a decimal that overflows the node" << std::endl;
  for (UnrolledLL<double>::iterator itr = c.begin(); itr != c.end(); itr++) {
    if (*itr == 4.45) {
      itr = c.insert(itr,4.03);
      itr++;
    } 
  }
  //inserts it in list
  for (std::list<double>::iterator itr = d.begin(); itr != d.end(); itr++) {
    if (*itr == 4.45) {
      itr = d.insert(itr,4.03);
      itr++;
    } 
  }
  //prints results of insertion
  c.print(std::cout);
  std::cout << std::endl;
  assert (c.size() == 10);
  assert (SAME(c,d));
  //erasing all the elements in the node, 
  //therefore, removing the node
  std::cout << "removing a node" << std::endl;
  //erases elements from UnrolledLL and the list
  c_iter = c.begin();
  while (c_iter != c.end()) {
    if (*c_iter == 4.45 || *c_iter == 5.35) {
      c_iter = c.erase(c_iter);
    } else {
      c_iter++;
    }
  }
  d_iter = d.begin();
  while (d_iter != d.end()) {
    if (*d_iter == 4.45 || *d_iter == 5.35) {
      d_iter = d.erase(d_iter);
    } else {
      d_iter++;
    }
  }
  //prints results of removing the node
  c.print(std::cout);
  std::cout << std::endl;
  assert (c.size() == 8);
  assert (SAME(c,d));

  //checks the copy_list function
  std::cout << "testing copying" << std::endl;
  //copies the list
  UnrolledLL<double> ccopy(c);
  std::cout << "sucessfuly copied, asserting the size, front and back" <<std::endl;
  //checks assertion
  assert(c.size()== ccopy.size());
  assert(c.front()== ccopy.front());
  assert(c.back()== ccopy.back());
  std::cout << "passed assertions" << std::endl;
  //checks assertion operator
  std::cout << "checking if nodes are the same" << std::endl;
  if(c == ccopy){
    std::cout << "both are the same" << std::endl;
  }else{
     std::cout << "they are different" << std::endl;
  }
  //prints c and its copy
  std::cout << "C:" << std::endl; 
  c.print(std::cout);
  std::cout << "C(copy):" << std::endl; 
  ccopy.print(std::cout);
  //printing the front back and size accessorts
  std::cout << "printing the front, back, and size of c:" << std::endl;
  std::cout << "front: " << c.front() << std::endl;
  std::cout << "back: " << c.back() << std::endl;
  std::cout << "size: " << c.size() << std::endl;

  //testing clear
  std::cout << "testing clear" << std::endl;
  c.clear();
  //chcking if it's clear
  if(c.empty()){
    std::cout << "passed clear" << std::endl;
  }else{
    std::cout << "failed clear" << std::endl;
  }
}


