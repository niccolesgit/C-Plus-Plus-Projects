#ifndef query_h_
#define query_h_

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <utility>

//uses movie class in the query class
#include "Movie.h"


class Query
{
public:
    //constructs query class with default values all being 0
    Query() : title("0"), year(0), runtime(0), genrecount(0), actorcount(0), rolecount(0) {}
    //constructor that constructs query class based on parameters sent in
    Query(const std::string &s_, const std::string &title_, const int &year_, const int &runtime_, 
        const int &genrecount_, const int &actorcount_, const int &rolecount_, 
        const std::vector<std::string> &genres_, const std::vector<std::string> &actors_, const std::vector<std::string> &roles_);
    //makes a query object based off the movie class's parameters 
    Query(const Movie& m) : title(m.title), year(m.year), runtime(m.runtime), 
        genrecount(m.genrecount), actorcount(m.actorcount), rolecount(m.rolecount), 
        genres(m.genres), actors(m.actors), roles(m.roles) {}

    //accessors
    //gets the string created in createString function
    std::string getString() const {return s;}
    //gets the index of the class
    int getIndex() const {return index;} 

    //modifiers
    //sets all the new parameters to the current ones in the
    //query class
    void setTitle(const std::string& title_) {title = title_;}
    void setYear(const int& year_) {year = year_;}
    void setRunTime(const int& runtime_) {runtime = runtime_;}
    void setGenreCount(const int& genrecount_) {genrecount = genrecount_;}
    void setActorCount(const int& actorcount_) {actorcount = actorcount_;}
    void setRoleCount(const int& rolecount_) {rolecount = rolecount_;}
    void setGenres(const std::vector<std::string>& genres_) {genres = genres_;}
    void setActors(const std::vector<std::string>& actors_) {actors = actors_;}
    void setRoles(const std::vector<std::string>&roles_) {roles = roles_;}
    void setIndex(int index_) {index = index_;}

    //print and create string function
    void print() const;
    void createString();

    //== operater to check between two queries
    friend bool operator==(const Query& q1, const Query& q2) {
        //check variable to check if they are equal
         bool check = true;
         //checks all the parameters with the first query with the other
        if(q1.title == q2.title && q1.year == q2.year && q1.runtime == q2.runtime && q1.genrecount == q2.genrecount 
            && q1.actorcount == q2.actorcount && q1.rolecount == q2.rolecount){
                check = true;
            }else{
                //if it doesn't it's false
                check = false;
            }
        //if it's already false
        if (!check) {
            //then they aren't equal
            return check;
        }
        //now checking each element in the genres, actors, and roles
        //counter variables
        int gen_count = 0, act_count = 0, role_count = 0;
        //loops through each vector and adds to the counter
        // if their element matches at the same index
        for (int i = 0; i < q1.genrecount; i++) {
            if (q1.genres[i] == q2.genres[i]) {
                gen_count += 1;
            }
        }
        for (int i = 0; i < q1.actorcount; i++) {
            if (q1.actors[i] == q2.actors[i]) {
                act_count += 1;
            }
        }
        for (int i = 0; i < q1.rolecount; i++) {
            if (q1.roles[i] == q2.roles[i]) {
                role_count += 1;
            }
        }
        //if any of the counters is not equal to the count parameter
        if(gen_count != q1.genrecount || act_count != q1.actorcount || role_count != q1.rolecount){
            //then they're elements arent the same, and not equal
            check = false;
            return check;
        }
        //if they are equal
        // then they are equal
        return check;
    }
//private variables holding parameters for the query class.
private:
    std::string title, s;
    int year, runtime, genrecount, actorcount, rolecount, index;
    std::vector<std::string> genres, actors, roles;
};
#endif