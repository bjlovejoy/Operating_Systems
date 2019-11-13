/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed:_Brendon Lovejoy, Corey Miller, Colin Frame__ Date:_9-10-19__   */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.03, Fall 2019.               */

void handleInterrupt21(int,int,int,int);
int mod(int, int);
int div(int, int);
void printLogo("");

void main()
{
   char buffer[512];
   makeInterrupt21();
   interrupt(33, 2, buffer, 258, 1);
   interrupt(33, 12,buffer[0]+1, buffer[1]+1, 0);
   printLogo();
   interrupt(33, 4, "Shell\0", 2, 0);
   interrupt(33, 0, "Bad or missing command interpreter.\r\n\0", 0, 0);
   while(1);
}

/*Prints a passed string either to the screen or printer*/
void printString(char* c, int d)
{
   int i = 0;       /*Variable for iterating through c-string*/
   char al;         /*Set equal to current character in c-string*/
   char ah = 14;    /*Set equal to 14 to call interrupt 16*/
   int ax;          /*Value to pass to interrupt when d = 0*/
   
   if(d == 0)  /*print to screen*/
   {
      while(c[i] != '\0')  /*loop until null terminator is reached*/
      {
         al = c[i];        /*set to next character in string*/
         ax = ah * 256 + al;
         interrupt(16, ax, 0, 0, 0);    /*(your name hereprint to screen*/
         i++;  /*increment to next character in string*/
      }
   }
   else  /*print to printer*/
   {
      while(c[i] != '\0')  /*loop until null terminator is reached*/
      {
         al = c[i];        /*set to next character in string*/
         interrupt(23, al, 0, 0, 0);  /*print to printer*/
         i++;  /*increment to next character in string*/
      }
   }

   return;
}

void printLogo()
{
   printString("       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0);
   printString("      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0);
   printString("     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0);
   printString("    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0);
   printString("   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0);
   printString("._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0);
   printString(" BlackDOS2020 v. 1.03, c. 2019. Based on a project by M. Black. \r\n\0",0);
   printString(" Author(s): Brendon Lovejoy, Corey Miller, Colin Frame.\r\n\r\n\0",0);
}

/*Reads a string from keyboard input adn stores the characters in an array*/
void readString(char c[100])
{
    int i = 0;    /*Variable for iterating through character array*/
    char test;    /*Variable to hold character before placing in array*/
    while(test != 13)  /*Loop until return is pressed*/
    {
       test = interrupt(22, 0, 0, 0, 0);  /*read keyboard*/
       if(test == 8 && i > 0)  /*if backspace is pressed*/
       {
          i--;  /*Decrement array element*/
          interrupt(16, (14 * 256 + test), 0, 0, 0); /*Print backspace to screen*/
       }
       else if(test == 13)  /*if return is pressed*/
       {
          c[i] = '\0';      /*store the null terminator*/
          interrupt(16, (14 * 256 + '\r'), 0, 0, 0);
          interrupt(16, (14 * 256 + '\n'), 0, 0, 0);
       }
       else
       {
          c[i] = test;  /*store variable in array*/
          interrupt(16, (14 * 256 + c[i]), 0, 0, 0);  /*print character to screen*/
          i++;  /*increment array*/
       }
    }
}

/*Function to use modulous*/
int mod(int a, int b)
{
   int x = a;
   while (x >= b) x = x - b;
   return x;
}

/*Function to use integer division*/
int div(int a, int b)
{
   int q = 0;
   while (q * b <= a) q++;
   return (q - 1);
}

/*Reads an integer as a string and converts to an integer*/
void readInt(int* n)
{
   int i = 0;  /*Variable for iterating through character array*/
   char *p;    /*C-string to save user input of integer*/
   *n = 0;     /*Ensure integer has value of zero*/
   interrupt(33, 1, p, 0, 0);  /*Collect user input*/
   while(p[i] != '\0')
   {
      *n *= 10;
      *n += (p[i] - '0');
      i++;
   }
}

/*Converts an integer to a string and prints to screen*/
void writeInt(int x, int d)
{
   int size = 0;  /*Variable to hold size of integer*/
   int temp = x;  /*Temporary variable hold integer value*/
   int i;         /*Variable for iterating through character array*/
   char c[10];    /*Character array only holds 10 elements due to int size*/
                  /*(large array size not needed)*/
   if(temp == 0)
      size++;  /*Ensures enough space for null terminator if int is zero*/
   while(temp != 0)  /*Collects number of digits in integer*/
   {
      size++;
      temp = div(temp, 10);
   }
   c[size] = '\0';
   for(i = (size-1); i >= 0; i--)  /*Save all digits to array*/
   {
      c[i] = mod(x, 10) + '0';
      x = div(x, 10);
   }
   interrupt(33, 0, c, d, 0);  /*Prints array to screen*/
}

/*Reads consecutive disk sectors*/
void readSector(char*buffer, int sector, int sectorCount)
{
   /*conversions provided for floppy disks*/
   int relSecNo = mod(sector, 18) + 1;   /*relative sector number*/
   int headNo = mod(div(sector, 18), 2); /*head number*/
   int trackNo = div(sector, 36);        /*track number*/
   
   int ax = 512 + sectorCount;
   int cx = trackNo * 256 + relSecNo;
   int dx = headNo * 256;
   
   interrupt(19, ax, buffer, cx, dx);    /*reads the sector into the buffer*/
}

/*Writes consecutive disk sectors*/
void writeSector(char*buffer, int sector, int sectorCount)
{
   /*conversions provided for floppy disks*/
   int relSecNo = mod(sector, 18) + 1;   /*relative sector number*/
   int headNo = mod(div(sector, 18), 2); /*head number*/
   int trackNo = div(sector, 36);        /*track number*/
   
   int ax = 768 + sectorCount;
   int cx = trackNo * 256 + relSecNo;
   int dx = headNo * 256;
   
   interrupt(19, ax, buffer, cx, dx);    /*writes the sector from the buffer*/
}

/*Clears the screen and sets both the background and foreground colors*/
void clearScreen(int bx, int cx)
{
   int i;
   /*prints 24 newline/return combinations to the screen*/
   for(i = 0; i < 24; i++)
   {
      interrupt(16, (14 * 256 + '\r'), 0, 0, 0);
      interrupt(16, (14 * 256 + '\n'), 0, 0, 0);
   }
   interrupt(16,512,0,0,0);  /*repositions the cursor to the upper left corner*/
   
   if(bx > 0 && cx > 0 && bx <=8 && cx <= 16)
   {
      /*scrolls the window and replace the background and foreground colors*/
      interrupt(16, 1536, 4096 * (bx - 1) + 256 * (cx - 1), 0, 6223);
   }
}

/*Loads a program file into memory and then executes*/
void runProgram(char *name, int segment)
{
   char buffer[13312]; /*ensures a program size of 13312 bytes*/
   int i = 0;  /*variable for iterating through buffer*/
   int size;

   /*loads the file from the disk into the buffer*/
   interrupt(33, 3, name, buffer, size);
   segment *= 0x1000;  /*derives the base location of the segment*/

   for(i = 0; i < 13312; i++)
   {
      /*transfers the file from the buffer into memory*/
      putInMemory(segment, i, buffer[i]);
   }

   launchProgram(segment);  /*executes the program*/
}


/*Determines if a file exists and saves it into the buffer*/
void readFile(char *fname, char *buffer, int *size)
{
   int i = 0;     /*Iterate through files*/
   int j = 0;     /*Iterate through individual characters*/
   int k = 0;     /*Iterate through file name*/
   int location = 0;    /*Holds location of file*/
   int fileSize = 0;    /*Holds size of file (number of sectors)*/
   int same = 1;        /*True if file name is the same as in the buffer*/
   int match = 0;       /*True if complete match*/
   int end = 0;         /*True if done with iteration*/
   char directory[512]; /*Holds contents of directory for comparison*/
   
   interrupt(33, 2, directory, 257, 1);   /*Collect contents of the directory*/
   
   while(i < 32 && !match)    /*Search each line of directory*/
   {
      j = 16 * i;    /*Set to first character of line*/
      
      while(j < (16 * i + 8) && fname[k] != '\0' && same)
      {
         if(fname[k] != directory[j])
            same = 0;
         j++;
         k++;
         end = 1;
      }
      
      if(same && end)
      {
         if(fname[k] == '\0' && j < (16 * i + 8) && directory[j] != '\0')
            match = 0;  /*Not an exact match*/
         else
         {
            match = 1;  /*Match found*/
            location = directory[16 * i + 8];   /*File location*/
            fileSize = directory[16 * i + 9];   /*File size*/
            *size = fileSize;
         }
      }
      i++;
      j += 8;
      k = 0;
      same = 1;
      end = 0;
   }

   if(match == 1)
   {
      interrupt(33, 2, buffer, location, fileSize);
   }
   else
   {
      interrupt(33, 15, 0, 0, 0);
   }
}


/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */

/*Writes a file to the disk*/
void writeFile(char *name, char *buffer, int numberOfSectors)
{
   int i = 0;        /*Iterate through files*/
   int j = 0;        /*Iterate through individual characters*/
   int k = 0;        /*Iterate through file name*/
   int same = 1;     /*True if file name is the same as in the buffer*/
   int match = 0;    /*True if complete match*/
   int end = 0;      /*True if done with iteration*/
   int emptyLocation = 0;  /*Holds location for new file*/
   int foundEmpty = 0;     /*Determine if already found empty location*/
   int spaceStart = 0;     /*Where empty map space starts*/
   int space = 0;          /*Amount of empty map space available after spaceStart*/

   char directory[512]; /*Holds contents of disk directory*/
   char map[512];       /*Holds contents of disk map*/
   
   interrupt(33, 2, directory, 257, 1);   /*Collect contents of the directory*/
   interrupt(33, 2, map, 256, 1);         /*Collect contents of the map*/

   while(i < 32 && !match)    /*Search each line of directory*/
   {
      j = 16 * i;    /*Set to first character of line*/
      
      if(directory[j] == '\0' && !foundEmpty)
      {
         emptyLocation = 16 * i;
         foundEmpty = 1;
      }
      
      while(j < (16 * i + 8) && name[k] != '\0' && same)
      {
         if(name[k] != directory[j])
            same = 0;
         j++;
         k++;
         end = 1;
      }
      
      if(same && end)
      {
         if(name[k] == '\0' && j < (16 * i + 8) && directory[j] != '\0')
            match = 0;  /*Not an exact match*/
         else
         {
            match = 1;  /*Match found*/
         }
      }
      i++;
      j += 8;
      k = 0;
      same = 1;
      end = 0;
   }

   if(match == 1)
   {
      interrupt(33, 15, 1, 0, 0);  /*name already exists*/
   }
   else if(foundEmpty) /*name is unique*/
   {
      i = 0;
      while(i < 8 && name[i] != '\0')  /*copy name to free directory entry*/
      {
         directory[emptyLocation + i] = name[i];
         i++;
      }
      i = 0;
      while(space < numberOfSectors && i < 512) /*determine if enough disk space*/
      {
         if(map[i] == 0)
            space++;
         else
            space = 0;
         
         if(space == 1)
            spaceStart = i;
         i++;
      }

      if(space == numberOfSectors)  /*enough disk space*/
      {
         /*set map entries for new file to 255 (0xff)*/
         for(i = spaceStart; i < (spaceStart + space); i++)
            map[i] = 0xff;
         
         /*store file locaiton and size in the directory*/
         directory[emptyLocation + 8] = spaceStart;
         directory[emptyLocation + 9] = numberOfSectors;
         
         /*write buffer to correct sectors*/
         interrupt(33, 6, buffer, spaceStart, numberOfSectors);
         
         /*write edited map and directory back to the disk*/
         interrupt(33, 6, directory, 257, 1);
         interrupt(33, 6, map, 256, 1);
      }
      else
         interrupt(33, 15, 2, 0, 0);  /*disk full error*/
   }
   else
   {
      interrupt(33, 15, 2, 0, 0);  /*no free directory entries*/
   }
}

void deleteFile(char *name)
{
   int i = 0;     /*Iterate through files*/
   int j = 0;     /*Iterate through individual characters*/
   int k = 0;     /*Iterate through file name*/
   int l = 0;     /*Iterate through sectors that need written to null*/
   int location = 0;    /*Holds location of file*/
   int fileSize = 0;    /*Holds size of file*/
   int same = 1;        /*True if file name is the same as in the buffer*/
   int match = 0;       /*True if complete match*/
   int end = 0;         /*True if done with iteration*/
   char directory[512]; /*Holds contents of directory for comparison*/
   char map[512];       /*Holds contents of disk map*/
   char emptySector[512]; /*Declare an empty buffer to write over old file buffer*/
   
   interrupt(33, 2, directory, 257, 1);   /*Collect contents of the directory*/
   interrupt(33, 2, map, 256, 1);         /*Collect contents of the map*/
   
   while(i < 32 && !match)    /*Search each line of directory*/
   {
      j = 16 * i;    /*Set to first character of line*/
      
      while(j < (16 * i + 8) && name[k] != '\0' && same)
      {
         if(name[k] != directory[j])
            same = 0;
         j++;
         k++;
         end = 1;
      }
      
      if(same && end)
      {
         if(name[k] == '\0' && j < (16 * i + 8) && directory[j] != '\0')
            match = 0;  /*Not an exact match*/
         else
         {
            match = 1;  /*Match found*/
            location = directory[16 * i + 8];   /*File location*/
            fileSize = directory[16 * i + 9];   /*File size*/
         }
      }
      i++;
      j += 8;
      k = 0;
      same = 1;
      end = 0;
   }

   if(match == 1)
   {
      i--;  /*Return to previous row*/
      
      for (j = i*16; j<(i*16+16); j++)
      {
         directory[j] = '\0';  /*Delete directory entry*/
      }
      
      for (l = location; l < location + fileSize; l++)
      {
         map[l] = '\0';  /*Free map space*/
         /*Empty file data from sector (NOT IMPLEMENTED)*/
         /*interrupt(33, 6, emptySector, l, 1);*/
      }
      
      /*write edited map and directory back to the disk*/
      interrupt(33, 6, directory, 257, 1);
      interrupt(33, 6, map, 256, 1);
         
   }
   else
   {
      interrupt(33, 15, 0, 0, 0);  /*File not found error*/
   }
}


/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */


/*Handles errors*/
void error(int bx)
{
   switch (bx) {
	   case 0:
	   /* error 0 = "File not found." */
	   interrupt(16, 3654, 0, 0, 0); interrupt(16, 3689, 0, 0, 0); interrupt(16, 3692, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3694, 0, 0, 0);
	   interrupt(16, 3695, 0, 0, 0); interrupt(16, 3700, 0, 0, 0); interrupt(16, 3616, 0, 0, 0);
	   interrupt(16, 3686, 0, 0, 0); interrupt(16, 3695, 0, 0, 0); interrupt(16, 3701, 0, 0, 0);
	   interrupt(16, 3694, 0, 0, 0); interrupt(16, 3684, 0, 0, 0);
	   break;
	   case 1:
	   /* error 1 = "Bad file name." */
	   interrupt(16, 3650, 0, 0, 0); interrupt(16, 3681, 0, 0, 0); interrupt(16, 3684, 0, 0, 0);
	   interrupt(16, 3616, 0, 0, 0); interrupt(16, 3686, 0, 0, 0); interrupt(16, 3689, 0, 0, 0);
	   interrupt(16, 3692, 0, 0, 0); interrupt(16, 3685, 0, 0, 0); interrupt(16, 3616, 0, 0, 0);
	   interrupt(16, 3694, 0, 0, 0); interrupt(16, 3681, 0, 0, 0); interrupt(16, 3693, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0);
	   break;
	   case 2:
	   /* error 2 = "Disk full." */
	   interrupt(16, 3652, 0, 0, 0); interrupt(16, 3689, 0, 0, 0); interrupt(16, 3699, 0, 0, 0);
	   interrupt(16, 3691, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3686, 0, 0, 0);
	   interrupt(16, 3701, 0, 0, 0); interrupt(16, 3692, 0, 0, 0); interrupt(16, 3692, 0, 0, 0);
	   break;
	   default:
	   /* default = "General error." */
	   interrupt(16, 3655, 0, 0, 0); interrupt(16, 3685, 0, 0, 0); interrupt(16, 3694, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0); interrupt(16, 3698, 0, 0, 0); interrupt(16, 3681, 0, 0, 0);
	   interrupt(16, 3692, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3685, 0, 0, 0);
	   interrupt(16, 3698, 0, 0, 0); interrupt(16, 3698, 0, 0, 0); interrupt(16, 3695, 0, 0, 0);
	   interrupt(16, 3698, 0, 0, 0);
   }
   interrupt(16, 3630, 0, 0, 0); interrupt(16, 3597, 0, 0, 0); interrupt(16, 3594, 0, 0, 0);
   interrupt(33, 5, 0, 0, 0);
}

/*Allows the program to terminate*/
void stop() { launchProgram(8192); }



void handleInterrupt21(int ax, int bx, int cx, int dx)
{
/*   return;  */
   switch(ax) {
      case 0:  printString(bx, cx);
               break;
      case 1:  readString(bx);
               break;
      case 2:  readSector(bx, cx, dx);
               break;
      case 3:  readFile(bx, cx, dx);
               break;
      case 4:  runProgram(bx, cx);
               break;
      case 5:  stop();
               break;
      case 6:  writeSector(bx, cx, dx);
               break;
      case 7:  deleteFile(bx);
               break;
      case 8:  writeFile(bx, cx, dx);
               break;
      case 12: clearScreen(bx, cx);
               break;
      case 13: writeInt(bx, cx);
               break;
      case 14: readInt(bx);
               break;
      case 15: error(bx);
               break;
/*      case 9: case 10: */
/*      case 11: */
      default: error(3);
   }
}
