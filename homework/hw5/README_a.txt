HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  VALERIA VILLANUEVA-RUIZ


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

	- Devak Patel (UPE tutor)

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20hrs



TESTING & DEBUGGING STRATEGY:
Please be concise!  
I relied on printing (using cout) a lot to be able to see what was going on
in some parts of my code and how it responded to the main.cpp provided specially
at the beginning and middle parts of the homework.
I also used the compiler (Ubuntu) and added the -Wall -Wextra -g commands
to check for warnings to check for leaks with drmemory (and get the line numbers).
Furthermore, when I had debugged everything that was test with the tests provided
I implemented some corner cases involving the functions that were not used on the
case provided to make sure that they worked. I believe I checked all of them and
made the necessary changes to be able to have a fully (or at least close to fully)
functioning program.


ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

n = number of elements in the list
d = number of nodes
e = number of elements in the node

Assuming that allocating and deleting nodes is O(1)
Used the dslist_partial.h from lecture 11 for comparison to dslist

- Time complexity:
	list_iterator
		operator++ (both): O(1) 
		operator-- (both): O(1)
	UnrolledLL
		constructor (default): O(1)
 			compared to STL list => constant, same time complexity
			compared to dslist =>constant, same time complexity

		constructor (copy): O(n)
 			compared to STL list => linear, same time complexity
			compared to dslist => linear, same time complexity

		operator= : O(n+d) -> O(n) [because n >= d]
 			compared to STL list => linear, same time complexity
			compared to dslist => linear, same time complexity

		destructor : O(d)
 			compared to STL list => STL list time complexity (linear) > UnrolledLL time complexity (linear)
						*both are linear, however STL list goes through more values [e.g.O(n)] than UnrolledLL [e.g.O(d)]*
			compared to dslist => N/A, function not implemented on dslist

		size: O(1)
 			compared to STL list => constant, same time complexity
			compared to dslist => constant, same time complexity

		empty: O(1)
 			compared to STL list => constant, same time complexity
			compared to dslist => constant, same time complexity

		clear: O(d)
 			compared to STL list => STL list time complexity (linear) > UnrolledLL time complexity (linear)
						*both are linear, however STL list goes through more values [e.g.O(n)] than UnrolledLL [e.g.O(d)]*
			compared to dslist => relies on destroy_list() which is not implemented on dslist

		front (write/read): O(1)
 			compared to STL list => constant, same time complexity
			compared to dslist => constant, same time complexity

		back (write/read): O(1)
 			compared to STL list => constant, same time complexity
			compared to dslist => constant, same time complexity

		push_front: O(e)
 			compared to STL list => STL list time complexity (constant) < UnrolledLL time complexity (linear)
			compared to dslist =>  N/A, function not implemented on dslist

		pop_front: O(e)
 			compared to STL list => STL list time complexity (constant) < UnrolledLL time complexity (linear)
			compared to dslist =>  N/A, function not implemented on dslist

		push_back: O(1)
 			compared to STL list => constant, same time complexity
			compared to dslist => constant, same time complexity

		pop_back: O(1) 
 			compared to STL list => constant, same time complexity
			compared to dslist =>  N/A, function not implemented on dslist

		print: O(n) [because it goes through all of the elements]
 			compared to STL list => N/A - STL list does not have a print function
			compared to dslist => N/A - dslist does not have a print function

		erase: O(e)
 			compared to STL list => linear, same time complexity
			compared to dslist => dslist time complexity (constant) < UnrolledLL time complexity (linear)

		insert: O(e)
 			compared to STL list => linear, same time complexity
			compared to dslist => dslist time complexity (constant) < UnrolledLL time complexity (linear)

		begin: O(1)
			compared to STL list => constant, same time complexity
			compared to dslist => constant, same time complexity

		end: O(1)
			compared to STL list => constant, same time complexity
			compared to dslist => constant, same time complexity

		copy_list: O(n)
			compared to STL list => N/A - STL list does not have a copy_list function
			compared to dslist => constant, same time complexity

		destroy_list: O(d)
			compared to STL list => N/A - STL list does not have a destroy_list function
			compared to dslist => N/A - dslist does not have a destroy_list function


- Memory usage:
	A STL list's memory usage would be O(n) because this kind of list allocates
	spaces according to the number of elements being added into it. The
	memory usage of an UnrolledLL would be O(d*e) because this kind of list allocates
	a fixed amount of space per node from which some might not be used. The worst case
	would be if there are all nodes only contain one element, in that case d = n, the 
	unrolled list would take e times more space than a regular STL list.
	(Example) This case can happen if I fill up the nodes to their max capacity (using push_back(T))
	and then erase (usinf erase()) all of the elements but the first one in each one, then I would 
	have one element and a lot of unused spaces per node.


EXTRA CREDIT:
Improved memory usage implementation. Discussion as outlined in .pdf.
----did not do this----



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


