/*
 * Brendon Lovejoy, Corey Miller, Colin Frame
 * bjl66@zips.uakron.edu
 * Operating Systems
 */

void handleCommands(char *, char, char);
int compareCommands(char *, char *);
void parseWord(char *, char *, int, int);
void clearBuffer(char *, int);

void main()
{
   char buffer[100];
   char color_buffer[512];
   char config_background;
   char config_foreground;
   
   interrupt(33, 2, color_buffer, 258, 1);
   config_background = color_buffer[0];
   config_foreground = color_buffer[1];
   
   interrupt(33,0,"\r\n\0",0,0);
   while(1)
   {
      interrupt(33,0,"^(~(oo)~)^ \0",0,0);  /*Print prompt to screen*/
      interrupt(33, 1, buffer, 0, 0);  /*Collect user input*/
      /*Parse the input and execute the command*/
      handleCommands(buffer, config_background, config_foreground);
      clearBuffer(buffer, 100);  /*Clear the buffer for new input*/
   }
}

/*Parse the user input and execute the command if valid. *
 *Here, buffer holds the input and a/b are the screen    *
 *background/foreground colors, respectively.            */
void handleCommands(char *buffer, char background, char foreground)
{
   char word[100];      /*will hold the parsed word*/
   char cmd[10];         /*will hold the parsed command*/
   int i;               /*iterator for copying command*/
   int incomplete = 0;  /*flag true if not enough arguments*/
   
   parseWord(word, buffer, 0, 0);  /*Determine the command*/
   clearBuffer(cmd, 10);           /*clear cmd buffer*/
   
   if(word[0] == '\0')       /*if no input, return*/
      return;
   else
      for(i = 0; i < 10; i++)  /*copy command from word to cmd*/
         cmd[i] = word[i];
   

   
   /*Structure for determining cmd from user input and execute    *
    *(In this version, the command and arguments are printed,     *
    * where only boot, clrs and echo can be executed as intended) */
   if(compareCommands(cmd, "boot\0"))
      interrupt(25, 0, 0, 0, 0);
   else if(compareCommands(cmd, "clrs\0"))
      interrupt(33, 12, background+1, foreground+1, 0);
   else if(compareCommands(cmd, "echo\0"))
   {
      parseWord(word, buffer, 0, 1);
      interrupt(33, 0, word, 0, 0);
      interrupt(33, 0, "\r\n\0", 0, 0);
   }
   else if(compareCommands(cmd, "copy\0"))
   {
      parseWord(word, buffer, 1, 0);
      incomplete = (word[0] == '\0');
      parseWord(word, buffer, 2, 0);
      incomplete = incomplete || (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command    : \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         parseWord(word, buffer, 1, 0);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, " \0", 0, 0);
         parseWord(word, buffer, 2, 0);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, "\r\n\0", 0, 0);
      }
   }
   else if(compareCommands(cmd, "ddir\0"))
   {
      interrupt(33, 0, "Command    : \0", 0, 0);
      interrupt(33, 0, cmd, 0, 0);
      interrupt(33, 0, "\r\n\0", 0, 0);
   }
   else if(compareCommands(cmd, "exec\0"))
   {
      parseWord(word, buffer, 1, 0);
      incomplete = (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command    : \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, "\r\n\0", 0, 0);
      }
   }
   else if(compareCommands(cmd, "help\0"))
   {
      interrupt(33, 0, "Command    : \0", 0, 0);
      interrupt(33, 0, cmd, 0, 0);
      interrupt(33, 0, "\r\n\0", 0, 0);
   }
   else if(compareCommands(cmd, "prnt\0"))
   {
      parseWord(word, buffer, 1, 0);
      incomplete = (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command    : \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, "\r\n\0", 0, 0);
      }
   }
   else if(compareCommands(cmd, "remv\0"))
   {
      parseWord(word, buffer, 1, 0);
      incomplete = (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command    : \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, "\r\n\0", 0, 0);
      }
   }
   else if(compareCommands(cmd, "senv\0"))
   {
      interrupt(33, 0, "Command    : \0", 0, 0);
      interrupt(33, 0, cmd, 0, 0);
      interrupt(33, 0, "\r\n\0", 0, 0);
   }
   else if(compareCommands(cmd, "show\0"))
   {
      parseWord(word, buffer, 1, 0);
      incomplete = (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command    : \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, "\r\n\0", 0, 0);
      }
   }
   else if(compareCommands(cmd, "twet\0"))
   {
      parseWord(word, buffer, 1, 0);
      incomplete = (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command    : \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, "\r\n\0", 0, 0);
      }
   }
   else
      interrupt(33, 0, "That is not a valid command.\r\n\0", 0, 0);
   
   if(incomplete == 1)
   {
      interrupt(33, 0, "The command is incomplete.\r\n\0", 0, 0);
      incomplete = 0;
   }
}

/*Return true if the user command is equal to the passed command.*/
int compareCommands(char *cmdWord, char *matchWord)
{
   int same = 1;
   int i = 0;
   
   while(cmdWord[i] != '\0')
   {
      if(cmdWord[i] != matchWord[i])
         same = 0;
      i++;
   }
   cmdWord[i] = '\0';

   return same;
}

/*Break up the input one word at a time, determined by function arguments.   *
 *Here, word will hold the parsed word, buffer holds the user input, fileNum *
 *determines which argument/file to collect (0 is the command) and when echo *
 *is 1, the entire buffer after the command will be read.                    */
void parseWord(char *word, char *buffer, int fileNum, int echo)
{
   int i = 0;
   int j = 0;
   int k = 0;
   
   clearBuffer(word, 100);
   
   if(echo == 1)  /*string parsing for echo only*/
   {
      i = 5;
      while(buffer[i] == ' ')
         i++;
      while(buffer[i] != '\0')
      {
         word[j] = buffer[i];
         i++;
         j++;
      }
   }
   else           /*for commands (with and without arguments*/
   {
      for(k = 0; k < fileNum; k++)
      {
         /*Get to each argument*/
         while(buffer[i] != ' ' && buffer[i] != '\0')
            i++;
         while(buffer[i] == ' ')
            i++;
      }
      
      /*collect text from argument*/
      while(buffer[i] != '\0' && buffer[i] != ' ')
      {
         word[j] = buffer[i];
         i++;
         j++;
      }
   }
   word[j] = '\0';
}

/*Replace all characters in the buffer with null.*/
void clearBuffer(char *buffer, int size)
{
   int i = 0;
   while(buffer[i] != '\0' && i < size)
   {
         buffer[i] = '\0';
         i++;
   }
}

