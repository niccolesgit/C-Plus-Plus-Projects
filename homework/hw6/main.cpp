//include headers for reading and writing files, vector usage, and cstring for stoi
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
//include the header file used
#include "board.h"
// takes in an input file, output file, S value, output mode, and solution mode
// the code creates a puzzle object and solves it based on the output and solution mode
//main code
int main(int argc, char* argv[]){
    //checks that the user input a valid number of arguments
    if(argc < 6 || argc > 6){ //6 including a.out
        std::cerr << "Error: Invalid number of arguments (requires 6)" << std::endl;
        return 0;
    }
    //creates strings for each of the other commands
    std::string stars, comm1, comm2;
    //sets them to their argurments 
    stars = argv[3];
    comm1 = argv[4];
    comm2 = argv[5];
    //opens the file for data from 2nd command
    std::ifstream infile(argv[1]);
    //if the file can't be opened, it doesn't exist
    if(!infile.is_open()){
        std::cerr << "Input file not found." << "\n";
    }
    //if the output file can't be opened, it doesn't exist
    //opens output file from second command
    std::ofstream outfile(argv[2]);
        if(!outfile.is_open()){
            std::cerr << "Output file not found." << "\n";
        }
    // initalizes the 
    //creates a vector to hold all the data
    std::vector<std::string> data;
    //creates a temp string to connect the data
    std::string temp;
    //while you're in the file, look for strings
    while(infile >> temp){
        //add them to the data vector
        data.push_back(temp);
    }
    //creates board with the data
    board b(data);
    //sets the stars from the user to the 
    // board star variable
    //uses stoi to convert a string to an int
    b.setStars(std::stoi(stars));
    //creates a vector that holds all of the solutions
    std::vector<std::vector<point>> sol_vect;
    //loops through each zone
    for (int i = 0; i < b.getZSize(); i++) {
        for(int j = 0; j < b.getZ(i).znum; j++) {
            //makes a counter variable
            int c =0;
            //while c is less than 5
            while(c<5) {
                //make a vector of the current points 
                 std::vector<point> cvector;
                 //find a solution at the boards current zone, 
                 // finds the solution at the specific zone, 
                 // the index of 0, the current vector of points, and all the solutions
                b.findSolution(b.getZ(i).zonev[j], 0, cvector, sol_vect);
                //if the current vectors size adds up to the zone's size
                //times the number of stars in it
                //or if the current vector is in the vector with all of the solutions
                if (cvector.size() == b.getZSize()*b.getStars() || isInSolution(cvector,sol_vect)) {
                    //then add it to the all solutions vector
                    sol_vect.push_back(cvector);
                    //increment the counter
                    c++;
                //else just increment the counter
                }else{
                    c++;
                }
            }
        }
    }
    //if the user uses the command count
    if (comm1 == "count") {
        //prints the number of solutions found 
        outfile << "Number of solutions: " << sol_vect.size() << std::endl;
    }
    //if the user uses the command print
    if (comm1 == "print") {
        //if the 6th command is all solutions
        if (comm2 == "all_solutions") {
            //print the total number of all solutions found
            outfile << "Number of solutions: " << sol_vect.size() << "\n" << std::endl;
            //print all the solutions
            b.printAll(outfile, sol_vect);
        //if the 6th command is one solution
        }else if (comm2 == "one_solution") {
            //print that there is one solution
            outfile << "Number of solutions: 1" << "\n" << std::endl;
            //print one solution
            outfile << "Solution 1:" << std::endl;
            b.printOne(outfile, sol_vect);
        }
    }
    return 0;
}