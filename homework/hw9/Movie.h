#ifndef movie_h_
#define movie_h_

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <utility>

class Movie
{
public:
    //constructs movie class
    Movie(const std::string &title_, const int &year_, 
          const int &runtime_, const int &genrecount_, const int &actorcount_, const int &rolecount_,
          const std::vector<std::string> &genres_, const std::vector<std::string> &actors_, const std::vector<std::string> &roles_);
    //print function if given a map of a string and the data with all the actors
    void print(std::map<std::string, std::string>& actor_data) const;
    //== operator for comparisons between movie class objects
    friend bool operator==(const Movie& m1, const Movie& m2) {
        //bool value to check if it's the same movie class
        // assuming it's equal
        bool check = true;
        //checks that the parameters match for both in the movie class
        if(m1.title == m2.title && m1.year == m2.year && m1.runtime == m2.runtime && m1.genrecount == m2.genrecount 
            && m1.actorcount == m2.actorcount && m1.rolecount == m2.rolecount){
                //if so, it's the same
                check = true;
            //else it's not
            }else{
                check = false;
            }
        //if it already doesn't match parameters,
        if (!check) {
            //then it's not equal
            return check;
        }
        //counters for the genres, actors, and roles
        int gen_count = 0, act_count = 0, role_count =0;
        //now checking through every genre actor and role
        //if they match it adds to the counter

        //checks genres
        int g = 0;
        while (g<m1.genrecount){
            if (m1.genres[g] == m2.genres[g]) {
                gen_count++;
                g++;
            }
            g++;
        }
        //checks actors
        int a = 0;
        while (a<m1.actorcount){
            if (m1.actors[a] == m2.actors[a]) {
                act_count++;
                a++;
            }
            a++;
        }
        //checks roles
        int r = 0;
        while (r<m1.rolecount){
            if (m1.roles[r] == m2.roles[r]) {
                role_count++;
                r++;
            }
            r++;
        }
        //if the counter amount isnt the same as how many are in the movie's counts (how
        //many are in each category)
        if(gen_count != m1.genrecount || act_count != m1.actorcount || role_count != m1.rolecount){
            //then they aren't equal (since they have the wrong items in their vectors)
            check = false;
            return check;
        }
        //else, then they are equal
        return check;
    }
    //public variables to access parameters 
    std::string title;
    int year, runtime, genrecount, actorcount, rolecount;
    std::vector<std::string> genres, actors, roles;
};
#endif
