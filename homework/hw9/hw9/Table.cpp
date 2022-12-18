#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <utility>

#include "Table.h"

//based on insert from ds_hashset.h
void Table::insert(Query &q, const Movie &m)
{
    float curr_occupancy;
    //calculates the current occupancy of the table and compare it to 
    //max it can be till it has to be resized
    curr_occupancy = size / m_table.size();
    if (occupancy < curr_occupancy) {
         //call resize_table with new size
        this -> resize_table(2*m_table.size());
    }
    //gets the hash value from the hash function
    unsigned int hash_value = hashFunction(q);
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
                //else also keep incrementing (searching though all the movie objexts)
                iter++;
            }
        }
        //after it's goes through all the movie objects
        // adds the movie at the given index
        m_table[index].second.push_back(m);
        return;
    }
    //if there is not movie at that index (meaning its empty)
    if (m_table[index].second.size() == 0) {
        //set the string value at the index to the query
        m_table[index].first = q;
        //add the movie object to the data
        m_table[index].second.push_back(m);
        //increment the size because you added a new movie
        size++;
        return;
        
    }

    //checks if you are trying to insert another value at that query
    //if the value doesnt match the query or there is already a movie at that index
    if (!(m_table[index].first == q) || m_table[index].second.size() > 1) {
        //index is already in table, but key doesn't match(linear probing)
        int i = 1;
        //if you're at the end of the table,
        // set the indicator to -1 to indicate you need to check
        //values previous
        if (index == m_table.size()-1) {
            i = -1;
        }else{
            //else if there are movies at those indexes (0,1,2,3) (1,2,3,4)
            while(m_table[index+i].second.size() != 0) { 
            //if the index is at the end of the table
            if (index+i == m_table.size()-1 ) {
                //set the indicator to -1 
                i = -1;
            }
            //if i is less then or equal to 0
            if (i <= 0){
                //decrement the indicator (to go previous values)
                i--;
            }else{ 
                //increment the indicator (to go next values)
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
//resize function that changes the size of the table given a new size
void Table::resize_table(unsigned int new_s) {
    //copies the current table to a variable that holds the old table (not resized yet)
    std::vector< std::pair<Query, std::list<Movie> > > old_table = m_table;
    //clears the m_table of its data
    m_table.clear();
    //then resizes the table
    m_table.resize(new_s);
    //loops through the old table's size
    for ( unsigned int i=0; i<old_table.size(); i++ ){
        //
        indexIterator iter_index = old_table[i].second.begin(); 
      while(iter_index !=old_table[i].second.end()){
        this -> insert(old_table[i].first, *iter_index);
        iter_index++;
        }
    }
}
// Modified SDBM Hash Function
// from http://www.partow.net/programming/hashfunctions/  
int Table::hashFunction(const Query &q) const {
    int n = q.getString().size();
    unsigned int hash = 0;

    for (int i = 0; i < n; i++){
         hash = q.getString()[i] + (hash << 6) + (hash << 16) - hash;
    }
    hash = hash  % m_table.size();
    return hash;

}
//print function
void Table::print(const Query& q, std::map<std::string, std::string>& a_data) const {
    //gets the index at the query
    int i = q.getIndex();
    //if there are no movies at that index, or if the the string at that index equals
    // the query object (meaning there's notrhing in it)
    if (m_table[i].second.size() == 0 || !(m_table[i].first == q)) {
        //prints there are no results
        std::cout << "No results for query." << "\n";
        return;
    //else, meaning there are valid to print
    //prints the number of results and all of the data of the actors/movies
    }else{
        std::cout << "Printing " << m_table[i].second.size() << " result(s):" << "\n";
        //uses const iterator to iterate through the movie data
        constIndIterator iter = m_table[i].second.begin();
        while(iter != m_table[i].second.end()){
        iter -> print(a_data);
        iter++;
        }
    }
}



