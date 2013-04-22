/************************************************************************************************************
 * Program:  The program implements the shell command 'ls' simply                                           *
 * Author :  June                                                                                           *
 * History:  1st Version 2013/4/13                                                                          *
 ************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

void do_ls(char[]);

int main(int ac, char *av[])
{
  if (ac == 1)
    do_ls(".");
  else
    while(--ac) {
      printf("%s:\n", *++av);
      do_ls(*av);
    }
  return 0;
}

void do_ls(char directname[])
{
  DIR*   dir_ptr;
  struct dirent* dirent_ptr;
  
  if ((dir_ptr = opendir(directname)) == NULL) /* The opendir() funciton is in dirent.h */
    perror("Open Directory:");
  else {
    while ((dirent_ptr = readdir(dir_ptr)) != NULL) /* The readdir() funciton is declared in dirent.h */
      printf("%s  ",dirent_ptr->d_name);
    closedir(dir_ptr);
    printf("\n");
  }
}
