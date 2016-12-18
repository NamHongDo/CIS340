/* Name : Nam Do, Bahareh Abrishami, Mathew Steward
CSU ID: 2594704,
CIS 340 Project 1_b part 2: Read an input file with many strings, split them and sort their orders.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void ascendingBubbleSort(const char*sa[], int n){
	int c,d;
	const char *temp;
for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if ((strcmp(sa[d] , sa[d+1]))>0) /* For ascending order use < */
      {
        temp     = sa[d];
        sa[d]   = sa[d+1];
        sa[d+1] = temp;
      }
    }
  }
  for ( c = 0 ; c < n ; c++ )
     printf("%s\n", sa[c]);
}
	


void descendingBubbleSort(const char *sa[], int n){
	int c,d;
	const char *temp;
for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if ((strcmp(sa[d+1] , sa[d]))>0) /* For descending order use < */
      {
        temp     = sa[d];
        sa[d]   = sa[d+1];
        sa[d+1] = temp;
      }
    }
  }
  	for ( c = 0 ; c < n ; c++ )
     printf("%s\n", sa[c]);
}


void custout(const char*sa[], const char* fl){
	int i=0;
	
	switch(*fl){
		case 'x':
			while(sa[i]!='\0'){
				printf("%s\n", sa[i]);
				i++;
			}
			break;
		case 'f':
		case 'F':
			while(sa[i]!='\0'){
				i++;
			}
			ascendingBubbleSort(sa,i);
			break;
			
		case 'b':
		case 'B':
		while(sa[i]!='\0'){
				i++;
			}
			descendingBubbleSort(sa,i);
			
		default:
			break;
	}

}

