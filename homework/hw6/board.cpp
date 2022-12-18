//include headers for reading and writing files, vector and string usage
// and algorithm for sorting
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
//include header file
#include "board.h"
//constructor that constructs the board
board::board(std::vector<std::string>& v) {
    //sets the row and column to the 1st and 2nd element
    // (always in this case the 1st and 2nd element)
    row = std::stoi(v[0]);
    col = std::stoi(v[1]);
    //zone's character variable
    std::string zchar;
    //the number of of coordinates expected
    // in the zone
    unsigned int num_per_zone;
    //counter variable
    int count = 0;
    //loops through the column
    for (int i = 0; i < col; i++) {
        //creates a vector to make the rows
        std::vector<point> rowv;
        //loops through the rows
        for (int j = 0; j < row; j++) {
            //adds row to row vector with
            //default values, (0,0) in an
            //empty zone
            rowv.push_back(point(0,0,""));
        }
        //pushes back each row for each column
        bd.push_back(rowv);
    }
    //while loop to loop through the board
    while (true) {
        //creates a breakpoint variable for the while loop
        bool breakpoint = false;
        //sets the zone character to
        // the 3rd element in the list
        zchar = v[2+count];
        //sets the number per zone to the 4th element in the list
        num_per_zone = std::stoi(v[3+count]);
        //creates a zone class of a zone "vector"
        zone zvector;
        //loops through, starting at the 5th element (1st coordinate)
        //goes until its gone through all of the coordinates
        // multiplied by 2 to account for both x and y coordinates
        // and +3 and the count to skip the first 4 elements and any other
        // zone inputs
        //increments by 2 to skip each pair of coordinates
        for (unsigned int i = 4+count; i < ((num_per_zone * 2) + 3+count); i=i+2) {
            //adds the point (x and y) and zone's character to the zone
            zvector.add(point(std::stoi(v[i]),std::stoi(v[i+1]),zchar));
            //adds the point (x and y) and zone's character to the point vector
            pvect.push_back(point(std::stoi(v[i]),std::stoi(v[i+1]),zchar));
            //creates a board, setting the current coordinates the the point's coordinates
            // and using te zone character
            bd[std::stoi(v[i])][std::stoi(v[i+1])] = point(std::stoi(v[i]),std::stoi(v[i+1]),zchar);
            //if the i (+2) since at this point it will be complete with 1 pair of coordinates
            //if it equals the size, means we are at the end of the data
            if (i+2 >= v.size()) {
                //set the breakpoint to true
                breakpoint = true;
            }
        }
        //adds the zones made to the zone vector
        zvect.push_back(zvector);
        //if we reach the breakpoint
        if (breakpoint) {
            //break from the while loop
            break;
        }
        //change the count to the zone number times 2 (to account for x an y)
        // and +2 to account for the zone info
        count += num_per_zone * 2 +2;
    }
    //sort the zones with sort function
    std::sort(zvect.begin(), zvect.end(), sortZ);
}
//function that finds the solutions
int board::findSolution(const point& start, unsigned int pindex, std::vector<point>& cpoints, 
    const std::vector<std::vector<point>>& sol_vect) {
    //if the current points size equals te zone size times the star value
    if (cpoints.size() == (this -> getZSize())*s) {
        //return 1
        return 1;
    //else if it  equals 0
    }else if(cpoints.size() == 0){
        //push back the point to the current points
        cpoints.push_back(start);
        //find the solution again w/ the point now added to the vector
        findSolution(zvect[0].zonev[1], 0, cpoints, sol_vect);
    }
    //if the index is greater thatn the point vectors' size
    if (pindex >= pvect.size()) {
        //return 0
        return 0;
    }
    //if the point's index in the pint vector is valid in its current points
    //and the index is less than the size
    if (isValid(pvect[pindex], cpoints, s) && pindex < pvect.size()) {
        //push back the point at the index to the current points
        cpoints.push_back(pvect[pindex]);
        //but if point you added was a duplicate and already
        // in the solution
        if (isInSolution(cpoints, sol_vect)) {
            //remove the point you just added
            cpoints.pop_back();
        }
    }
    //find the solution again after adding points to the cpoints
    findSolution(start, pindex+1, cpoints, sol_vect);
    //return 0 if nothing else
    return 0;
}
//function that prints all solutions
void board::printAll(std::ofstream& out, const std::vector<std::vector<point>>& sol_vect) const {
    //loops through all the solutions
    for (unsigned int i = 0; i < sol_vect.size(); i++) {
        //prints which solution we are on
        out << "Solution " << i+1 << ":" << std::endl;
        //breakpoint variable
        bool breakpoint = true;
        //loops through each row and column
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                //loops through the solutions (2d vector)
                for (unsigned int j = 0; j < sol_vect[i].size(); j++) {
                    //if the row and column equals the solution vector at that point
                    if (r == sol_vect[i][j].y && c == sol_vect[i][j].x) {
                        //print a star at that location
                        out << star;
                        //set the breakpoint to false
                        breakpoint = false;
                        //break
                        break;
                    }
                }
                //if the havent met the breakpoint, meaning
                //no star was printed
                if (breakpoint) {
                    //print the zone character at the current row and column
                    out << bd[c][r].zone_char;
                }
                //reset the breakpoint
                breakpoint = true;
            }
            //print a new line
            out << std::endl;
        }
        //print a new line
        out << std::endl;
    }
}
//prints one solution
void board::printOne(std::ofstream& out, const std::vector<std::vector<point>>& sol_vect) const {
    //creates a breakpoint variable
    bool breakpoint = true;
    //loop through the row and column 
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            //loop through the solution vector
            for (unsigned int i = 0; i < sol_vect[0].size(); i++) {
                //if the row or column equals the x or y of the solution
                if (r == sol_vect[0][i].y && c == sol_vect[0][i].x) {
                    //print a star at that location
                    out << star;
                    //set the breakpoint to false
                    breakpoint = false;
                    //break from the while loop
                    break;
                }
            }
            //if the havent met the breakpoint, meaning
            //no star was printed
            if (breakpoint) {
                //print the zone's character at that
                //column and row
                out << bd[c][r].zone_char;
            }
            //reset the breakpoint
            breakpoint = true;
        }
        //print a new line
        out << std::endl;
    }
}
//checks is the point is valid in the current points
bool isValid(const point& p, std::vector<point>& cpoints, unsigned int s) {
    //create variables to keep track of the row, column, and zone
    unsigned int r = 0;
    unsigned int c = 0;
    unsigned int z = 0;
    //loops through the current points
    for (unsigned int i = 0; i < cpoints.size(); i++) {
        //if the point is at the current point, its invalid
        if (p.x == cpoints[i].x && p.y == cpoints[i].y) {
            return false;
        //if the point is surrounding the current point,
        // it is also invalid
        }else if((p.x == cpoints[i].x && p.y == cpoints[i].y+1) || 
            (p.x == cpoints[i].x && p.y == cpoints[i].y-1) ||
            (p.x == cpoints[i].x+1 && p.y == cpoints[i].y) || 
            (p.x == cpoints[i].x-1 && p.y == cpoints[i].y) ||
            (p.x == cpoints[i].x+1 && p.y == cpoints[i].y+1) || 
            (p.x == cpoints[i].x-1 && p.y == cpoints[i].y+1) ||
            (p.x == cpoints[i].x+1 && p.y == cpoints[i].y-1) ||
            (p.x == cpoints[i].x-1 && p.y == cpoints[i].y-1)) {
            return false;
        }
        //if the point's y is the same as the current point's y
        if (p.y == cpoints[i].y) {
            //increment the row
            r++;
        } 
        //if the point's x is the same as the current point's x
        if (p.x == cpoints[i].x){
            //increment the columns
            c++;
        } 
        //if the point's zone is the same as the current point's zone
        if (p.zone_char == cpoints[i].zone_char) {
            //increment the zone
            z++;
        }
    }
    //if the row, column, or zone counter is equal to the number of stars,
    // then it is invalid
    if ( r == s || c == s || z == s) {
        return false;
    //else, the point is valid
    }else{
        return true;
    }
    //if it isn't false due to any of these conditions we can assume its valid
    return true;
}
//function to check if the current vector is in the solutions
bool isInSolution(const std::vector<point>& cvector, const std::vector<std::vector<point>>& sol_vect) {
    //loops through the solutions 
    for (unsigned int i = 0; i < sol_vect.size(); i++) {
        //counter variable
        unsigned int c = 0;
        //loops through the current vector
        for (unsigned int j = 0; j < cvector.size(); j++) {
            //still looping through the solutions (2D vector)
            for (unsigned int k = 0; k < sol_vect[i].size(); k++) {
                //if the current vector's coordinates equal the solution's vectors cordinates
                if (cvector[j].x == sol_vect[i][k].x && cvector[j].y == sol_vect[i][k].y) {
                    //increment the counter (for each coordinate in each)
                    c++;
                }
            }
            //if the counter is equal to the solution's size
            if (c == sol_vect[i].size()) {
                //then the current vector is in the solution vector
                //returning true
                return true;
            }
        }
    }
    //else return false, since the coordinates don't match 
    return false;
}
//sorts the zones from smallest to largest
bool sortZ(zone b1, zone b2) {
    //if the first zone is smaller than the second
    if(b1.znum < b2.znum){
        //then returns truw
        return true;
    }else{
        //else returns false
        return false;
    }
}
