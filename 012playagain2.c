/****************************************************************************
 * Program: The program is written to test the terminal response in time    *
 * Author : June                                                            *
 * History: 2st Version 2013/4/16                                           *
 ****************************************************************************/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define QUESTION "Do you want another transaction?"
#define TRIES 3
#define SLEEPTIME 2
#define BEEP putchar('\a')

int get_response(char *, int);
void set_cbc_noecho_mode();
void set_nodelay_mode();
void tty_mode(int);
int  get_ok_char();

int main()
{
  int response;
  tty_mode(0);                  /* save the default tty mode */
  set_cbc_noecho_mode();
  set_nodelay_mode();
  response = get_response(QUESTION, TRIES);
  printf("\n");
  tty_mode(1);                  /* reset tty mode default */
  return response;
}

int get_response(char *question, int maxtries)
{
  int put;
  printf("%s(y/n)?", question);
  fflush(stdout);
  while (1) {
    sleep(SLEEPTIME);
    put = tolower(get_ok_char());
    if (put == 'y')
      return 0;
    if (put == 'n')
      return 1;
    if (maxtries-- == 0)
      return 2;
    BEEP;
  }
}

int get_ok_char()               /*note :is not safe  */
{
  int c;
  while ((c = getchar()) != EOF && strchr("yYnN",c) == NULL)
    ;
  return c;
}

void set_cbc_noecho_mode()              /* set the mode character-by-character */
{
  struct termios ttystate;
  tcgetattr(0, &ttystate);       /* get the current input setting*/
  ttystate.c_lflag &= ~ICANON;   /* no buffer  */
  ttystate.c_lflag &= ~ECHO;      /* no echo */
  ttystate.c_cc[VMIN] = 1;      /* read one character once */
  tcsetattr(0, TCSANOW, &ttystate); /* settting */
}

void set_nodelay_mode()
{
  int termflags;
  termflags = fcntl(0, F_GETFL);
  termflags |= O_NDELAY;
  fcntl(0, F_SETFL, termflags);
}

void tty_mode(int how)          /* back and restore the mode  */
{
  static struct termios original_mode;
  static int original_flags;
  if (how == 0) {
    tcgetattr(0, &original_mode);
    original_flags = fcntl(0,F_GETFL);
  }
  else {
    tcsetattr(0, TCSANOW, &original_mode);
    fcntl(0, F_SETFL, original_flags);
  }
}


