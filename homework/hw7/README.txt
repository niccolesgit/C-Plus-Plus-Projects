HOMEWORK 7: WORD FREQUENCY MAPS


NAME: Nicole Lee


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Bhavya Chavali, William Zheng, Samuel Leung, David Vasquez, 
skeleton code given in main.cpp, Lab 9 files, Submitty Lecture Notes
HW5 files to reference to iterators & defreferencing 

Map Reference: https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/ 
std::rand: https://en.cppreference.com/w/cpp/numeric/random/rand

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  40



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word
x = the number of words that should be generated

How much memory will the map data structure require, in terms of n, m,
w, p, x (order notation for memory use)?
O((n*w)^2) + O((x*p)^3) + O(m)
I think it would take about this much memory because it has to loop through all the words
and the specifed window and making maps out of each word and window, and based on generation 
that it goes through it goes through a triple for loop and based on the words that follow it, 
and added accountability for analyzing all of the unique words in the file



What is the order notation for performance (running time) of each of
the commands?
Load: O(n*w)
The loading function only loads the total words into maps in one while loop,
based on the width of the window
Print: O(m*p)^3
Print function prints in a triple loop, based on the unique words they want
and words that follow
Generate:
    -Random: O(m*x)^4
    Random function goes through a quadruple loop that checks every unique word and random words to be 
    generated
    -Most Common: O(m*p)
    Most common function goes through a quadruple loop that checks every unique word and specific 
    most common words to be generated


EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).
N/A 



MISC. COMMENTS TO GRADER:  
I got covid mid-week for this hw, so I couldn't get most of the homework done
due to headaches :p

