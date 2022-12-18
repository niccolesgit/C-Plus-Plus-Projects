// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
void add(vector<string> &phonebook, int number, string const& name) { // O(1)
  phonebook[number] = name;
    
}
// given a phone number, determine who is calling
void identify(const vector<string> & phonebook, int number) { // O(1)
  if (phonebook[number] == "UNASSIGNED")
    cout << "unknown caller!" << endl;
  else
    cout << phonebook[number] << " is calling!" << endl;
}
void add(map<const string, int>& mphone, int number, string const& name) { // O(log n)
    mphone.insert(pair<const string, int>(name, number));
}
void identify(map<const string, int>& mphone, int number) { // O(n)
    map<const string, int>::const_iterator it = mphone.begin();
    for( ; it != mphone.end(); it++) {
        if(it -> second == number) {
            cout << it -> first << " is calling!" << endl;
            return;
        }
    }
    cout << "unknown caller!" << endl;
    return;
}

int main() {
  // create the phonebook; initially all numbers are unassigned
  vector<string> phonebook(10000, "UNASSIGNED"); // O(N) - memory
    
  // add several names to the phonebook O(1)
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook O(1);
  std::cout << "sally:" << std::endl;
  identify(phonebook, 2222);
  std::cout << "invalid number in phonebook:" << std::endl;
  identify(phonebook, 4444);
  
  std::cout << std::endl;
  std::cout << "trying longer numbers:" << std::endl;
  map<const string, int> mphone; // O(n) - memory

  add(mphone, 1202349, "bill");
  add(mphone, 2126736082, "nicole");

  std::cout << "bill:" << std::endl;
  identify(mphone, 1202349);
  std::cout << "nicole:" << std::endl;
  identify(mphone, 2126736082);
  std::cout << "unknown 7:" << std::endl;
  identify(mphone, 1234567);
  std::cout << "unknown 10:" << std::endl;
  identify(mphone, 1234567890);

    
  // vector - time: O(1) - memory: O(N)
  // map - time: O(n) - memory: O(n)
  // vector is faster but takes up more memory
    
}
