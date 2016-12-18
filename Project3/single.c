//single.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
//Use single link list to store paths, this make implementing path + and path - more convinient

void add(char *new)//add new node
{
	struct node *temp;
	temp=(struct node*)malloc(sizeof(node));
	
	if(head==NULL){//if there are no linklist exist yet, create a node
		char *s=(char*)malloc(256);
		strcpy(s,new);
		head=temp;
		head->data=s;
		head->next=NULL;
	}else{//Null node is fixed, whenever a new path is added, that path become the new head node
		char *s=(char*)malloc(256);
		strcpy(s,new);
		temp->data=s;
		temp->next=head;
		head=temp;
	}
}


void delete(char *new)//feed the function with a string we desire to delete
{
	struct node *temp, *previous;//use two node to adjust the linklist
	temp=head;
	while(temp!=NULL){
		if(strcmp(head->data,new)==0){//check the whole list until the exact string is found
			head=head->next;
			break;
		}else if(strcmp(temp->data,new)==0){
			previous->next=temp->next;
			break;
		}
	previous=temp;//set previous-> next to the temp->next to exclude the node we want to delete
	temp=temp->next;					
	}
}

char *get(int position)//get node
{
	struct node *temp;
	temp=head;
	for(int i=0; i<position; i++){
		temp=temp->next;
	}
	return temp->data;
}

int listsize(){//return size of the linklist
	struct node *temp;
	temp=head;
	int i;
	for(i=0; temp!=NULL; i++){
		temp=temp->next;
	}
	return i;
}
