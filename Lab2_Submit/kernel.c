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
/*void printString(char*,int);*/
/*void readString(char[]);*/
int mod(int, int);
int div(int, int);
/*void readInt(int*);*/
/*void writeInt(int, int);*/
void printLogo("");

void main()
{
   char food[25], adjective[25], color[25], animal[25];
   int temp;
   makeInterrupt21();
   printLogo();
   interrupt(33,0,"\r\nWelcome to the Mad Libs kernel.\r\n\0",0,0);
   interrupt(33,0,"Enter a food: \0",0,0);
   interrupt(33,1,food,0,0);
   temp = 0;
   while ((temp < 100) || (temp > 120)) {
      interrupt(33,0,"Enter a number between 100 and 120: \0",0,0);
      interrupt(33,14,&temp,0,0);
   }
   interrupt(33,0,"Enter an adjective: \0",0,0);
   interrupt(33,1,adjective,0,0);
   interrupt(33,0,"Enter a color: \0",0,0);
   interrupt(33,1,color,0,0);
   interrupt(33,0,"Enter an animal: \0",0,0);
   interrupt(33,1,animal,0,0);
   interrupt(33,0,"Your note is on the printer, go get it.\r\n\0",0,0);
   interrupt(33,0,"Dear Professor O\'Neil,\r\n\0",1,0);
   interrupt(33,0,"\r\nI am so sorry that I am unable to turn in my program at this time.\r\n\0",1,0);
   interrupt(33,0,"First, I ate a rotten \0",1,0);
   interrupt(33,0,food,1,0);
   interrupt(33,0,", which made me turn \0",1,0);
   interrupt(33,0,color,1,0);
   interrupt(33,0," and extremely ill.\r\n\0",1,0);
   interrupt(33,0,"I came down with a fever of \0",1,0);
   interrupt(33,13,temp,1,0);
   interrupt(33,0,". Next my \0",1,0);
   interrupt(33,0,adjective,1,0);
   interrupt(33,0," pet \0",1,0);
   interrupt(33,0,animal,1,0);
   interrupt(33,0," must have\r\nsmelled the remains of the \0",1,0);
   interrupt(33,0,food,1,0);
   interrupt(33,0," on my computer, because he ate it. I am\r\n\0",1,0);
   interrupt(33,0,"currently rewriting the program and hope you will accept it late.\r\n\0",1,0);
   interrupt(33,0,"\r\nSincerely,\r\n\0",1,0);
   interrupt(33,0,"(your name here)\r\n\0",1,0);
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

/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */

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
/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
/*   return;  */
   switch(ax) {
      case 0:  printString(bx, cx);
               break;
      case 1:  readString(bx);
               break;

      case 13: writeInt(bx, cx);
               break;
      case 14: readInt(bx);
               break;
/*      case 2: case 3: case 4: case 5: */
/*      case 6: case 7: case 8: case 9: case 10: */
/*      case 11: case 12: case 15: */
      default: printString("General BlackDOS error.\r\n\0");
   }
}
