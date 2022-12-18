#include <iostream> // input output stream
#include <fstream> // file stream
#include <string> //string header file
#include <vector> //vector header file
#include <iomanip>
#include "myclass.h"
using namespace std; //creates proper scope
//helper funtion to help
string repeat(string s, int n)
{
    // Copying given string to temporary string.
    string s1 = s;
 
    for (int i=1; i<n;i++)
        s += s1; // Concatenating strings
 
    return s;
}
void setDays(std::string &aDays,std::string &aDay1,std::string &aDay2){
    if (aDays == "MR"){
        aDay1 = "Monday";
        aDay2 = "Thursday";
    }else if (aDays == "TF"){
        aDay1 = "Tuesday";
        aDay2 = "Friday";
    }else{
        aDay1 = "Wednesday";
        aDay2 = "None";
    }
}
int main(int argc, char* argv[]) 
{
  std::ifstream infile(argv[1]);
  std::ofstream outfile(argv[2]);
  std::string com = argv[3];
  std::string crn, dept, cnum, course, days, start, end, room, day1, day2;
  unsigned int clen = 0;
  unsigned int entryc = 0;
  unsigned int dlen = 0;
  std::string defroom, defdept, scourse,sday;
  std::string line = "-";
  unsigned int c = 0;
  std::vector<Course> vect;
  if (argc < 4){
      std::cout << "Error: invalid arguments" << std::endl;
  }
  if ( infile.peek() == std::ifstream::traits_type::eof() )
  {
      outfile << "No data available.";
      infile.close();
      outfile.close();
      }
  //64859 CSCI 4030-01 RANDOMIZED_ALGORITHMS MR 10:00AM 11:50AM DARRIN_239
  while(infile >> crn >> dept >> cnum >> course >> days >> start >> end >> room){
      Course cs = Course(crn, dept, cnum, course, days, start, end, room);
      std::string cstring = cs.aCourse;
      defroom = cs.aRoom;
      defdept = cs.aDept;
      if (cstring.length()>clen){
          clen = cstring.length();
      }
      setDays(cs.aDays, day1, day2);
      if (day2 != "None"){
          entryc +=2;
          if(day1.length()>day2.length()){
              dlen = day1.length();
          }else if(day1.length()<day2.length()) {
              dlen = day2.length();
          }else{
              dlen = day1.length();
          }
      }else{
          entryc +=1;
          if (day1.length()>dlen){
              dlen = day1.length();
          }
      }
    if(c == 0){
        if (argc == 4){
          if (com == "room"){
              outfile <<"Room " << defroom << "\n";
              scourse = repeat(line, clen);
                sday = repeat(line, dlen);
                clen +=2;
                dlen += 2;
                    outfile
                            << left
                            << setw(6)
                            << "Dept"
                            << left
                            << setw(11)
                            << "Coursenum"
                            << left
                            << setw(clen)
                            << "Class Title"
                            << left
                            << setw(dlen)
                            << "Day"
                            << left
                            << setw(12)
                            << "Start Time"
                            << left
                            << setw(8)
                            << "End Time"
                            << endl;
                    outfile
                            << left
                            << setw(6)
                            << "----"
                            << left
                            << setw(11)
                            << "---------"
                            << left
                            << setw(clen)
                            << scourse
                            << left
                            << setw(dlen)
                            << sday
                            << left
                            << setw(12)
                            << "----------"
                            << left
                            << setw(8)
                            << "--------"
                            << endl;
                            c+=1;
          }
          }else if(argc == 5 && com == "dept"){
              std::string specif = argv[4];
              outfile <<"Dept " << specif << "\n";
              scourse = repeat(line, clen);
              sday = repeat(line, dlen);
                clen +=2;
                dlen += 2;
        outfile
            << left
            << setw(11)
            << "Coursenum"
            << left
            << setw(clen)
            << "Class Title"
            << left
            << setw(dlen)
            << "Day"
            << left
            << setw(12)
            << "Start Time"
            << left
            << setw(8)
            << "End Time"
            << endl;
            outfile
            << left
            << setw(11)
            << "---------"
            << left
            << setw(clen)
            << scourse
            << left
            << setw(dlen)
            << sday
            << left
            << setw(12)
            << "----------"
            << left
            << setw(8)
            << "--------"
            << endl;
        c+=1;
        }else if(argc == 5 && com == "room"){
          std::string specif = argv[4];
              cout<<"Room " << specif << endl;
              scourse = repeat(line, clen);
              sday = repeat(line, dlen);
                clen +=2;
                dlen += 2;
        outfile
            << left
            << setw(11)
            << "Coursenum"
            << left
            << setw(clen)
            << "Class Title"
            << left
            << setw(dlen)
            << "Day"
            << left
            << setw(12)
            << "Start Time"
            << left
            << setw(8)
            << "End Time"
            << endl;
            outfile
            << left
            << setw(11)
            << "---------"
            << left
            << setw(clen)
            << scourse
            << left
            << setw(dlen)
            << sday
            << left
            << setw(12)
            << "----------"
            << left
            << setw(8)
            << "--------"
            << endl;
        c+=1;
              }
        }

    if (day2!= "None" && com == "room"){
         outfile 
            << left
            << setw(6)
            << cs.aDept
            << left
            << setw(11)
            << cs.aCnum
            << left
            << setw(clen)
            << cs.aCourse
            << left
            << setw(dlen)
            << day1
            << left
            << setw(12)
            << cs.aStart
            << left
            << setw(8)
            << cs.aEnd
            << endl;
        outfile
            << left
            << setw(6)
            << cs.aDept
            << left
            << setw(11)
            << cs.aCnum
            << left
            << setw(clen)
            << cs.aCourse
            << left
            << setw(dlen)
            << day2
            << left
            << setw(12)
            << cs.aStart
            << left
            << setw(8)
            << cs.aEnd
            << endl;

    }else if (day2!= "None" && com == "dept"){
        outfile
            << left
            << setw(11)
            << cs.aCnum
            << left
            << setw(clen)
            << cs.aCourse
            << left
            << setw(dlen)
            << day1
            << left
            << setw(12)
            << cs.aStart
            << left
            << setw(8)
            << cs.aEnd
            << endl;
    outfile
            << left
            << setw(11)
            << cs.aCnum
            << left
            << setw(clen)
            << cs.aCourse
            << left
            << setw(dlen)
            << day2
            << left
            << setw(12)
            << cs.aStart
            << left
            << setw(8)
            << cs.aEnd
            << endl;
    }
    }
  outfile << entryc << " entries";
  outfile << std::endl;
  outfile.close();
   return 0;
}


