// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <cstdlib> 
#include <cassert>
#include <map>


// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
//for a window of 2
typedef std::map<std::string, std::map<std::string, int> > MY_MAP;
//for a window of 3
typedef std::map<std::string, std::pair<MY_MAP, int> > MY_MAP3;  


// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
	istr.get(c);
	word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}
//function that creates the maps after loading the file
void makeMaps(std::ifstream& istr, MY_MAP& data){
  //elements to search through the map
  std::string current, next;
  //while reading each word
  while (ReadNextWord(istr, next)) {
    //if you reach a quote, skip
    if (next == "\""){
      continue;
    }
    //if the current word is at the end
   if (data.find(current) == data.end()){
     //set it to 1 since its the only time we see it
     data[current][next] = 1;
    } else { 
      //if the the next is at the end
      if (data[current].find(next) == data[current].end()) {
        //set it to one since its only time we see it
        data[current][next] = 1;
      } else {
        //else increment since we've seen it before
        data[current][next]++;
        }
      }
      //set the current to the next to move 
      // to the next word
      current = next;
    }
//if we reach the last word & we've already seen it
if(next == ""){
  //increment it 
  data[current][next]++;
  }
}
// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data, const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }
  if(ignore_punctuation){
    //passes all test cases and prints that it has loaded
  std::cout << "Loaded " << filename << " with window = " << window << " and parse method = " << parse_method << "\n" << std::endl;
  //then creates the maps
  makeMaps(istr, data);
  }else{
    //passes all test cases and prints that it has loaded
  std::cout << "Loaded " << filename << " with window = " << window << " and parse method = " << parse_method << "\n" << std::endl;
  //then creates the maps
  makeMaps(istr, data);
  }
    //
    // ASSIGNMENT: PROCESS ALL THE NON PUNCTUATION WORDS
    // INSERTING THESE WORDS INTO THE DATA STRUCTURE
    //
}
//print function
void print(int window, std::vector<std::string>& sentence, MY_MAP& data){
//checks window
if (window == 2 || window == 3) {
  //loops through the sentence
  for (unsigned int i = 0; i < sentence.size(); i++) {
    //makes a variable that keeps track of total occurences
    int total = 0;
    //makes an iter that iterates through the maps
    std::map<std::string, int>::iterator iter;
    //loops through the data
    for (iter = data[sentence[i]].begin(); iter != data[sentence[i]].end(); iter++)
    //adds the total amount of occurences 
        total += iter->second;
    //prints total amount of occurences
    std::cout << sentence[i] << " (" << total << ")" << std::endl;
    //loops through data again
    for (iter = data[sentence[i]].begin(); iter != data[sentence[i]].end(); iter++) {
      //if you're not at the end of the file
        if(iter->first != ""){
          //print the word and its occurence
          std::cout << sentence[i] << ' ' << iter->first << " (" << iter->second << ")" << std::endl;
        }
      }
    }
  }
}
//generates random function
void generateR(int &window, std::vector<std::string>& sentence, MY_MAP& data, int &length){
  //checks window
  if(window == 2 || window == 3){
    //variables for the current and next word
    std::string current, next;
    //loops through the quoted word/words
    for (unsigned int i = 0; i < sentence.size(); i++) { 
      //print the current word and a space
      std::cout << sentence[i] << ' ';
      //set the current word to the word in the sentence
      current = sentence[i];
      //loops through the length
      for (int j = 1; j < length; j++) {
        //makes a map that holds the random words
        std::map<int, std::string> rand_map;
        //creates an offset
        int off = 0;
        //creates a const iterator to loop through data
        std::map<std::string, int>::const_iterator iter;
        //loops through data at current word
        for (iter = data[current].begin(); iter != data[current].end(); iter++) {
          //sets the variable to the offset, loops through until the
          // offset plus occurance
          for (int o = off; o < (off+iter->second); o++) {
            //sets the random map to the word
            rand_map[o] = iter->first;
          }
          //increments the offset
          off += iter->second;
        }
        //creates a random number with the range of offset
        int r_num = std::rand() % (off);
        //sets a random number to the next element
        next = rand_map[r_num];
        //prints the next word
        std::cout << next << ' ';
        //sets the current word to the next
        current = next;
      }
    }
  }
}
//generates most common
void generateMC(int& window, std::vector<std::string>& sentence, MY_MAP& data, int& length){
//checks window
  if(window == 2 || window == 3){
    //makes variables for current and next word
    std::string current, next;
    //loops through the sentence
    for (unsigned int i = 0; i < sentence.size(); i++) { 
      std::cout << sentence[i] << ' ';
      current = sentence[i];
    //loops through the given length 
    for (int j = 1; j < length; j++) {
      //counts the number of occurences
      int m_occur = 0;
      //creates an iterator to loop through the map
      std::map<std::string, int>::iterator iter;
      //loops through the data
      for (iter = data[current].begin(); iter != data[current].end(); iter++) {
        //if the word is before the next and the number of occurences is equal to the max
        if ((*iter).first < next && (*iter).second == m_occur){
          //set the word to the next one
          next = (*iter).first; 
        //else if the max is less than the number of occurences
        }else if (m_occur < iter->second){
          //set word to the next one
          next = (*iter).first; 
        }
      }
      //print the next word and space
      std::cout << next << ' ';
      //set the current to next
      current = next;
      }
    }
  }
}

int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  //declares maps 
  MY_MAP data;
  MY_MAP3 data3;
  //variables for cin 
  std::string filename, command, parse_method;
  int window;

  // Parse each command  
  while (std::cin >> command) {

    // load the sample text file
    if (command == "load") {
      std::cin >> filename >> window >> parse_method;  
      //check if you can load the file with valid filename, window, and parse method(EC)
      LoadSampleText(data, filename, window, parse_method);
      //if it has loaded properly, make the map for either a map or a bigger map
      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //
    } 
    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //
      print(window, sentence, data);
      std::cout << std::endl;
    }

    // generate the specified number of words 
    else if (command == "generate") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      //gets length and selection method
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      //sets flag
      if (selection_method == "random") {
	      random_flag = true;
      } else {
	      assert (selection_method == "most_common");
	      random_flag = false;
      }
      //checks flag
      if(random_flag){
        //if true, generate random
        generateR(window, sentence, data, length);
        std::cout << std::endl;
      }else{
        //if false, generate most common
        generateMC(window, sentence, data, length);
        std::cout << std::endl;
      }
      //if the command is quit
    } else if (command == "quit") {
      //break from the loop
      break;
    } else {
      //else print there's an error with commands
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}
