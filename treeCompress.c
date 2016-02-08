
#include "treeCompress.h"
#include "tree_3cell.h"
#include "hoffmanTree.h"
#include <stdlib.h>
#include <stdbool.h>


void compress(binary_tree* hoffmanTree, char const inputFile[], char const encodedFile[]) {

	int **byteTabel;
	int codeArray[50];
	int i = 0;

	byteTabel = malloc(256*sizeof(int*));

	codeArray[i] = 0;
	i++;
	traverseTree(hoffmanTree->root->leftChild, byteTabel, codeArray, i);

	i = 0;
	codeArray[i] = 1;
	i++;
	traverseTree(hoffmanTree->root->rightChild, byteTabel, codeArray, i);

  int v = 0;
	int w = 256;

	for ( ; v < w; v++) {

		int k = 0;
		while ((int)byteTabel[v][k] != -1 ) {
			k++;
		}

	}

  writeToBinaryFile(inputFile,encodedFile,byteTabel);

	freeMemory(hoffmanTree, byteTabel);


}

void traverseTree(node* treeNode, int **byteTabel, int codeArray[], int i) {

	if ( treeNode->label != NULL ) {

		//printf("%c  ", *((unsigned char *)treeNode->label));

		int *bitArray = calloc((i + 1), sizeof(int));

		for ( int k = 0; k < i; k++) {

			//printf("%d", codeArray[k]);
			bitArray[k] = codeArray[k];

		}

		//printf("\n");
		bitArray[i] = -1;
		byteTabel[*(unsigned char*)treeNode->label] = bitArray;
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

void writeToBinaryFile(char const inputFile[], char const encodedFile[], int **byteTabel){

	bitset* bSet = bitset_empty();

  FILE *input;
  FILE *output;

  unsigned char readChar;
  char stopFile=0;
  int k=0;
  int bitNo=1;
	long int nrBytesInFil=0;
	long int nrBytesEncoded=0;

  input = fopen(inputFile, "r");
  output = fopen(encodedFile, "wb");
	do{
    stopFile = fgetc(input);
    readChar = (unsigned char)stopFile;
    k=0;
    while (byteTabel[readChar][k]>=0){
      if (bitNo%8==0){
        bSet = pushBitstoFile(output,bSet);
        bitNo=1;
				nrBytesEncoded++;
      }

      bitset_setBitValue(bSet,bitNo-1,byteTabel[readChar][k]);
      k++;
      bitNo++;
    }
		nrBytesInFil++;
  } while (stopFile != EOF);

  fputc('\4',output);
  fclose(input);
  fclose(output);

	bitset_free(bSet);
  printf("%ld bytes read from %s.\n",nrBytesInFil,inputFile);
  printf("%ld bytes used in encoded form.\n",nrBytesEncoded);

}

bitset* pushBitstoFile(FILE *output, bitset *bSet){

  char *str;

  str = toByteArray(bSet);
  fputc(str[0],output);

  bitset_free(bSet);
  free(str);

  return bitset_empty();


}

void freeMemory(binary_tree *hoffmanTree, int **byteTabel){
	binaryTree_free(hoffmanTree);
	for (int i=0; i<256; i++){
		free(byteTabel[i]);
	}
	free(byteTabel);
}
