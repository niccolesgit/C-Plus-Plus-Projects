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
//print given the map
void Movie::print(std::map<std::string, std::string>& actor_data) const{
    //prints title year and run time and genre count
    std::cout << title << "\n";
    std::cout << year << "\n";
    std::cout << runtime << "\n";
    std::cout << genrecount;
    int g = 0;
    //prints all the genres
    while (g<genrecount){
        std::cout << " " << genres[g];
        g++;
    }
    //new line
    std::cout << "\n";
    //prints the actor count
    std::cout << actorcount;
    int a = 0;
    //prints all the actors and their roles
    while(a<actorcount){
        std::cout << " " << actor_data[actors[a]] << " (" << roles[a] << ")";
        a++;
    }
    //new line
    std::cout << "\n";
}
