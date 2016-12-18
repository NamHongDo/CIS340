/*
 * Name: Nam Do, Brett Robertson, Sims Matthew
 * CIS 340 Project 2A
 * Project description: Write a custom shell, implement 2 internal command "cd" and "path" as given instruction
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

char *line;
char *ptr;

int main()
{  
  	 while(1){
        printf("$ ");
        scanf(" %[^\n]",arr1);
   		ptr=strtok(arr1," ");//spliting the input string into several strings
		arr[0]=ptr;
		int d=1;
		while(ptr!=NULL){
			ptr=strtok(NULL," ");

			if(ptr==NULL)
				break;

			arr[d]=ptr;
			d++;
		}
		arr[d]=NULL;
	//check for different cases 
		if((strcmp(arr[0],"quit"))==0){
			break;
		}else if(((strcmp(arr[0],"path"))==0)&&(arr[1]!=NULL)&&(((strcmp(arr[1],"+"))==0)||((strcmp(arr[1],"-"))==0))){
			pathsign(arr[1]);
		}else if((strcmp(arr[0],"path"))==0){	
			path();
		}else if(((strcmp(arr[0],"cd"))==0)&&(arr[1]!=NULL)){
			cd(arr[1]);
		}else{
			int count=0;
			for(int i=0;i<32;i++){
				if(arr[i]==NULL){
					break;
				}
				count++;
			}
			exec(arr[0],count);
		}
		for(int i=0; i<32; i++){
			arr[i]="\0";
		}
    }
    return 0;
}
