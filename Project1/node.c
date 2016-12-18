// Name: Nam Hong Do, Gregory Dubelko, Paul Durandt
// CSU ID: 2594704, 2507980, 2639603
// CIS 340: Project #1a
// Description: Creates a double lnked list from input and sorts it by value

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct mynode
{
	int const value;
	struct mynode *next;
	struct mynode *prev;
};

// Creates the first Node in the list, explicitly sets prev to NULL
// accepts the node's value
// returns pointer to created node
struct mynode *createFirst(int inputValue)
{
	struct mynode init = { inputValue, NULL, NULL };

	struct mynode *ret = malloc(sizeof(struct mynode));
	memcpy(ret, &init, sizeof(struct mynode));

	return ret;
}

// Creates subsequent nodes, doubly links new node to previous
// accepts the node's value and a pointer to the previous node
// returns pointer to created node
struct mynode *create(int inputValue, struct mynode *nodePrev)
{

	struct mynode init = { inputValue, NULL, nodePrev };

	struct mynode *ret = malloc(sizeof(struct mynode));
	nodePrev->next = ret;
	memcpy(ret, &init, sizeof(struct mynode));

	return ret;
}

// frees all created notes to clean up memory
// accepts a pointer to the head node
// returns noting
void destroy(struct mynode *nodeTarget)
{
	struct mynode *nodeNext = (*nodeTarget).next;
	free(nodeTarget);
	if (!nodeNext)
	{
		return;
	}	
	destroy(nodeNext);
}

// finds the first node in the list
// accepts a pointer to any node in the list
// returns a pointer to the first node in the list
struct mynode *findFirst(struct mynode *nodeTarget)
{
	while ((*nodeTarget).prev != NULL)
	{
		nodeTarget = (*nodeTarget).prev;
	}
	return nodeTarget;
}

// swaps the position of a node pair in the list
// accepts a pointer to a left hand and a right hand node
// returns nothing
void swap(struct mynode *left, struct mynode *right)
{

	// Stage the new values
	struct mynode *node0Next = right;
	struct mynode *node1Next = (*right).next;
	struct mynode *node2Next = left;
	struct mynode *node1Prev = right;
	struct mynode *node2Prev = (*left).prev;
	struct mynode *node3Prev = left;
	struct mynode *temp;

	// Assign new values, start with node 0
	// it's possible for node 0 to not exist, guard against this possibility
	temp = (*left).prev;
	if (temp)
	{
		temp->next = node0Next;
	}
	
	//Assign new values, ending node 3
	// right could have been the final node, making it possible for node 3 to not exist
	temp = (*right).next;
	if (temp)
	{
		temp->prev = node3Prev;
	}

	// now swap left and right
	left->next = node1Next;
	left->prev = node1Prev;
	right->next = node2Next;
	right->prev = node2Prev;
}

// prints the list of node values in a formatted line
// accepts a pointer to the head node
// returns nothing
void printlist(struct mynode *nodeTarget)
{
	printf("\n");
	while (nodeTarget != NULL)
	{
		printf("%d", (*nodeTarget).value);
		if ((*nodeTarget).next != NULL)
		{
			printf("<==>");
		}
		nodeTarget = (*nodeTarget).next;
	}
	printf("\n");
}

// sorts the node list from smallest to largest values
// accepts a pointer to the head node in the list
// returns a paointe to the new head node
struct mynode *quicksort(struct mynode *nodeTarget)
{
	struct mynode *quickleft = nodeTarget;
	struct mynode *quickright = (*quickleft).next;
	
	while (quickright != NULL)
	{
		if ((*quickleft).value > (*quickright).value)
		{
			swap(quickleft, quickright);
			if (quickleft == nodeTarget)
			{
				nodeTarget = findFirst(nodeTarget);
			}
			nodeTarget = quicksort(nodeTarget);
			break;
		}
		else
		{
			quickleft = (*quickleft).next;
			quickright = (*quickright).next;
		}


	}

	return nodeTarget;
}

