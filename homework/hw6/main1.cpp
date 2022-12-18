#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "board1.h"
//main code
int main(int argc, char* argv[]){
    //checks that the user input a valid number of arguments
    if(argc < 6 || argc > 6){ //6 including a.out
        std::cerr << "Error: Invalid number of arguments" << std::endl;
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
    //creates a vector to hold all the data
    std::vector<std::string> data;
    //creates a temp string to connect the data
    std::string temp;
    //while you're in the file, look for strings
    while(infile >> temp){
        //add them to the data vector
        data.push_back(temp);
    }
    //make a board class based on the data
    Board b(data);
    //set the number of stars per zone to the class
    // uses stoi to convert a string to an int value
    b.setStars(std::stoi(stars));
    //creates a point vector for all the solutions
    std::vector<std::vector<Point>> avect;
    //loop through the entire board
    for(int i = 0; i<b.getZSize(); i++){
        //loop through each zone
        for(int j = 0; j < b.getZ(i).nzone;j++){
            //create values for x and y coordinates
             int c =0;
            while(c!=5) {
                std::vector<Point> cvect;
                b.solve(b.getZ(i).zpoints[j], 0, cvect, avect);
                if (cvect.size() == b.getZSize()*b.getStars() || isInAll(cvect, avect)) {
                    avect.push_back(cvect);
                }
                c++;
            }
        }
    }
    //if the user uses the count function
        if(comm1 == "count"){
            //write the number of solutions for that text file
            outfile << "Number of solutions: " << avect.size() << std::endl;
        }
        //if they use the print function
        if(comm1 == "print"){
            //if the print 1 solution
            if(comm2 == "all_solutions"){
                //print the number of total solutions found
                outfile << "Number of solutions: " << avect.size() << "\n"<< std::endl;
                //print all the possible solutions
                b.printAll(outfile, avect);
            //else if they print all solutions
            }else if(comm2 == "one_solution"){
                //write there's only one solutions
                outfile << "Number of solutions: 1" << "\n" << std::endl;
                outfile << "Solution 1:" << std::endl;
                //print only the first solution
                b.printOne(outfile, avect);
            }
        }
    return 0;

}