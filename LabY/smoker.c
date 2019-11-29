#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>	//POSIX functions
#include <stdio.h>	//printing to screen (for testing)
#include <stdlib.h>	//basic functions
#include <pthread.h>
#include <semaphore.h>

#define true  1
#define false 0

void P();  //wait and --
void V();  //release and ++

void *agent1();
void *agent2();
void *agent3();

void *pusher1();
void *pusher2();
void *pusher3();

void *tobaccoSmoker1();
void *tobaccoSmoker2();
void *paperSmoker1();
void *paperSmoker2();
void *matchSmoker1();
void *matchSmoker2();

//These determine what is currently on the table
int	isTobacco = false,
	isPaper   = false,
	isMatch   = false;

//*agentSem is so only one agent outputs to the table
//*tobacco, paper and match are binary semaphores for
// the items on the table
//*tobaccoSem, paperSem and matchSem singal the smokers
//*mutex is for mutual exclusion
/*sem_t		agentSem,
		tobacco,
		paper,
		match,
		tobaccoSem,
		paperSem,
		matchSem,
		mutex;*/

int		agentSem = 1,
		tobacco = 0,
		paper = 0,
		match = 0,
		tobaccoSem = 0,
		paperSem = 0,
		matchSem = 0,
		mutex = 1;




int main()
{
printf("Here First");

/*   sem_init(&agentSem, 0, 1);
   sem_init(&tobacco, 0, 0);
   sem_init(&paper, 0, 0);
   sem_init(&match, 0, 0);
   sem_init(&tobaccoSem, 0, 0);
   sem_init(&paperSem, 0, 0);
   sem_init(&matchSem, 0, 0);
   sem_init(&mutex, 0, 1);*/

   pthread_t a1, a2, a3;
   pthread_t p1, p2, p3;
   pthread_t tS1, tS2, pS1, pS2, mS1, mS2;
printf("Here");
   pthread_create(&a1, NULL, agent1, NULL);
   pthread_create(&a2, NULL, agent2, NULL);
   pthread_create(&a3, NULL, agent3, NULL);
printf("Over Here");
   pthread_create(&p1, NULL, pusher1, NULL);
   pthread_create(&p2, NULL, pusher2, NULL);
   pthread_create(&p3, NULL, pusher3, NULL);

   pthread_create(&tS1, NULL, tobaccoSmoker1, NULL);
   pthread_create(&tS2, NULL, tobaccoSmoker2, NULL);
   pthread_create(&pS1, NULL, paperSmoker1, NULL);
   pthread_create(&pS2, NULL, paperSmoker2, NULL);
   pthread_create(&mS1, NULL, matchSmoker1, NULL);
   pthread_create(&mS2, NULL, matchSmoker2, NULL);


   pthread_join(a1, NULL);
   pthread_join(a2, NULL);
   pthread_join(a3, NULL);

   pthread_join(p1, NULL);
   pthread_join(p2, NULL);
   pthread_join(p3, NULL);

   pthread_join(tS1, NULL);
   pthread_join(tS2, NULL);
   pthread_join(pS1, NULL);
   pthread_join(pS2, NULL);
   pthread_join(mS1, NULL);
   pthread_join(mS2, NULL);

   return 0;
}






//Need to make 3 agent threads sleep for random period
//of time (up to 200 milliseconds) before beginning to
//wait on agentSem
void *agent1()
{
   printf("Inside agent1\n");
   int i = 0;
   while(i < 6)
   {
      usleep(((rand() % 200) + 1) * 1000);
      P(agentSem);
      V(tobacco);
      V(paper);
	  printf("Output tobacco and paper\n");
      i++;
   }
   pthread_exit(0);
}

void *agent2()
{
   printf("Inside agent2\n");
   int j = 0;
   while(j < 6)
   {
      usleep(((rand() % 200) + 1) * 1000);
      P(agentSem);
      V(tobacco);
      V(match);
	  printf("Output tobacco and match\n");
      j++;
   }
   pthread_exit(0);
}

void *agent3()
{
   printf("Inside agent3\n");
   int k = 0;
   while(k < 6)
   {
      usleep(((rand() % 200) + 1) * 1000);
      P(agentSem);
      V(match);
      V(paper);
	  printf("Output match and paper\n");
      k++;
   }
   pthread_exit(0);
}



//3 pushers for each combination
//One with tobacco
void *pusher1()
{
   printf("Inside pusher1\n");
   int x = 0;
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
   pthread_exit(0);
}

//One with paper
void *pusher2()
{
   printf("Inside pusher2\n");
   int y = 0;
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
   pthread_exit(0);
}

//One with match
void *pusher3()
{
   printf("Inside pusher3\n");
   int z = 0;
   while(z < 12)
   {
      P(match);
      P(mutex);
      if(isPaper)
      {
         isPaper = false;
         V(tobaccoSem);
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
   pthread_exit(0);
}


//CONSIDER THAT SEMAPHORES ARE ITERATORS (instead of a, b, c, ...)
//50 milliseconds for making and smoking the cigarette
// (don't forget to release anything important)
//6 smokers, each holding 2 items needing one additional item
void *tobaccoSmoker1()
{
   int a = 0;
   while(a < 3)
   {
      P(tobaccoSem);
	  printf("tS1 smoking\n");
      usleep(((rand() % 50) + 1) * 1000);
      V(agentSem);
      usleep(((rand() % 50) + 1) * 1000);
      a++;
   }
   pthread_exit(0);
}

void *tobaccoSmoker2()
{
   int b = 0;
   while(b < 3)
   {
      P(tobaccoSem);
	  printf("tS2 smoking\n");
      usleep(((rand() % 50) + 1) * 1000);
      V(agentSem);
      usleep(((rand() % 50) + 1) * 1000);
      b++;
   }
   pthread_exit(0);
}

void *paperSmoker1()
{
   int c = 0;
   while(c < 3)
   {
      P(paperSem);
	  printf("pS1 smoking\n");
      usleep(((rand() % 50) + 1) * 1000);
      V(agentSem);
      usleep(((rand() % 50) + 1) * 1000);
      c++;
   }
   pthread_exit(0);
}

void *paperSmoker2()
{
   int d = 0;
   while(d < 3)
   {
      P(paperSem);
	  printf("pS2 smoking\n");
      usleep(((rand() % 50) + 1) * 1000);
      V(agentSem);
      usleep(((rand() % 50) + 1) * 1000);
      d++;
   }
   pthread_exit(0);
}

void *matchSmoker1()
{
   int e = 0;
   while(e < 3)
   {
      P(matchSem);
	  printf("mS1 smoking\n");
      usleep(((rand() % 50) + 1) * 1000);
      V(agentSem);
      usleep(((rand() % 50) + 1) * 1000);
      e++;
   }
   pthread_exit(0);
}

void *matchSmoker2()
{
   int f = 0;
   while(f < 3)
   {
      P(matchSem);
	  printf("mS2 smoking\n");
      usleep(((rand() % 50) + 1) * 1000);
      V(agentSem);
      usleep(((rand() % 50) + 1) * 1000);
      f++;
   }
   pthread_exit(0);
}





void P(int s)
{
   while(s == 0);
      //wait

   s = s -1;
}

void V(int s)
{
   s = s + 1;
}
