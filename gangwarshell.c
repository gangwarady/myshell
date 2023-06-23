#define _GNU_SOURCE        char *strcasestr(const char *haystack, const char *needle);
#include "csapp.h"
#include<pthread.h>
#include <string.h>
#include "conio.h"
#include<readline/readline.h>
#include<readline/history.h>
#include <pwd.h>
#include <grp.h>


char *strrev(char *s)
{
      char *ptr1, *ptr2;

      if (! s || ! *s)
      {
            return s;
       }
       ptr1 = s;
       ptr2 = s + strlen(s) - 1;
      while ( ptr2 > ptr1 )
      {
            *ptr1 ^= *ptr2;
            *ptr2 ^= *ptr1;
            *ptr1 ^= *ptr2;
            ptr1++; 
            ptr2--;
            
      }
      return s;
}




char directory[300];


void total(){
	long int t=0;
	DIR *mydir;
	struct dirent *mydirst;
    	mydir = opendir(directory);
    	if(mydir == NULL)
    	{
        	puts("Unable to read directory");
        		
    	}
    	else
    	{
        	while ((mydirst = readdir(mydir)) != NULL){
        		if ( !strcmp(mydirst->d_name, ".") || !strcmp(mydirst->d_name, "..") ){
			} 
			else {
				struct stat gstat;
     				stat(mydirst->d_name,&gstat);
     				t=t+gstat.st_blocks;
			}
        			 	
        				
        	}
    	}
    	closedir(mydir);
    	printf("total = %ld\n",t/2);
}

void detail(char *s){
	struct stat gstat;
	stat(s, &gstat);
	if (S_ISDIR(gstat.st_mode)){
 		printf("d");
 	}
 	else{
 		printf("-");
 	}
 	if ((gstat.st_mode & S_IRUSR)){
 		printf("r");
 	}
 	else{
 		printf("-");
 	}
 	if ((gstat.st_mode & S_IWUSR)){
 		printf("w");
 	}
 	else{
 		printf("-");
 	}
 	if ((gstat.st_mode & S_IXUSR)){
 		printf("x");
 	}
 	else{
 		printf("-");
 	}
 	if ((gstat.st_mode & S_IRGRP)){
 		printf("r");
 	}
 	else{
 		printf("-");
 	}
 	if ((gstat.st_mode & S_IWGRP)){
 		printf("w");
 	}
 	else{
 		printf("-");
 	}
 	if ((gstat.st_mode & S_IXGRP)){
 		printf("x");
 	}
 	else{
 		printf("-");
 	}
 	if ((gstat.st_mode & S_IROTH)){
 		printf("r");
 	}
 	else{
 		printf("-");
 	}
 	if ((gstat.st_mode & S_IWOTH)){
 		printf("w");
 	}
 	else{
 		printf("-");
 	}
 	if ((gstat.st_mode & S_IXOTH)){
 		printf("x");
 	}
 	else{
 		printf("-");
 	}
 	printf(" %li ", gstat.st_nlink);
 	/*struct passwd *un;
 	struct group *gn;
 	un=getpwuid(gstat.st_uid);
 	printf("%s ",un->pw_name);
 	gn=getgrgid(gstat.st_gid);
 	printf("%s ",gn->gr_name);*/
 	printf("gangwarady ");
 	printf("gangwarady ");
 	printf("%ld ",gstat.st_size);
 	struct tm *time;
 	char temp[200];
 	time_t time2=gstat.st_mtime;
 	time=localtime(&time2);
 	strftime(temp, sizeof(temp), "%b %d %R", time);
	printf("%s ", temp);
 	printf("\t%s",s);
 	printf("\n");
 	

    	
}


void myps(){
	DIR *myps;
	myps = opendir("/proc");
	int file1, file2;
	file1= open("/proc/self/fd/0", O_RDONLY);
	char pathname[300];
	char track[300];
	char *pn;
	sprintf(pathname, "%s", ttyname(file1));
	struct dirent *pst;
	FILE *file3;
	int count=0;
	printf("PID\t TTY\t TIME\t \tCMD\n");
	while((pst = readdir(myps)) != NULL){
		
		for (int i = 0; pst->d_name[i]; i++)
			if (isdigit(pst->d_name[i])){
			
				sprintf(track, "/proc/%s/fd/0", pst->d_name);
  				file2 = open(track, O_RDONLY);
  				pn= ttyname(file2);
  				if(pn && strcmp(pn,pathname)==0){
  		
  					sprintf(track, "/proc/%s/stat", pst->d_name);
  					file3=fopen(track,"r");
  					
  					char cf[300];
  					fscanf(file3, "%d%s", &i, cf);
  					int len =strlen(cf);
  					cf[len-1]='\0';
  					
  					unsigned long time, start_time,total;
  					fscanf(file3, "%lu", &time);
  					fscanf(file3, "%lu", &start_time);
  					total = (int)((double)(time + start_time) / sysconf(_SC_CLK_TCK));
  					char mytime[300];
  					sprintf(mytime, "%2lu:%2lu:%2lu",(total/ 3600) % 3600, (total / 60) % 60, total % 60);
  					printf("%s\t %s\t %s\t %s\n", pst->d_name, pn + 5, mytime, cf +1);
  					fclose(file3);
  				}
  				close(file2);
			}
			else{
				break;
			}
			
			
		
	}
	close(file1);
	
	
}


void myls (char *s){
	
	if(strstr(s,"m")){
		DIR *mydir;
		struct dirent *mydirst;
    		mydir = opendir(directory);
    		if(mydir == NULL)
    		{
        		puts("Unable to read directory");
        		
    		}
    		else
    		{
        		while ((mydirst = readdir(mydir)) != NULL){
        			 if ( !strcmp(mydirst->d_name, ".") || !strcmp(mydirst->d_name, "..") ){
				} 
				else {
     					printf("%s, ", mydirst->d_name);
				}
        			 	
        				
        		}
    		}
    		closedir(mydir);
	}
	else if(strstr(s,"1")){
		DIR *mydir;
		struct dirent *mydirst;
    		mydir = opendir(directory);
    		if(mydir == NULL)
    		{
        		puts("Unable to read directory");
        		
    		}
    		else
    		{
        		while ((mydirst = readdir(mydir)) != NULL){
        			 if ( !strcmp(mydirst->d_name, ".") || !strcmp(mydirst->d_name, "..") ){
				} 
				else {
     					printf("%s\n", mydirst->d_name);
				}
        			 	
        				
        		}
    		}
    		closedir(mydir);
		
	}
	else if(strstr(s,"r")){
		const char *arr[50];
		int i=0;
		total();
		DIR *mydir;
		struct dirent *mydirst;
    		mydir = opendir(directory);
    		if(mydir == NULL)
    		{
        		puts("Unable to read directory");
        		
    		}
    		else
    		{
        		while ((mydirst = readdir(mydir)) != NULL){
        			 if ( !strcmp(mydirst->d_name, ".") || !strcmp(mydirst->d_name, "..") ){
				} 
				else {
     					arr[i]=mydirst->d_name;
     					i++;
				}
        			 	
        				
        		}
    		}
    		closedir(mydir);
    		i--;
    		while(i>=0){
    			char file_n[30];
    			strcpy(file_n,arr[i]);
    			detail(file_n);
    			i--;
    		}
	}
	else if(strstr(s,"l")){
		total();
		DIR *mydir;
		struct dirent *mydirst;
    		mydir = opendir(directory);
    		if(mydir == NULL)
    		{
        		puts("Unable to read directory");
        		
    		}
    		else
    		{
        		while ((mydirst = readdir(mydir)) != NULL){
        			 if ( !strcmp(mydirst->d_name, ".") || !strcmp(mydirst->d_name, "..") ){
				} 
				else {
     					detail(mydirst->d_name);
				}
        			 	
        				
        		}
    		}
    		closedir(mydir);
	}
	else{
		printf("%s command not found",s);
		
	}
}

void mycp (char *s)
{
	int n_words=0;
	int i=0;
	while(s[i]){
		if(s[i]== ' ' && s[i+1]!=' '){
			n_words++;
		}
		i++;
	}
	n_words++;
	if(n_words==3){
		char *file1;
		char *file2;
		file1=strtok(s," ");
		file1=strtok(NULL," ");
		file2=strtok(NULL," ");
		int size;
		rio_t myrio;
		char data[MAXLINE];
		int f1=open(file1, O_RDONLY);
		int f2=open(file2, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		Rio_readinitb(&myrio, f1);
		while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
			Rio_writen(f2, data, size);
		}
		close(f1);
		close(f2);
	}
	else if(n_words<3){
		printf("INVALID COMMAND: NOT ENOUGH ARGUMENTS");
	}
	else{
		s=strtok(s," ");
		s=strtok(NULL,"");
		strrev(s);
		
		char * file1;
		file1=strtok(s," ");
		s=strtok(NULL,"");
		strrev(file1);
		char * file2;
		file2=strtok(s," ");
		s=strtok(NULL,"");
		strrev(file2);
		strrev(s);
		if(strstr(file1,"-version")){
			printf("cp (GNU coreutils) 8.30\nCopyright (C) 2018 Free Software Foundation, Inc.\nLicense GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\nThis is 					free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n\nWritten by Aditya Singh Gangwar.");
		}
		else if(strstr(s,"n")){
			FILE *myfile;
			if ((myfile = fopen(file1, "r")))
    			{
    			}
    			else{
    				int size;
				rio_t myrio;
				char data[MAXLINE];
				int f1=open(file2, O_RDONLY);
				int f2=open(file1, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
				Rio_readinitb(&myrio, f1);
				while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
					Rio_writen(f2, data, size);
				}	
				close(f1);
				close(f2);
    			}
		}
		else if(strstr(s,"i")){
			char y[10];
			FILE *myfile;
			int new=0;
    			if ((myfile = fopen(file1, "r")))
    			{
        			printf("mv: overwrite '%s'? ",file1);
        			scanf("%s",y);
        			if(strstr(s,"b")){
        				new=1;
        			}
    			}
    			else{
    				strcpy(y,"y");
    			}
    			if(strcmp(y,"y")==0){
    				if(new==1){
    					char file3[30];
    					strcpy(file3,file1);
    					strcat(file3,"~");
    					int size;
					rio_t myrio;
					char data[MAXLINE];
					int f1=open(file1, O_RDONLY);
					int f2=open(file3, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
					Rio_readinitb(&myrio, f1);
					while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
						Rio_writen(f2, data, size);
					}	
					close(f1);
					close(f2);
    				}
    				int size;
				rio_t myrio;
				char data[MAXLINE];
				int f1=open(file2, O_RDONLY);
				int f2=open(file1, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
				Rio_readinitb(&myrio, f1);
				while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
					Rio_writen(f2, data, size);
				}	
				close(f1);
				close(f2);
    			}
		}
		else if(strstr(s,"b")){
			FILE *myfile;
			int new=0;
    			if ((myfile = fopen(file1, "r")))
    			{
        			if(strstr(s,"b")){
        				new=1;
        			}
    			}
    			if(new==1){
    				char file3[30];
    				strcpy(file3,file1);
    				strcat(file3,"~");
    				int size;
				rio_t myrio;
				char data[MAXLINE];
				int f1=open(file1, O_RDONLY);
				int f2=open(file3, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
				Rio_readinitb(&myrio, f1);
				while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
					Rio_writen(f2, data, size);
				}	
				close(f1);
				close(f2);
    			}
    			int size;
			rio_t myrio;
			char data[MAXLINE];
			int f1=open(file2, O_RDONLY);
			int f2=open(file1, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			Rio_readinitb(&myrio, f1);
			while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
				Rio_writen(f2, data, size);
			}	
			close(f1);
			close(f2);
		}
		else{
			printf("INVALID COMMAND\n");
			printf("TRY AGAIN");
		}
		
	}
}

void mymv(char *s){
	
	int n_words=0;
	int i=0;
	while(s[i]){
		if(s[i]== ' ' && s[i+1]!=' '){
			n_words++;
		}
		i++;
	}
	n_words++;
	if(n_words==3){
		char *file1;
		char *file2;
		file1=strtok(s," ");
		file1=strtok(NULL," ");
		file2=strtok(NULL," ");
		int size;
		rio_t myrio;
		char data[MAXLINE];
		int f1=open(file1, O_RDONLY);
		int f2=open(file2, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		Rio_readinitb(&myrio, f1);
		while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
			Rio_writen(f2, data, size);
		}
		close(f1);
		close(f2);
		remove(file1);
	}
	else if(n_words<3){
		printf("INVALID COMMAND: NOT ENOUGH ARGUMENTS");
	}
	else{
		s=strtok(s," ");
		s=strtok(NULL,"");
		strrev(s);
		
		char * file1;
		file1=strtok(s," ");
		s=strtok(NULL,"");
		strrev(file1);
		char * file2;
		file2=strtok(s," ");
		s=strtok(NULL,"");
		strrev(file2);
		strrev(s);
		if(strstr(file1,"-version")){
			printf("mv (GNU coreutils) 8.30\nCopyright (C) 2018 Free Software Foundation, Inc.\nLicense GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\nThis is 					free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n\nWritten by Aditya Singh Gangwar");
		}
		else if(strstr(s,"n")){
			FILE *myfile;
			if ((myfile = fopen(file1, "r")))
    			{
    			}
    			else{
    				int size;
				rio_t myrio;
				char data[MAXLINE];
				int f1=open(file2, O_RDONLY);
				int f2=open(file1, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
				Rio_readinitb(&myrio, f1);
				while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
					Rio_writen(f2, data, size);
				}	
				close(f1);
				close(f2);
				remove(file2);
    			}
		}
		else if(strstr(s,"i")){
			char y[10];
			FILE *myfile;
			int new=0;
    			if ((myfile = fopen(file1, "r")))
    			{
        			printf("mv: overwrite '%s'? ",file1);
        			scanf("%s",y);
        			if(strstr(s,"b")){
        				new=1;
        			}
    			}
    			else{
    				strcpy(y,"y");
    			}
    			if(strcmp(y,"y")==0){
    				if(new==1){
    					char file3[30];
    					strcpy(file3,file1);
    					strcat(file3,"~");
    					int size;
					rio_t myrio;
					char data[MAXLINE];
					int f1=open(file1, O_RDONLY);
					int f2=open(file3, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
					Rio_readinitb(&myrio, f1);
					while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
						Rio_writen(f2, data, size);
					}	
					close(f1);
					close(f2);
    				}
    				int size;
				rio_t myrio;
				char data[MAXLINE];
				int f1=open(file2, O_RDONLY);
				int f2=open(file1, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
				Rio_readinitb(&myrio, f1);
				while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
					Rio_writen(f2, data, size);
				}	
				close(f1);
				close(f2);
				remove(file2);
    			}
		}
		else if(strstr(s,"b")){
			FILE *myfile;
			int new=0;
    			if ((myfile = fopen(file1, "r")))
    			{
        			if(strstr(s,"b")){
        				new=1;
        			}
    			}
    			if(new==1){
    				char file3[30];
    				strcpy(file3,file1);
    				strcat(file3,"~");
    				int size;
				rio_t myrio;
				char data[MAXLINE];
				int f1=open(file1, O_RDONLY);
				int f2=open(file3, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
				Rio_readinitb(&myrio, f1);
				while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
					Rio_writen(f2, data, size);
				}	
				close(f1);
				close(f2);
    			}
    			int size;
			rio_t myrio;
			char data[MAXLINE];
			int f1=open(file2, O_RDONLY);
			int f2=open(file1, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			Rio_readinitb(&myrio, f1);
			while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
				Rio_writen(f2, data, size);
			}	
			close(f1);
			close(f2);
			remove(file2);
		}
		else{
			printf("INVALID COMMAND\n");
			printf("TRY AGAIN");
		}
		
	}
}

void mygrep(char *s){
	int n_words=0;
	int i=0;
	while(s[i]){
		if(s[i]== ' ' && s[i+1]!=' '){
			n_words++;
		}
		i++;
	}
	n_words++;
	if(n_words==3){
		char *file1;
		s=strtok(s," ");
		s=strtok(NULL, " ");
		file1=strtok(NULL," ");
		int size;
		rio_t myrio;
		char data[MAXLINE];
		int f1=open(file1, O_RDONLY);
		Rio_readinitb(&myrio, f1);
		while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
			if(strstr(data,s)){
				printf("%s", data);
			}
		}
		close(f1);
	}
	else{
		s=strtok(s," ");
		s=strtok(NULL,"");
		strrev(s);
		
		char * file1;
		file1=strtok(s," ");
		s=strtok(NULL,"");
		strrev(file1);
		char * patt;
		patt=strtok(s," ");
		s=strtok(NULL,"");
		strrev(patt);
		strrev(s);
		if(strstr(s,"v")){
			int size;
			int count=0;
			rio_t myrio;
			char data[MAXLINE];
			int f1=open(file1, O_RDONLY);
			Rio_readinitb(&myrio, f1);
			while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
				if(strstr(s,"i")){
					if(!strcasestr(data,patt)){
						if(!strstr(s,"c")){
						printf("%s",data);
						}
						count++;
					}
				}
				else{
					if(!strstr(data,patt)){
						if(!strstr(s,"c")){
						printf("%s",data);
						}
						count++;
					}
				}
			}
			close(f1);
			if(strstr(s,"c")){
				printf("%d",count);
			}
		}
		else if(strstr(s,"c")){
			int size;
			int count=0;
			rio_t myrio;
			char data[MAXLINE];
			int f1=open(file1, O_RDONLY);
			Rio_readinitb(&myrio, f1);
			while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
				if(strstr(s,"i")){
					if(strcasestr(data,patt)){
						count++;
					}
				}
				else{
					if(strstr(data,patt)){
						count++;
					}
				}
			}
			close(f1);
			printf("%d",count);
		}
		
		else if(strstr(s,"n")){
			int size;
			int count=0;
			int line_no=0;
			rio_t myrio;
			char data[MAXLINE];
			int f1=open(file1, O_RDONLY);
			Rio_readinitb(&myrio, f1);
			while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
				line_no++;
				if(strstr(s,"i")){
					if(strcasestr(data,patt)){
						printf("%d:%s",line_no, data);
						count++;
					}
				}
				else{
					if(strstr(data,patt)){
						printf("%d:%s",line_no, data);
						count++;
					}
				}
			}
			close(f1);
		}
		
		else if(strstr(s,"i")){
			int size;
			int count=0;
			rio_t myrio;
			char data[MAXLINE];
			int f1=open(file1, O_RDONLY);
			Rio_readinitb(&myrio, f1);
			while((size= Rio_readlineb(&myrio, data, MAXLINE)) != 0){
				if(strcasestr(data,patt)){
					printf("%s", data);
					count++;
				}
			}
			close(f1);
		}
		else{
			printf("INVALID COMMAND\n");
			printf("TRY AGAIN");
		}
		
		
	}
}

void cyan () {
  printf("\033[0;36m");
}

void reset () {
  printf("\033[0m");
}

void welcome (){
	cyan();
    	printf("\ngangwarady@%s:~", getenv("USER"));
	
   	if (getcwd(directory, sizeof(directory)) != NULL) {
       	printf("%s$", directory);
   	}
	reset();
}

int main(){
	
	int e;
	unsigned char arrow;
	welcome();
	/*char c = getch();
        
        printf("%d",c);*/
		
		
	//char input1[90];
	char input2[90];
	char input5[90];
   	//fgets(input1, 90, stdin);
   	char* input1;
   	
      	input1 = readline(" ");
   	input1[strcspn(input1, "\n")] = 0;
   	if(strlen(input1)){
   		add_history(input1);
   	}
   	char input9[90];
   	char *input;

   	strcpy(input9,input1);
   	input=strtok(input9," ");
   	
	
   	if(input && strcmp(input,"ls")==0){
   		
   			if(strstr(input1, "-")){
   				char *par;
   				par=strtok(input1," ");
   				par=strtok(NULL,"");
   				if(par!=NULL){
   					myls(par);
   				}
   			}
   			else if(strlen(input1)>2){
   				printf("Kindly enter valid command\n");
   			}
   			else{
   				DIR *mydir;
				struct dirent *mydirst;
    				mydir = opendir(directory);
    				if(mydir == NULL)
    				{
        				puts("Unable to read directory");
        		
    				}
    				else
    				{
        			 	while ((mydirst = readdir(mydir)) != NULL)
        			 	{
        			 		if ( !strcmp(mydirst->d_name, ".") || !strcmp(mydirst->d_name, "..") )
						{
						} 
						else {
     							printf("%s   ", mydirst->d_name);
						}
        			 	
        				
        				}
    				}
    				closedir(mydir);
 
   			}
   		
   	}
   	else if(input && strcmp(input,"ps")==0){
   	
   			myps();
   		
  		
   	}
   	else if(input && strcmp(input,"cp")==0){
   		
   			mycp(input1);
   		
   	}
   	else if(input && strcmp(input, "mv")==0){
   		mymv(input1);
   		
   	}
   	else if(input && strcmp(input, "grep")==0){
   		mygrep(input1);
   	}
   	else if(input && strcmp(input,"cd")==0){
   		char *par;

   		par=strtok(input1," ");
   		par=strtok(NULL,"");
   		
   		chdir(par);
   		
   	}
   	else if(input && (strcmp(input,"help")==0 || strcmp(input,"man")==0))
   	{
   		if(strstr(input1,"ls")){
   		printf("ls - list directory contents\nList information about the FILEs\n\n-m\tfill width with a comma separated list of entries\n-l\tuse a long listing format\n-r\treverse order while sorting\n-1\tlist one file per line.");
   		}
   		else if(strstr(input1,"ps")){
   		printf("ps displays information about a selection of the active processes.");
   		}
   		else if(strstr(input1,"cp")){
   		printf("cp - copy files and directories\n-b(backup):\t With this option cp command creates the backup of the destination file in the same folder with the different name and in different format.\n-i(interactive):\t i stands for Interactive copying. With this option system first warns the user before overwriting the destination file. cp prompts for a response, if you press y then it overwrites the file and with any other option leave it uncopied.\n-n\t --no-clobber do not overwrite an existing file \n--version \toutput version information");
   		}
   		else if(strstr(input1,"mv")){
   		printf("Rename SOURCE to DEST, or move SOURCE(s) to DIRECTORY.\n-b(backup): \tWith this option cp command creates the backup of the destination file in the same folder with the different name and in different format.\n-i(interactive): \ti stands for Interactive copying. With this option system first warns the user before overwriting the destination file. mv prompts for a response, if you press y then it overwrites the file and with any other option leave it uncopied.\n-n\t --no-clobber do not overwrite an existing file \n--version\t output version information");
   		}
   		else if(strstr(input1,"grep")){
   		printf("grep searches the named input FILEs for lines containing a match to the given PATTERN. By default, grep prints the matching lines.\n-c : This prints only a count of the lines that match a pattern\n-n : Display the matched lines and their line numbers.\n-i : Ignores, case for matching\n-v : This prints out all the lines that do not matches the pattern");
   		}
   		else{
   			printf("---------------I AM HERE TO HELP :)--------------------\n");
   			printf("ENTER THE FUNCTION YOU WANT HELP WITH\n");
   			char input3[90];
   			fgets(input3,90,stdin);
   			input3[strcspn(input3, "\n")] = 0;
   			char input4[90];
   			strcpy(input4, "man ");
   			strcat(input4, input3);
   			system(input4);
   		}
   	}
   	else if(input && strcmp(input,"exit")==0){
   		printf("------------------THANK YOU FOR USING THIS SHELL---------------------\n");
   		printf("EXITING..............\n");
   		exit(0);
   	}
   	else{
   		e=system(input1);
   		
   		if(e==-1){
   			printf("ERROR :(");
   		}
   		else if(WEXITSTATUS(e) == 127){
   			printf("%s COMMAND NOT FOUND :(\n",input1);
   			printf("KINDLY ENTER A VALID COMMAND");
   		}
   	}
	
	main();
	return 0;
}
   	
   
