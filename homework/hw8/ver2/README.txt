HOMEWORK 8: ROPES


NAME: Nicole Lee


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

TJ Layton, Bhavya Chavali, William Zheng, David Vasquez, Nadia Choudhury
Charles Cook (TA), Samuel Leung

Submitty Lecture Notes for Trees, Lab 10 Code, Code from Lecture 17
https://www.geeksforgeeks.org/, https://en.cppreference.com/ 

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 40

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor:
1) Balanced rope: O(p*m)
2) Unbalanced rope: O(p*m)
They are the same because copy would take the same path from the root to the leaf (p), reguardless if they are balanced or unbalanced. 
If they both had the same amount of leaves, it would still take O(p*m) to copy it. 

Construct from Node*:
1) Balanced rope: O(p)
2) Unbalanced rope: O(p)
An unbalanced rope might go though more nodes, but they still are both constructed based on how long the path is, counting up the weights on the right. 

Index:
1) Balanced rope: O(p)
2) Unbalanced rope: O(n)
A balanced rope just needs to go through the longest path, while an unbalanced rope would have to check every single character for the index.

Report:
1) Balanced rope: O(n)
2) Unbalanced rope: O(n)
They are both the same because both needs to check every character to see if it's within the index.

iterator operator++:
1) Balanced rope: O(1)
2) Unbalanced rope: O(1)
Doing a simple iterator incremeation, so it would take linear time reguardless for both. 

Split:
1) Balanced rope: O(p)
2) Unbalanced rope: O(p)
The balanced rope would have to search an old path to the leaf, while an unbalanced rope would take
the same amount of time while also going through each node to get to the leaf. 

Concat:
1) Balanced rope: O(p*m)
2) Unbalanced rope: O(p*m)
Concat copies and adds the string to the original rope, so time to copy and add the string to the rope
would take O(p*m) to also account for every character in the string while also searching along the longest path. 

TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?
I tested to make sure that the functions in the main tested properly (left, right, and index) and checked they 
were able to print the nodes and the strings. I then tested the size(), index and report. I checked
to make sure the rope size can be differentiated from the string's length. I also tested if the rope's index
can differate character differences even if the length is different, so I swapped one character with another. 
I then checked if report would work, by inputting an invalid index and sees if it can get the error message if that occurs.

When debugging, I went through the list of functions in the Rope_student.cpp, and did each function one by one and testing 
it through the basic tests and commenting out functions I didn't implement yet. I used g++ command with -o, -Wall -Wextra commands
I also used Dr. Memory to check any memory leaks, and used gdb debugger when I was confused with specific memory line errors.
I also consulted collaborators listed above with questions for errors if I didn't understand them. 



MISC. COMMENTS TO GRADER:  
Note: I had COVID with this HW, so I'm sorry for any typos

