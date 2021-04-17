#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>

int main() {
  	pid_t child, child;
  	int status, status2;

  	child = fork();

  	if (child < 0) {
   		exit(EXIT_FAILURE);
  	}

  	if(child == 0) {
   		char *argv[] = {"mkdir", "-p", "/home/ahmad/modul2/petshop", NULL};
   		execv("/bin/mkdir", argv);
  	}
   	else {
   		while((wait(&status)) > 0);
		child = fork();
		if(child == 0) {
   			char *argv[] = {"unzip","/home/ahmad/Downloads/pets.zip", "-d", "/home/ahmad/modul2/petshop", NULL };
   			execv("/usr/bin/unzip",argv);
		}
		else {
			while((wait(&status2)) > 0);
			
		}
  	}
}
