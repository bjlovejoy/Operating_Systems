/*
 * Brendon Lovejoy, Corey Miller, Colin Frame
 * bjl66@zips.uakron.edu
 * Operating Systems
 */


#include <sys/types.h>
#include <unistd.h>	//POSIX functions
#include <stdio.h>	//printing to screen (for testing)
#include <stdlib.h>	//basic functions
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define true  1
#define false 0

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

time_t t;
//These determine what is currently on the table
int	isTobacco = false,
      isPaper   = false,
      isMatch   = false;

//*agentSem is so only one agent outputs to the table
//*tobacco, paper and match are binary semaphores for
// the items on the table
//*tobaccoSem, paperSem and matchSem singal the smokers
//*mutex is for mutual exclusion
sem_t    agentSem,
         tobacco,
         paper,
         match,
         tobaccoSem,
         paperSem,
         matchSem,
         mutex;

int main()
{
   srand((unsigned) time(&t));
   
   sem_init(&agentSem, 0, 1);
   sem_init(&tobacco, 0, 0);
   sem_init(&paper, 0, 0);
   sem_init(&match, 0, 0);
   sem_init(&tobaccoSem, 0, 0);
   sem_init(&paperSem, 0, 0);
   sem_init(&matchSem, 0, 0);
   sem_init(&mutex, 0, 1);

   pthread_t a1, a2, a3;
   pthread_t p1, p2, p3;
   pthread_t tS1, tS2, pS1, pS2, mS1, mS2;

   pthread_create(&a1, NULL, agent1, NULL);
   pthread_create(&a2, NULL, agent2, NULL);
   pthread_create(&a3, NULL, agent3, NULL);

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
   printf("AGENT1:\t\tENTER\n");
   int i = 0;
   while(i < 6)
   {
      usleep(((rand() % 200) + 1) * 1000);
      sem_wait(&agentSem);
      sem_post(&tobacco);
      sem_post(&paper);
	   printf("AGENT1:\t\toutput tobacco and paper\n");
      i++;
   }
   printf("AGENT1:\t\tEXIT\n");
   pthread_exit(0);
}

void *agent2()
{
   printf("AGENT2:\t\tENTER\n");
   int j = 0;
   while(j < 6)
   {
      usleep(((rand() % 200) + 1) * 1000);
      sem_wait(&agentSem);
      sem_post(&tobacco);
      sem_post(&match);
      printf("AGENT2:\t\toutput tobacco and match\n");
      j++;
   }
   printf("AGENT2:\t\tEXIT\n");
   pthread_exit(0);
}

void *agent3()
{
   printf("AGENT3:\t\tENTER\n");
   int k = 0;
   while(k < 6)
   {
      usleep(((rand() % 200) + 1) * 1000);
      sem_wait(&agentSem);
      sem_post(&match);
      sem_post(&paper);
      printf("AGENT3:\t\toutput match and paper\n");
      k++;
   }
   printf("AGENT3:\t\tEXIT\n");
   pthread_exit(0);
}



//3 pushers for each combination
//One with tobacco
void *pusher1()
{
   printf("PUSHER1:\tENTER\n");
   int x = 0;
   while(x < 12)
   {
      sem_wait(&tobacco);
      sem_wait(&mutex);
      if(isPaper)
      {
         isPaper = false;
         sem_post(&matchSem);
      }
      else if(isMatch)
      {
         isMatch = false;
         sem_post(&paperSem);
      }
      else
         isTobacco = true;
      sem_post(&mutex);
      x++;
   }
   printf("PUSHER1:\tEXIT\n");
   pthread_exit(0);
}

//One with paper
void *pusher2()
{
   printf("PUSHER2:\tENTER\n");
   int y = 0;
   while(y < 12)
   {
      sem_wait(&paper);
      sem_wait(&mutex);
      if(isTobacco)
      {
         isTobacco = false;
         sem_post(&matchSem);
      }
      else if(isMatch)
      {
         isMatch = false;
         sem_post(&tobaccoSem);
      }
      else
         isPaper = true;
      sem_post(&mutex);
      y++;
   }
   printf("PUSHER2:\tEXIT\n");
   pthread_exit(0);
}

//One with match
void *pusher3()
{
   printf("PUSHER3:\tENTER\n");
   int z = 0;
   while(z < 12)
   {
      sem_wait(&match);
      sem_wait(&mutex);
      if(isPaper)
      {
         isPaper = false;
         sem_post(&tobaccoSem);
      }
      else if(isTobacco)
      {
         isTobacco = false;
         sem_post(&paperSem);
      }
      else
         isMatch = true;
      sem_post(&mutex);
      z++;
   }
   printf("PUSHER3:\tEXIT\n");
   pthread_exit(0);
}


//CONSIDER THAT SEMAPHORES ARE ITERATORS (instead of a, b, c, ...)
//50 milliseconds for making and smoking the cigarette
// (don't forget to release anything important)
//6 smokers, each holding 2 items needing one additional item
void *tobaccoSmoker1()
{
   printf("T-SMOKER1:\tENTER\n");
   int a = 0;
   int ms;
   while(a < 3)
   {
      sem_wait(&tobaccoSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("tS1:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("tS1:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);
      a++;
   }
   printf("T-SMOKER1:\tEXIT\n");
   pthread_exit(0);
}

void *tobaccoSmoker2()
{
   printf("T-SMOKER2:\tENTER\n");
   int b = 0;
   int ms;
   while(b < 3)
   {
      sem_wait(&tobaccoSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("tS2:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("tS2:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);
      b++;
   }
   printf("T-SMOKER2:\tEXIT\n");
   pthread_exit(0);
}

void *paperSmoker1()
{
   printf("P-SMOKER1:\tENTER\n");
   int c = 0;
   int ms;
   while(c < 3)
   {
      sem_wait(&paperSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("pS1:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("pS1:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);
      c++;
   }
   printf("P-SMOKER1:\tEXIT\n");
   pthread_exit(0);
}

void *paperSmoker2()
{
   printf("P-SMOKER2:\tENTER\n");
   int d = 0;
   int ms;
   while(d < 3)
   {
      sem_wait(&paperSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("pS2:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("pS2:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);
      d++;
   }
   printf("P-SMOKER2:\tEXIT\n");
   pthread_exit(0);
}

void *matchSmoker1()
{
   printf("M-SMOKER1:\tENTER\n");
   int e = 0;
   int ms;
   while(e < 3)
   {
      sem_wait(&matchSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("mS1:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("mS1:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);
      e++;
   }
   printf("M-SMOKER1:\tEXIT\n");
   pthread_exit(0);
}

void *matchSmoker2()
{
   printf("M-SMOKER2:\tENTER\n");
   int f = 0;
   int ms;
   while(f < 3)
   {
      sem_wait(&matchSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("mS2:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("mS2:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);
      f++;
   }
   printf("M-SMOKER2:\tEXIT\n");
   pthread_exit(0);
}




