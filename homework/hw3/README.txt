HOMEWORK 3: CONNECT FOUR


NAME: Nicole Lee


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Samuel Leung, Bhavya Chavali, William Zheng, Nick Chite (ALAC), Submitty Lecture Notes, Benson Chang, 
Sphia, Alexa Shaw, David Vasquez


Remember: Your implementation for this assignment must be done on your
own, as described in the "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  <72>



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

insert (excluding checking for connected four)
addElement:O(n^2)
expandBoard: O(n^3)
insert (including checking for connected four)
O(n^2)
numTokensInColum
O(1)
numTokensInRow
O(n)
numColumns
O(1)
numRows
O(1)
print
O(m) * O(n)
clear
2O(n)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?
I used visual studio debugger and Dr.Memory. I made sure that the columns
I was adding was equal to the length of the column the user inserted
and filled in the empty gaps with nulls. 


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

