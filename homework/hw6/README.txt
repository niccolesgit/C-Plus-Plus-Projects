HOMEWORK 6: STAR BATTLE


NAME: Nicole Lee



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Tyler Layton, David Vasquez, Alexis Shaw, Bhavya Chavali, William Zheng, 
Submitty Lecture Notes

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 40



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of zones (z)? 
The average number of squares in a zone   
The number of stars per zone(s)? 
etc.
For Zone class, add function would be O(1). For Point class, there are no functions, but declaraion iself is O(1)
For Board class, getZSize/Stars/Board is O(1), getZ is O(z), setStars is O(1),  
findSolution is O(log(z*w*h)), printOne is O(w*h)^2, printAll is O(w*h)^3. I think what changes the complexity
the most is the dimensions of the board, determining how much we loop, and the number of zones,
because we have to loop through and check each zone.


DESCRIPTION OF YOUR ADDTIONAL PUZZLES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).
test1.txt: I attempted to make a 3x3 grid and fill it with coordinates and creates a zone of one square, to 
test if there was any possible solutions if there is one zone in the middle.
test2.txt: I made a 4x4 grid that put zones in each corner and the middle, to test the corner zones



SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles / stars per zone for a single solution or all solutions. Be
specific about which puzzle/parameters you were timing.
These would be my guesses for the puzzles:
provided files:
custom1.txt: 3-5 minutes is my best guess, since it's only using 1 star
                and its all solutions is a fairly small number
custom2.txt: 5-7 minutes because all solutions and time to count them all would 
                take longer since there are more solutions and using 1 star
sporcle1.txt: 1-2 minutes since there's only 1 solution and using 1 star
twonot1.txt: 10-14 minutes because its using mutiple stars and calulcating and comparing
                to find the solution trying to check every star
twonot2.txt: 7-9 minutes even though there are no solutions
custom files:
test1.txt: 3-4 minutes because the grid is fairly small and the zone of 1 would also be fast to check
            if there was more than 1 star
test2.txt: 7-9 minutes because the grid is a fair size, but it's checking each corner in each zone and 
            also checking the middle zone.

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


