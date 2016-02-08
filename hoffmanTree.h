/*
  File Name   : hoffmanTree.h

  Purpose     : The function in this file have the purpose to make a
                frequency analysis of a file and from that create a
                hoffman tree.

  Usage       : Usage in OU3 - DV2

*/


#ifndef __hoffmanTree__
#define __hoffmanTree__

#include "tree_3cell.h"
#include "prioqueue.h"
#include <stdlib.h>
#include <stdio.h>

/*  pqCell will be used as a queue holder for the diffrent
    subtrees for the priority queue */
typedef struct{
  int weight;
  node* nodePtr;
} pqCell;


/*Description : Will be used as a compare function in the priority queue
                and will compare the weight variabel in a pqCell.
  Input       : Value a and b will be pointers to a pqCell.
  Output      : Will return 1 if a is smaller than b, otherwise return 0
*/
int ascendingOrder(VALUE a,VALUE b);

/*Description : This function will act like the main function is this file.
                It will first call the function for the frequency analysis
                and later the function for building the hoffman tree
  Input       : The input is the name of the file that we wich to contuct
                the analysis on.
  Output      : Will return the pointer to a hoffman tree.*/


binary_tree* frequencyAnalysis(char const frequencyText[]);
/*Description : This function will count the frequency of each ascii values in
                the desired file and store the frequency in an array.
  Input       : Name of the file that we choose to conduct the frequency
                analysis and a array which will store the frequency analysis.
  Output      : Array that stores in information from the analysis.
  Written by  : dv15jvd
*/
void textFileTraverse(int *frequencyArray, char const frequencyText[]);

/*Description : This function will build the hoffman tree based on the
                frequency analysis.
  Input       : An array which contains the frequency analysis
  Output      : A pointer to the hoffmantree
  Written by  : dv15man
*/

binary_tree* buildTree(int frequencyArray[]);

/*Description : Creating leaves and pqNodes for the that that will be
                inserted in PQueue. Pqnodes will have a pointer to a tree noes.
  Input       : An array which contains the frequency analysis
  Output      : A pointer to the priority queue, which contains all the leaves
  Written by  : dv15man
*/
pqueue *setUpPrioQueue(int frequencyArray[]);

#endif
