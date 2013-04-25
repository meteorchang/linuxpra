#include <stdio.h>
#include <unistd.h>

int main()
{
  char *arglist[3];
  arglist[0] = "ls";
  arglist[1] = "-l";
  arglist[2] = 0;
  printf("*********About to execute ls -l\n");
  execvp("ls", arglist);
  printf("********* ls is done. bye\n"); /* The code does not execute */
  return 0;
}
/*
 * The exec system call clear the current process,then 
 * execute in the free process
 */
