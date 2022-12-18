//includes headers for reading files and string & vector usage
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//point class guards
#ifndef point_h
#define point_H
class point {
    public:
    //constructor that creates the x & y coords and assigns it to its zone
    // (letter character)
        point(int x_, int y_, std::string zone_char_) {
            x = x_;
            y = y_;
            zone_char = zone_char_;
        }
    int x;
    int y;
    std::string zone_char;
};
#endif
//ends here

//zone class guards
#ifndef zone_h
#define zone_h
class zone {
    public:
    //constructor
    //sets the zone number to 0, since there are no zones yet
        zone() {
            znum = 0;
        } 
        //function that adds points to a vector of the point class
        // for each zone
        void add(const point& p) {
            zonev.push_back(p);
            //also sets the name of the point to a variable to access it
            name = p.zone_char;
            //increments the number of points in a zone
            znum += 1;
        }
    int znum;
    std::vector<point> zonev;
    std::string name;
};
//ends here
#endif
//board class guards
#ifndef board_h
#define board_h
class board{
    public:
        //constructor
        board(std::vector<std::string>& v);
        //acessors
        int getZSize() const {return zvect.size();} //get the size of the zone
        zone getZ(int i) const {return zvect[i];} //get a specific zone
         unsigned int getStars() const {return s;} // get the number of stars the user input
        std::vector<std::vector<point>> getBoard() {return bd;} //get the entire board
        //modifiers
        void setStars(unsigned int s_) {s = s_;} //sets the stars the user input to a variable
                                                    //s in the board class
        //function that finds the solutions of the board
        int findSolution(const point& start, unsigned int pindex, std::vector<point>& cpoints, 
            const std::vector<std::vector<point>>& sol_vect);

        //print functions
        void printAll(std::ofstream& out, const std::vector<std::vector<point>>& sol_vect) const;
        void printOne(std::ofstream& out, const std::vector<std::vector<point>>& sol_vect) const;
    private:
        std::vector<std::vector<point>> bd; //2d point vector for the board
        std::vector<std::vector<point>> bds; //2d point vector for the boards with solutions
                                            //history that keeps track of all the board solutions
        std::vector<zone> zvect; //zone vector that holds all the zones
        std::vector<point> pvect; //point vector that holds all the points
        unsigned int s; //variable that holds the number of stars
        int row; //variable that keeps track of how many rows there are
        int col; //variable that keeps track of the columns
        //variable that holds the star character (@ sign)
        std::string star = "@";
};
//bool functions
//checks if the point is in all of the current points
bool isValid(const point& p, std::vector<point>& cpoints, unsigned int s);
//checks if the current points is in all of the points 
bool isInSolution(const std::vector<point>& cvector, const std::vector<std::vector<point>>& sol_vect);
//sorts the zones
bool sortZ(zone b1, zone b2);
#endif
//ends heere