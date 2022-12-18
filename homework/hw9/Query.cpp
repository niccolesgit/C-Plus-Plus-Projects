#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Query.h"
//function that concantenates a string
void Query::createString() {
    //adds the title, year, runtime, genrecount
    s = title + std::to_string(year) + std::to_string(runtime) + std::to_string(genrecount);
    //adds all the genres
    int g = 0;
    while(g<genrecount){
        s += genres[g];
        g++;
    }
    //adds the actor count and all actors
    s += std::to_string(actorcount);
    int a = 0;
    while(a < actorcount){
        s += actors[a];
        a++;
    }
    //add role count and all the roles
    s += std::to_string(rolecount);
    int r =0;
    while(r < rolecount){
        s += roles[r];
        r++;
    }
}
