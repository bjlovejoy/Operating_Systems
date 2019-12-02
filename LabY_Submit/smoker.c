/*
 * Brendon Lovejoy, Corey Miller, Colin Frame
 * bjl66@zips.uakron.edu
 * Operating Systems
 * LabY: POSIX Threads (pthreads) and Semaphores
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

//Agent threads (functions)
void *agent1();
void *agent2();
void *agent3();

//Pusher threads (functions)
void *pusher1();
void *pusher2();
void *pusher3();

//Smoker threads (functions)
void *tobaccoSmoker1();
void *tobaccoSmoker2();
void *paperSmoker1();
void *paperSmoker2();
void *matchSmoker1();
void *matchSmoker2();

time_t t;   //for seeding the random integer generator

//These determine what is currently on the table
int	isTobacco = false,
      isPaper   = false,
      isMatch   = false;

//-agentSem is so only one agent outputs to the table
//-tobacco, paper and match are binary semaphores for
// the items on the table
//-tobaccoSem, paperSem and matchSem singal the smokers
//-mutex is for mutual exclusion
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
   srand((unsigned) time(&t));   //seed the random integer generator
   
   //initialize the semaphores
   sem_init(&agentSem, 0, 1);
   sem_init(&tobacco, 0, 0);
   sem_init(&paper, 0, 0);
   sem_init(&match, 0, 0);
   sem_init(&tobaccoSem, 0, 0);
   sem_init(&paperSem, 0, 0);
   sem_init(&matchSem, 0, 0);
   sem_init(&mutex, 0, 1);

   pthread_t a1, a2, a3;   //agent threads
   pthread_t p1, p2, p3;   //pusher threads
   pthread_t tS1, tS2, pS1, pS2, mS1, mS2;   //smoker threads

   //create the agent threads
   pthread_create(&a1, NULL, agent1, NULL);
   pthread_create(&a2, NULL, agent2, NULL);
   pthread_create(&a3, NULL, agent3, NULL);

   //create the pusher threads
   pthread_create(&p1, NULL, pusher1, NULL);
   pthread_create(&p2, NULL, pusher2, NULL);
   pthread_create(&p3, NULL, pusher3, NULL);

   //create the smoker threads
   pthread_create(&tS1, NULL, tobaccoSmoker1, NULL);
   pthread_create(&tS2, NULL, tobaccoSmoker2, NULL);
   pthread_create(&pS1, NULL, paperSmoker1, NULL);
   pthread_create(&pS2, NULL, paperSmoker2, NULL);
   pthread_create(&mS1, NULL, matchSmoker1, NULL);
   pthread_create(&mS2, NULL, matchSmoker2, NULL);


   //wait for the agent threads to terminate and join
   pthread_join(a1, NULL);
   pthread_join(a2, NULL);
   pthread_join(a3, NULL);

   //wait for the pusher threads to terminate and join
   pthread_join(p1, NULL);
   pthread_join(p2, NULL);
   pthread_join(p3, NULL);

   //wait for the smoker threads to terminate and join
   pthread_join(tS1, NULL);
   pthread_join(tS2, NULL);
   pthread_join(pS1, NULL);
   pthread_join(pS2, NULL);
   pthread_join(mS1, NULL);
   pthread_join(mS2, NULL);

   printf("\nAll threads joined, ending simulation.\n\n");
   return 0;
}


//Wait to acquire the agent semaphore, then
//output tobacco and paper (loops 3 times)
void *agent1()
{
   printf("AGENT1:\t\tENTER\n");
   int i = 0;
   while(i < 6)
   {
      usleep(((rand() % 200) + 1) * 1000);   //wait for up to 200 milliseconds
      sem_wait(&agentSem);
      sem_post(&tobacco);
      sem_post(&paper);
	   printf("AGENT1:\t\toutput tobacco and paper\n");
      i++;
   }
   printf("AGENT1:\t\tEXIT\n");
   pthread_exit(0);
}

//Wait to acquire the agent semaphore, then
//output tobacco and match (loops 3 times)
void *agent2()
{
   printf("AGENT2:\t\tENTER\n");
   int j = 0;
   while(j < 6)
   {
      usleep(((rand() % 200) + 1) * 1000);   //wait for up to 200 milliseconds
      sem_wait(&agentSem);
      sem_post(&tobacco);
      sem_post(&match);
      printf("AGENT2:\t\toutput tobacco and match\n");
      j++;
   }
   printf("AGENT2:\t\tEXIT\n");
   pthread_exit(0);
}

//Wait to acquire the agent semaphore, then
//output match and paper (loops 3 times)
void *agent3()
{
   printf("AGENT3:\t\tENTER\n");
   int k = 0;
   while(k < 6)
   {
      usleep(((rand() % 200) + 1) * 1000);   //wait for up to 200 milliseconds
      sem_wait(&agentSem);
      sem_post(&match);
      sem_post(&paper);
      printf("AGENT3:\t\toutput match and paper\n");
      k++;
   }
   printf("AGENT3:\t\tEXIT\n");
   pthread_exit(0);
}



//Wait to acquire the tobacco and mutex semaphores,
//then determine what else is on the table, assuming
//that tobacco is the first item on the table.  Depending
//on what is on the table, increment the appropraite
//semaphore to signal the corresponding smoker.
void *pusher1()
{
   printf("PUSHER1:\tENTER\n");
   int x = 0;
   while(x < 12)
   {
      sem_wait(&tobacco);
      sem_wait(&mutex);
      if(isPaper)   //tobacco and paper on table
      {
         isPaper = false;
         sem_post(&matchSem);  //signal match smoker
      }
      else if(isMatch)   //tobacco and match on table
      {
         isMatch = false;
         sem_post(&paperSem);  //signal paper smoker
      }
      else
         isTobacco = true;  //only tobacco on the table
      sem_post(&mutex);
      x++;
   }
   printf("PUSHER1:\tEXIT\n");
   pthread_exit(0);
}

//Wait to acquire the paper and mutex semaphores,
//then determine what else is on the table, assuming
//that paper is the first item on the table.  Depending
//on what is on the table, increment the appropraite
//semaphore to signal the corresponding smoker.
void *pusher2()
{
   printf("PUSHER2:\tENTER\n");
   int y = 0;
   while(y < 12)
   {
      sem_wait(&paper);
      sem_wait(&mutex);
      if(isTobacco)     //paper and tobacco on table
      {
         isTobacco = false;
         sem_post(&matchSem);   //signal the match smoker
      }
      else if(isMatch)  //paper and match on table
      {
         isMatch = false;
         sem_post(&tobaccoSem); //singal the tobacco smoker
      }
      else
         isPaper = true;  //only paper on the table
      sem_post(&mutex);
      y++;
   }
   printf("PUSHER2:\tEXIT\n");
   pthread_exit(0);
}

//Wait to acquire the match and mutex semaphores,
//then determine what else is on the table, assuming
//that match is the first item on the table.  Depending
//on what is on the table, increment the appropraite
//semaphore to signal the corresponding smoker.
void *pusher3()
{
   printf("PUSHER3:\tENTER\n");
   int z = 0;
   while(z < 12)
   {
      sem_wait(&match);
      sem_wait(&mutex);
      if(isPaper)         //match and paper on the table
      {
         isPaper = false;
         sem_post(&tobaccoSem);  //signal tobacco smoker
      }
      else if(isTobacco)  //match and tobacco on the table
      {
         isTobacco = false;
         sem_post(&paperSem);    //signal paper smoker
      }
      else
         isMatch = true;  //only match on the table
      sem_post(&mutex);
      z++;
   }
   printf("PUSHER3:\tEXIT\n");
   pthread_exit(0);
}


//First tobacco smoker, who waits for the semaphore
//to be available and then proceeds to make the
//cigarette, release the agent and then smoke the
//cigarette.
void *tobaccoSmoker1()
{
   printf("T-SMOKER1:\tENTER\n");
   int a = 0;
   int ms;     //integer to hold random number of milliseconds
   while(a < 3)
   {
      sem_wait(&tobaccoSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("tS1:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("tS1:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      a++;
   }
   printf("T-SMOKER1:\tEXIT\n");
   pthread_exit(0);
}

//Second tobacco smoker, who waits for the semaphore
//to be available and then proceeds to make the
//cigarette, release the agent and then smoke the
//cigarette.
void *tobaccoSmoker2()
{
   printf("T-SMOKER2:\tENTER\n");
   int b = 0;
   int ms;     //integer to hold random number of milliseconds
   while(b < 3)
   {
      sem_wait(&tobaccoSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("tS2:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("tS2:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      b++;
   }
   printf("T-SMOKER2:\tEXIT\n");
   pthread_exit(0);
}

//First paper smoker, who waits for the semaphore
//to be available and then proceeds to make the
//cigarette, release the agent and then smoke the
//cigarette.
void *paperSmoker1()
{
   printf("P-SMOKER1:\tENTER\n");
   int c = 0;
   int ms;     //integer to hold random number of milliseconds
   while(c < 3)
   {
      sem_wait(&paperSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("pS1:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("pS1:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      c++;
   }
   printf("P-SMOKER1:\tEXIT\n");
   pthread_exit(0);
}

//Second paper smoker, who waits for the semaphore
//to be available and then proceeds to make the
//cigarette, release the agent and then smoke the
//cigarette.
void *paperSmoker2()
{
   printf("P-SMOKER2:\tENTER\n");
   int d = 0;
   int ms;     //integer to hold random number of milliseconds
   while(d < 3)
   {
      sem_wait(&paperSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("pS2:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("pS2:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      d++;
   }
   printf("P-SMOKER2:\tEXIT\n");
   pthread_exit(0);
}

//First match smoker, who waits for the semaphore
//to be available and then proceeds to make the
//cigarette, release the agent and then smoke the
//cigarette.
void *matchSmoker1()
{
   printf("M-SMOKER1:\tENTER\n");
   int e = 0;
   int ms;     //integer to hold random number of milliseconds
   while(e < 3)
   {
      sem_wait(&matchSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("mS1:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("mS1:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      e++;
   }
   printf("M-SMOKER1:\tEXIT\n");
   pthread_exit(0);
}

//Second match smoker, who waits for the semaphore
//to be available and then proceeds to make the
//cigarette, release the agent and then smoke the
//cigarette.
void *matchSmoker2()
{
   printf("M-SMOKER2:\tENTER\n");
   int f = 0;
   int ms;     //integer to hold random number of milliseconds
   while(f < 3)
   {
      sem_wait(&matchSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("mS2:\t\tmaking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      sem_post(&agentSem);
      ms = ((rand() % 50) + 1) * 1000;
      printf("mS2:\t\tsmoking for %d ms\n", ms/1000);
      usleep(ms);    //wait for up to 50 milliseconds
      f++;
   }
   printf("M-SMOKER2:\tEXIT\n");
   pthread_exit(0);
}

