#include "blackdos.h"

void newLine();

void main()
{
   int n;
   PRINTS("|                General Commands Manual                |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   *----------------Important Notes----------------*   |\r\n\0");
   PRINTS("|   * The term \"arg#\" is the argument, where # is   *   |\r\n\0");
   PRINTS("|   * the number in which the argument will appear. *   |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   boot   Reboots the operating system, where the      |\r\n\0");
   PRINTS("|          welcome message will print and the user      |\r\n\0");
   PRINTS("|          will enter the shell.                        |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   clrs   Clears the screen and sets the background    |\r\n\0");
   PRINTS("|          and foreground colors automatically          |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   echo arg1                                           |\r\n\0");
   PRINTS("|          Outputs arg1 to the console, where arg1 is   |\r\n\0");
   PRINTS("|          user inputted text.  This text may include   |\r\n\0");
   PRINTS("|          spaces and does not need to be wrapped in    |\r\n\0");
   PRINTS("|          quotes.  Any leading spaces will be removed. |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|[Press ENTER to continue]                              |\0");
   
   SCANN(n);
   
   PRINTS("|                General Commands Manual                |\r\n\0");
   PRINTS("|                      (continued)                      |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   copy arg1 arg2                                      |\r\n\0");
   PRINTS("|          Copies arg1 and renames to arg2, where arg1  |\r\n\0");
   PRINTS("|          is the file name to copy and arg2 is what    |\r\n\0");
   PRINTS("|          the copied file will be named.               |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   ddir                                                |\r\n\0");
   PRINTS("|          Lists the disk directory contents and        |\r\n\0");
   PRINTS("|          determines how much space is still           |\r\n\0");
   PRINTS("|          available for use.                           |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   exec arg1                                           |\r\n\0");
   PRINTS("|          Loads and executes a user determined file,   |\r\n\0");
   PRINTS("|          where arg1 is the file to run.               |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   help                                                |\r\n\0");
   PRINTS("|          Displays the user manual, which contains     |\r\n\0");
   PRINTS("|          operating system provided commands.          |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|[Press ENTER to continue]                              |\0");
   
   SCANN(n);
   
   PRINTS("|                General Commands Manual                |\r\n\0");
   PRINTS("|                      (continued)                      |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   prnt arg1                                           |\r\n\0");
   PRINTS("|          Loads and outputs the contents of a file to  |\r\n\0");
   PRINTS("|          the printer, where arg1 is the file to       |\r\n\0");
   PRINTS("|          print.                                       |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   remv arg1                                           |\r\n\0");
   PRINTS("|          Deletes a specific file, where arg1 is the   |\r\n\0");
   PRINTS("|          file to delete.                              |\r\n\0");
   PRINTS("|   senv                                                |\r\n\0");
   PRINTS("|          Set environment variables, which includes    |\r\n\0");
   PRINTS("|          the background and foreground colors.        |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   show arg1                                           |\r\n\0");
   PRINTS("|          Loads and outputs the contents of a file to  |\r\n\0");
   PRINTS("|          the console/screen, where arg1 is the file   |\r\n\0");
   PRINTS("|          to display.                                  |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|   tewt arg1                                           |\r\n\0");
   PRINTS("|          Not implemented as of yet.                   |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|                                                       |\r\n\0");
   PRINTS("|[Press ENTER to continue]                              |\0");
   
   SCANN(n);
   
   END;
}

void newLine()
{
   PRINTS("\r\n\0");
}
