/***************************************************************************
 * Program :  Set ticker by using setitmer function                        * 
 * Author  :  June                                                         *
 * History :  2013/4/17                                                    *
 **************************************************************************/
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void countdown(int);            /* the sinal handler  */
int  set_ticker(int);           /* set the ticker */

int main()
{
  signal(SIGALRM, countdown);   /* setup the signal handler */
  if (set_ticker(500) == -1)
    perror("set_ticker");
  else
    while(1)
      pause();
  return 0;
}

void countdown(int signum)
{
  static int num = 10;
  printf("%d..", num--);
  fflush(stdout);
  if (num < 0) {
    printf("DONE\n");
    exit(0);
  }
  
}

int set_ticker(int n_msecs)
{
  struct itimerval new_timeset;
  long n_sec, n_usecs;
  
  n_sec = n_msecs/1000;
  n_usecs = (n_msecs%1000) *1000L;

  new_timeset.it_interval.tv_sec = n_sec; /* set the initiazing interval timer */
  new_timeset.it_interval.tv_usec = n_usecs;
  
  new_timeset.it_value.tv_sec = n_sec; /* set the repeat interval timer */
  new_timeset.it_value.tv_usec = n_usecs;
  

  return setitimer(ITIMER_REAL, &new_timeset, NULL);
}
