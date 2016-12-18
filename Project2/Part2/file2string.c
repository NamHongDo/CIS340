/* Name : Nam Do, Bahareh Abrishami, Mathew Steward
CSU ID: 2594704,
CIS 340 Project 1_b part 2: Read an input file with many strings, split them and sort their orders.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void custout(const char*sa[], const char* fl);

int main(int argc, char **argv){
	char farray[128];
	char flags;
	FILE *fd;
	
	if(argc==2){
		fd=fopen(argv[1],"r");
		flags='x';
	}else if(argc==3){
		fd=fopen(argv[1],"r");
		flags=argv[2][1];	
	}else{
		printf("Error: The format should be: file2string ifile or file2string ifile -F\n"); 
	}
	
	if(fd==NULL){
		perror("Error: ");
		exit(1);
	}
	
	int elementsRead=fread(farray, 1, 128, fd);

	int k=0;
	for(int i=0; i<elementsRead; i++){
		if(farray[i]=='\0')
			k++;
	}
	
	char const *sarray[k];
	int b=0;
	sarray[0]=&(farray[0]);	
	for(int i=0; i<elementsRead; i++){
			if(farray[i]=='\0'){
				b++;
				sarray[b]=&(farray[i+1]);
			}
	}
	sarray[k]='\0';

	custout(sarray,&flags);
	
	return 0;
}

