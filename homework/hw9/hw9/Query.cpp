#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Query.h"
//create string concantenates a string with all the parameters
void Query::createString() {
    //adds the title, year, runtime, and genrecount
    s = title + std::to_string(year) + std::to_string(runtime) + std::to_string(genrecount);
    // then adds all the genres
    int g = 0;
    while(g < genrecount){
        s += genres[g];
        g++;
    }
    //adds the number of actors
    s += std::to_string(actorcount);
    //then adds all of the actors
    int a = 0;
    while(a < actorcount){
        s += actors[a];
        a++;
    }
    //adds the number of roles
    s += std::to_string(rolecount);
    //adds all the roles
    int r = 0;
    while(r < rolecount){
        s += roles[r];
        r++;
    }
}
