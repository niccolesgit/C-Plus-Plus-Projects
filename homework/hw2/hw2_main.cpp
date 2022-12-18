// Program:  hw2_main.cpp
// Purpose:  To sort and organize classes based on the user input
#include <iostream> // input output stream
#include <fstream> // file stream
#include <string> //string header file
#include <vector> //vector header file
#include <iomanip> //
#include "myclass.h" //uses class header file
#include <algorithm> //uses algorithm header
using namespace std; //creates proper scope
//function to concantentate strings based on a number of times
string repeat(string s, int n) 
{
    string s1 = s;
 
    for (int i=1; i<n;i++)
        s += s1; 
    return s;
}
//function that sets days based on the day intitals 
void setDays(std::string &aDays,std::string &aDay1,std::string &aDay2){
    if (aDays == "MR"){ //sets monday and thursday
        aDay1 = "Monday";
        aDay2 = "Thursday";
    }else if (aDays == "TF"){ //sets tuesday and friday
        aDay1 = "Tuesday";
        aDay2 = "Friday";
    }else if (aDays == "T"){ // sets if only tuesday
        aDay1 = "Tuesday";
    }else if (aDays == "W"){ //sets if only wednesday
        aDay1 = "Wednesday";
        aDay2 = "None";
    }
}
//function that sorts the time based on the data in the vector
void sortTime(std::vector<Course>& timev){
    std::vector<string> ams, pms, twelves;
     std::vector<Course> times;
    //Takes all the ams into a vector
    for (unsigned int i = 0;i<timev.size();i++){
        std::string start = timev[i].aStart;
        std::string merid = start.substr(5, 6);
        if (merid == "AM"){
            ams.push_back(start);
        }
    }
    //Takes all the pms into a vector and 
    //inputs 12s into a seperate vector to not
    //mess up sorting
    for (unsigned int i = 0;i<timev.size();i++){
        std::string start = timev[i].aStart;
        std::string merid = start.substr(5, 6);
        std::string hour = start.substr(0, 2);
        if (merid == "PM" && hour != "12"){
            pms.push_back(start);
        }else if(merid == "PM" && hour == "12"){
            twelves.push_back(start);
        }
    }
    //sorts ams pms and 12s
    sort(ams.begin(), ams.end());
    sort(pms.begin(), pms.end());
    sort(twelves.begin(), twelves.end());
    //creates a new vector that has all of the times in order
    std::vector<string> atimes(ams);
    atimes.insert(atimes.end(), twelves.begin(), twelves.end());
    atimes.insert(atimes.end(), pms.begin(), pms.end());
    //takes those times and puts the classes in order based on the times
    for (unsigned int i = 0;i<atimes.size();i++){
        for (unsigned int j = 0;j<timev.size();j++){
            if (atimes[i] == timev[j].aStart){
                times.push_back(timev[j]);
                }
        }
     }
     //changes the original classes to sorted time classes
    timev = times;
}
//custom: checks if the file/user has a class at 8AM
void eightAMs(std::vector<Course>& timev){
    std::vector<Course> eights;
    for (unsigned int i = 0;i<timev.size();i++){
        std::string start = timev[i].aStart;
        std::string merid = start.substr(5, 6);
        std::string hour = start.substr(0, 2);
        if (merid == "AM" && hour == "08"){ //if its am and starts with 08
            eights.push_back(timev[i]); //adds it so an 8am vector
        }
    }
    timev = eights;//sets time vector to 8ams only
}
//function that sorts course numbers
void sortCnum(std::vector<Course>& cnumv){
    std::vector<string> cnums; 
    std::vector<Course> scnums;
    //takes all the course nums and adds it to the vector
    for (unsigned int i = 0;i<cnumv.size();i++){
        cnums.push_back(cnumv[i].aCnum);
    }
    //sorts the vector
    sort(cnums.begin(), cnums.end());
    //takes the sorted course nums and orders the classes
    //based on the sorting
     for (unsigned int i = 0;i<cnums.size();i++){
        for (unsigned int j = 0;j<cnumv.size();j++){
            if (cnums[i] == cnumv[j].aCnum){
                scnums.push_back(cnumv[j]);
                }
        }
     }
     cnumv = scnums;//changes the classes to sorted classes

}
//function to print the read command for mondays, tuesdays, and wednesdays
void printR_MTW(std::vector<Course>&vec, unsigned int &clen, unsigned int &dlen, std::ofstream& outfile){
for (unsigned int i = 0;i<vec.size();i++){
    outfile
            << left
            << setw(6)
            << vec[i].aDept
            << left
            << setw(11)
            << vec[i].aCnum
            << left
            << setw(clen)
            << vec[i].aCourse
            << left
            << setw(dlen)
            << vec[i].aDay1 //Only prints day 1 (with the possibilities only being MT&W)
            << left
            << setw(12)
            << vec[i].aStart
            << left
            << setw(8)
            << vec[i].aEnd
            << endl;
            }
}
//print function to print thursdays and fridays
void printR_TF(std::vector<Course>&vec, unsigned int &clen, unsigned int &dlen, std::ofstream& outfile){
    for (unsigned int i = 0;i<vec.size();i++){
    outfile
            << left
            << setw(6)
            << vec[i].aDept
            << left
            << setw(11)
            << vec[i].aCnum
            << left
            << setw(clen)
            << vec[i].aCourse
            << left
            << setw(dlen)
            << vec[i].aDay2 //prints day2 which can only be R or F
            << left
            << setw(12)
            << vec[i].aStart
            << left
            << setw(8)
            << vec[i].aEnd
            << endl;
            }
}
//fucntion that prints the vector sorted by course number
void printDept(std::vector<Course>&vec, unsigned int &clen, unsigned int &dlen, std::ofstream& outfile){
    for (unsigned int i = 0;i<vec.size();i++){
        //if the day1 is monday, tuesday, or wednesday, prints only the day1
        if (vec[i].aDay1 == "Monday" || vec[i].aDay1 == "Tuesday" || vec[i].aDay1 == "Wednesday"){
                outfile
                    << left
                    << setw(11)
                    << vec[i].aCnum
                    << left
                    << setw(clen)
                    << vec[i].aCourse
                    << left
                    << setw(dlen)
                    << vec[i].aDay1
                    << left
                    << setw(12)
                    << vec[i].aStart
                    << left
                    << setw(8)
                    << vec[i].aEnd
                    << endl;
        }//if the day2 is thursday or friday, only prints the day2
            if(vec[i].aDay2 == "Thursday" || vec[i].aDay2 == "Friday"){
                outfile
                    << left
                    << setw(11)
                    << vec[i].aCnum
                    << left
                    << setw(clen)
                    << vec[i].aCourse
                    << left
                    << setw(dlen)
                    << vec[i].aDay2
                    << left
                    << setw(12)
                    << vec[i].aStart
                    << left
                    << setw(8)
                    << vec[i].aEnd
                    << endl;
            }
    }
}
int main(int argc, char* argv[]) 
{
  std::ifstream infile(argv[1]);//sets and creates input file from command
  std::ofstream outfile(argv[2]);//creates output file from command
  std::string com = argv[3];//makes the third arg a string for comparisons
  std::string crn, dept, cnum, course, days, start, end, room, day1, day2; //creates various string variables
  unsigned int entryc = 0; //creates a counter for the amount of entires
  std::string defroom, defdept, scourse, sday; //creats more strings
  unsigned int clen = 0; //sets course length for read
  unsigned int dlen = 0; //sets depertment length for read
  unsigned int dclen = 0; //sets course length for dept
  unsigned int ddlen = 0; //sets dept length for dept
  std::string line = "-"; //sets string to header char
  std::vector<Course> vect, mon, tues,weds,thurs,fri; //creates class vector and days of the week vector
  std::vector<string> arooms; //creates a string to hold all the rooms
  //error checks:
  if (argc < 4){//if there are invalid number of commands
      std::cerr << "Inavlid arguments (please use 4 to 5)"; 
  }
  if (argc == 4 && com == "dept"){//if there is no 5th argument for dept
      std::cerr << "Please input a specified department."; 
  }
  if (!infile){//if the file doesn't exist
        std::cerr << "Could not find input file.";
  }
   if(!infile.is_open()){//if the input file can't be opened
        std::cerr << "Could not open input file.";
   }
  if ( infile.peek() == std::ifstream::traits_type::eof() )//if the input file is blank
  {
      outfile << "No data available."; //outputs no data is available
      infile.close();
      outfile.close();
      }
//loop that goes through the entire file to get all the information in the line
  while(infile >> crn >> dept >> cnum >> course >> days >> start >> end >> room){
      //creates a course class with variables from the line and empty day1 and day2
      Course cs = Course(crn, dept, cnum, course, days, start, end, room, day1, day2);
      std::string cstring = cs.aCourse; //string of the course
      defroom = cs.aRoom; //finds the default room
      defdept = cs.aDept; //finds the default dept
      if (cstring.length()>clen){//checks to find the longest course string
          clen = cstring.length();
            }
      setDays(cs.aDays, cs.aDay1, cs.aDay2);//sets the days of the class to day1 and day2
      std::string sDay1 = cs.aDay1;
      std::string sDay2 = cs.aDay2;
      vect.push_back(cs);//adds the updated class to the new vector
      if (sDay1.length() > dlen || sDay2.length() > dlen){ //checks to find the longest day string
          if (sDay1.length() > sDay2.length()){
              dlen = sDay1.length();                                                                                
          }else if (sDay1.length() < sDay2.length()){
              dlen = sDay2.length();
        }
    }
  } //while 

  //loops through if the command is room (a sad attempt at medium1.txt room command :( )
  if (argc == 4 && com == "room"){
      std::vector<Course> vsproom; //creates vector for specific room
      for(unsigned int i = 0; i<vect.size();i++){ //adds all the rooms to a vector
          std::string sroom = vect[i].aRoom;
          arooms.push_back(sroom);
      }
      std::sort(arooms.begin(), arooms.end()); //sorts the rooms alphabetically
      std::unique(arooms.begin(), arooms.end()); //finds all the unique rooms
      for (unsigned int i = 0; i<arooms.size();i++){//loops through all the rooms
          vsproom.clear(); //clears vector for next input
          for(unsigned int j = 0; j<vect.size();j++){ //if the room matches the current room in the loop
              if (vect[j].aRoom == arooms[i]){
                  vsproom.push_back(vect[j]); //add it to the vector
              }
          }
          //finds the length of the course and days from the newly sorted vector (similar to the code above)
          for(unsigned int i = 0; i<vsproom.size();i++){
            std::string vcourse = vsproom[i].aCourse;
            if (vcourse.length()>clen){
            clen = vcourse.length();
            }
        std::string sDay1 = vsproom[i].aDay1;
        std::string sDay2 = vsproom[i].aDay2;
        if (sDay1.length() > dlen || sDay2.length() > dlen){
          if (sDay1.length() > sDay2.length()){
              dlen = sDay1.length();                                                                                
          }else if (sDay1.length() < sDay2.length()){
              dlen = sDay2.length();
                }
            }
        }
        vect = vsproom; 
        //creates vectors for days of the week, sorting all the classes into them
        for(unsigned int i = 0; i<vect.size();i++){
            if (vect[i].aDay1 == "Monday"){
                mon.push_back(vect[i]);
            }else if (vect[i].aDay1 == "Tuesday"){
                tues.push_back(vect[i]);
            }else if(vect[i].aDay1 == "Wednesday"){
                weds.push_back(vect[i]);
            }
        }
    for(unsigned int i = 0; i<vect.size();i++){
        if (vect[i].aDay2 == "Thursday"){
            thurs.push_back(vect[i]);
        }else if(vect[i].aDay2 == "Friday"){
            fri.push_back(vect[i]);
        }
    }
    //prints the room specifed and the proper heading
        outfile <<"Room " << arooms[i] << "\n";
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
        //print all of the classes in the room
        //sorts all the times for all the days of the week vectors
        sortTime(mon);
        sortTime(tues);
        sortTime(weds);
        sortTime(thurs);
        sortTime(fri);
        //combines vectors 
        std::vector<Course> finalv(mon);
        finalv.insert(finalv.end(), tues.begin(), tues.end());
        finalv.insert(finalv.end(), weds.begin(), weds.end());
        finalv.insert(finalv.end(), thurs.begin(), thurs.end());
        finalv.insert(finalv.end(), fri.begin(), fri.end());
        //prints all the vectors
        printR_MTW(mon, clen, dlen, outfile);
        printR_MTW(tues, clen, dlen, outfile);
        printR_MTW(weds, clen, dlen, outfile);
        printR_TF(thurs, clen, dlen, outfile);
        printR_TF(fri, clen, dlen, outfile);

        //takes the size of all the vectors to get the number of entries
        entryc = finalv.size();
        //prints entries and new lines
        outfile << entryc << " entries";
        outfile << "\n";
        outfile << "\n";
        exit(-1); //exits to not mess up other inputs (simple2.txt)
      }
      //closes the files after loop is done
      infile.close();
     outfile.close();
    }


  
  //sorts the vector into the courses with the specified department
  if (argc == 5 && com == "dept"){
       std::string specif = argv[4]; //gets specific department
        std::vector<Course> sdept; //creates new vector to put unique classes in
       for(unsigned int i = 0; i<vect.size();i++){
           std::string vdept = vect[i].aDept;
           if (vdept == specif){
               sdept.push_back(vect[i]);
           }
        }
    vect = sdept; //sets the old classes to the specified classes
    //gets the new max length of the course and max length of the day(similar to code above)
    for(unsigned int i = 0; i<vect.size();i++){
        std::string vcourse = vect[i].aCourse;
        if (vcourse.length()>dclen){
          dclen = vcourse.length();
          }
        std::string sDay1 = vect[i].aDay1;
        std::string sDay2 = vect[i].aDay2;
      if (sDay1.length() > ddlen || sDay2.length() > ddlen){
          if (sDay1.length() > sDay2.length()){
              ddlen = sDay1.length();                                                                                
          }else if (sDay1.length() < sDay2.length()){
              ddlen = sDay2.length();
                }
            }
        vect = sdept; 
        }
  }
  //sorts the new specifc room into new vectors (simiar to departments above)
  if(argc == 5 && com == "room"){ 
       std::string specif = argv[4];
        std::vector<Course> sroom;
       for(unsigned int i = 0; i<vect.size();i++){ 
           std::string vroom = vect[i].aRoom;
           if (vroom == specif){
               sroom.push_back(vect[i]);
           }
        }
    vect = sroom; 
    //gets the new max length of the course and max length of the day
    for(unsigned int i = 0; i<vect.size();i++){
        std::string vroom = vect[i].aRoom;
        if (vroom.length()>dclen){
          dclen = vroom.length();
          }
        std::string sDay1 = vect[i].aDay1;
        std::string sDay2 = vect[i].aDay2;
      if (sDay1.length() > ddlen || sDay2.length() > ddlen){
          if (sDay1.length() > sDay2.length()){
              ddlen = sDay1.length();                                                                                
          }else if (sDay1.length() < sDay2.length()){
              ddlen = sDay2.length();
            }
            }
        }
  }
  //puts sorts the courses by days of the week into their own vectors
  if (com == "room" || com == "custom"){
  for(unsigned int i = 0; i<vect.size();i++){
        if (vect[i].aDay1 == "Monday"){
            mon.push_back(vect[i]);
        }else if (vect[i].aDay1 == "Tuesday"){
            tues.push_back(vect[i]);
        }else{
            weds.push_back(vect[i]);
        }
    }
    for(unsigned int i = 0; i<vect.size();i++){
        if (vect[i].aDay2 == "Thursday"){
            thurs.push_back(vect[i]);
        }else if(vect[i].aDay2 == "Friday"){
            fri.push_back(vect[i]);
        }
    }
  }
  //creates and prints the header for the dept command
  if(argc == 5){
      std::string specif = argv[4];
      if (com == "dept"){
              outfile <<"Dept " << specif << "\n";
              scourse = repeat(line, dclen); //repeat function to get the header for course names
              sday = repeat(line, ddlen); //repeat function to get header for days
                //adds two to legnth so it leaves two spaces in between
                dclen +=2; 
                ddlen += 2;
        //writes them into the file with proper formatting
        outfile
            << left
            << setw(11)
            << "Coursenum"
            << left
            << setw(dclen)
            << "Class Title"
            << left
            << setw(ddlen)
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
            << setw(dclen)
            << scourse
            << left
            << setw(ddlen)
            << sday
            << left
            << setw(12)
            << "----------"
            << left
            << setw(8)
            << "--------"
            << endl;
        //same thing but with the room command if a room is specified
      }else if (com == "room"){
          outfile <<"Room " << specif << "\n";
              scourse = repeat(line, dclen);
              sday = repeat(line, ddlen);
                dclen +=2;
                ddlen += 2;
        outfile
            << left
            << setw(11)
            << "Coursenum"
            << left
            << setw(dclen)
            << "Class Title"
            << left
            << setw(ddlen)
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
            << setw(dclen)
            << scourse
            << left
            << setw(ddlen)
            << sday
            << left
            << setw(12)
            << "----------"
            << left
            << setw(8)
            << "--------"
            << endl;
    }
  }
//prints a simple header for my custom command
if(argc == 4 && com == "custom"){
    outfile <<"Custom: 8AM Classes " <<"\n";
}
//if the 4th argument is room an nothing else        
if (argc == 4){
    if (com == "room"){
    //sorts all the time
    sortTime(mon);
    sortTime(tues);
    sortTime(weds);
    sortTime(thurs);
    sortTime(fri);

    //combines them all into one vector
    std::vector<Course> finalv(mon);
    finalv.insert(finalv.end(), tues.begin(), tues.end());
    finalv.insert(finalv.end(), weds.begin(), weds.end());
    finalv.insert(finalv.end(), thurs.begin(), thurs.end());
    finalv.insert(finalv.end(), fri.begin(), fri.end());

    //prints all of the vectors
    printR_MTW(mon, clen, dlen, outfile);
    printR_MTW(tues, clen, dlen, outfile);
    printR_MTW(weds, clen, dlen, outfile);
    printR_TF(thurs, clen, dlen, outfile);
    printR_TF(fri, clen, dlen, outfile);
    //gets the number of entries size
    entryc = finalv.size();
    outfile << entryc << " entries";
    outfile << "\n";
    outfile << "\n";
    infile.close();
    outfile.close();
    //if its my custom command
    }else if(com == "custom"){
        //sends and finds all the classes with 8AMs
    eightAMs(mon);
    eightAMs(tues);
    eightAMs(weds);
    eightAMs(thurs);
    eightAMs(fri);

    //combines them into one vector
    std::vector<Course> finalv(mon);
    finalv.insert(finalv.end(), tues.begin(), tues.end());
    finalv.insert(finalv.end(), weds.begin(), weds.end());
    finalv.insert(finalv.end(), thurs.begin(), thurs.end());
    finalv.insert(finalv.end(), fri.begin(), fri.end());

    //prints all the entries with 8AM
    printR_MTW(mon, clen, dlen, outfile);
    printR_MTW(tues, clen, dlen, outfile);
    printR_MTW(weds, clen, dlen, outfile);
    printR_TF(thurs, clen, dlen, outfile);
    printR_TF(fri, clen, dlen, outfile);
    entryc = finalv.size();
    outfile << entryc << " entries" << "\n";
    //if the entry size is 0
    if (entryc == 0) {
        outfile << "Lucky! No 8 AMs!"; //prints that they should be happy they have no 8AMS
    }else{
        outfile << "Sadly, enjoy these 8 AMs!"; //sarcastically prints they got 8AMs
    }
    //closes files once dont
    infile.close();
    outfile.close();
    }

}
if (argc == 5){
    //if it is a dept command
    if (com == "dept"){
    //sorts it by course number
    sortCnum(vect);
    //prints the department
    printDept(vect, dclen, ddlen, outfile);
    //gets entry size
    entryc = vect.size();
    //mulitplies it by two since it does not account for MR or TF
    entryc *=2;
    //displays amount of entries
    outfile << entryc << " entries";
    //prints new lines and closes files
    outfile << "\n";
    outfile << "\n";
    infile.close();
    outfile.close();
    //if its a specific room command
    }else if(com == "room"){
    //sorts the vectors by time
    sortTime(mon);
    sortTime(tues);
    sortTime(weds);
    sortTime(thurs);
    sortTime(fri);
    //creates one vector of all of the vectors
    std::vector<Course> finalv(mon);
    finalv.insert(finalv.end(), tues.begin(), tues.end());
    finalv.insert(finalv.end(), weds.begin(), weds.end());
    finalv.insert(finalv.end(), thurs.begin(), thurs.end());
    finalv.insert(finalv.end(), fri.begin(), fri.end());
    //prints all vectors by their days of the week
    printR_MTW(mon, clen, dlen, outfile);
    printR_MTW(tues, clen, dlen, outfile);
    printR_MTW(tues, clen, dlen, outfile);
    printR_TF(thurs, clen, dlen, outfile);
    printR_TF(fri, clen, dlen, outfile);
    //gets the entry size and prints it
    entryc = finalv.size();
    outfile << entryc << " entries";
    //adds new lines and closes files
    outfile << "\n";
    outfile << "\n";
    infile.close();
    outfile.close();
    }

}
   return 0;
}


