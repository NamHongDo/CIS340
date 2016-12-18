//shell.h
#ifndef _NAM_H
#define _NAM_H

char arr1[515];
char *arr[64];
char *list[4];
pid_t mypid;
typedef struct node{
	char *data;
	struct node *next;
}node;
void cd(char *path);
struct node *head;
void path();
void pathsign(char *sign);
void add(char *new);
void delete(char *new);
char *get(int position);
int listsize();
void exec(char *cmd,int count);
void exec2(char *cmd, int count);
void closepipes(int *parray,int pcounter);
#endif
