// ACADEMIC INTEGRITY PLEDGE
//
// - I have not used source code obtained from another student nor
//   any other unauthorized source, either modified or unmodified.
//
// - All source code and documentation used in my program is either
//   my original work or was derived by me from the source code
//   published in the textbook for this course or presented in
//   class.
//
// - I have not discussed coding details about this project with
//   anyone other than my instructor. I understand that I may discuss
//   the concepts of this program with other students and that another
//   student may help me debug my program so long as neither of us
//   writes anything during the discussion or modifies any computer
//   file during the discussion.
//
// - I have violated neither the spirit nor letter of these restrictions.
//
//
//
// Signed:_Brendon Lovejoy, Corey Miller, Colin Frame___ Date:__11-18-2019____

// 3460:426 Lab 4A - Basic C shell

/* Basic shell */

/*
 * This is a very minimal shell. It finds an executable in the
 * PATH, then loads it and executes it (using execv). Since
 * it uses "." (dot) as a separator, it cannot handle file
 * names like "minishell.h"
 *
 * The focus on this exercise is to use fork, PATH variables,
 * and execv.
 */

#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_ARGS	64
#define MAX_ARG_LEN	16
#define MAX_LINE_LEN	80
#define WHITESPACE	" ,\t\n"
#define TRUE 1

struct command_t
{
   char *name;             //name of command
   int argc;               //number of arguments
   char *argv[MAX_ARGS];   //argument array
};

/* Function prototypes */
int parseCommand(char *, struct command_t *);
void printPrompt();
void readCommand(char *);
void storeString(char *, char *, int);
void help();
void list();
void internet();
void execute(char *, int);

//int main(int argc, char *argv[])
int main()
{
   int pid;          //process ID
   int status;       //integer to pass to wait
   int skip;         //determine to skip execvp in main
   int background;   //determine to skip wait() in main
                     //(for background processes)
   char cmdLine[MAX_LINE_LEN];   //user input character array
   struct command_t command;     //command_t object

   while(TRUE)
   {
      skip = 0;
      background = 0;
      printPrompt();
      /* Read the command line and parse it */
      readCommand(cmdLine);
      
      parseCommand(cmdLine, &command);
      
      command.argv[command.argc] = NULL;

      switch(command.name[0])
      {
         case 'C':  //Copy file
            storeString(command.name, "cp", 2);
            printf("\nCOPY ARG: %d\n", command.argc);
            break;
         case 'D':  //Delete file
            storeString(command.name, "rm", 2);
            break;
         case 'E':  //Echo text
            storeString(command.name, "echo", 4);
            break;
         case 'H':  //Help
            help();
            skip = 1;
            break;
         case 'L':  //List directory contents
            list();
            skip = 1;
            break;
         case 'M':  //Make text file and launch editor
            storeString(command.name, "nano", 4);
            break;
         case 'P':  //Print file contents to screen
            storeString(command.name, "more", 4);
            break;
         case 'Q':  //Shell termination
            printf("\nshell: Terminating successfully\n\n");
            return 0;
         case 'S':  //Launch internet browser as background process
            internet();
            background = 1;
            skip = 1;
            break;
         case 'W':  //Clear screen
            storeString(command.name, "clear", 5);
            break;
         case 'X':  //Execute program
            execute(command.argv[1], command.argc);
            skip = 1;
            break;
         case '\0': //Enter key pressed without a command
            skip = 1;
            break;
      }

      /* Create a child process to execute the command */
      if(skip)
         ;  //Does nothing, avoids creating a child process
      else if((pid = fork()) == 0)
      {
         /* Child executing command */
         execvp(command.name, command.argv);
//         printf("\nERROR - execvp returned -1\n");
         printf("\nERROR: NOT VALID COMMAND\n");
         return 0;
      }

      /* Wait for the child to terminate (if not a background process) */
      if(!background)
         wait(&status);
   }
}

/* End basic shell */

/* Parse Command function */

/* Determine command name and construct the parameter list.
 * This function will build argv[] and set the argc value.
 * argc is the number of "tokens" or words on the command line
 * argv[] is an array of strings (pointers to char *). The last
 * element in argv[] must be NULL. As we scan the command line
 * from the left, the first token goes in argv[0], the second in
 * argv[1], and so on. Each time we add a token to argv[],
 * we increment argc.
 */
int parseCommand(char *cLine, struct command_t *cmd)
{
   int argc;
   char **clPtr;
   /* Initialization */
   clPtr = &cLine;	/* cLine is the command line */
   argc = 0;
   cmd->argv[argc] = (char *) malloc(MAX_ARG_LEN);
   /* Fill argv[] */
   while ((cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL)
   {
      cmd->argv[++argc] = (char *) malloc(MAX_ARG_LEN);
   }
   /* Set the command name and argc */
   cmd->argc = argc - 1;
   cmd->name = (char *) malloc(sizeof(cmd->argv[0]));
   strcpy(cmd->name, cmd->argv[0]);
   return 1;
}

/* End parseCommand function */

/* Print prompt and read command functions - pp. 79-80 */

void printPrompt()
{
   /* Build the prompt string to have the machine name,
    * current directory, or other desired information
    */
   char *promptString = "linux(bjl66)|>\0";
   printf("%s ", promptString);
}

void readCommand(char *buffer)
{
   /* This code uses any set of I/O functions, such as those in
    * the stdio library to read the entire command line into
    * the buffer. This implementation is greatly simplified,
    * but it does the job.
    */
   fgets(buffer, 80, stdin);
}

/* End printPrompt and readCommand */


//Used to copy character arrays, where char array to copy to
//is passed first, followed by the char array holding the text
//to copy form, followed by the number of characters to copy
void storeString(char *save, char *text, int num)
{
   int i;   //iterator variable
   for(i = 0; i < num; i++)
      save[i] = text[i];
}

//Function to handle the help (H) command
void help()
{
   int pid;    //Process ID
   int status; //Status int to pass to wait()
   struct command_t cmd;   //command_t object
   char helpBuf[13];       //character buffer for help command
   
   storeString(helpBuf, "more helpMan\0", 13);  //store help command in buffer
   parseCommand(helpBuf, &cmd);  //parse the input for execvp
   
   printf("\n");  //print newline
   
   if((pid = fork()) == 0)
   {
      /* Child executing cmd */
      execvp(cmd.name, cmd.argv);
      printf("\nERROR: NOT VALID COMMAND\n");
      exit(0);
   }
   wait(&status);
}

//Function to handle the list (L) command
void list()
{
   int pid;    //Process ID
   int status; //Status int to pass to wait()
   struct command_t pwdCmd;   //command_t object for pwd command
   struct command_t lsCmd;    //command_t object for ls -l command
   char pwdBuf[4];            //character buffer for pwd command
   char lsBuf[6];             //character buffer for ls -l command
   
   storeString(pwdBuf, "pwd\0", 4); //store pwd command in buffer
   parseCommand(pwdBuf, &pwdCmd);   //parse the input for execvp
   
   printf("\n");  //print newline
   
   if((pid = fork()) == 0)
   {
      /* Child executing cmd */
      execvp(pwdCmd.name, pwdCmd.argv);
      printf("\nERROR: NOT VALID COMMAND\n");
      exit(0);
   }
   wait(&status);

   printf("\n");  //print newline
   storeString(lsBuf, "ls -l\0", 6);   //store ls -l command in buffer
   parseCommand(lsBuf, &lsCmd);        //parse the input for execvp
   
   if((pid = fork()) == 0)
   {
      /* Child executing cmd */
      execvp(lsCmd.name, lsCmd.argv);
      printf("\nERROR: NOT VALID COMMAND\n");
      exit(0);
   }
}

//Function to handle the internet browser (S) command
void internet()
{
   int pid;                //Process ID
   struct command_t cmd;   //command_t object
   char inBuf[9];          //input buffer
   
   storeString(inBuf, "firefox\0", 8); //store firefox command in buffer
   
   parseCommand(inBuf, &cmd);          //parse the input for execvp

   if((pid = fork()) == 0)
   {
      /* Child executing cmd */
      execvp(cmd.name, cmd.argv);
      printf("\nERROR: NOT VALID COMMAND\n");
      exit(0);
   }
}

//Function to handle the execution of files
void execute(char* text, int num)
{
   struct command_t cmd;   //command_t object
   
   if(num == 2)
   {
      int i;      //iterator variable
      int pid;    //Process ID
      int status; //Status int to pass to wait()
      int len = strlen(text); //length of file name to execute
      char buffer[len + 3];   //buffer to hold command
      
      //Add ./ to filename to allow execution
      buffer[0] = '.';
      buffer[1] = '/';
      for(i = 0; i < len; i++)
         buffer[i + 2] = text[i];
      
      buffer[len + 2] = '\0';
      
      parseCommand(buffer, &cmd);   //parse the input for execvp
      if((pid = fork()) == 0)
      {
         /* Child executing cmd */
         execvp(cmd.name, cmd.argv);
         printf("\nERROR: not valid file name\n");
         exit(0);
      }
      wait(&status);
   }
   else
      printf("\nPlease list 1 program.\n\n");   //error handling
}



