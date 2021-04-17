#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main()
{
  pid_t child_id, child_id2, child_id3;
  int status;

  child_id=fork();

//1a

if(child_id==0)
  {
       char *argv[]={"mkdir", "Musyik", "Fylm", "Pyoto", NULL};
       execv("/bin/mkdir", argv);
  }

//1b

else
{
    while((wait(&status))>0);
    child_id2=fork();
    if(child_id2==0)
    {
        char *dwnldmusik[]={"wget --no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stevany.zip"};
        execv("/bin/wget", dwnldmusik);
    }
    else
    {
        while((wait(&status))>0);
        child_id3=fork();
        if(child_id3==0)
        {
            char *dwnldfoto[]={"wget --no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto_for_Stevany.zip"};
            execv("/bin/wget", dwnldfoto);
        }
        else
        {
            while((wait(&status))>0);
            char *dwnldfilm[]={"wget --no-check-certificate", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film_for_Stevany.zip"};
            execv("/bin/wget", dwnldfilm);
        }
    }
}

}
