#include <stdlib.h>
#include <stdio.h>
#include "tree_3cell.h"

void compress(binary_tree* hoffmanTree, char const inputFile[], char const encodedFile[]);

void traverseTree(node* treeNode, int **byteTabel, int codeArray[], int i);

