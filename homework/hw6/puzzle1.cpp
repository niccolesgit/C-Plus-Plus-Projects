#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "puzzle1.h"
// returns true if the current set of points is in "all"
bool inall(const std::vector<point>& cur, const std::vector<std::vector<point>>& all) {
    
    // loops through each solved vector of points in "all"
    for (unsigned int i = 0; i < all.size(); i++) {
        // starts a counter for the amount of points that match in "all" vector
        unsigned int x = 0;
        // loops through each point in the solved vector
        for (unsigned int z = 0; z < cur.size(); z++) {
            
            // loops through each point in cur
            for (unsigned int j = 0; j < all[i].size(); j++) {
                // compares the current point to each solved point
                if (cur[z].x == all[i][j].x && cur[z].y == all[i][j].y) {
                    x++;
                }
            }
            if (x == all[i].size()) {
                return true;
            }
        }
    }

    return false;
}

// goes through the bad points and check to make sure if the current point is valid
bool validpt(const point& pt, std::vector<point>& current_pts, unsigned int S) {
    unsigned int zone_ = 0;
    unsigned int row_ = 0;
    unsigned int column_ = 0;
    // loops through current points
    for (unsigned int i = 0; i < current_pts.size(); i++) {
        // if the points are the same
        if (pt.x == current_pts[i].x && pt.y == current_pts[i].y) {
            return false;
        }

        // if the point is in the same x coloumn, y row, or zone
        if (pt.x == current_pts[i].x){
            column_++;
        } 
        if (pt.y == current_pts[i].y) {
            row_++;
        } 
        if (pt.zone == current_pts[i].zone) {
            zone_++;
        }

        // if the point is directly touching any other point
        if ((pt.x == current_pts[i].x+1 && pt.y == current_pts[i].y+1) || (pt.x == current_pts[i].x+1 && pt.y == current_pts[i].y-1) ||
                    (pt.x == current_pts[i].x-1 && pt.y == current_pts[i].y-1) || (pt.x == current_pts[i].x-1 && pt.y == current_pts[i].y+1) ||
                        (pt.x == current_pts[i].x+1 && pt.y == current_pts[i].y) || (pt.x == current_pts[i].x-1 && pt.y == current_pts[i].y) ||
                            (pt.x == current_pts[i].x && pt.y == current_pts[i].y+1) || (pt.x == current_pts[i].x && pt.y == current_pts[i].y-1)) {
            return false;
        }
    }
    // compares the counters to S
    if (column_ == S || row_ == S || zone_ == S) {
        return false;
    }
    return true;
}

bool sortzones(zone a, zone b) {
    if (a.numzone >= b.numzone) {
        return false;
    }
    else {
        return true;
    }
}

puzzle::puzzle(std::vector<std::string>& vec) {
    length = std::stoi(vec[0]);
    width = std::stoi(vec[1]);
    int tmp = 0;
    std::string let;
    unsigned int zone_num;
    for (int i = 0; i < width; i++) {
        std::vector<point> tmp1;
        for (int j = 0; j < length; j++) {
            tmp1.push_back(point(0,0,""));
        }
        puz.push_back(tmp1);
    }

    while (true) {
        int x = 0;
        let = vec[2+tmp];
        zone_num = std::stoi(vec[3+tmp]);
        zone tmp2;
        for (unsigned int i = 4+tmp; i < ((zone_num * 2) + 3+tmp); i=i+2) {
            tmp2.add(point(std::stoi(vec[i]),std::stoi(vec[i+1]),let));
            points.push_back(point(std::stoi(vec[i]),std::stoi(vec[i+1]),let));
            puz[std::stoi(vec[i])][std::stoi(vec[i+1])] = point(std::stoi(vec[i]),std::stoi(vec[i+1]),let);
            if (i+2 >= vec.size()) {
                x = 1;
            }
        }
        zones.push_back(tmp2);
        if (x == 1) {
            break;
        };
        tmp += zone_num * 2 +2;
    }
    std::sort(zones.begin(), zones.end(), sortzones);
    /*for (unsigned int i = 0; i < points.size(); i ++) {
        points[i].print();
    }*/
}

void puzzle::print(std::ofstream& out, const std::vector<std::vector<point>>& all) const {
    for (unsigned int i_ = 0; i_ < all.size(); i_++) {
        out << "Solution " << i_+1 << ":" << std::endl;
        int tmp = 0;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                for (unsigned int j_ = 0; j_ < all[i_].size(); j_++) {
                    if (i == all[i_][j_].y && j == all[i_][j_].x) {
                        out << "@";
                        tmp = 1;
                        break;
                    }
                }
                if (tmp == 0) {
                    out << puz[j][i].zone;
                }
                tmp = 0;
            }
            out << std::endl;
        }
        out << "\n";
    }
}

void puzzle::print1(std::ofstream& out, const std::vector<std::vector<point>>& all) const {
    int tmp = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            for (unsigned int i_ = 0; i_ < all[0].size(); i_++) {
                if (i == all[0][i_].y && j == all[0][i_].x) {
                    out << "@";
                    tmp = 1;
                    break;
                }
            }
            if (tmp == 0) {
                out << puz[j][i].zone;
            }
            tmp = 0;
        }
        out << std::endl;
    }
}

// uses recursion to solve the puzzle with the intial point given
int puzzle::solve(const point& orig, unsigned int pt_indx, std::vector<point>& current_pts, const std::vector<std::vector<point>>& all) {
    // the inital point is pushed into the current points vector
    if (current_pts.size() == 0) {
        current_pts.push_back(orig);
        solve(zones[0].zonepoints[1], 0, current_pts, all);
    }
    // base case if the amount of current points equals the amount of zones times S
    if (current_pts.size() == (this -> getzones())*S) {
        return 1;
    }
    // if the point is valid and the index is less than the size off all the points
    if (validpt(points[pt_indx], current_pts, S) && pt_indx < points.size()) {
        current_pts.push_back(points[pt_indx]);
        if (inall(current_pts, all)) {
            current_pts.pop_back();
        }
    }
    if (pt_indx >= points.size()) {
        return 0;
    }
    solve(orig, pt_indx+1, current_pts, all);
    return 0;
}