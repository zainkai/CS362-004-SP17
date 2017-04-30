/*
Kevin Turkington

before starting the quiz i needed to see how testme.c worked
I found out it was a simple state machine that worked in a range
from 0 to 9. with a simple exit state if a string equalled "reset", 
otherwise known as the error state in context to this quiz.

First I started by making the inputChar function to select exactly 
one of of the required characters to change states
second I created a inputstring function that would spit out a string
saying "reset" or a random 5 letter string, by casting a randomly
generated integer into a character.

there are some problems with my inputstring function, because it doesnt free 
its allocated string, if run long enough an error will occur from out of memory.

after both of the functions where created I ran the program a couple of times
to ensure it worked and check the print statments for extra verification.
*/
