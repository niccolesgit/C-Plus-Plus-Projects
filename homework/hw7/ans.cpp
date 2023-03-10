// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <string>
#include <list>
#include <vector>
#include <map>

#include "solh.h"

// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef std::map<std::string, std::map<std::string, int> > MY_MAP2;
typedef std::map<std::string, MY_MAP2 > MY_MAP3;

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

// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText3(MY_MAP3 &data, const std::string &filename, int window, const std::string &parse_method) {
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

  std::string word, next_word, next_next_word;
  ReadNextWord(istr, word);
  ReadNextWord(istr, next_word);
  while (ReadNextWord(istr, next_next_word)) {
    // skip the quotation marks (not used for this part)
    if (next_word == "\"") continue;

    if (data.find(word) != data.end() && data[word].find(next_word) != data[word].end()) { 
      /* This tuple of words has been seen before. We need to check if the
       * 3-tuple has been seen before. */
      if (data[word][next_word].find(next_next_word) != data[word][next_word].end()) {
        /* We've seen this 3-tuple before. Just increment the times this
         * 3-tuple has been seen. */
        data[word][next_word][next_next_word]++;
      } else {
        /* We're seeing this 3-tuple for the first time. So we set the number of
         * times we've seen this 3-tuple to 1. */
        data[word][next_word][next_next_word] = 1;
      }
    } else { 
      /* We haven't seen the next_word. We need to add it to the map with the next
       * next_word in its corresponding map. */
      data[word][next_word][next_next_word] = 1;
    }

    word = next_word;
    next_word = next_next_word;
  }
}

// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText2(MY_MAP2 &data, const std::string &filename, int window, const std::string &parse_method) {
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

  std::string present_word, next_word;
  ReadNextWord(istr, present_word);

  while (ReadNextWord(istr, next_word)) {
    // skip the quotation marks (not used for this part)
    if (next_word == "\"") continue;

    if (data.find(present_word) != data.end()){ 
      /* next_word has already been seen. We need to check if the next next_word has been
       * seen. */
      if (data[present_word].find(next_word) != data[present_word].end()) {
        /* We've seen the sequence of these two next_words together before. Just
         * increment the times this tuple has been seen. */
        data[present_word][next_word]++;
      } else {
        /* We're seeing this tuple for the first time. So we set the number of
         * times we've seen this tuple to 1. */
        data[present_word][next_word] = 1;
      }
    } else { 
      /* We haven't seen the next_word. We need to add it to the map with the next
       * next_word in its corresponding map. */
      data[present_word][next_word] = 1;
    }

    present_word = next_word;
  }
} 

void NextWord3(/*const*/ MY_MAP3 &data, 
    const std::string &word, const std::string &next_word, std::string &next_next_word, bool random_flag)
{
  if (random_flag) {
    /* We're going to build somewhat of a random distribution map. The easiest
     * way to explain it is by example:
     *
     * Suppose we have the following map:
     *  forest -> 2
     *  hansel -> 1
     *  bird   -> 3
     *
     * Then we will build a map of integers to strings of the following form:
     *
     *  0 -> forest
     *  1 -> forest
     *  2 -> hansel
     *  3 -> bird
     *  4 -> bird
     *  5 -> bird 
     *
     * This will allow us to pick a random number and come up with one of these
     * words based on their frequency. */
    std::map<int, std::string> random_distribution;
    int offset = 0, i = 0;
    std::map<std::string, int>::const_iterator it;
    for (it = data[word][next_word].begin(); it != data[word][next_word].end(); it++) {
      for (int i = offset; i < offset+it->second; i++) {
        random_distribution[i] = it->first;
      }
      offset += it->second;
    }

    MTRand m;
    int random_offset = m.randInt(offset-1);
    next_next_word = random_distribution[random_offset];
  } else { // get the most common next word

    int max_occurrences = 0;
    std::map<std::string, int>::iterator it;
    for (it = data[word][next_word].begin(); it != data[word][next_word].end(); it++) {
      // find the most common next word
      if (it->second == max_occurrences && it->first < next_next_word)
        next_next_word = it->first; // if there's a tie, only make the new word the next word if it's less alphabetically
      else if (max_occurrences < it->second)
        next_next_word = it->first; // this word has appeared more times, so make it the new next word
    }
  }
}

void NextWord2(/*const*/ MY_MAP2 &data, const std::string &present_word, std::string &next_word, bool random_flag)
{
  if (random_flag) {
    /* We're going to build somewhat of a random distribution map. The easiest
     * way to explain it is by example:
     *
     * Suppose we have the following map:
     *  forest -> 2
     *  hansel -> 1
     *  bird   -> 3
     *
     * Then we will build a map of integers to strings of the following form:
     *
     *  0 -> forest
     *  1 -> forest
     *  2 -> hansel
     *  3 -> bird
     *  4 -> bird
     *  5 -> bird 
     *
     * This will allow us to pick a random number and come up with one of these
     * words based on their frequency. */
    std::map<int, std::string> random_distribution;
    int offset = 0, i = 0;
    std::map<std::string, int>::const_iterator it;
    for (it = data[present_word].begin(); it != data[present_word].end(); it++) {
      for (int i = offset; i < offset+it->second; i++) {
        random_distribution[i] = it->first;
      }
      offset += it->second;
    }

    MTRand m;
    int random_offset = m.randInt(offset-1);
    next_word = random_distribution[random_offset];
  } else { // get the most common next word

    int max_occurrences = 0;
    std::map<std::string, int>::const_iterator it;
    for (it = data[present_word].begin(); it != data[present_word].end(); it++) {
      // find the most common next word
      if (it->second == max_occurrences && it->first < next_word)
        next_word = it->first; // if there's a tie, only make the new word the next word if it's less alphabetically
      else if (max_occurrences < it->second)
        next_word = it->first; // this word has appeared more times, so make it the new next word
    }
  }
}

int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  MY_MAP2 data2;
  MY_MAP3 data3;

  // Parse each command
  std::string command;    
  int window;
  while (std::cin >> command) {

    // load the sample text file
    if (command == "load") {
      std::string filename;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;      

      /* Declare map to be doubly indirected or triply indirected based on the
       * window size. */
      if (window == 2)
        LoadSampleText2(data2, filename, window, parse_method);
      else {
        assert (window == 3);
        LoadSampleText3(data3, filename, window, parse_method);
      }
    } 

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      int total_occurrences;

      if (window == 2) {
        for (int i = 0; i < sentence.size(); i++) {
          // reset the total number of times you've seen the word
          total_occurrences = 0;

          // sum up the number of times the word has appeared
          for (std::map<std::string, int>::iterator it = data2[sentence[i]].begin();
              it != data2[sentence[i]].end(); it++)
            total_occurrences += it->second;

          // print out the number of times the word has appeared
          std::cout << sentence[i] << " (" << total_occurrences << ")" << std::endl;

          // print out the number of times each tuple has been seen
          for (std::map<std::string, int>::iterator it = data2[sentence[i]].begin(); 
            it != data2[sentence[i]].end(); it++) {
            std::cout << sentence[i] << ' ' << it->first << " (" << it->second << ")" << std::endl;
          }
        }
      } else {
        assert (window == 3) ;
        assert (sentence.size() % 2 == 0 && sentence.size() >= 2); // there must be at least two words in the sentence
        for (int i = 0; i < sentence.size()-1; i += 2) {
          // reset the total number of times you've seen the tuple
          total_occurrences = 0;

          // sum up the number of times the tuple has been seen
          for (std::map<std::string, int>::iterator it = data3[sentence[i]][sentence[i+1]].begin(); 
              it != data3[sentence[i]][sentence[i+1]].end(); it++)
            total_occurrences += it->second;

          // print out the number of times the tuple has been seen
          std::cout << sentence[i] << ' ' << sentence[i+1] << " (" << total_occurrences << ")" << std::endl;

          // print out the number of times each 3-tuple has been seen
          for (std::map<std::string, int>::iterator it = data3[sentence[i]][sentence[i+1]].begin(); 
              it != data3[sentence[i]][sentence[i+1]].end(); it++) {
            std::cout << sentence[i] << ' ' << sentence[i+1] << ' ' << 
              it->first << " (" << it->second << ")" << std::endl;
          }
        }
      }
    }

    // generate the specified number of words 
    else if (command == "generate") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag = false;
      if (selection_method == "random" || selection_method == "most_common") {
        if (selection_method == "random")
          random_flag = true;

        if (window == 2) {
          /* Form a sentence with `length' words, starting with the words in
           * sentence. */
          std::string present_word, next_word;
          for (int i = 0; i < sentence.size(); i++) { // for all of the words in the sentence
            // print out the first word
            std::cout << sentence[i] << ' ';

          present_word = sentence[i];
          for (int j = 0; j < length-1; j++) {
            // find the most common word or the next random word
            NextWord2(data2, present_word, next_word, random_flag);
            std::cout << next_word << ' ';
            present_word = next_word;
          }
          std::cout << std::endl;
          }
        } else {
          assert (window == 3);
          assert (sentence.size() % 2 == 0 && sentence.size() >= 2);
          /* Form a sentence with `length' words, starting with the tuples in
           * sentence. */
          std::string word, next_word, next_next_word;
          for (int i = 0; i < sentence.size()-1; i += 2) { // for all the words in the sentence
            // print out the first tuple
            std::cout << sentence[i] << ' ' << sentence[i+1] << ' ';

            word = sentence[i];
            next_word = sentence[i+1];
            for (int j = 0; j < length-2; j++) {
              // find the most common next word or the next random word
              NextWord3(data3, word, next_word, next_next_word, random_flag);
              // print out the next word
              std::cout << next_next_word << ' ';
              // shift the words down
              word = next_word;
              next_word = next_next_word;
            }
            std::cout << std::endl;
          }
        }
      }
    } else if (command == "quit") {
      break;
    } else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}