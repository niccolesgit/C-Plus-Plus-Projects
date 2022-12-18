#include <iostream> // input output stream
#include <fstream> // file stream
#include <string> //string header file
#include <vector> //vector header file
#include <iomanip>
#include "myclass.h"
using namespace std; //creates proper scope

/*void room(std::vector<vector<string>>& vect, std::string aroom){
    std::vector<vector<string>> vectcopy;
    vectcopy = vect;


}*/
int main(int argc, char* argv[]) 
{
  std::ifstream infile(argv[1]);
  std::ofstream outfile(argv[2]);
  std::string crn, dept, cnum, course, days, start, end, room;
  std::vector<string> vCRN, vDEPT, vCNUM, vCOURSE, vDAYS, vSTART, vEND, vROOM;
  //64859 CSCI 4030-01 RANDOMIZED_ALGORITHMS MR 10:00AM 11:50AM DARRIN_239
  while(infile >> crn >> dept >> cnum >> course >> days >> start >> end >> room){
      vCRN.push_back(crn);
      vDEPT.push_back(dept);
      vCNUM.push_back(cnum);
      vCOURSE.push_back(course);
      vDAYS.push_back(days);
      vSTART.push_back(start);
      vEND.push_back(end);
      vROOM.push_back(room);

    }
    std::vector<vector<string>> filev{vCRN, vDEPT, vCNUM, vCOURSE, vDAYS, vSTART, vEND, vROOM};
    std::string comm = argv[3];
    std::string specif = argv[4];

    std::cout << "Room " <<specif << std::endl;
    std::cout << comm << " " <<specif << std::endl; 


   for (unsigned int i = 0; i < filev.size(); i++)
    {
        for (unsigned int j = 0; j < filev[i].size(); j++)
        {
            cout << filev[i][j] << endl;
        }   
    }
   return 0;
}

