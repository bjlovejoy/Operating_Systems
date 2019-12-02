Brendon Lovejoy, Corey Miller, Colin Frame
bjl66@zips.uakron.edu
Operating Systems
Lab Y

Instructions for compiling and running the program:

    1. Open the terminal
    2. Navigate to the directory containg the file "smoker.c"
    3. Type "./compile.sh" into the terminal, without quotations
    4. Type "./smoker"     into the terminal, without quotations


The purpose of this lab was to understand how to use and implement
a program containing pthreads and semaphores.  In creating a
simulation of the cigarette smoker's problem, a solution making
use of three agents, three pushers and six smokers was implemented.
Here, the agents contain an infinite amount of two of the three
available items required to make a cigarette, being tobacco, paper
and matches.  Three agents were created, where each has one of the
three combinations of the two items.  The pushers act as the method
by which the smokers are able to determine what items are currently
on the table and who should take them.  When the pushers determine
which two items are on the table, the semaphore to the appropriate
smoker (the one containing the third item to make the cigarette) is
signaled.  There are six smokers in total, where there are two of
each type, such that there are 2 smoker holding tobacco, 2 holding
paper and 2 holding matches.  These smokers simple make and smoke
the cigarettes, represented by a delay.

In order to implement this, each of the agents, pushers and smokers
were made into functions and were created as pthreads.  In main, all
of the semaphores were initialized to their appropriate values and
each function was used to create a pthread.  All of the pthreads will
run concurrently and exit upon completion.  In main, we wait for all
of the pthreads to terminate and rejoin the main thread.  When running
this code, the console will output which threads have been started and
ended, denoted by "ENTER" and "EXIT".  In addition, it will output
which items the agents produce as well as which smokers used the items
to make and smoke their cigarette (accompanied by the amount of time
randomly generated to complete these "pseudo-tasks").  This lab greatly
helped in understanding the importance and usage of both POSIX threads
and semaphores in solving multithreading problems.
