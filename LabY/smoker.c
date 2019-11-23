#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void P();  //wait and --
void V();  //release and ++

Semaphore	agentSem = 1,
		tobacco = 0;
		paper = 0;
		match = 0;

int main()
{
//Need to make 3 agent threads sleep for random period
//of time (up to 200 milliseconds) before beginning to
//wait on agentSem
while(true)
{
   usleep(((rand() % 200) + 1) * 1000);
   P(agentSem);
   V(tobacco);
   V(paper);
}

while(true)
{
   usleep(((rand() % 200) + 1) * 1000);
   P(agentSem);
   V(tobacco);
   V(match);
}

while(true)
{
   usleep(((rand() % 200) + 1) * 1000);
   P(agentSem);
   V(match);
   V(paper);
}



while(true)
{
   P(tobacco)
   P(mutex)
   if(isPaper)
   {
      isPaper = false
      V(matchSem)
   }
   else if(isMatch)
   {
      isMatch = false
      V(paperSem)
   }
   else
      isTobacco = true
   V(mutex)
}

}

void P(int s)
{
   while(s == 0)
      wait();

   s = s -1;
}

void V(int s)
{
   s = s + 1;
}
