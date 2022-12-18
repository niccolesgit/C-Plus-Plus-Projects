#include "superhero.h"
#include <string>
#include <iostream>
#include <list>
Superhero::Superhero(const std::string &name_, const std::string &id_, const std::string &power_){
    name = name_;
    id = id_;
    power = power_;
}

const std::string Superhero::getName(){
    return name;
}
const std::string Superhero::getPower(){
    return power;
}
std::ostream& operator<< (std::ostream& out, Superhero& s){
    out << "Superhero " << s.getName() << " has power " << s.getPower() << std::endl;
}