#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <utility>

#include "Table.h"

//based on insert from ds_hashset.h
void Table::insert(Query &q, const Movie &m){
    float curr_occupancy;
    //calculates the current occupancy of the table and compare it to 
    //max it can be till it has to be resized
    curr_occupancy = size / m_table.size();
    if (occupancy < curr_occupancy) {
         //call resize_table with new size
        this -> resize_table(2*m_table.size());
    }
    //gets the hash value from the hash function
    unsigned int hash_value = SDBMHash(q);
    //gets the index by taking the hash value and 
    // modular dividing it by the total size
    unsigned int index = hash_value % m_table.size();
    //if the table matches the query at that index
    if (m_table[index].first == q) {
        //iterate through the movie class elements
        std::list<Movie>::const_iterator iter = m_table[index].second.begin();
        //while you aren't at the end of the table
        while(iter != m_table[index].second.end()) {
            //if the movie is the element at that point
            if (*iter == m) {
                //keep incrementing
                iter++;
            }else{
                //else also keep incrementing (searching trhough all the movie objexts)
                iter++;
            }
        }
        //after it's goes through all the movie objects
        // adds the movie at the given index
        m_table[index].second.push_back(m);
        return;
    }
    //if there is not movie at that index
    if (m_table[index].second.size() == 0) {
        //set the first value at the index to the query
        m_table[index].first = q;
        //add the movie object to the data
        m_table[index].second.push_back(m);
        //increment the size because you addded a new movie
        size++;
        return;
        
    }

    //checks if you are trying to insert another value at that query
    //if the value doesnt match the query or there is already a movie at that index
    if (!(m_table[index].first == q) || m_table[index].second.size() > 1) {
        //index is already in table, but key doesn't match(linear probing)
        int i = 1;
        //if you're at the end of the table,
        // sets it to -1 to check the indexes backwards
        if (index == m_table.size()-1) {
            i = -1;
        }else{
            //else if there are movies at those indexes
            while(m_table[index+i].second.size() != 0) {
            //if the index is at the end of the table
            if (index+i == m_table.size()-1 ) {
                //set the indicator to -1 (to start going backwards to
                //check values)
                i = -1;
            }
            //if i is less then or equal to 0
            if (i <= 0){
                //decrement the indicator (going previous index)
                i--;
            }else{ 
                //increment the indicator (going to the next index)
                 i++;
            }
          }
        }
        //assigns the query to that given index
        m_table[index+i].first = q;
        //adds the movie at that index
        m_table[index+i].second.push_back(m);
        //increment the size
        // because you added another movie
        size++;
        //then set the index to the new index 
        // that you set the movie to
        q.setIndex(index+i);
        
    }
    
}
//resizes the table
void Table::resize_table(unsigned int new_s) {
    //copies the current table to another table
    std::vector< std::pair<Query, std::list<Movie> > > old_table = m_table;
    //clears current table
    m_table.clear();
    //resizes current table
    m_table.resize(new_s);
    //loops through the old table
    for ( unsigned int i=0; i<old_table.size(); i++ ){
        //loops through the items in the old table
    indexIterator iter_index = old_table[i].second.begin(); 
      while(iter_index !=old_table[i].second.end()){
          //insert elements fromm the old table into the new table
        this -> insert(old_table[i].first, *iter_index);
        //increment
        iter_index++;
        }
    }
}
//Modified algorithm of the SDMB function
// from http://www.partow.net/programming/hashfunctions/  
int Table::SDBMHash(const Query &q) const {
    int n = q.getString().size();
    unsigned long hash = 0;
    for (int i = 0; i < n; i++)
        hash = q.getString()[i] + (hash << 6) + (hash << 16) - hash;
    hash = hash % m_table.size();
    return hash;

}
//print function
void Table::print(const Query& q, std::map<std::string, std::string>& a_data) const {
    //get the index
    int i = q.getIndex();
    //if there are no movies or if the query doesn't match
    if (m_table[i].second.size() == 0 || !(m_table[i].first == q)) {
        //there are no results
        std::cout << "No results for query." << std::endl;
        return;
    }
    //else, the query does exist,
    // printing the number of results
    std::cout << "Printing " << m_table[i].second.size() << " result(s):" << std::endl;
    //iterates through the data printing each item in the actor data
    constIndIterator iter = m_table[i].second.begin();
    while(iter != m_table[i].second.end()){
        iter -> print(a_data);
        iter++;
    }
}



