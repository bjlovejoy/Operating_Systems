/*
 * Brendon Lovejoy, Corey Miller, Colin Frame
 * bjl66@zips.uakron.edu
 * Operating Systems
 */

void handleCommands(char *, int, int);
int compareCommands(char *, char *);
void parseWord(char *, char *, int, int);
void clearBuffer(char *, int);

void main()
{
   /*Define variables first*/
   char buffer[100];
   char color_buffer[512];
   char config_background;
   char config_foreground;
   int i = 0;
   
   interrupt(33, 2, color_buffer, 258, 1);
   config_background = color_buffer[0];
   config_foreground = color_buffer[1];
   
   interrupt(33,0,"\r\n\0",0,0);
   while(1)
   {
      interrupt(33,0,"^(~(oo)~)^ \0",0,0);
      interrupt(33, 1, buffer, 0, 0);
      handleCommands(buffer, config_background, config_foreground);
      i = 0;
      clearBuffer(buffer, 100);
   }
}

void handleCommands(char *buffer, int a, int b)
{
   char word[100];
   char cmd[5];
   int i;
   int incomplete = 0;
   parseWord(word, buffer, 4, 0);
   
   clearBuffer(cmd, 5);
   for(i = 0; i < 5; i++)
      cmd[i] = word[i];
   
   if(compareCommands(cmd, "boot"))
      interrupt(25, 0, 0, 0, 0);
   else if(compareCommands(cmd, "clrs"))
      interrupt(33, 12, a+1, b+1, 0);
   else if(compareCommands(cmd, "echo"))
   {
      parseWord(word, buffer, 0, 0);
      interrupt(33, 0, word, 0, 0);
      interrupt(33, 0, "\r\n\0", 0, 0);
   }
   else if(compareCommands(cmd, "copy"))
   {
      parseWord(word, buffer, 0, 1);
      incomplete = (word[0] == '\0');
      parseWord(word, buffer, 0, 2);
      incomplete = incomplete || (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command:     \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         parseWord(word, buffer, 0, 1);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, " \0", 0, 0);
         parseWord(word, buffer, 0, 2);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, "\r\n\0", 0, 0);
      }
   }
   else if(compareCommands(cmd, "ddir"))
   {
      interrupt(33, 0, "Command: \0", 0, 0);
      interrupt(33, 0, cmd, 0, 0);
      interrupt(33, 0, "\r\n\0", 0, 0);
   }
   else if(compareCommands(cmd, "exec"))
   {
      parseWord(word, buffer, 0, 1);
      incomplete = (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command:     \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         parseWord(word, buffer, 0, 1);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, "\r\n\0", 0, 0);
      }
   }
   else if(compareCommands(cmd, "help"))
   {
      interrupt(33, 0, "Command: \0", 0, 0);
      interrupt(33, 0, cmd, 0, 0);
      interrupt(33, 0, "\r\n\0", 0, 0);
   }
   else if(compareCommands(cmd, "prnt"))
   {
      parseWord(word, buffer, 0, 1);
      incomplete = (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command:     \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         parseWord(word, buffer, 0, 1);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, "\r\n\0", 0, 0);
      }
   }
   else if(compareCommands(cmd, "remv"))
   {
      parseWord(word, buffer, 0, 1);
      incomplete = (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command:     \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         parseWord(word, buffer, 0, 1);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, "\r\n\0", 0, 0);
      }
   }
   else if(compareCommands(cmd, "senv"))
   {
      interrupt(33, 0, "Command: \0", 0, 0);
      interrupt(33, 0, cmd, 0, 0);
      interrupt(33, 0, "\r\n\0", 0, 0);
   }
   else if(compareCommands(cmd, "show"))
   {
      parseWord(word, buffer, 0, 1);
      incomplete = (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command:     \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         parseWord(word, buffer, 0, 1);
         interrupt(33, 0, word, 0, 0);
         interrupt(33, 0, "\r\n\0", 0, 0);
      }
   }
   else if(compareCommands(cmd, "twet"))
   {
      parseWord(word, buffer, 0, 1);
      incomplete = (word[0] == '\0');
      if(!incomplete)
      {
         interrupt(33, 0, "Command:     \0", 0, 0);
         interrupt(33, 0, cmd, 0, 0);
         interrupt(33, 0, "\r\nArgument(s): \0", 0, 0);
         parseWord(word, buffer, 0, 1);
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

int compareCommands(char *cmdWord, char *matchWord)
{
   int same = 1;
   int i;
   for(i = 0; i < 4; i++)
   {
      if(cmdWord[i] != matchWord[i])
         same = 0;
   }
   return same;
}

void parseWord(char *word, char *buffer, int num, int fileNum)
{
   int i = 0;
   int j = 0;
   int k = 0;
   
   clearBuffer(word, 100);
   
   if(num == 0 && fileNum == 0)           /*For echo*/
   {
      while(buffer[i] != ' ')
         i++;
      while(buffer[i] == ' ')
         i++;
      while(buffer[i] != '\0')
      {
         word[j] = buffer[i];
         i++;
         j++;
      }
      word[j] = '\0';
   }
   else if(num == 0)        /*For copy and rest (2 and single filename)*/
   {
      for(k = 0; k < fileNum; k++)
      {
         while(buffer[i] != ' ')     /*Get to each argument*/
            i++;
         i++;
      }

      while(buffer[i] != '\0' && buffer[i] != ' ')
      {
         word[j] = buffer[i];
         i++;
         j++;
      }
      word[j] = '\0';
   }
   else
   {
      while(i < num)
      {
         word[i] = buffer[i];
         i++;
      }
      word[i] = '\0';
   }
}

void clearBuffer(char *buffer, int size)
{
   int i = 0;
   while(buffer[i] != '\0' && i < size)
   {
         buffer[i] = '\0';
         i++;
   }
}

