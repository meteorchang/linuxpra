#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXARGS 20
#define ARGLEN 100

char * makestring(char*);       /* switch LR to \0 */

int main()
{
  char *arglist[MAXARGS+1];
  int numargs;                  /* args counter */
  char argbuf[ARGLEN];          /* a temp variable */

  numargs = 0;
  while (numargs < MAXARGS) {
    printf("Arg[%d]?", numargs);
    /*
     * argbuf is a char sequence end with LR, so use makestring to 
     * make argbuf a string
     */
    if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n') 
      arglist[numargs++] = makestring(argbuf);
    else {
      if (numargs > 0) {        /* LR printed */
        arglist[numargs] = NULL;
        execute(arglist);
        //numargs = 0;
      }
    }
  }
  return 0;
}

int execute(char*arglist[])
{
  execvp(arglist[0], arglist);
  perror("execvp failed");
  exit(10);
}

char * makestring(char * buf)
{
  char * cp;
  buf[strlen(buf)-1] = '\0';
  cp = malloc(strlen(buf)+1);
  if (cp == NULL) {
    fprintf(stderr, "no memory\n");
    exit(1);
  }
  strcpy(cp, buf);
  return cp;

}
