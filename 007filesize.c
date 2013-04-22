#include <stdio.h>
#include <sys/stat.h>

int main()
{
  struct stat stat_ptr;
  if (stat("/etc/passwd",&stat_ptr) == -1)
    perror("Stat");
  else 
    printf("The size of /etc/passwd is %d\n", stat_ptr.st_size);
  return 0;

}
