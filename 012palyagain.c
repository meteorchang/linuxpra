/****************************************************************************
 * Program: The program is written to test the terminal response in time    *
 * Author : June                                                            *
 * History: 2st Version 2013/4/16                                           *
 ****************************************************************************/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define QUESTION "Do you want another transaction?"

int get_response(char *);
void set_cbc_noecho_mode();
void tty_mode(int);

int main()
{
  int response;
  tty_mode(0);                  /* save the default tty mode */
  set_cbcmode();
  response = get_response(QUESTION);
  printf("\n");
  tty_mode(1);                  /* reset tty mode default */
  return response;
}

int get_response(char *question)
{
  int put;
  printf("%s(y/n)?", question);
  while (1) {
    switch(put = getchar()) {
    case 'y':
    case 'Y':
      return 0;
    case 'n':
    case 'N':
    case EOF:
      return 1;
    default:
      printf("\nCannot uderstand %c, ", put);
      printf("Please type y or no \n ");
    }
  }
}

void set_cbc_noecho_mode()              /* set the mode character-by-character */
{
  struct termios ttystate;
  tcgetattr(0, &ttystate);       /* get the current input setting*/
  ttystate.c_lflag &= ~ICANON;   /* no buffer  */
  ttystate.c_lflag &= ~ECHO      /* no echo */
  ttystate.c_cc[VMIN] = 1;      /* read one character once */
  tcsetattr(0, TCSANOW, &ttystate); /* settting */
}

void tty_mode(int how)          /* back and restore the mode  */
{
  static struct termios orginal_mode;
  if (how == 0)
    tcgetattr(0,&orginal_mode); 
  else
    tcsetattr(0, TCSANOW, &orginal_mode);
}
