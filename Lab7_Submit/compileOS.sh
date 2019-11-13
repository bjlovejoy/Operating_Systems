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

#Used to set up the initial file system
dd if=map of=floppya.img bs=512 count=1 seek=256 conv=notrunc

#Reads the config file into floppya.img at sector 258
dd if=config of=floppya.img bs=512 count=1 seek=258 conv=notrunc

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


#*****These commands are for preparing Shell*****

#Compiles Shell.c
bcc -ansi -c -o Shell.o Shell.c

#Assembles blackdos.asm into basm.o - only needs to run once
#as86 blackdos.asm -o basm.o

#Links Shell.o with basm.o
ld86 -o Shell -d Shell.o basm.o

#Copies Shell to sector 259
dd if=Shell of=floppya.img bs=512 count=25 seek=30 conv=notrunc

#*****End commands for preparing Shell*****

#Uncomment to edit lab7
#bcc -ansi -c -o lab7.o lab7.c
#ld86 -o lab7 -d lab7.o basm.o

#Uncomment to edit the userManual
#bcc -ansi -c -o userManual.o userManual.c
#ld86 -o userManual -d userManual.o basm.o

#Load files into memory
./loadFile Shell
./loadFile kitty1
./loadFile kitty2
./loadFile fib
./loadFile msg
./loadFile Stenv
./loadFile ddir
./loadFile userManual
./loadFile t3
./loadFile cal
./loadFile lab7
./loadFile fpc02


#Run this to start the bochs simulator after running this script (./compileOS.sh)
#echo "c" | bochs -f bdos.txt
