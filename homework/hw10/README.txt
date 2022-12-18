HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME: Nicole Lee


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Val Villanueva, TJ Layton, Alexa Shaw, Bhavya Chavali, William Zheng, Samuel Leung, David Vasquez

https://www.cplusplus.com/reference/queue/priority_queue/ 
https://www.cplusplus.com/reference/string/string/npos/ 
https://www.techiedelight.com/find-element-with-the-maximum-value-in-a-map-in-cpp/  
https://stackoverflow.com/questions/9370945/finding-the-max-value-in-a-map 
https://www.geeksforgeeks.org/longest-common-substring-array-strings/ 
https://www.bigocheatsheet.com/ 

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  25



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

---------------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f  | longest           |
|          | sort     | dups     | mode     | pair     | sorted   | substr            | 
---------------------------------------------------------------------------------------
|          |          |          |          |          |          |                   |
| vector   |O(nlog(n))|  O(n^2)  |O(nlog(n))|O(nlog(n))|O(nlog(n))|O(n^2(l^3))        |
---------------------------------------------------------------------------------------
|          |          |          |          |          |          |                   |
| list     |O(nlog(n))|  O(n^2)  |O(nlog(n))|O(nlog(n))|O(nlog(n))|O(n^2(l^3))        |
---------------------------------------------------------------------------------------
|          |          |          |          |          |          |                   |
| bst      |O(nlog(n))|O(nlog(n))|O(nlog(n))|O(nlog(n))|O(nlog(n))|O(nl^2(log(nl^2))) |
---------------------------------------------------------------------------------------
|          |          |          |          |          |          |                   |
| pq       |O(nlog(n))|    X     |O(nlog(n))|O(nlog(n))|O(nlog(n))|         X         |
---------------------------------------------------------------------------------------
|          |          |          |          |          |          |                   |
| hash     |    X     |   O(n)   |   O(n)   |  O(n^2)  |    X     | O(nl^3)           |
---------------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

Files:
File Name	                Size	Max & Min
medium_string_input1.txt	10000	5 & 5
medium_string_input2.txt	20000	5 & 5
medium_string_input3.txt	50000	5 & 5

medium_integer_input1.txt	10000	5 & 3
medium_integer_input2.txt	20000	5 & 3
medium_integer_input3.txt	50000	5 & 3

Performance and K Constants:

Vector Performance:
# of strings	Vector sort operation (sec)
10000	        0.015625 k = 3.9 x 10 ^-7
20000	        0.015625 k = 1.8 x 10^-7
50000	        0.046875 k = 1.9 x 10^-7

# of strings	Vector remove_duplicates operation (sec)
10000	        0.828125 k = 0
20000	        3.46875 k = 0
50000	        56.6719 k = 2 x 10^-8

# of strings	Vector mode operation (sec)
10000	        0 k = 0
20000	        0.03125 k = 3.6 x 10^-7
50000	        0.046875 k = 1.9 x 10^-7

# of strings	Vector first_sorted operation (for 3) (sec)
10000	        0.015625 k = 3.9 x 10^-7
20000	        0 k = 0
50000	        0.046875 k = 1.9 x 10^-7

# of integers	Vector closest_pair operation (sec)
10000	        0.015625 k = 3.9 x 10^-7
20000	        0 k = 0
50000	        0.03125 k = 13 x 10^-7

# of strings	Vector longest_substring operation (sec)
10000	        2.23438 k = 0
20000	        8.34375 k = 0
50000	        175.344 k = 0



List Performance:
# of strings	List sort operation (sec)
10000	        0.015625 k = 3.9 x 10^-7
20000	        0.03125 k = 3.6 x 10^-7
50000	        0.0625 k = 2.6 x 10^-7

# of strings	List remove_duplicates operation (sec)
10000	        1.29688 k = 1 x 10^-8
20000	        5.26562 k = 1 x 10^-8
50000	        99.5156 k = 3 x 10^-8

# of strings	List mode operation (sec)
10000	        0.015625 k = 3.9 x 10^-7
20000	        0.03125 k = 3.6 x 10^-7
50000	        0.0625 k = 2.6 x 10^-7

# of strings	List first_sorted operation (for 3) (sec)
10000	        0.015625 k = 3.9 x 10^-7
20000	        0.015625 k = 1.8 x 10^-7
50000	        0.046875 k = 1.9 x 10^-7

# of integers	List closest_pair operation (sec)
10000	        0 k = 0
20000	        0.015625 k = 1.8 x 10^-7
50000	        0.0625 k = 2.6 x 10^-7

# of strings	List longest_substring operation (sec)
10000	        7.98438 k = 0
20000	        99.6875 k = 0
50000	        729.094 k = 0

BST (map) Performance:
# of strings	BST sort operation (sec)
10000	        0.015625 k = 3.9 x 10^-7
20000	        0.03125 k = 3.6 x 10^-7
50000	        0.078125 k = 3.3 x 10^-7

# of strings	BST remove_duplicates operation (sec)
10000	        0.078125 k = 0
20000	        0.1875 k = 0
50000	        0.5 k = 0

# of strings	BST mode operation (sec)
10000	        0.015625 k = 3.9 x 10^-7
20000	        0.015625 k = 1.8 x 10^-7
50000	        0.0625 k = 2.6 x 10^-7

# of strings	BST first_sorted operation (for 3) (sec)
10000	        0 k = 0
20000	        0.03125 k = 3.6 x 10^-7
50000	        0.0625 k = 2.6 x 10^-7

# of integers	BST closest_pair operation (sec)
10000	        0.015625 k = 3.9 x 10^-7
20000	        0.015625 k = 1.8 x 10^-7
50000	        0.046875 k = 1.9 x 10^-7

# of strings	BST longest_substring operation (sec)
10000	        32.9375 k = 2.44 x 10 ^-5
20000	        219.062 k = 7.687 x 10^-5
50000	        298.953 k = 3.922 x 10^-5

Hash table (unordered_map) Performance:
# of strings	Hash Table sort operation (sec)
NO K CONSTANT SINCE ITS NOT USED
10000	        0 k = N/A
20000	        0 k = N/A
50000	        0.046875 k = N/A

# of strings	Hash Table remove_duplicates operation (sec)
10000	        0.078125 k = 0.078125
20000	        0.140625 k = 0.078125
50000	        0.4375 k = 0.4375

# of strings	Hash Table mode operation (sec)
10000	        0.015625 k = 0.015625
20000	        0 k = 0 
50000	        0.046875 k = 0.046875

# of strings	Hash Table first_sorted operation (for 3) (sec)
NO K CONSTANT SINCE ITS NOT USED
10000	        0.015625 k = N/A
20000	        0.015625 k = N/A
50000	        0.046875 k = N/A

# of integers	Hash Table closest_pair operation (sec)
10000	        N/A (seg faulted) k = N/A
20000	        N/A (seg faulted) k = N/A
50000	        N/A (seg faulted) k = N/A

# of strings	Hash Table longest_substring operation (sec)
10000	        8.45312 k = 6.76 x 10^-6
20000	        55.1875 k = 2.207 x 10^-5
50000	        307.422 k = 4.918 x 10^-5

Priority Queue Performance:
# of strings	Priority Queue sort operation (sec)
10000	        0.078125 k = 1.95 x 10 ^-6
20000	        0.0625 k = 7.2 x 10^-7
50000	        0.1875 k = 7.9 x 10^-7

# of strings	Priority Queue remove_duplicates operation (sec)
NO K CONSTANT SINCE ITS NOT USED
10000	        0 k = N/A
20000	        0 k = N/A
50000	        0 k = N/A

# of strings	Priority Queue mode operation (sec)
10000	        0.015625 k = 3.9 x 10^-7
20000	        0.015625 k = 1.8 x 10^-7
50000	        0.046875 k = 1.9 x 10^-7

# of strings	Priority Queue first_sorted operation (for 3) (sec)
10000	        0 k = 0
20000	        0 k = 0
50000	        0 k = 0

# of integers	Priority Queue closest_pair operation (sec)
10000	        0.015625 k = 3.9 x 10^-7
20000	        0.015625 k = 1.8 x 10^-7
50000	        0.03125 k = 1.3 x 10^-7

# of strings	Priority Queue longest_substring operation (sec)
NO K CONSTANT SINCE ITS NOT USED
10000	        0 k = N/A
20000	        0 k = N/A
50000	        0.015625 k = N/A




DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  

These answers did match the ones on my table. I did change whether my 
hash table or priority queue had certain functions. I discussed and debated 
a lot about the table with my colleagues (listed above) and I ended up with 
this final table. We were able to determine that the priority queue doesn’t 
need to remove duplicates because even though it can hold duplicates, the 
values would be ranked in the same place. Also, that priority queue doesn’t 
need to have the longest substring either because you can get the top or 
highest value and could have the longest substring in it. For hash tables, 
I ruled out the sort functions because you don’t need to sort hash tables. 
Everything else in the table is based on what I’ve learned in lectures and 
from online resources (listed above). I did not expect the coefficients to be so similar, 
I found myself getting similar numbers for each function. 
I thought because they were all different data types, I assumed the numbers and coefficients 
would be entirely unique for each. I didn’t realize how more efficient hash tables could be 
until I was going over and adjusting the O Notation to match the run time numbers that I got. 
After going through all of the data types, it really helped me understand how they are all 
interconnected to each other. From transitioning from each data type in each file, it helped me 
understand why some are more efficient than others. I think this will help me determine which 
data structures to use in the future because they all have different efficiencies. But I 
think I’d also need to consider which would be best for the problem at hand. For example, 
if I needed something with IDs and items, I don’t think I’d use vectors or lists. 



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
