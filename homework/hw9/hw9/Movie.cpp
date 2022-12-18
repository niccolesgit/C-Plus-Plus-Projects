#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Movie.h"
//constructs the movie class
Movie::Movie(const std::string &title_, const int &year_, const int &runtime_, 
             const int &genrecount_, const int &actorcount_, const int &rolecount_,
             const std::vector<std::string> &genres_, const std::vector<std::string> &actors_, const std::vector<std::string> &roles_){
    //sets all the inputs to parameters to the movie class
    title = title_;
    year = year_;
    runtime = runtime_;
    genrecount = genrecount_;
    actorcount = actorcount_;
    rolecount = rolecount_;
    genres = genres_;
    actors = actors_;
    roles = roles_;
}
//print given the map including all of the data of the actors
void Movie::print(std::map<std::string, std::string>& m_data) const{
    //prints the movie title, year, run time and number of genres
    std::cout << title << std::endl;
    std::cout << year << std::endl;
    std::cout << runtime << std::endl;
    std::cout << genrecount;
    //prints all of the genres 
    int g = 0;
    while(g<genrecount){
        std::cout << " " << genres[g];
        g++;
    }
    //new line
    std::cout << "\n";
    //prints number of actors
    std::cout << actorcount;
    //prints all of the actors in the actor data and their specified role
    int a = 0;
    while(a<actorcount){
        std::cout << " " << m_data[actors[a]] << " (" << roles[a] << ")";
        a++;
    }
    //new line
    std::cout << "\n";
}
