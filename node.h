// Name: Nam Hong Do, Gregory Dubelko, Paul Durandt
// CSU ID: 2594704, 2507980, 2639603
// CIS 340: Project #1a
// Description: Creates a double lnked list from input and sorts it by value

#ifndef __NODE_H__
#define __NODE_H__

struct mynode;
struct mynode *createFirst(int inputValue);
struct mynode *create(int inputValue, struct mynode *nodePrev);
void destroy(struct mynode *nodeTarget);
struct mynode *findFirst(struct mynode *nodeTarget);
void swap(struct mynode *left, struct mynode *right);
void printlist(struct mynode *nodeTarget);
struct mynode *quicksort(struct mynode *nodeTarget);


#endif /* __NODE_H__ */
