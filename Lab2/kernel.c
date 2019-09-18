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
char *readString(char[]);
int mod(int, int);
int div(int, int);
void readInt(int*);
void writeInt(int);
void printLogo("");

void main()
{
   char c[100];
   char *test;
   
   makeInterrupt21();
   printLogo();
   writeInt(5678);
   interrupt(33, 0, "Please enter input: \0", 0, 0);
   interrupt(33, 1, test, 0, 0);
   interrupt(33, 0, "\r\nYou typed: \0", 0, 0);
   interrupt(33, 0, test, 0, 0);
   while(1);
}

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
         interrupt(16, ax, 0, 0, 0);    /*print to screen*/
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

char *readString(char c[100])
{
    int i = 0;
    int e;
    char test;
    /*char *test2;*/
    while(test != 13)
    {
       test = interrupt(22, 0, 0, 0, 0);
       if(test == 8 && i > 0)
       {
          i--;
          interrupt(16, (14 * 256 + test), 0, 0, 0);
       }
       else if(test == 13)
          c[i] = '\0';
       else
       {
          c[i] = test;
          interrupt(16, (14 * 256 + c[i]), 0, 0, 0);
          i++;
       }
    }
    /*for(e = 0; e <= i; e++)
       test2[e] = c[e];
    return test2;*/
    return c;
    /*interrupt(16, (14 * 256 + '\n'), 0, 0, 0);
    printString(c, 0);*/
}

int mod(int a, int b)
{
   int x = a;
   while (x >= b) x = x - b;
   return x;
}

int div(int a, int b)
{
   int q = 0;
   while (q * b <= a) q++;
   return (q - 1);
}

void readInt(int* n)
{
   int i = 0;
   char c[100];
   char *p;
   *n = 0;
   p = readString(c);
   while(p[i] != '\0')
   {
      n[i] = (int)p[i];
      i++;
   }
}

void writeInt(int x)
{
   int size = 0;
   int temp = x;
   int i;
   char c[10];
   
   if(temp == 0)
      size++;
   while(temp != 0)
   {
      size++;
      temp = div(temp, 10);
   }
   c[size] = '\0';
   for(i = (size-1); i >= 0; i--)
   {
      c[i] = (char)mod(x, 10);
      x = div(x, 10);
   }
   printString(c, 0);
}
/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
/*   return;  */
   switch(ax) {
      case 0: printString(bx, cx);
              break;
      case 1: readString(bx);
              break;
/*      case 2: case 3: case 4: case 5: */
/*      case 6: case 7: case 8: case 9: case 10: */
/*      case 11: case 12: case 13: case 14: case 15: */
      default: printString("General BlackDOS error.\r\n\0");
   }
}
