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
	pid_t child;
	int stat;

	child = fork();
	if(child == 0) {
		execv(command, argv);
	}
	else {
		while((wait(&stat)) > 0);
	}
}

char* cutName (char* s){
    	int n, i;
    	char* new;
	for (i = 0; s[i] != '\0'; i++);
    	n = i - 4 + 1;
    	if (n < 1)
        	return NULL;
    	new = (char*) malloc (n * sizeof(char));
    	for (i = 0; i < n - 1; i++)
        	new[i] = s[i];
    	new[i] = '\0';
   	return new;
}

void order() {
	pid_t child;
	int stat;

    	child = fork();
   	if(child < 0)
    	{
       		exit(EXIT_FAILURE);
    	}

    	if (child == 0)
    	{
    		DIR *dr;
    		char directory[100] = "home/ahmad/modul2/petshop";
    		dr = opendir(directory);
        	if (dr != NULL)
        	{
            		struct dirent *folder;
            		while((folder = readdir(dr))!= NULL)
            		{   
                		if(folder->d_type == DT_REG)
                		{
                    			char *flag1,*flag2,*flag3,*flag4;
                    			char *fileName=folder->d_name;
                    			char *newName=cutName(fileName);
                    
                    			char copy1[100], copy2[100], copy3[100];
                    			char base2[100], base3[100];
                    
                    			for(flag1=strtok_r(newName,"_",&flag3); flag1!=NULL; flag1=strtok_r(NULL,"_",&flag3))
                    			{
                        			char hewan[100], nama[100], umur[100];
                        			int i=0;
                        			char base[100]="home/ahmad/modul2/petshop";
                        
                        			strcpy(copy1, folder->d_name);
                        			strcpy(base2, base);
                        			strcpy(base3, base);
                        			strcpy(copy2, folder->d_name);
                        			strcpy(copy3, folder->d_name);

                        			for(flag2=strtok_r(flag1,";",&flag4); flag2!=NULL; flag2=strtok_r(NULL,";",&flag4))
                            			{
                                			if(i==0) strcpy(hewan,flag2);
                                			if(i==1) strcpy(nama,flag2);
                                			if(i==2) strcpy(umur,flag2);
                                			i=i+1;
                            			}
                        

                        			//2b
                        			strcat(base,hewan);
                        			char *argv1[]={"mkdir","-p",base,NULL};
                        			execute("/bin/mkdir",argv1);
                        
                        			//2e flag
                        			char txtloc[100],txtpath[100];
                        			strcpy(txtloc,base);
                        			strcpy(txtpath,txtloc);

                        			char namaditxt[100], isi[100];
                        			strcpy(namaditxt,nama);

                       				//2c
                        			strcat(nama,".jpg");
                        			strcat(base2,copy2);
                        
                        			char *argv2[]={"copy","-r", base2, base, NULL};
                        			execute("/bin/copy",argv2);

                        			strcpy(base3,base);
                        			strcat(base3,"/");
                        			strcat(base3,copy2);
                        			strcat(base,"/");
                        			strcat(base,nama);
                        			char *argv3[]={"move",base3,base,NULL};
                        			execute("/bin/move",argv3);
                        
                        			//2e
                        			strcat(txtpath,"/keterangan.txt");
                        			strcpy(isi,"nama : ");
                        			strcat(isi,namaditxt);
                        			strcat(isi,"\n");
                        			strcat(isi,"umur : ");
                        			strcat(isi,umur);
                        			strcat(isi,"tahun\n\n");
                        			FILE *fptr=fopen(txtpath,"a");
                        			fputs(isi,fptr);
                        			fclose(fptr);
                    			}
                		}
                		if(folder->d_type == DT_REG)
                		{
                    			char base[99]="/home/ahmad/modul2/petshop/";
                    			strcat(base,folder->d_name);

                    			char *argv4[]={"remove","-rf",base,NULL};
                    			execute("/bin/remove",argv4);
                		}
            		}
        	}
    		(void) closedir(dr);
    	}
	else 
	{
		while ((wait(&stat))>0);
    	}
}

//2a
void extract() {

	pid_t child;
	int stat;
	
	child = fork();

	if(child < 0) {
		exit(EXIT_FAILURE);
	}	

	if(child == 0) {
		char *argv[] = {"mkdir","-p","home/ahmad/modul2/petshop",NULL};
		execute("/bin/mkdir", argv);
		
		char *argv2[] = {"unzip", "-q", "-d", "home/ahmad/modul2/petshop", "/home/ahmad/Downloads/pets.zip", NULL};

		DIR *directory;
		directory = opendir("home/ahmad/modul2/petshop");
		if(directory!=NULL) {
			struct dirent *folder;
			while((folder = readdir(directory)) != NULL) {
				if(strcmp(folder->d_name, ".") != 0 && strcmp(folder->d_name, "..") !=0) {
					if(folder->d_type == DT_DIR) {
						char awal[100] = "home/ahmad/modul2/petshop";
						strcat(awal, folder->d_name);
                        			char *listPets[] = {"rm", "-r", "-f", awal, NULL};
                       				execute("/bin/rm", listPets);
					}
				}			
			}
		}
		
		closedir(directory);	
	}
	
	else {
		while((wait(&stat)) > 0);
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
		extract();
		order();
	}
	else {
		while((wait(&stat)) > 0);
	}

	return 0;
}
