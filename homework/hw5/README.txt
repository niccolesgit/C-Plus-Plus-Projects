HOMEWORK 5: UNROLLED LINKED LISTS

NAME: Nicole Lee


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Val Villanueva, Bhavya Chavali, William Zheng, David Vasquez, Alexis Shaw,
dslist_partial.h, dslist_handout.h, lec11.cpp, Lecture 11 on Submitty, Submitty
Lecture 11 notes

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 45



TESTING & DEBUGGING STRATEGY:
I would start by trying to get the header file to work with one function first then printing it
then debug the function needed until it worked. I did that until I had all of the functions completed
then checked the output for each function as I went along. After I implemented all of my functions 
I ran Dr.Memory to check for memory leaks and discussed with collaborators if I was unsure on how to fix it. I 
also ran gdb to find specified line errors I didn't understand. When compliling I also ran it with g++ commands,
using -lm -g -Wall -Wextra to find any compiler errors I had.



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

i = # of elements in list
e = # of elements in node
o = # of nodes

list_iterator:
    pre operator++: O(1) 
    post operator++: O(1) 
    pre operator--: O(1)
    post operator--: O(1)
UnrolledLL:
    constructor: O(1)
    -constant same as STL list and dslist
    other constructor: O(i)
    -linear, same as STL list and dslist
    operator= : O(i) 
    -linear, same as STL list and dslist
    destructor : O(e)
    -STL list goes through more elements so it takes longer
    than UnrolledLL, and dslist doesnt have a destructor (DNE)
    size: O(1)
    -constant same as STL list and dslist
    clear: O(e)
    -STL list takes longer than UnrolledLL
    and dslist doesn't have a destroy_list function so it can't 
    clear properly (DNE)
    empty: O(1)
    -constant same as STL list and dslist
    push_front: O(e)
    -STL list takes less time than UnrolledLL,
    and dslist doesnt have push_front (DNE)
    push_back: O(1)
    -constant same as STL list and dslist
    pop_front: O(e)
    -STL list takes less time than UnrolledLL,
    and dslist doesn't have pop_front (DNE)
    pop_back: O(1) 
    -STL list is constant and same as UnrolledLL,
    and dslist doesn't have pop_back (DNE)
    print: O(i) 
    -STL list & dslist don't have print (DNE)
    front: O(1)
    -constant same as STL list and dslist
    back: O(1)
    -constant same as STL list and dslist
    insert: O(e)
    -STL list is the same, linear, but dslist
    takes less time than UnrolledLL because its constant
    erase: O(e)
    -STL list is the same, linear, but dslist
    takes less time than UnrolledLL because its constant
    begin: O(1)
    -constant same as STL list and dslist
    end: O(1)
    -constant same as STL list and dslist
    destroy_list: O(e)
    -STL list and dslist don't have destroy_list (DNE)
    copy_list: O(i)
    -STL list doesn't have a copy_list function (DNE), but is the same for
    dslist 


EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.
N/A

MISC. COMMENTS TO GRADER:  
Optional, please be concise!


