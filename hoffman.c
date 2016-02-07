#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hoffmanTree.h"
#include "tree_3cell.h"
#include "treeCompress.h"


void checkParameters(int argc);
int checkInput(char const *argv[]);
void errorOutput(void);


int main(int argc, char const *argv[]){

	binary_tree* hoffmanTree;

  checkParameters(argc);

  checkInput(argv);

  //FILE *infil;
  //FILE *utfil;

 // infil = fopen(argv[3], "r");
  //utfil = fopen(argv[4], "w");

  hoffmanTree = frequencyAnalasys(argv[2]);


	compress(hoffmanTree,argv[2],argv[3]);


  return 0;
}

int checkInput(char const *argv[]){
  int codeWhat = -1;

  if (!strcmp(argv[1],"encode")) {
    codeWhat = 1;
  }
  else if (!strcmp(argv[1],"decode" )) {
    codeWhat = 0;
  }
  else{
    errorOutput();
  }
  return codeWhat;
}


void checkParameters(int argc){
  if (argc <5){
    errorOutput();
  }
}

void errorOutput(void){

  fprintf(stderr, "Usage:\n huffman [OPTION] [FILE0] [FILE1] [FILE2]\n");
  fprintf(stderr, "Options:\n");
  fprintf(stderr, "-encode encodes FILE1 according to frequence analysis"
                    "done on FILE0. Stores the result in FILE2\n");
  fprintf(stderr, "-decode decodes FILE1 according to frequence analysis"
                    "done on FILE0. Stores the result in FILE2\n");
  exit(0);
}
