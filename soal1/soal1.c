#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

int main()
{
    pid_t child_id, child_idx, child_id2, child_id3;
    pid_t child_id4, child_id5, child_id6, child_id7;
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
        
        
        //1c dan 1d
        else
        {
            sleep(20);
            child_id4 = fork();
            if(child_id4==0)
            {
                child_id5 = fork();
                if(child_id5==0)
                {
                    char *unzipmusik[]={"unzip", "-j", "Musik_for_Stevany.zip", "-d", "./Musyik", NULL};
                    execv("/bin/unzip", unzipmusik);
                }
                else
                {
                    while ((wait(&status)) > 0);
                    child_id6 = fork();          
                    if (child_id6 == 0)
                    {
                        char *unzipfoto[]={"unzip", "-j", "Foto_for_Stevany.zip", "-d", "./Pyoto", NULL};
                        execv("/bin/unzip", unzipfoto);
                    }
                    else
                    {
                        while ((wait(&status)) > 0);
                        char *unzipfilm[]={"unzip", "-j", "Film_for_Stevany.zip", "-d", "./Fylm", NULL};
                        execv("/bin/unzip", unzipfilm);
                    }
                }
            }
        }
    }
}
