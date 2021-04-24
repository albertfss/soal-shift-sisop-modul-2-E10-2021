#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t child_id, child_idx, child_id2, child_id3;
    int status;
    
    //1a
    child_id = fork();
    if (child_id == 0)
    {
        char *argv[] = {"mkdir","Fylm","Musyik","Pyoto",NULL};
        execv("/bin/mkdir", argv); 
    }
    else
    {
        //1b
        child_idx = fork();
        if (child_idx == 0) 
        {
            child_id2 = fork();
            if (child_id2 == 0)
            {
                char *dwnldmusik[] = { "wget", "-q","--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O","Musik_for_Stevany.zip",NULL};
                execv("/bin/wget", dwnldmusik);
            }
            else 
            {
                while ((wait(&status)) > 0);
                child_id3 = fork();          
                if (child_id3 == 0)
                {
                    char *dwnldfoto[]=  { "wget", "-q","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O","Foto_for_Stevany.zip",NULL};
                    execv("/bin/wget", dwnldfoto);   
                }
                else 
                {
                    while ((wait(&status)) > 0);
                    char *dwnldfilm[]=  { "wget", "-q","--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O","Film_for_Stevany.zip",NULL};
                    execv("/bin/wget", dwnldfilm);
                }
            } 
        }
    }
}
