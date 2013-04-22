/* Name   :  013signaldemo.c
 * Purpose:  show the signal fucntion how-to-do-it
 * Need   :  run this and press Ctrl-C a few times
 * Author :  June
 * History:  Version 1, 2013/4/15
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
  void f(int);
  int i;
  signal(SIGINT,f);
  for (i = 0; i<5; i++) {
    printf("hello\n");
    sleep(1);
  }
  return 0;
}

void f(int signum)
{
  printf("OUCH!\n");
}
