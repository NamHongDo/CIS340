//shell.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

void cd(char *path){//cd command
	char *temp=malloc(256);
	strcpy(temp,path);
	chdir(temp);
	free(temp);
}

void path(){//path command
	int size= listsize();
	char *tempt[size];
	for(int i=0; i< size; i++){
		tempt[i]=malloc(256);
	}
	
	for(int i=0; i<size; i++){
		strcpy(tempt[i],get(i));
	}
	size--;
	for( ;size>=0;size--){
		if(size==0){
			printf("%s",tempt[0]);
		}else{	
			printf("%s:",tempt[size]);
		}
	}
	printf("\n");
}

void pathsign(char *sign){ 
	char *point;
	switch(sign[0]){
		case '+'://path +
			point=arr[2];
			add(point);
			break;
		case '-'://path -
			point=arr[2];
			delete(point);
			break;
		default:
			break;
	}
}

void exec(char *cmd,int count){	//execute command: using execv(char *path, char *argvs[])
	char *s1=(char*)malloc(64);	//we need two paramenters, one for path, one for user arguments(can be directory or extra feature command)
	strcpy(s1,cmd);
	
	//set up second paramenter (format: arg[0]=cmd name;arg[1->n]:extra user commands; arg[n+1]:NULL)
	//when passing a pointer to a string array into a function, it is safer to use strcpy the array into a mallock array to avoid reading bad memory location
	char *arg[64];
	for(int i=0; i<64;i++){
		arg[i]=malloc(64);
	}
	char *file;
	char sign;
	for(int i=0;i<count;i++){
		if (*arr[i]=='<'){
			sign='<';
			file=(char*)malloc(sizeof(char)*64);
			strcpy(file,arr[i+1]);	
			arg[i]=NULL;
			break;
		}else if(*arr[i]=='>'){
			sign='>';
			file=(char*)malloc(sizeof(char)*64);
			strcpy(file,arr[i+1]);	
			arg[i]=NULL;
			break;
		}	
		strcpy(arg[i],arr[i]);
	}
	arg[count]=NULL;

	//altering the path list by adding the name of cmd at the end of each node (format of 1st parameter of execv is directories/cmd)
	int size= listsize();
	char *tempt[size];
	
	for(int i=0; i< size; i++){
		tempt[i]=malloc(256);
	}
	
	for(int i=0; i<size; i++){
		strcpy(tempt[i],get(i));
		strcat(tempt[i],"/");
		strcat(tempt[i],s1);
	}
	
	//create proccess
	if((mypid=fork())<0){
		perror("fork failure");
	}else if(mypid==0){//child process
		for(int i=0;i<size;i++){//loop for the process to look for the cmd file in all the directories stored in path
			if(sign=='<'){
				int fd0 = open(file, O_RDONLY);
				dup2(fd0, STDIN_FILENO);
				close(fd0);
			}
			if(sign=='>'){
				int fd1 = creat(file, 0644) ;
				dup2(fd1, STDOUT_FILENO);
				close(fd1);
			}
			execv(tempt[i],arg);//execute
		}
		perror("Can't find the cmd file in the internal existing paths");
		_exit(1);
	}else{
		wait(NULL);
	}
	free(s1);
	for(int i=0; i<64;i++){
		free(arg[i]);
	}
		for(int i=0; i< size; i++){
		free(tempt[i]);
	}
}

void exec2(char *cmd, int count){
	char *arg[64];
	int pipecounter=0;
	for(int i =0; i<64; i++){
		arg[i]=malloc(64);	
	}
						
	for(int i=0; i<count;i++)	{
			strcpy(arg[i],arr[i]);
	}
	arg[count]=NULL;
	
	for(int i=0; i<count;i++){
		if(strcmp(arg[i],"|")==0){
			arg[i]=NULL;
			pipecounter++;
		}
	}
	
	int sign;
	int size = listsize();	
	char *arr2[16];
	char *tempt[size];
	int pipearray[pipecounter*2];
	int argcounter=0;
	int processamount=pipecounter+1;
	int childStatus;
	char *file;
	pid_t mypid;
	for(int i=0;i<pipecounter*2;i+=2){ //creating pipes
		pipe(pipearray+i);
	}
	file ="lol";	
	for(int i=0; i<processamount;i++){
		for(int f=0;f<16;f++){
			arr2[f]=malloc(64);
		}
		for(int h=0;h<16;h++){
			if(arg[argcounter]==NULL){
				arr2[h]=NULL;
				argcounter++;
				break;
			}else{
				if(*arg[argcounter]=='<'){
					sign='<';
					file=(char*)malloc(sizeof(char)*64);
					strcpy(file,arg[argcounter+1]);
				}else if(*arg[argcounter]=='>'){
					sign='>';
					file=(char*)malloc(sizeof(char)*64);
					printf("arg is:%s\n", arg[argcounter+1]);
					strcpy(file,arg[argcounter+1]);
				}
				strcpy(arr2[h],arg[argcounter]);
				argcounter++;
			}
		}		
		printf("file is: %s\n",file);
		printf("sign is: %c\n",sign);
		for(int f=0; f< size; f++){
			tempt[f]=malloc(64);
		}
		for(int f=0; f<size; f++){			
			sprintf(tempt[f], "%s/%s", get(f), arr2[0]);
		}
		for(int f=0;f< size;f++){
		printf("temp:%s\n", tempt[f]);
		}
		for(int f=0;;f++){			
			printf("arr2:%s\n",arr2[f]);
			if(arr2[f]==NULL)
				break;
		}

		if((mypid=fork())==0){
			if(i==0){		
				dup2(pipearray[1],1);
			}else if(i==processamount-1){
				dup2(pipearray[i*2-2],0);
					}else{		
				dup2(pipearray[(i-1)*2],0);			
				dup2(pipearray[i*2+1],1);				
			}
			closepipes(pipearray,pipecounter);
			if(sign=='>'){
				int fd1 = open(file,O_WRONLY);
				dup2(fd1,1);
				close(fd1);
			}
/*	if(sign=='<'){
			int fd0=open(file, O_RDONLY);
			dup2(fd0, STDIN_FILENO);
			close(fd0);
		}*/
				for(int f=0; f<size;f++){
				execv(tempt[f],arr2);
			}
			_exit(1);
		}		
		for(int f=0;f<16;f++){
			free(arr2[f]);
		}
		for(int f=0;f<size;f++){
			free(tempt[f]);
		}
		sign='h';
	}
		closepipes(pipearray,pipecounter);
		waitpid(mypid, &childStatus, 0);
		for(int i=0;i<64;i++){
			free(arg[i]);
		}
}

void closepipes(int *parray,int pcounter){
	for(int i=0;i<pcounter*2;i++){
		close(parray[0]+i);
	}
}
