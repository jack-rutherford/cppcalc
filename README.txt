First for the adequate section of the project I implemented the divide and times methods into ast.c and ast.h. I then began to implement RestTerm in parser.c.
I then changed parser.C so that storable returns a factor and factor is now the one that checks the next token (Storable is basically a pass through method right now) and added recall and store nodes in ast.c and ast.h.
After that I got the left and right parentheses working recursively and making sure that it only looks ahead by one and made sure that the Storeable method was implemented more correctly.

I learned from parsing that the 1 look ahead from the left is actually pretty interesting, and when you implement all of the different levels correctly it doesn't make it too harad to implement other parts of the project.
One example of this was the SUPERIOR portion of the project, I thought it would be difficult to deal with finding the value inside of the parentheses after R and S, but in reality it was as easy as calling factor() since we deal with
getting values between a l and r parentheses. Tokens were also interesting because you can simplify everything in your code to some type of token. It ties into abstract syntax trees well too, because if there's ever a token that's not
where it's supposed to be then your program should naturally throw an error with a cout statement because the method that was checking the next token does not recognize it and simply does not do anything with it, until expr finishes
executing and the prog method throws an error.

For the superior portion of this project I added int memLoc private fields and parameters to store and recall nodes in ast.h and added memLoc parameters to RecallNode and StoreNode constructor and evaluate method. 
parser.C was changed to call Factor() if it sees an S or R so it can get the expression between the parentheses (the memory location) and use that integer for when we return new StoreNode/RecallNode.
Other than that I just changed calculator.c and calculator.h to have a int[10] array called memory instead of just an integer value, and changed the evaluate methods to take a parameter of a memory location so the
evaluate method knows where to access in the memory array.

Some examples include "3S(0)" returns 3, "3S(0)+R(0)" returns 6, "(10/2S(0))S(1)*(R(0)*5)S(2)*(R(1)*R(2))/R(1)" returns 500.
