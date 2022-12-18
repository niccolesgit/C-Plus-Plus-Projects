#include <iostream>
#include <string>
#include "time.h"
#include <algorithm>

Time::Time(){	//default constructor
  hour = 0;
  minute = 0;
  second = 0;
}

Time::Time(int aHour, int aMinute, int aSecond){ // construct from month, day, & year
  hour = aHour;
  minute= aMinute;
  second = aSecond;
}


int Time::getHour() const {
  return hour;
}

int Time::getMinute() const {
  return minute;
}
	
int Time::getSecond() const {
  return second;
}

void Time::setHour(int h) {
  hour = h;
}

void Time::setMinute(int m) {
    minute = m;
}

void Time::setSecond(int s) {
    second = s; 
}


void Time::PrintAMPM(){
  int armHour, armMinute, armSecond;
  std::string merid;
  if (hour < 13 && hour !=0){
      armHour = hour;
      merid = "am";
  }else if (hour > 12){
      armHour = hour-12;
      merid = "pm";
  }else if(hour == 0){
      armHour = hour +12;
      merid = "am";
  }
  armMinute = minute;
  armSecond = second;
  
  if (armSecond < 10 && armMinute < 10){
    std::cout << armHour << ":0" << armMinute << ":0"<< armSecond << merid << std::endl;
  }else if (armSecond < 10){
    std::cout << armHour << ":" << armMinute << ":0" << armSecond << merid << std::endl;
  }else if (armMinute < 10){
    std::cout << armHour << ":0" << armMinute << ":" << armSecond << merid << std::endl;
  }else{
    std::cout << armHour << ":" << armMinute << ":" << armSecond << merid << std::endl;
  }
}

bool IsEarlierThan(const Time& t1, const Time& t2){
    if (t1.getHour()<t2.getHour()){
        return true;
    }else if (t1.getHour()>t2.getHour()){
        return false;
    }else if (t1.getMinute()<t2.getMinute()){
        return true;
    }else if (t1.getMinute()>t2.getMinute()){
        return false;
    }else if (t1.getSecond()<t2.getSecond()){
        return true;
    }else if (t1.getSecond()>t2.getSecond()){
        return false;
    }else{
        return false;
    }
}


