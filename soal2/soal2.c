#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <dirent.h>

void execute(char command[], char *argv[]) {
    
	int status;
    	pid_t child;
    
	child=fork();

    	if(child==0){
        	execv(command, argv);
    	}	
	else{
        	while((wait(&status))>0){}
    	}
}

void sliceStr(const char *str, char *buffer, size_t start, size_t end){
    	size_t j = 0;
    	for(size_t i = start; i<=end; ++i) {
        	buffer[j++] = str[i];
    	}
    	buffer[j] = 0;
}

//2a
void extract() {
    	pid_t child;
	int status;

    	child = fork();

    	if (child == 0) {
        	char *argv[] = {"unzip", "/home/ahmad/Downloads/pets.zip",
                        	"-x",    "*/*",
                        	"-d",    "/home/ahmad/modul2/petshop",
                        	NULL};
        	execv("/usr/bin/unzip", argv);
        	exit(EXIT_SUCCESS);
 	}
    	while ((wait(&status)) > 0);
}

void order(){
    int status;
    pid_t child;
    child=fork();

    if (child < 0){
        exit(EXIT_FAILURE); 
    }

    if (child == 0){
        DIR *directory;
        directory=opendir("/home/ahmad/modul2/petshop");
        if(directory != NULL){
            struct dirent *ep;
            while((ep = readdir(directory)) != NULL){
                if(ep->d_type == DT_REG){
                    char *temp1, *temp2, *temp3, *temp4;
                    char copy[99], copy2[99], copy3[99];
                    char base2[99], base3[99];
                    char hewan[25], name[25], umur[25];
                    int flag;
			
                    char *fileName = ep->d_name;
                    int length=strlen(fileName);
                    char newName[length];
                    sliceStr(fileName, newName, 0, length-5); 

                    temp1=strtok_r(newName, "_", &temp4);
                    for(;temp1!=NULL;temp1=strtok_r(NULL, "_", &temp4)){
                        flag= 0;
                        char base[99] = "/home/ahmad/modul2/petshop/";
                        strcpy(copy, ep->d_name);
                        strcpy(base2, base);
                        strcpy(base3, base);
                        strcpy(copy2, ep->d_name);
                        strcpy(copy3, ep->d_name);
                        temp3=strtok_r(temp1, ";", &temp2);
                        for (; temp3!=NULL; temp3=strtok_r(NULL, ";", &temp2)){
                            if (flag == 0) strcpy(hewan, temp3);
                            if (flag == 1) strcpy(name, temp3);
                            if (flag == 2) strcpy(umur, temp3);
                            flag=flag+1;
                        }
                    	
			//2b
                        strcat(base, hewan);
                        char *mkFolder[] = {"make-directory", "-p", base, NULL};
                        execute("/bin/mkdir", mkFolder);
                        
			//2e temporary
                        char txtLoc[99], txtPath[99];
                        strcpy(txtLoc, base);
                        strcpy(txtPath, txtLoc);

                        char namePerAnimal[99], nama[99];
                        strcpy(namePerAnimal, name);
			 
			//2c
                        strcat(base2, copy2);
                        char *copytoFolder[] = {"cp", "-r", base2, base, NULL};
                        execute("/bin/cp", copytoFolder);

                        strcat(name, ".jpg");
                        strcpy(base3, base);
                        strcat(base3, "/");
                        strcat(base3, copy2);
                        strcat(base, "/");
                        strcat(base, name);
                        char *renameFile[] = {"mv", base3, base, NULL};
                        execute("/bin/mv", renameFile);

			//2e
                        strcat(txtPath, "/keterangan.txt");
                        strcpy(nama, "nama : ");
                        strcat(nama, namePerAnimal);
                        strcat(nama, "\n");
                        strcat(nama,"umur : ");
                        strcat(nama, umur);
                        strcat(nama," tahun\n\n");
 
                        FILE *fPtr = fopen(txtPath, "a");
                        fputs(nama, fPtr);
                        fclose(fPtr);

                }
            }
		//Menghapus file yang telah dipindahkan
                if (ep->d_type == DT_REG){
                    char path[99] = "/home/ahmad/modul2/petshop/";
                    strcat(path, ep->d_name);
                    // printf("%s\n", path);
                    char *removeFile[] = {"remove file","-r", "-f", path, NULL};
                    execute("/bin/rm", removeFile);
                }
            }

        }
        closedir(directory);
    }
    
    else{
        while((wait(&status))>0){
        }
    }
}

int main() {
	pid_t child;
	int stat;
	
	child = fork();
	
	if(child < 0) {
		exit(EXIT_FAILURE);
	}
	
	if(child == 0) {
		char *argv[] = {"mkdir", "-p", "/home/ahmad/modul2/petshop", NULL};
        	execv("/bin/mkdir", argv);
	}
	else {
		while((wait(&stat)) > 0);
		extract();
		order();
	}
}
