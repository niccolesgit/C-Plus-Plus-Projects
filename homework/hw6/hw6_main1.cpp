#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#include "puzzle1.h"

// takes in an input file, output file, S value, output mode, and solution mode
// the code creates a puzzle object and solves it based on the output and solution mode
int main(int argc, char* argv[]) {

    if (argc != 6) {
        std::cerr << "command error" << std::endl;
        return 0;
    }
    
    // sets all of the command arguments 
    std::string inp, outp, S_, outmod, solmod;
    inp = argv[1];
    outp = argv[2];
    S_ = argv[3];
    outmod = argv[4];
    solmod = argv[5];

    //opens the input and output files, prints an error if it cant open
    std::ifstream in_str(inp);
    if (!in_str.good()) {
        std::cerr << "Can't open " << inp << " to read.\n";
        exit(1);
    }
    std::ofstream out_str(outp);
    if (!out_str.good()) {
        std::cerr << "Can't open " << outp << " to write.\n";
        exit(1);
    }

    // initalizes the 
    std::vector<std::string> puz_;
    std::string tmp;
    while (in_str >> tmp) {
        puz_.push_back(tmp);
    }

    puzzle a(puz_);
    a.setS(std::stoi(S_));

    std::vector<std::vector<point>> all;
    // loops through each zone
    for (int i = 0; i < a.getzones(); i++) {
        // loops through each point in the zone
        for(int j = 0; j < a.getzone(i).numzone; j++) {
            int x =0;
            while(x!=5) {
                std::vector<point> cur;
                a.solve(a.getzone(i).zonepoints[j], 0, cur, all);
                if (cur.size() == a.getzones()*a.getS() || inall(cur,all)) {
                    all.push_back(cur);
                }
                x++;
            }
        }
    }

    if (outmod == "count") {
        out_str << "Number of solutions: " << all.size() << std::endl;
    }

    if (outmod == "print") {
        if (solmod == "one_solution") {
            out_str << "Number of solutions: 1" << "\n" << std::endl;
            out_str << "Solution 1:" << std::endl;
            a.print1(out_str, all);
        }
        else if (solmod == "all_solutions") {
            out_str << "Number of solutions: " << all.size() << "\n" << std::endl;
            a.print(out_str, all);
        }
    }
    return 0;
}