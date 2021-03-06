#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
 
int main()
{
    pid_t pid, sid; // Variabel untuk menyimpan PID   
    pid_t child_id, child_idx, child_id2, child_id3;
    pid_t child_id4, child_id5, child_id6, child_pid;
 
    int status;
    pid = fork();// Menyimpan PID dari Child Process
 
    //1a
    /* Keluar saat fork gagal (nilai variabel pid < 0) */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
 
    /* Keluar saat fork berhasil (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
 
    umask(0);
 
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }
 
    /*if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }*/
 
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
 
    int executed = 0;
    while (1)
    {
    time_t rawtime = time(NULL);
    struct tm info = *localtime(&rawtime);
    if(info.tm_mday == 9 & info.tm_mon + 1 == 4 && 22 - info.tm_hour == 6 && 
        info.tm_min == 22 && executed == 0)
    {
        executed = 1;
        //1a
        child_id = fork(); 
        if (child_id == 0)
        {
            char *argv[] = {"mkdir","Fylm","Musyik","Pyoto",NULL};
            execv("/bin/mkdir", argv); 
        }
        while(wait(NULL) > 0);
        //1b
        child_id2 = fork();
        if (child_id2 == 0)
        {
            char *dwnldmusik[] = { "wget", "-q","--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O","Musik_for_Stevany.zip",NULL};
            execv("/bin/wget", dwnldmusik);
        }
 
        while ((wait(NULL)) > 0);
        child_id3 = fork();          
        if (child_id3 == 0)
        {
            char *dwnldfoto[]=  { "wget", "-q","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O","Foto_for_Stevany.zip",NULL};
            execv("/bin/wget", dwnldfoto);   
        }
 
        while ((wait(NULL)) > 0);
        child_idx = fork();
        if (child_idx == 0)  
        {
            char *dwnldfilm[]=  { "wget", "-q","--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O","Film_for_Stevany.zip",NULL};
            execv("/bin/wget", dwnldfilm);
        }
             
        
        
        while(wait(NULL) > 0);
        child_id5 = fork();
        if(child_id5==0)
        {
            char *unzipmusik[]={"unzip", "-j", "Musik_for_Stevany.zip", "-d", "./Musyik", NULL};
            execv("/bin/unzip", unzipmusik);
        }
 
        while ((wait(NULL)) > 0);
        child_id6 = fork();          
        if (child_id6 == 0)
        {
            char *unzipfoto[]={"unzip", "-j", "Foto_for_Stevany.zip", "-d", "./Pyoto", NULL};
            execv("/bin/unzip", unzipfoto);
        }
        child_id4 = fork();
        if(child_id4==0)
        {
            while ((wait(&status)) > 0);
            char *unzipfilm[]={"unzip", "-j", "Film_for_Stevany.zip", "-d", "./Fylm", NULL};
            execv("/bin/unzip", unzipfilm);
        }
        
    
    }
    if(info.tm_mday == 9 & info.tm_mon + 1 == 4 && 22 - info.tm_hour == 0 && 
        info.tm_min == 22 && executed == 1)
    {
        child_pid = fork();
        if (child_pid == 0)
        {
            char *ZIP[]= {"zip","-r","Lopyu_Stevany.zip","Fylm","Musyik","Pyoto",NULL};
            execv("/bin/zip", ZIP);
        }
        while ((wait(NULL)) > 0);
        child_pid = fork();
        if (child_pid == 0)
        {
            char *delete[]={"rm", "-r", "Fylm", "Musyik", "Pyoto", NULL};
            execv("/bin/rm", delete);
        }
    }
    sleep(20);
    }
}
