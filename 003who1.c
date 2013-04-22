/***************************************************************************************
 *    Program:    The program implements the command "who" in a simple way             *
 *    Author :    June                                                                 *
 *    History:    1st Version 2013/4/13                                                *
 **************************************************************************************/  
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST

void show_info(struct utmp*);	/* show the record has been read in  format */
int main()
{
  struct utmp current_record;	/* the struct reserve the information from the file UTMP_FILE */
  int         utmpfd;		/* the file description of the UTMPFILE */
  int         reclen = sizeof(current_record); /* the size of a utmp type */

  if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
    perror(UTMP_FILE);		/* UTMP_FILE is in utmp.h */
    exit(EXIT_FAILURE);
  }

  while (read(utmpfd, &current_record, reclen) == reclen)
    show_info(&current_record);
  close(utmpfd);
  return 0;
}

void show_info(struct utmp* utbufp)
{
  printf("%-8.8s", utbufp->ut_name);
  printf(" ");
  printf("%-8.8s", utbufp->ut_line);
  printf(" ");
  printf("%10ld", utbufp->ut_time);
  printf(" ");
#ifdef SHOWHOST
  printf("(%s)", utbufp->ut_host);
#endif
  printf("\n");
}
