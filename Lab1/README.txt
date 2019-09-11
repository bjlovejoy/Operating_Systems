Brendon Lovejoy
bjl66@zips.uakron.edu
Operating Systems 

In this lab, a disk image is created and booted from.  First, the bootloader is assembled and a blank image disk filled with zeros is created.  Following this, the bootloader is placed in sector zero (beginning of floppya.img) so that floppya.img can be run using Bochs.  At this time, a script file, compileOS.sh, was started and given permission to execute in order to make the compile process quicker and easier.  This script contains commands to create the blank image disk, place the bootloader into sector zero, and future commands to compile kernel.c, link kernel.o with kasm.o
