Brendon Lovejoy, Corey Miller, Colin Frame
bjl66@zips.uakron.edu
Operating Systems
Lab 2

The purpose of this lab was to apply some of the basic concepts of interrupts that were introduced in lab 1 to write functions for user I/O. In particular, the keyboard is driving the interrupts.

The first step in this lab is to write a function called "readString," which accepts a character array of at least 80 empty elements. The function calls interrupt 22 to store keyboard input into the char array until the enter key is pressed- then a null terminator is added to the element after the most recently accessed in the array.

During step 2, functions readInt and writeInt were written to get input from the keyboard, which is expected to be a number- specifically it is an ASCII represented number. It is important that this function converts the input string to an integer- otherwise calculations that may end up using this input will be done with an ASCII offset, which would screw up the calculations. Similarly, a function called writeInt was written to take an integer representation of a number and print it to the screen, which would involve adding an ASCII offset to this number to ensure that the number can be understood by the interrupt for printing output. It is worth noting that integer division and modulo functions aren't implemented in ANSI C, so the functions to use these operations needed to be written (or taken from the lab instructions) during the lab.

Then, the functions that were written in step 2 were added to the interrupt 33 handler so that the functions can be used as interrupt service routines rather than just simple function calls. This will probably come more in handy later, but for now it's still pretty neat to think about it anyhow.

Lastly comes the main event- Mad Libs! This part was very straightforward; just copy the given madlibs function from madLibKernel.c, and test it out to ensure that the user experience is simple and hey, maybe a little fun!

Overall, the lab yielded a greater understanding of everything from obtaining, representing, and converting user input to learning more about ANSI C, so the lab was successful and enjoyable.
