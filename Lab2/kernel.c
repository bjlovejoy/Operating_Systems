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
/*char *readString(char[]);*/
int mod(int, int);
int div(int, int);
void readInt(int*);
void writeInt(int);
void printLogo("");

void main()
{
   char c[100];
   char *test;
   int t = 0;
   
   makeInterrupt21();
   printLogo();
   
   interrupt(33, 0, "Please enter num: \0", 0, 0);
   readInt(&t);
   interrupt(33, 0, "\r\nYou typed: \0", 0, 0);
   writeInt(t);
   
   interrupt(33, 0, "\r\n\nPlease enter input: \0", 0, 0);
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
    char test;
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
    return c;
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
   char *p;
   /*char c[100];*/
   interrupt(33, 1, p, 0, 0);
   interrupt(33, 0, p, 0, 0);
   while(p[i] != '\0')
   {
      *n *= 10;
      *n += (p[i] - '0');
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
      c[i] = mod(x, 10) + '0';
      x = div(x, 10);
   }
   interrupt(33, 0, c, 0, 0);
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
