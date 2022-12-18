#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#ifndef point_h
#define point_H

class point {
    public:
        point(int x_, int y_, std::string zone_) {
            x = x_;
            y = y_;
            zone = zone_;
        }
        void print() const{
            std::cout << "(" << x <<"," << y << ") " << zone << std::endl;
        }
    int x;
    int y;
    std::string zone;
};
#endif

#ifndef zone_h
#define zone_h

class zone {
    public:
        zone() {
            numzone = 0;
        } 

        void add(const point& a) {
            zonepoints.push_back(a);
            numzone += 1;
            name = a.zone;
        }
        
    std::vector<point> zonepoints;
    int numzone;
    std::string name;
};


#endif

#ifndef __puzzle_H
#define __puzzle_H

class puzzle {
    public:
        puzzle(std::vector<std::string>& vec);

        void print(std::ofstream& out, const std::vector<std::vector<point>>& all) const;
        void print1(std::ofstream& out, const std::vector<std::vector<point>>& all) const;
        int solve(const point& orig, unsigned int pt_indx, std::vector<point>& current_pts, const std::vector<std::vector<point>>& all);
        int getzones() const {return zones.size();}
        zone getzone(int i) const {return zones[i];}
        void setS(unsigned int s) {S = s;}
        unsigned int getS() const {return S;}
        std::vector<std::vector<point>> getpuz() {return puz;}

    private:
        std::vector<std::vector<point>> puz;
        std::vector<point> points;
        std::vector<std::vector<point>> solved;
        std::vector<zone> zones;
        int length;
        int width;
        unsigned int S;
};

bool sortzones(zone a, zone b);
bool validpt(const point& pt, std::vector<point>& current_pts);
bool inall(const std::vector<point>& cur, const std::vector<std::vector<point>>& all);

#endif