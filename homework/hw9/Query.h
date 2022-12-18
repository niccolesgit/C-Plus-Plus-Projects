#ifndef query_h_
#define query_h_

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "Movie.h"

class Query
{
public:  
    //default constructor that sets parameters to default values to 0
    Query() : title("0"), year(0), runtime(0), genrecount(0), actorcount(0), rolecount(0) {}
    //constructor that creates a query object given parameters
    Query(const std::string &s_, const std::string &title_, const int &year_, const int &runtime_, 
        const int &genrecount_, const int &actorcount_, const int &rolecount_, 
        const std::vector<std::string> &genres_, const std::vector<std::string> &actors_, const std::vector<std::string> &roles_);
    
    //creates a query based on parameters from a movie
    Query(const Movie& m) : title(m.title), year(m.year), runtime(m.runtime), 
        genrecount(m.genrecount), actorcount(m.actorcount), rolecount(m.rolecount), 
        genres(m.genres), actors(m.actors), roles(m.roles) {}

    //accessors
    //gets the string made in create string
    std::string getString() const {return s;}
    //gets the index at the query
    int getIndex() const {return index;} 

    //modifiers
    //sets all the parameters based on if you need to update any parameters
    //or query variables
    void setTitle(const std::string& title_) {title = title_;}
    void setYear(const int& year_) {year = year_;}
    void setRunTime(const int& runtime_) {runtime = runtime_;}
    void setGenreCount(const int& genrecount_) {genrecount = genrecount_;}
    void setActorCount(const int& actorcount_) {actorcount = actorcount_;}
    void setRoleCount(const int& rolecount_) {rolecount = rolecount_;}
    void setGenres(const std::vector<std::string>& genres_) {genres = genres_;}
    void setActors(const std::vector<std::string>& actors_) {actors = actors_;}
    void setRoles(const std::vector<std::string>&roles_) {roles = roles_;}
    //updates the index
    void setIndex(int index_) {index = index_;}

    //print and create string functions
    void print() const;
    //concantenates a string for the hash function
    void createString();

    //== operator that helps compare queries
    friend bool operator==(const Query& q1, const Query& q2) {
        //bool variable ot check
         bool check = true;
         //checks that all the parameters are the same in both
        if(q1.title == q2.title && q1.year == q2.year && q1.runtime == q2.runtime && q1.genrecount == q2.genrecount 
            && q1.actorcount == q2.actorcount && q1.rolecount == q2.rolecount){
                //if it does, its true (for now)
                check = true;
                //else they are not equal
            }else{
                check = false;
            }
        //if they aren't equal
        if (!check) {
            //return that they aren't equal
            return check;
        }
        //counters to keep track of how many variables they have
        //in common in the genres, actors, and roles 
        // vector
        int gen_count = 0, act_count = 0, role_count = 0;
        //checks genres
        int g = 0;
        while(g < q1.genrecount){
            if (q1.genres[g] == q2.genres[g]) {
                gen_count++;
                g++;
            }else{
                g++;
            }
        }
        //checks actors
        int a = 0;
        while(a < q1.actorcount){
            if (q1.actors[a] == q2.actors[a]) {
                act_count++;
                a++;
            }else{
                a++;
            }
        }
        //checks roles
        int r = 0;
        while(r < q1.rolecount){
            if (q1.roles[r] == q2.roles[r]) {
                role_count++;
                r++;
            }else{
                r++;
            }
        }
        //if the counters aren't the same as the counts
        if(gen_count != q1.genrecount || act_count != q1.actorcount || role_count != q1.rolecount){
            //then they aren't equal
            check = false;
            //return that they aren't false
            return check;
        }
        //else return that they are equal.
        return check;
    }
//private variables used for the query class
private:
    std::string title, s;
    int year, runtime, genrecount, actorcount, rolecount, index;
    std::vector<std::string> genres, actors, roles;
};
#endif