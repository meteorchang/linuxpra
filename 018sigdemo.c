/*************************************************************************
 * Program :   Test the weak of the signal function                      *
 * Need    :   Send signal repeatly to see the handling of the program   *
 * Author  :   June                                                      *
 * History :   Version 1, 2013/4/18                                      *
 *************************************************************************/

#include <stdio.h>
#include <signal.h>

#define INPUTLEN 100

void inthandler(int);           /* intpret signal handler */
void quithandler(int);          /* quit signal handler */

int main(int ac, char *av[])
{
  char input[INPUTLEN];
  int nchars;
  
  signal(SIGINT, inthandler);
  signal(SIGQUIT, quithandler);
  
  do {
    printf("\nType a message\n");
    nchars = read(0, input, (INPUTLEN-1));
    
    if (nchars == -1)
      perror("Read returned an error");
    else {
      input[nchars] = '\0';
      printf("You typed: %s", input);
    }
  } while (strncmp(input, "quit", 4) != 0);

    return 0;
}

void inthandler(int s)
{
  printf("Received signal %d.. waiting\n", s);
  sleep(2);
  printf("Leaving inthandler \n");
}

void quithandler(int s)
{
  printf("Received signal %d.. waiting\n", s);
  sleep(3);
  printf("Leaving quithandler \n");

}
