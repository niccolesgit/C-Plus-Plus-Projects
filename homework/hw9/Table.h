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
    //gets the size
    unsigned int getSize() const {return size;}
    //gets the table
    std::vector< std::pair<Query, std::list<Movie> > > getTable() const {return m_table;}

    //modifiers
    //sets the occupancy
    void setOccupancy(float occupancy_) {occupancy = occupancy_;}
    //resizes the table
    void resize_table(unsigned int new_s);
    //inserts movies at the given query
    void insert(Query &q, const Movie &m);

    //hash function and print function
    int SDBMHash(const Query& q) const;
    void print(const Query& q, std::map<std::string, std::string>& actor_data) const;
//private variables for the table class
private:
    //HASHTABLE
    std::vector< std::pair<Query, std::list<Movie> > > m_table;
    //iterator typedefs, to make using iterators easier
    typedef typename std::list<Movie>::const_iterator constIndIterator;
    typedef typename std::list<Movie>::iterator indexIterator;
    //variables for the size of the table and its occupancy
    unsigned int size;
    float occupancy;

};

#endif