#include <iostream>//adds iostream header for files
#include <string>//adds string header to use strings
#include <vector>//adds vector to use vectors
//header file guards
#ifndef __MYCLASS_H
#define __MYCLASS_H
using namespace std;//creates scope

class Course{
public:
//creates strings for the following class to be used
std::string aCRN, aDept, aCnum, aCourse, aDays, aStart, aEnd, aRoom, aDay1, aDay2;
//creates course class and assigns the elements to strings
  Course(std::string crn, std::string dept, std::string cnum, std::string course, std::string days, std::string start, std::string end, std::string room, std::string day1, std::string day2)
  {
      aCRN = crn;
      aDept = dept;
      aCnum = cnum;
      aCourse = course;
      aDays = days;
      aStart = start;
      aEnd = end;
      aRoom = room;
      aDay1 = day1;
      aDay2 = day2;
  }
  // ACCESSORS
  //gets desired element and returns it when called
    std::string getDept(){return aDept;};
    std::string getCnum(){return aCnum;};
    std::string getCourse(){return aCourse;};
    std::string getStart(){return aStart;};
    std::string getEnd(){return aEnd;};
    std::string getRoom(){return aRoom;};
    std::string getDays(){return aDays;};
};
//end if guard
#endif