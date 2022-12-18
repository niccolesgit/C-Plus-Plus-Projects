#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "board1.h"
Board::Board(std::vector<std::string> & v){
    row = std::stoi(v[0]);
    col = std::stoi(v[1]);
    std::string zchar;
    unsigned int num_in_zone;
    int temp = 0;
    for(int i =0;i<col;i++){
        std::vector<Point> tempvect;
        for(int j = 0; j<row;j++){
            tempvect.push_back(Point(0,0,""));
        }
        boardv.push_back(tempvect);

    }
    while(true){
        int c = 0;
        zchar = v[2+temp];
        num_in_zone = std::stoi(v[3+temp]);
        Zone zTemp;
        for(unsigned int i = 4+temp; i<((num_in_zone*2)+3+temp); i=i+2){
            zTemp.add(Point(std::stoi(v[i]), std::stoi(v[i+1]), zchar));
            vpoints.push_back(Point(std::stoi(v[i]), std::stoi(v[i+1]), zchar));
            boardv[std::stoi(v[i])][std::stoi(v[i+1])];
            if(i+2 >= v.size()){
                c =1;
            }
        }
        all_zones.push_back(zTemp);
        if(c==1){
            break;
        }
        temp += num_in_zone *2+2;
    }
    std::sort(all_zones.begin(), all_zones.end(), sortZ);

}
int Board::getIndex(Point p) const {
    for(unsigned int i = 0; i<vpoints.size();i++){
        if(p.x == vpoints[i].x && p.y == vpoints[i].y){
            return i;
        }
    }
    return 0;
}
int Board::solve(const Point& start, unsigned int pindex, std::vector<Point> &cpoints, 
        std::vector<std::vector<Point>>& avect){
    if (cpoints.size() == 0) {
        cpoints.push_back(start);
        solve(all_zones[0].zpoints[1], 0, cpoints, avect);
    }
    // base case if the amount of current points equals the amount of zones times S
    if (cpoints.size() == (this -> getZSize())*s) {
        return 1;
    }
    // if the point is valid and the index is less than the size off all the points
    if (isValid(vpoints[pindex], cpoints, s) && pindex < vpoints.size()) {
        cpoints.push_back(vpoints[pindex]);
        if (isInAll(cpoints, avect)) {
            cpoints.pop_back();
        }
    }
    if (pindex >= vpoints.size()) {
        return 0;
    }
    solve(start, pindex+1, cpoints, avect);
    return 0;
}
void Board::printOne(std::ofstream & out, const std::vector<std::vector<Point>>& avect) const{
    int temp = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            for (unsigned int k = 0; k < avect[0].size(); k++) {
                if (i == avect[0][k].y && j == avect[0][k].x) {
                    out << "@";
                    temp = 1;
                    break;
                }
            }
            if (temp == 0) {
                out << boardv[j][i].zone;
            }
            temp = 0;
        }
        out << std::endl;
    }
}
void Board::printAll(std::ofstream & out, const std::vector<std::vector<Point>>& avect) const{
    for(unsigned int x = 0; x<avect.size(); x++){
        out<<"Solution " << x+1 << ":" << std::endl;
        int temp = 0;
        for(int i =0; i<row;i++){
            for(int j = 0; j<col;j++){
                for(unsigned int y = 0; y < avect[x].size();y++){
                    if(j == avect[x][y].x && i == avect[x][y].y){
                        out << "@";
                        temp = 1;
                        break;
                    }
                }
                if(temp == 0){
                    out << boardv[j][i].zone;
                }
                temp = 0;
            }
            out << std::endl;
        }
        out << "\n";
    }
}
bool sortZ(Zone p1, Zone p2){
    if(p1.nzone < p2.nzone){
        return true;
    }else{
        return false;
    }

}
bool isValid(const Point & p, std::vector<Point>& cpoints, unsigned int s){
    unsigned int row = 0;
    unsigned int col = 0;
    unsigned int zon = 0;
    for(unsigned int i = 0; i<cpoints.size();i++){
        if (p.x == cpoints[i].x && p.y == cpoints[i].y){
            return false;
        }
        if(p.x == cpoints[i].x){
            col++;
        }
        if(p.y == cpoints[i].y){
            row++;
        }
        if(p.zone == cpoints[i].zone){
            zon++;
        }
        if((p.x == cpoints[i].x && p.y == cpoints[i].y +1)|| (p.x == cpoints[i].x && p.y == cpoints[i].y-1)||
        (p.x == cpoints[i].x+1 && p.y == cpoints[i].y)|| (p.x == cpoints[i].x-1 && p.y == cpoints[i].y)||
        (p.x == cpoints[i].x-1 && p.y == cpoints[i].y-1)||(p.x == cpoints[i].x-1 && p.y == cpoints[i].y+1)||
        (p.x == cpoints[i].x+1 && p.y == cpoints[i].y+1)|| (p.x == cpoints[i].x+1 && p.y == cpoints[i].y-1)){
            return false;
        }
    }
    if(row == s || col == s || zon == s){
        return false;
    }
    return true;
    

}
bool isInAll(const std::vector<Point>& cvect, const std::vector<std::vector<Point>> & avect){
    for(unsigned int i = 0; i < avect.size();i++){
        unsigned int c = 0;
        for(unsigned int j = 0; j<cvect.size();j++){
            for(unsigned int k = 0; k<avect[i].size(); k++){
                if (cvect[j].x == avect[i][k].x && cvect[j].y == avect[i][k].y){
                    c++;
                }
            }
            if(c == avect[i].size()){
                return true;
            }
        }
    }
    return false;

}
