#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
  pid_t child_id;
  int status;

  child_id=fork();
  
//1a

  if(child_id==0)
  {
       char *argv[]={"mkdir", "Musyik", "Fylm", "Pyoto", NULL};
       execv("/bin/mkdir", argv); 
  }
  
}
