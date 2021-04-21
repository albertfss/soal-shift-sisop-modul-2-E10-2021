#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <signal.h>
#include <wait.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createKiller(int);

int main(int argc, char** argv) {
    if(argc != 2 || (strcmp(argv[1], "-z") != 0 && strcmp(argv[1], "-x") != 0)) {
        printf("Invalid Mode!\n");
        return 1;
    }

    pid_t pid, sid;        // Variabel untuk menyimpan PID

    pid = fork();     // Menyimpan PID dari Child Process
    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    int flag;
    if (strcmp(argv[1], "-z") == 0) {
        flag = 1;
    }
    if (strcmp(argv[1], "-x") == 0) {
        flag = 2;
    }
    createKiller(flag);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1) {
        time_t rawtime;
        struct tm *info;
        char buffer[80];
        time(&rawtime);
        info = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d_%X", info);

        pid_t child_id;
        child_id = fork();

        if(child_id == 0) {
            char* arg[] = {"mkdir", "-p", buffer, NULL};
            execv("/bin/mkdir", arg);
        }

        child_id = fork();
        if(child_id == 0) {
            for(int i=0; i<10; i++) {
                child_id = fork();
                if(child_id == 0) {
                    rawtime = time(NULL);
                    info = localtime(&rawtime);
                    char buff[80], path[80], link[80];

                    // folder name
                    strftime(buff, sizeof(buff), "%Y-%m-%d_%X", info);

                    // path
                    strcpy(path, buffer);
                    strcat(path, "/");
                    strcat(path, buff);

                    sprintf(link, "https://picsum.photos/%ld", ((rawtime % 1000) + 50));

                    char* arg[] = {"wget", "-q", "-O", path, link, NULL};
                    execv("/bin/wget", arg);

                }
                sleep(5);
            }
            while(wait(NULL) > 0);

            child_id = fork();
            if(child_id == 0) {
                char str[80] = "Download Success";
                char file_name[80];
                for(int j=0; j < strlen(str); j++) {
                    if(str[j] == ' ') continue;
                    str[j] += 5;
                    if( (str[j] > 'Z' && str[j] < 'a') || str[j] > 'z') {
                        str[j] -= 26;
                    }
                }
                strcpy(file_name, buffer);
                strcat(file_name, "/");
                strcat(file_name, "status.txt");

                FILE *txt = fopen(file_name, "w");
                fputs(str, txt);
                fclose(txt);

                strcpy(file_name, buffer);
                strcat(file_name, ".zip");
                char *argx[] = {"zip", file_name, "-r", buffer, NULL};
                execv("/bin/zip", argx);
            }
            while(wait(NULL) != child_id);

            char *rm[] = {"rm", "-r", buffer, NULL};
            execv("/bin/rm", rm);
        }
        sleep(40);
    }
}

void createKiller(int flag) {
    FILE *src = fopen("killer.sh", "w");
 
    if (flag == 1) {
        char *code = ""
        "#!/bin/bash\n"
        "killall -9 ./soal3\n"
        "rm $0\n";
        fprintf(src, code, NULL);
    }
 
    if (flag == 2) {
        char *code = ""
        "#!/bin/bash\n"
        "kill %d\n"
        "rm $0\n";
        fprintf(src, code, getpid());
    }
    fclose(src);
}
