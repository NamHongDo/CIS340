// Name: Nam Hong Do, Gregory Dubelko, Paul Durandt
// CSU ID: 2594704, 2507980, 2639603
// CIS 340: Project #1a
// Description: Creates a double lnked list from input and sorts it by value


#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main()
{
	struct mynode *currentNode = NULL;
	struct mynode *firstNode;
	int a;
	
	scanf("%d", &a);
	firstNode = createFirst(a);
	currentNode = firstNode;

	do
	{
		scanf("%d", &a);
		if (a != 0)
		{
			currentNode = create(a, currentNode);
		}
	} while (a != 0);

	// print unsordted list
	printlist(firstNode);
	firstNode = quicksort(firstNode);
	// print sorted list
	printlist(firstNode);
	destroy(firstNode);

	exit(EXIT_SUCCESS);
}
