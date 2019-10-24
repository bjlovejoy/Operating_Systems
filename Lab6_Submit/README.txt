Brendon Lovejoy, Corey Miller, Colin Frame
bjl66@zips.uakron.edu
Operating Systems
Lab 6

The purpose of this lab was to add functionality to the operating
system, particularly the file system.  In order to prepare for
this, several files were needed, including map, loadFile.c,
ddir.c and error.c.  First, map was added to the disk image in
order to determine the amount of used and free space in the file
system.  Here, the disk map is available at sector 256, whereas
the disk directory is at 257, which contains the file names along
with their respective locations and size.  In order to add files
to the file system, the disk map and directory are modified using
loadFile.  After the kernel is compiled as usual, loadFile is called
with the file to load as an argument (for example: ./loadFile msg).
By performing a hexdump, it can be shown starting around address
0x00020000 that tha map, directory and config are shown in order,
where the disk directory contains the loaded files.

Now, the function readFile must be created and two functions need
to be updated.  Here, readFile must determine if the passed file
name exists, where if it does, then it must be loaded into the
buffer.  To do this, readFile reads in the file directory and parses the
buffer to determine if the requested file name is available.  If it is,
then the respective file location and size are saved so that the file
can be loaded into the buffer passed to readFile.  Otherwise, an error
occurs and is printed to the screen.  This function was tied to 
interrupt 33/3 and tested with the file "msg," which was loaded into
the disk image.  Here, "msg" was found, passed to the buffer and then
printed to the screen in main.  Errors were implemented in the kernel as
well, where a function was copied from error.c and tied to interrupt 33/15.

Next, runProgram was edited in order to use the recently created function,
readFile, rather than readSector.  This worked as expected, where the test
function in main ran the programs that were loaded onto the disk and
resulted in an error if the passed name did not exist.  Finally, the last
task was to implement this new functionality in the shell, where by typing
the appropriate command, the correct corresponding output will result.
Here, the command ddir will specifically run the program "ddir" in order
to list all the files that are stored on the disk (with expection of those
starting with a capital letter, such as Stenv).  Next, exec followed by a
file name will execute that file, similar to the previous test cases
explained above.  The help command required the creation of a user manual,
which was implemented as the program, userManual, which explains all of the
commands and moves to the next page by pressing the return key.  The
commands prnt and show load a file and print its contents either to the
printer or the screen, respectively.  senv sets the background and foreground
colors, which will be implemented after either a boot or clrs commmand.
This lab helped to greatly explain the details on implementing the loading,
locating and execution of a file.  Adding this new functionality to the shell
was untilmately rewarding, as all of the commands worked as expected on a
user level.

