#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main()
{
  signal(SIGINT, SIG_IGN);
  printf("you cannot stop me!\n");
  while (1) {
    sleep(1);
    printf("aha\n");
  }
  return 0;
}
