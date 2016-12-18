//shell.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

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
	
	//when passing a pointer to a string array into a function, it is safer to use strcpy the array into a mallock array to avoid reading 
	//bad memory location
	char *arg[64];
	for(int i=0; i<64;i++){
		arg[i]=malloc(64);
	}
	for(int i=0;i<count;i++){
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
