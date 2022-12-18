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


// ===================================================================
void MoreTests() {

    //
    //
    // ADD YOUR OWN TEST CASES HERE
    // ADD COMMENTS TO EXPLAIN THE PURPOSE OF THE TEST CASES
    // TEST CASES SHOULD FINISH AND NOT CRASH. OUTPUT IS HELPFUL AS WELL.
    //
    //
 // THE FOLLOWING SMALL TEST CASE USES THE CHAR TYPE:

    // make two matching list of integers, one using an unrolled list,
    // one using an STL list.  They should stay the "SAME" throughout
    // these tests.
    UnrolledLL<char> c;
    std::list<char> d;
    c.push_back('a');
    d.push_back('a');
    c.push_back('b');
    d.push_back('b');
    c.push_back('c');
    d.push_back('c');
    c.push_back('d');
    d.push_back('d');
    c.push_back('e');
    d.push_back('e');
    c.push_back('f');
    d.push_back('f');
    c.push_back('g');
    d.push_back('g');
    c.push_back('h');
    d.push_back('h');
    c.push_back('i');
    d.push_back('i');
    c.push_back('j');
    d.push_back('j');
    c.push_back('k');
    d.push_back('k');

    // iterate through the chars and print them out
    std::cout << "the chars from a->k" << endl;
    for (UnrolledLL<char>::iterator itr = c.begin(); itr != c.end(); itr++) {
        std::cout << " " << *itr;
    }
    std::cout << std::endl << endl;
    assert (SAME(c,d));

    // use the output operator to print the underlying representation
    std::cout << "initial" << endl;
    c.print(std::cout);
    std::cout << endl;

    // testing some basic functions in the class
    std::cout << "some editing with pop & push" << std::endl;
    assert (c.size() == 11);
    assert (c.front() == 'a');
    assert (c.back() == 'k');
    c.pop_front();
    d.pop_front();
    assert (c.size() == 10);
    assert (c.front() == 'b');
    c.pop_back();
    d.pop_back();
    assert (c.size() == 9);
    assert (c.back() == 'j');
    c.print(std::cout);
    std::cout << endl;
    assert (SAME(c,d));

    // more editing
    std::cout << "more editing with pop & push" << std::endl;
    c.pop_front();
    c.pop_front();
    c.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    c.print(std::cout);
    c.pop_back();
    d.pop_back();
    c.print(std::cout);
    assert (c.size() == 5);
    assert (c.front() == 'e');
    assert (c.back() == 'i');
    c.push_front('x');
    c.push_front('y');
    c.push_front('z');
    d.push_front('x');
    d.push_front('y');
    d.push_front('z');
    c.print(std::cout);
    std::cout << std::endl;
    assert (c.size() == 8);
    assert (c.front() == 'z');
    assert (SAME(c,d));
    std::cout << "Clearing list..."<<std::endl;
    c.clear();
    assert(c.empty());
    std::cout << "Passed empty() assertion"<<std::endl;
    c.print(cout);




// CORNER CASES:
    // empty lists - no nodes - use clear, empty, functions that might not work
    std::cout << "\nINITIAL\nCorner Case #1: empty list (no nodes)" << std::endl;
    UnrolledLL<int> e;
    e.print(std::cout);
    std::cout  << std::endl;
    assert(e.empty());
    e.clear();
    std::cout << "using clear() on the empty list" << std::endl<< std::endl;
    assert(e.empty());
    assert(e.begin() == e.end());
    e.print(std::cout);
    UnrolledLL<int> e2(e);
    std::cout << "created another UnrolledLL making a copy of the original one -> empty" << std::endl<< std::endl;
    assert(e.empty() == e2.empty());
    std::cout << "original UnrolledLL:" << std::endl;
    e.print(std::cout);
    std::cout << "copy of the original UnrolledLL:" << std::endl;
    e2.print(std::cout);
    std::cout << "Passed comparison test between both UnrolledLLs" << std::endl;

    // one element
    e.push_back(1);
    std::cout << "Added one element to the first empty UnrolledLL created" << std::endl;
    e.print(std::cout);
    std::cout  << std::endl;
    std::cout << "Now testing..."<< std::endl << "Corner Case #2: one element in one node" << std::endl;
    assert(e.size()== 1);
    assert(e.front()== 1);
    assert(e.back()== 1);
    std::cout << "size() == 1, front() == 1, back() == 1 -- assertions passed" << std::endl;
    e.print(cout);
    std::cout << "\nMaking a copy of the list with one single value" << std::endl;
    UnrolledLL<int> e3(e);
    assert(e.size()== e3.size());
    assert(e.front()== e3.front());
    assert(e.back()== e3.back());
    std::cout << "comparison of size(), front(), back() between both lists -- assertions passed" << std::endl;
    std::cout << "\noriginal UnrolledLL:" << std::endl;
    e.print(cout);
    std::cout << "copy of the original UnrolledLL:" << std::endl;
    e3.print(cout);
    std::cout  << std::endl;

    // one full node - insert
    std::cout << "Now testing...\nCorner Case #3: one full node (aka node->elements is full)\nadding elements to previous list with push_back" << std::endl;

    e.push_back(2);
    e.push_back(3);
    e.push_back(4);
    e.push_back(5);
    e.push_back(6);
    std::cout << "This is how the list looks now, one full node: " << std::endl;
    e.print(cout);
    std::cout << "\nMaking a copy of the list with one full node" << std::endl;
    UnrolledLL<int> e4(e);
    e4.print(cout);
    assert(e.size()== e4.size());
    assert(e.front()== e4.front());
    assert(e.back()== e4.back());
    std::cout << "comparison of size(), front(), back() between both lists -- assertions passed" << std::endl;

}