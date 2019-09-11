Brendon Lovejoy
bjl66@zips.uakron.edu
Operating Systems 

In this lab, a disk image is created and booted from.  First, the bootloader is assembled and a blank image disk filled with zeros is created.  Following this, the bootloader is placed in sector zero (beginning of floppya.img) so that floppya.img can be run using Bochs.

At this time, a script file, compileOS.sh, was started and given permission to execute in order to make the compile process quicker and easier.  This script contains commands to create the blank image disk, place the bootloader into sector zero, and future commands to compile kernel.c, link kernel.o with kasm.o and copy the kernel to sector 259.

Returning to the project directory, kernel.c and kernel.asm are downloaded and added to the directory.  Here, kernel.asm can be assembled into kasm.o, which only needs to run once.  This is the final command that is not contained within the script file and needs to be run independently.  The kernel can now be compiled (among other functions) using the script by entering "./compileOS.sh" into the terminal.

The first task in modifying the kernel is to allow output to be printed to the screen.  This is handled by Interrupt 16 (0x10), which performs I/O functions.  This includes function 14, which prints ASCII characters to the screen.


All yours Corey.
