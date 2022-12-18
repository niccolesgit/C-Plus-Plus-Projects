#ifndef table_h_
#define table_h_

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Movie.h"
#include "Query.h"

class Table
{
public:
    //default constructors
    Table() : m_table(100), size(0) {}
    //constructor if given table size
    Table(unsigned int s) : m_table(s), size(0) {}
    //constructor if given another table (copying table)
    Table(const Table &orig_table) : m_table(orig_table.m_table), size(orig_table.size) {}

    //accessors
    //gets the size of the table
    unsigned int getSize() const {return size;}
    //gets the table 
    std::vector< std::pair<Query, std::list<Movie> > > getTable() const {return m_table;}

    //modifiers
    //sets the occupency from the inputs
    void setOccupancy(float occupancy_) {occupancy = occupancy_;}
    //resizes the table
    void resize_table(unsigned int new_s);
    //inserts movies at the given query
    void insert(Query &q, const Movie &m);

    //hash function and print function
    int hashFunction(const Query& q) const;
    void print(const Query& q, std::map<std::string, std::string>& a_data) const;
//private variables
private:
    //HASHTABLE:
    std::vector< std::pair<Query, std::list<Movie> > > m_table;
    //an iterater that helps loop through the movie list
    //(makes it easier than typing it out every time)
    typedef typename std::list<Movie>::iterator indexIterator;
    typedef typename std::list<Movie>::const_iterator constIndIterator;
    //parameters
    unsigned int size;
    float occupancy;

};

#endif