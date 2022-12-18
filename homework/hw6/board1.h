#include <iostream>
#include <string>
#include <vector>

#ifndef point_h
#define point_h

class Point{
    public:
        Point(int x_, int y_, std::string zone_){
            x = x_;
            y = y_;
            zone = zone_;

        }
    int x;
    int y;
    std::string zone; 
};
#endif

#ifndef zone_h
#define zone_h

class Zone{
    public:
        Zone(){
            nzone = 0;
        }
        void add(const Point& p){
            zpoints.push_back(p);
            zlet = p.zone;
            nzone +=1;
        }
    int nzone;
    std::vector<Point> zpoints;
    std::string zlet;
};
#endif

#ifndef board_h
#define board_h
class Board{
    public:
        //constructor
        Board(std::vector<std::string> & v);
        //acessors
        int getIndex(Point p) const;
        int getPSize() const {return vpoints.size();}
        unsigned int getStars() const {return s;}
        std::vector<std::vector<Point>> getBoard() {return boardv;}
        int getZSize() const {return all_zones.size();}
        Zone getZ(int i) const {return all_zones[i];}
        //modifiers
        void setStars(unsigned int s_) {s = s_;}
        //solve function
        int solve(const Point& start, unsigned int pindex, std::vector<Point> &cpoints, 
            std::vector<std::vector<Point>>& all);
        //print functions
        void printOne(std::ofstream & out, const std::vector<std::vector<Point>>& all) const;
        void printAll(std::ofstream & out, const std::vector<std::vector<Point>>& all) const;
    private:
        std::vector<std::vector<Point>> boardv;
        std::vector<std::vector<Point>> solutionv;
        std::vector<Point> vpoints;
        std::vector<Zone> all_zones;
        int row;
        int col;
        unsigned int s;
};
bool sortZ(Zone p1, Zone p2);
bool isInAll(const std::vector<Point>& current, const std::vector<std::vector<Point>> & all);
bool isValid(const Point & p, std::vector<Point>& cpoints, unsigned int s);
#endif