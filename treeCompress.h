#include <stdlib.h>
#include <stdio.h>
#include "tree_3cell.h"
#include "bitset.h"
#include <string.h>

void compress(binary_tree* hoffmanTree, char const inputFile[], char const encodedFile[]);

void traverseTree(node* treeNode, int **byteTabel, int codeArray[], int i);

void writeToBinaryFile(char const inputFile[], char const encodedFile[], int **byteTabel);

bitset* pushBitstoFile(FILE *output, bitset *bSet);

void freeMemory(binary_tree *hoffmanTree, int **byteTabel);
