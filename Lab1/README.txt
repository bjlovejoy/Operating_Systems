Brendon Lovejoy, Corey Miller, Colin Frame
bjl66@zips.uakron.edu
Operating Systems 

In this lab, a disk image is created and booted from.  First, the bootloader is assembled
and a blank image disk filled with zeros is created.  Following this, the bootloader is
placed in sector zero (beginning of floppya.img) so that floppya.img can be run using
Bochs.

At this time, a script file, compileOS.sh, was started and given permission to execute
in order to make the compile process quicker and easier.  This script contains commands
to create the blank image disk, place the bootloader into sector zero, and future
commands to compile kernel.c, link kernel.o with kasm.o and copy the kernel to sector
259.

Returning to the project directory, kernel.c and kernel.asm are downloaded and added
to the directory.  Here, kernel.asm can be assembled into kasm.o, which only needs to
run once.  This is the final command that is not contained within the script file and needs
to be run independently.  The kernel can now be compiled (among other functions) using
the script by entering "./compileOS.sh" into the terminal.

The first task in modifying the kernel is to allow output to be printed to the screen.  This
is handled by Interrupt 16 (0x10), which performs I/O functions.  This includes function 14,
which prints ASCII characters to the screen. However, this function, along with
interrupt 23 (0x17), on its own would be quite tedious to use on its own. The interrupt is only
good for printing one ASCII character to the screen. Calling this function over and over again
would become a pain, which is why writing a function to call the interrupt in a loop over the
length of an ASCII string would be best. This function is called printString() in this case, and it
essentially prints characters on the screen via interrupt 16 until the null terminator. Then,
this function was modified to enable printing a string to a "printer," which bochs emulates
with a printer.out plain text file. The function accepts a string and an integer as arguments- 
the string being what is printed, and the integer (either 0 or 1) representing where the string
is printed to.

The last section of the lab involved implementing an interrupt. The task of moving the address
for the interrupt routine in the interrupt vector table was taken care of by the kernel.asm,
because the granularity of assembly language was required here (for the record, the asm
source was pretty cool to check out after completing the lab). The implementation of the
routine, however, could be done in C, as long as the symbol name matched in assembly. Since
this lab's source code followed a template, the naming was not a problem. The interrupt handler
essentially looked at the first input (ax) and checked what value it contained. So far, the
function only checks for one value- whether its value is 0 or anything else. If the value of the
ax input is 0, then the function "printString" is called, which looks at inputs bx and cx, which
correspond to the string that is being printed and where the string is printed to. One of the
tricks from this lab was the abscence of a break statement in the code that was given.
Without this, the switch statement performs a "passthrough," where regardless of the value
of ax, the default case is executed. This issue was rectified by simply adding a break
statement after the printString call in case 0. After this, the default case stopped executing,
and the error message went away.
