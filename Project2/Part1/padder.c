#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MASK1 0xFF000000
#define MASK2 0x00FF0000
#define MASK3 0x0000FF00
#define MASK4 0x000000FF

int main(int argc, char *argv[]) {
	int elementsRead;	
	FILE *fd1;
	FILE *fd2;
	int pad_val;
	int a;
	int b;
	char buffer[128];
	char bufferint[4];

	if(argc!=4){
		printf("The format is not correct! Format should be: padder srcfile destfile pad_val");
	}else{
		pad_val=atoi(argv[3]);
		bufferint[0]=pad_val&MASK1>>24;
		bufferint[1]=pad_val&MASK2>>16;
		bufferint[2]=pad_val&MASK3>>8;
		bufferint[3]=pad_val&MASK4;
			
		a=open(argv[2],O_WRONLY);
		
		if(a == -1) {
			perror("fd2");	
			exit(1);
		}
		
		write(bufferint,argv[2],4);
		
		
		b=open(argv[1],O_RDONLY);	
		if(b == -1) {
			perror("fd1");	
			exit(1);
		}
		
		elementsRead=read(argv[1],buffer,128);
	
	
		if(elementsRead>=128)
			{
				write(buffer,argv[2],128);
				while(elementsRead>=128){
						elementsRead=read(buffer,argv[1],128);
						write(buffer,argv[2],128);
				}		
				write(buffer,argv[2],elementsRead);
				printf("source successfully written to destination after padding by pad-val\n");
		}
		else
		{
				write(buffer,argv[2],elementsRead);
				printf("source successfully written to destination after padding by pad-val\n");
		}
		fclose(argv[1]);
		fclose(argv[2]);
	}
}
