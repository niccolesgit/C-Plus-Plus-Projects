// Build and maintain a list of students enrolled in a class and the waiting list.  
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;

void enroll_student(const string& id_number, unsigned int max_students, 
		    vector<string>& enrolled, vector<string>& waiting);
void remove_student(const string& id_number, unsigned int max_students, 
		    vector<string>& enrolled, vector<string>& waiting);
void erase_from_vector(vector<string>::iterator itr,  vector<string>& v);

int main() {
  // Read in the maximum number of students in the course
  unsigned int max_students;
  cout << "\nWelcome to the enrollment program for CSCI 1200\n"
       << "Please enter the maximum number of students allowed\n";
  cin >> max_students;
  
  // Initialize the vector
  vector<string> enrolled;
  vector<string> waiting;
  
  // Invariant:
  // (1) enrolled contains the students already in the course, 
  // (2) waiting contains students who would will to be admitted (in
  //     the order of request) if a spot opens up, in the  
  // (3) enrolled.size() <= max_students, 
  // (4) if the course is not filled (enrolled.size() != max_students)
  //     then waiting is empty
  do {
    // check (part of) the invariant
    assert (enrolled.size() <= max_students);
    assert (enrolled.size() == max_students || waiting.size() == 0);

    cout << "\nOptions:\n"
         << "  To enroll a student type 0\n"
         << "  To remove a student type 1\n"
         << "  To end type 2\n"
         << "Type option ==> ";
    int option;
    
    if (!(cin >> option)) { // if we can't read the input integer, then just fail.
      cout << "Illegal input.  Good-bye.\n";
      return 1;
    } else if (option == 2) { 
      break; // quit by breaking out of the loop.
    } else if (option != 0 && option != 1) {
      cout << "Invalid option.  Try again.\n";
    } else { // option is 0 or 1
      string id_number;
      cout << "Enter student id: ";
      if (!(cin >> id_number)) {
        cout << "Illegal input.  Good-bye.\n";
        return 1;
      } else if (option == 0) {
        enroll_student(id_number, max_students, enrolled, waiting);
      } else {
        remove_student(id_number, max_students, enrolled, waiting); 
      }
    }
  }
  while (true);
  
  // some nice output
  sort(enrolled.begin(), enrolled.end());
  cout << "\nAt the end of the enrollment period, the following students\n"
       << "are in the class:\n\n";
  for (vector<string>::iterator i=enrolled.begin(); i != enrolled.end(); i++) {
    cout << *i << endl;
  }
  if (!waiting.empty()) {
    cout << "\nStudents are on the waiting list in the following order:\n";
    for (vector<string>::iterator j=waiting.begin(); j != waiting.end(); j++) {
      cout << *j << endl;
    }
  }
  return 0;
}

// Enroll a student in the course if there is room and if the student
// is not already in the course or on the waiting list.
void enroll_student(const string& id_number, unsigned int max_students, 
		    vector<string>& enrolled, vector<string>& waiting) {
  // Check to see if the student is already enrolled. 
  unsigned int i;
  for (vector<string>::iterator i=enrolled.begin(); i != enrolled.end(); i++) {
    if (*i == id_number) {
      cout << "Student " << id_number << " is already enrolled." << endl;
      return;
    }
  }
  
  // If the course isn't full, add the student.
  if (enrolled.size() < max_students) {
    enrolled.push_back(id_number);
    cout << "Student " << id_number << " added.\n" << enrolled.size() 
         << " students are now in the course." << endl;
    return;
  }
  
  // Check to see if the student is already on the waiting list.
  for (vector<string>::iterator j=waiting.begin(); j != waiting.end(); j++) {
    if (*j == id_number) {
      cout << "Student " << id_number << " is already on the waiting list." << endl;
      return;
    }
  }
  
  // If not, add the student to the waiting list.
  waiting.push_back(id_number);
  cout << "The course is full.  Student " << id_number
       << " has been added to the waiting list.\n" << waiting.size() 
       << " students are on the waiting list." << endl;
}

// Remove a student from the course or from the waiting list.  If
// removing the student from the course opens up a slot, then the
// first person on the waiting list is placed in the course.
void remove_student(const string& id_number, unsigned int max_students, 
		    vector<string>& enrolled, vector<string>& waiting) {
  // Check to see if the student is on the course list.
  bool found = false;
  vector<string>::iterator itr = enrolled.begin();
  while (!found && itr != enrolled.end()) {
    found = *itr == id_number;
    if (!found) itr++;
  }
  
  if (found) {
    // Remove the student and see if a student can be taken from the waiting list.
    erase_from_vector(itr, enrolled);
    cout << "Student " << id_number << " removed from the course." << endl;
    if (waiting.size() > 0) {
      enrolled.push_back(*waiting.begin());
      cout << "Student " << *waiting.begin() << " added to the course "
           << "from the waiting list." << endl;
      erase_from_vector(waiting.begin(), waiting);
      cout << waiting.size() << " students remain on the waiting list." << endl;
    } else {
      cout << enrolled.size() << " students are now in the course." << endl;
    }
  } else {
    // Check to see if the student is on the waiting list
    found = false;
    vector<string>::iterator wait_itr = waiting.begin();
    while (!found && wait_itr != waiting.end()) {
      found = *wait_itr == id_number;
      if (!found) ++wait_itr;
    }
    if (found) {
      erase_from_vector(wait_itr, waiting);
      cout << "Student " << id_number << " removed from the waiting list.\n"
           << waiting.size() << " students remain on the waiting list." << endl;
    } else {
      cout << "Student " << id_number << " is in neither the course nor the waiting list" << endl;
    }
  }
}

// Remove the value at index location i from a vector of strings.  The
// size of the vector should be reduced by one when the function is finished.
void erase_from_vector(vector<string>::iterator itr,  vector<string>& v) {

  assert (itr >= v.begin());
  assert (v.size() > 0);
  assert (itr < v.end());

  int old_size = v.size();

  // shift everything forward
  vector<string>::iterator itr2 = itr;
  itr2++;
  while (itr2 != v.end()) {
    *itr = *itr2;
    itr++;
    itr2++;
  }
  
  // shorten the vector by 1
  v.pop_back();
  
  assert (v.size() == old_size - 1);
}
