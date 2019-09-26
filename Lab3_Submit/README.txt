Brendon Lovejoy, Corey Miller, Colin Frame
bjl66@zips.uakron.edu
Operating Systems
Lab 3

The purpose of this lab was to understand how to make BIOS system calls in order to read
and write to sectors on the disk.  Firstly, interrupt 33 was updated to provide this
functionality.  Then, naturally, the functions used in interrupt 33 to read and write to
sectors on the disk were written.  These functions utilized interrupt 19, along with
arguments that changed depending on read/write functionality and the locations where
things were read from and written to.  These functions used the mod and div functions
from past labs in order to provide relative sector numbers, the head number, and the
track number when the function was passed an absolute sector number (which, as stated
in the lab description, is what the rest of the project will deal with).  Overall, this lab
provided a straightforward understanding of how reading and writing from a disk is
usually abstracted.