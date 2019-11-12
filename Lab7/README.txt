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
buffer.  

