#ifndef __superhero_h_
#define __superhero_h_
#include <string>
#include <iostream>

class Superhero{

public:

    friend class Team;

    Superhero(std::string n, std::string i, std::string p): name(n), identity(i), power(p), good(true){}

    const std::string getName() const {return name;}
    const std::string getPower() const {return power;}
    bool isGood() const {return good;}

    bool operator==(const std::string& guess){if(guess == identity) return true; else return false;}
    bool operator!=(const std::string& guess){if(guess != identity) return true; else return false;}

    void operator-(){
        if(good) good = false;
        else good = true;
    }

    friend bool operator>(const Superhero& s1, const Superhero& s2){
        if(s1.getPower() == "Fire" && s2.getPower() == "Wood") return true;
        else if(s1.getPower() == "Wood" && s2.getPower() == "Water") return true;
        else if(s1.getPower() == "Water" && s2.getPower() == "Fire") return true;
        else if(s1.getPower() == "Laser" && s2.getPower() == "Flying") return true;
        else if(s1.getPower() == "Flying" && s2.getPower() == "Speed") return true;
        else if(s1.getPower() == "Speed" && s2.getPower() == "Flexible") return true;
        else if(s1.getPower() == "Flexible" && s2.getPower() == "Flying") return true;
        else return false;
    }
    friend std::ostream& operator<<(std::ostream& ostr, const Superhero& s){
        if(s.isGood())
            ostr << "Superhero " << s.getName() << " has power " << s.getPower() << std::endl;
        else
            ostr << "Supervillain " << s.getName() << " has power " << s.getPower() << std::endl;
        return ostr;
    }


private:
    std::string name;
    std::string identity;
    std::string power;
    bool good;
    const std::string getTrueIdentity() const {return identity;}

};

#endif