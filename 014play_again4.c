/* Name    : 014play_again3.c
 * Purpose : solve the question in the playagain 2 that cannot restore the setting
 *           default if press Ctrl-c when running use the signal;
 * Need    : run the program and Ctrl-C pressed
 * Author  : June
 * History : Version 3,2013/4/16
 */
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <stdlib.h>

#define ASK "Do you want another transaction"
#define TRIES 3
#define SLEEPTIME 2
#define BEEP putchar('\a')

void ctrl_chandler(int);
void ttymode(int);
void set_cr_noecho_mode();
void set_nodelay_mode();
int get_response(char *, int);
int get_ok_char();

int main()
{
  int response;
  
  ttymode(0);
  set_cr_noecho_mode();
  signal(SIGINT, ctrl_chandler);
  signal(SIGQUIT, SIG_IGN);
  response = get_response(ASK, TRIES);
  printf("\n");
  ttymode(1);
  return response;
}

int get_response(char *question, int maxtries)
{
  int input;
  
  printf("%s(y/n)?", question);
  fflush(stdout);
  while(1) {
    sleep(SLEEPTIME);
    input = tolower(get_ok_char());
  }
}

int get_ok_char()
{
  int c;
  while ((c = getchar()) != EOF && strchr("yYnN", c) == NULL) 
    ;
  return c;
}

void set_cr_noecho_mode()
{
  struct termios ttystate;
  
  tcgetattr(0, &ttystate);
  ttystate.c_lflag &= ~ICANON;
  ttystate.c_lflag &= ~ECHO;
  ttystate.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &ttystate);
}

void set_nodelay_mode()
{
  int termflags;
  
  termflags = fcntl(0, F_GETFL);
  termflags |= O_NDELAY;
  fcntl(0, F_SETFL, termflags);
}

void ttymode(int how)
{
  static struct termios original_mode;
  static int original_flags;
  static int stored = 0;
  
  if (how == 0) {
    tcgetattr(0, &original_mode);
    original_flags = fcntl(0, F_GETFL);
    stored = 1;
  }
  else if (stored) {
    tcsetattr(0, TCSANOW, &original_mode);
    fcntl(0, F_SETFL, original_flags);
  }
  
}

void ctrl_chandler(int signum)
{
  printf("\n");
  ttymode(1);
  exit(1);
}
