#Brendon Lovejoy
#bjl66@zips.uakron.edu
#September 9, 2019

#This shell script builds the bootable disk image, compiles the kernel and
#links kernel.o with kasm.o


#Assemble the bootloader - only needs to run once
#nasm bootload.asm

#Creates blank image disk filled with zeros
dd if=/dev/zero of=floppya.img bs=512 count=2880

#Puts bootload into sector zero
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc

#Optional to view the contents of floppya.img
#hexdump -C floppya.img

#Run once to change the permissions of compileOS.sh to executable
#chmod +x compileOS.sh

#Compiles kernel.c
bcc -ansi -c -o kernel.o kernel.c

#Assembles kernel.asm into kasm.o - only needs to run once
#as86 kernel.asm -o kasm.o

#Links kernel.o with kasm.o
ld86 -o kernel -d kernel.o kasm.o

#Copies kernel to sector 259
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259

#Reads the config file into floppya.img at sector 258
dd if=config of=floppya.img bs=512 count=1 seek=258 conv=notrunc


#*****These commands are for preparing fib*****

#Compiles fib.c
#bcc -ansi -c -o fib.o fib.c

#Assembles blackdos.asm into basm.o - only needs to run once
#as86 blackdos.asm -o basm.o

#Links fib.o with basm.o
#ld86 -o fib -d fib.o basm.o

#Copies fib to sector 259
dd if=fib of=floppya.img bs=512 count=1 seek=30 conv=notrunc

#*****End commands for preparing fib*****


#Adds file to execute to the disk image (for this lab only)
#dd if=Stenv of=floppya.img bs=512 count=4 seek=30 conv=notrunc

#Run this to start the bochs simulator after running this script (./compileOS.sh)
#echo "c" | bochs -f bdos.txt
