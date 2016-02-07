

#ifndef __hoffmanTree__
#define __hoffmanTree__

#include "tree_3cell.h"
#include "prioqueue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct{
  int weight;
  char character;
} arrayCell;

typedef struct{
  int weight;
  node* nodePtr;
} pqCell;

int ascendingOrder(VALUE a,VALUE b);
// Frekvensanalys
binary_tree* frequencyAnalasys(char const frequencyText[]);

void textFileTraverse(int *frequencyArray, char const frequencyText[]);

binary_tree* buildTree(int frequencyArray[]);

/*Creating leaves and pqNodes for the that that will be inserted in PQueue
* Pqnodes will have a pointer to a tree noes. */
pqueue *setUpPrioQueue(int frequencyArray[]);

#endif
