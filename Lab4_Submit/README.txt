Brendon Lovejoy, Corey Miller, Colin Frame
bjl66@zips.uakron.edu
Operating Systems
Lab 4

The purpose of this lab was to understand the process of loading program files
into memory and how to execute them.  In preparation for this lab, the config
file that was prepared towards the end of Lab 3 was placed within the same folder
and a command was added to compile.sh in order to read the screen's background
and foreground colors into floppya.img at sector 258.  Having done this, kernel.c
may now be edited to add the function, "runProgram," which uses two predefined
functions, "putInMemory" and "launchProgram."  In "runProgram," the previously
defined function, "readSector," loads the file from the disk into the buffer.
Then, "putInMemory" transfers the file from the buffer into memory one byte at a
time, followed by "launchProgram" in order to run the executable.  Upon recompiling,
the program prints the text image of the cat from kitty1 in the color saved in the
config file.

In order to run kitty2, a termination call is created and linked to interrupt 33/5.
If ran without the termination function, kitty2 would print many times over again.
However, with the addition of this function, the program now terminates after printing
kitty2 to the screen.  In order to implement the execution of multi-sector programs,
the command in compile.sh for adding the file to floppya.img needed to be updated to
4 sectors, which also needed to be updated in the "runProgram" call in kernel.c.  After
making these changes, Stenv executed correctly, which prompted to change the foreground
and background colors. which took effect after reseting Bochs.  The final test case
used the files blackdos.asm, blackdos.h and fib.c, where several lines were added to
compile.sh in order to prepare the new commands for input and output.  The program
prompts the user for a number, to which is performs the Fibonacci sequence for that
many terms.  As this program works, it demonstrates the proper implementation of
a function call to load and execute a program file, both for single and multiple
sector programs.

