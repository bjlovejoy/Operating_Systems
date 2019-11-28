#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>	//POSIX functions
#include <stdio.h>	//printing to screen (for testing)
#include <stdlib.h>	//basic functions

#define true  1
#define false 0

void P();  //wait and --
void V();  //release and ++

//These determine what is currently on the table
Boolean	isTobacco = false,
	isPaper   = false,
	isMatch   = false;

//*agentSem is so only one agent outputs to the table
//*tobacco, paper and match are binary semaphores for
// the items on the table
//*tobaccoSem, paperSem and matchSem singal the smokers
//*mutex is for mutual exclusion
Semaphore	agentSem   = 1,
		tobacco    = 0,
		paper      = 0,
		match      = 0,
		tobaccoSem = 0,
		paperSem   = 0,
		matchSem   = 0,
		mutex      = 1;

int main()
{
//Need to make 3 agent threads sleep for random period
//of time (up to 200 milliseconds) before beginning to
//wait on agentSem
while(i < 6)
{
   usleep(((rand() % 200) + 1) * 1000);
   P(agentSem);
   V(tobacco);
   V(paper);
   i++;
}

while(j < 6)
{
   usleep(((rand() % 200) + 1) * 1000);
   P(agentSem);
   V(tobacco);
   V(match);
   j++;
}

while(k < 6)
{
   usleep(((rand() % 200) + 1) * 1000);
   P(agentSem);
   V(match);
   V(paper);
   k++;
}




//3 pushers for each combination
//One with tobacco
while(x < 12)
{
   P(tobacco);
   P(mutex);
   if(isPaper)
   {
      isPaper = false;
      V(matchSem);
   }
   else if(isMatch)
   {
      isMatch = false;
      V(paperSem);
   }
   else
      isTobacco = true;
   V(mutex);
   x++;
}

//One with paper
while(y < 12)
{
   P(paper);
   P(mutex);
   if(isTobacco)
   {
      isTobacco = false;
      V(matchSem);
   }
   else if(isMatch)
   {
      isMatch = false;
      V(tobaccoSem);
   }
   else
      isPaper = true;
   V(mutex);
   y++;
}

//One with match
while(z < 12)
{
   P(match);
   P(mutex);
   if(isPaper)
   {
      isPaper = false;
      V(TobaccoSem);
   }
   else if(isTobacco)
   {
      isTobacco = false;
      V(paperSem);
   }
   else
      isMatch = true;
   V(mutex);
   z++;
}



//CONSIDER THAT SEMAPHORES ARE ITERATORS (instead of a, b, c, ...)
//50 milliseconds for making and smoking the cigarette
// (don't forget to release anything important)
//6 smokers, each holding 2 items needing one additional item
while(a < 3)
{
   P(tobaccoSem);
      >>>Make a cigarette<<<
   V(agentSem);
      >>>Smoke the cigarette<<<
   a++;
}

while(b < 3)
{
   P(tobaccoSem);
      >>>Make a cigarette<<<
   V(agentSem);
      >>>Smoke the cigarette<<<
   b++;
}

while(c < 3)
{
   P(paperSem);
      >>>Make a cigarette<<<
   V(agentSem);
      >>>Smoke the cigarette<<<
   c++;
}

while(d < 3)
{
   P(paperSem);
      >>>Make a cigarette<<<
   V(agentSem);
      >>>Smoke the cigarette<<<
   d++;
}

while(e < 3)
{
   P(matchSem);
      >>>Make a cigarette<<<
   V(agentSem);
      >>>Smoke the cigarette<<<
   e++;
}

while(f < 3)
{
   P(matchSem);
      >>>Make a cigarette<<<
   V(agentSem);
      >>>Smoke the cigarette<<<
   f++
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
