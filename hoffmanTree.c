#include "tree_3cell.h"
#include "hoffmanTree.h"
#include "prioqueue.h"





int ascendingOrder(VALUE a,VALUE b){

  return (*(pqCell *)a).weight < (*(pqCell *)b).weight;

}

//"main funktion" kallar på de andra.
binary_tree* frequencyAnalysis(char const frequencyText[]) {

  int *frequencyArray;

  frequencyArray= calloc(256, sizeof(int));

  textFileTraverse(frequencyArray, frequencyText);

  return buildTree(frequencyArray);

}

/*
* Traverse the text in the file and count how many times each character
* appears.
*/
void textFileTraverse(int *frequencyArray, char const frequencyText[]) {

	unsigned char readChar=0;
	char stopFile=0;

	FILE *freqfil;

	freqfil = fopen(frequencyText, "r");

	while ( stopFile != EOF ) {
		stopFile = fgetc(freqfil);
		readChar = (unsigned char)stopFile;
		frequencyArray[(int)readChar]++;
	}

	fclose(freqfil);


}

binary_tree* buildTree(int frequencyArray[]){
  pqueue *q;
  int complete=0;
  node *treeNode;
  pqCell *pqNode;
  pqCell *first;
  pqCell *second;

  q = setUpPrioQueue(frequencyArray);

  do{


    first = pqueue_inspect_first(q);
    pqueue_delete_first(q);

    if (pqueue_isEmpty(q)){
      complete=1;
    }
    else{

      treeNode = (node *)malloc(sizeof(node));
      pqNode = (pqCell *)malloc(sizeof(pqCell));

      second = pqueue_inspect_first(q);
      pqueue_delete_first(q);

      //The new treenodes is assigned its new children.
      treeNode->leftChild = first->nodePtr;
      treeNode->rightChild = second->nodePtr;

      //Making the two subtrees point to their new parent
      first->nodePtr->parent = treeNode;
      second->nodePtr->parent = treeNode;

      //To indicate that this node is not a leaf
      treeNode->label = NULL;

      //Adding the weight from previous subtrees, storing it in tree
      pqNode->weight=first->weight + second->weight;

      pqNode->nodePtr=treeNode;

      pqueue_insert(q,pqNode);

      free(first);
      free(second);
    }

  } while (!complete);

  binary_tree *tree = malloc(sizeof(binary_tree));
  //binaryTree_setMemHandler(tree, free);
  tree->freeFunc = free;

  tree->root = first->nodePtr;
  tree->root->parent = NULL;
  tree->root->label = NULL;

  free(first);
  pqueue_free(q);



	free(frequencyArray);

  return tree;

}

/*Creating leaves and pqNodes for the that that will be inserted in PQueue
 * Pqnodes will have a pointer to a tree noes. */
pqueue *setUpPrioQueue(int frequencyArray[]){
  pqueue *q= pqueue_empty(ascendingOrder);
  node *treeNode;
  pqCell *pqNode;
  unsigned char *character;


  for (int i = 0; i<256; i++){
    pqNode = (pqCell *)malloc(sizeof(pqCell));
    treeNode = (node *)malloc(sizeof(node));
    character= (unsigned char *)malloc(sizeof(unsigned char));

    /*Pqnode will have a pointer to the treenode initilize below*/
    pqNode->weight=frequencyArray[i] + 1;

    //printf("%c", (char)i);
    //printf("%d\n", pqNode->weight);

    /*Inserts the character in the tree node.*/
    *character=(unsigned char) i;
    treeNode->label=character;

    treeNode->leftChild = NULL;
    treeNode->rightChild = NULL;

    pqNode->nodePtr=treeNode;

    pqueue_insert(q,pqNode);
  }
  return q;
}
