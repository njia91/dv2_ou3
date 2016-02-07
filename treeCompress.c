
#include "treeCompress.h"
#include "tree_3cell.h"

void compress(binary_tree* hoffmanTree, char const inputFile[], char const encodedFile[]) {
  
	int **byteTabel;
	int codeArray[50];
	int i = 0;

	byteTabel = calloc(256, sizeof(int));
	
	codeArray[i] = 0;
	i++;
	traverseTree(hoffmanTree->root->leftChild, byteTabel, codeArray, i);	


	
	i = 0;	
	codeArray[i] = 1;
	i++;
	traverseTree(hoffmanTree->root->rightChild, byteTabel, codeArray, i);

	printf("hejehejejjejejejae %d\n", i);

	int v = 0; 
	int w = 256;

	for ( ; v < w; v++) {

		printf("%c", v);
		int k = 0;
		while ((int)byteTabel[v][k] != -1 ) {

			printf("%d", (int)byteTabel[v][k]);
			k++;
		}

		printf("\n");

	}

}

void traverseTree(node* treeNode, int **byteTabel, int codeArray[], int i) {

	if ( treeNode->label != NULL ) {
		
		printf("%c  ", *((unsigned char *)treeNode->label));

		int *bitArray = calloc((i + 1), sizeof(int));

		for ( int k = 0; k < i; k++) {

			printf("%d", codeArray[k]);
			bitArray[k] = codeArray[k];

		}

		printf("\n");
		bitArray[i] = -1;
		byteTabel[*(int*)(treeNode->label)] = bitArray;



		//printf("  %d\n", i);

	}

	else {
		
		codeArray[i] = 0;
		i++;
		traverseTree(treeNode->leftChild, byteTabel, codeArray, i);
		i--;
		
		codeArray[i] = 1;
		i++;
		traverseTree(treeNode->rightChild, byteTabel, codeArray, i);
		i--;
	}

}
